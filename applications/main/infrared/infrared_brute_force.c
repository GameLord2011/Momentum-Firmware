#include "infrared_brute_force.h"

#include <stdlib.h>
#include <m-dict.h>
#include <flipper_format/flipper_format.h>

#include "infrared_signal.h"

#define TAG "InfraredBruteforce"

#define INFRARED_FILE_HEADER     "IR signals file"
#define INFRARED_LIBRARY_HEADER  "IR library file"
#define INFRARED_LIBRARY_VERSION (1)

typedef struct {
    uint32_t index;
    uint32_t count;
} InfraredBruteForceRecord;

DICT_DEF2(
    InfraredBruteForceRecordDict,
    FuriString*,
    FURI_STRING_OPLIST,
    InfraredBruteForceRecord,
    M_POD_OPLIST);

struct InfraredBruteForce {
    FlipperFormat* ff;
    const char* db_filename;
    FuriString* current_record_name;
    InfraredSignal* current_signal;
    InfraredBruteForceRecordDict_t records;
    bool is_started;
};

InfraredBruteForce* infrared_brute_force_alloc(void) {
    InfraredBruteForce* brute_force = malloc(sizeof(InfraredBruteForce));
    brute_force->ff = NULL;
    brute_force->db_filename = NULL;
    brute_force->current_signal = NULL;
    brute_force->is_started = false;
    brute_force->current_record_name = furi_string_alloc();
    InfraredBruteForceRecordDict_init(brute_force->records);
    return brute_force;
}

void infrared_brute_force_free(InfraredBruteForce* brute_force) {
    furi_assert(!brute_force->is_started);
    InfraredBruteForceRecordDict_clear(brute_force->records);
    furi_string_free(brute_force->current_record_name);
    free(brute_force);
}

void infrared_brute_force_set_db_filename(InfraredBruteForce* brute_force, const char* db_filename) {
    furi_assert(!brute_force->is_started);
    brute_force->db_filename = db_filename;
}

InfraredErrorCode infrared_brute_force_calculate_messages(
    InfraredBruteForce* brute_force,
    bool auto_detect_buttons) {
    furi_assert(!brute_force->is_started);
    furi_assert(brute_force->db_filename);
    InfraredErrorCode error = InfraredErrorCodeNone;

    Storage* storage = furi_record_open(RECORD_STORAGE);
    FlipperFormat* ff = flipper_format_buffered_file_alloc(storage);
    FuriString* signal_name = furi_string_alloc();
    InfraredSignal* signal = infrared_signal_alloc();

    do {
        if(!flipper_format_buffered_file_open_existing(ff, brute_force->db_filename)) {
            error = InfraredErrorCodeFileOperationFailed;
            break;
        }

        uint32_t version;
        // Temporarily use signal_name to get header info
        if(!flipper_format_read_header(ff, signal_name, &version)) {
            error = InfraredErrorCodeFileOperationFailed;
            break;
        }

        if(furi_string_equal(signal_name, INFRARED_FILE_HEADER)) {
            FURI_LOG_E(TAG, "Remote file can't be loaded in this context");
            error = InfraredErrorCodeWrongFileType;
            break;
        }

        if(!furi_string_equal(signal_name, INFRARED_LIBRARY_HEADER)) {
            error = InfraredErrorCodeWrongFileType;
            FURI_LOG_E(TAG, "Filetype unknown");
            break;
        }

        if(version != INFRARED_LIBRARY_VERSION) {
            error = InfraredErrorCodeWrongFileVersion;
            FURI_LOG_E(TAG, "Wrong file version");
            break;
        }

        bool signals_valid = false;
        uint32_t auto_detect_button_index = 0;
        while(infrared_signal_read_name(ff, signal_name) == InfraredErrorCodeNone) {
            error = infrared_signal_read_body(signal, ff);
            signals_valid = (!INFRARED_ERROR_PRESENT(error)) && infrared_signal_is_valid(signal);
            if(!signals_valid) break;

            InfraredBruteForceRecord* record =
                InfraredBruteForceRecordDict_get(brute_force->records, signal_name);
            if(!record && auto_detect_buttons) {
                infrared_brute_force_add_record(
                    brute_force, auto_detect_button_index++, furi_string_get_cstr(signal_name));
                record = InfraredBruteForceRecordDict_get(brute_force->records, signal_name);
            }
            if(record) { //-V547
                ++(record->count);
            }
        }
        if(!signals_valid) break;
    } while(false);

    infrared_signal_free(signal);
    furi_string_free(signal_name);

    flipper_format_free(ff);
    furi_record_close(RECORD_STORAGE);
    return error;
}

bool infrared_brute_force_start(
    InfraredBruteForce* brute_force,
    uint32_t index,
    uint32_t* record_count) {
    furi_assert(!brute_force->is_started);
    bool success = false;
    *record_count = 0;

    InfraredBruteForceRecordDict_it_t it;
    for(InfraredBruteForceRecordDict_it(it, brute_force->records);
        !InfraredBruteForceRecordDict_end_p(it);
        InfraredBruteForceRecordDict_next(it)) {
        const InfraredBruteForceRecordDict_itref_t* record = InfraredBruteForceRecordDict_cref(it);
        if(record->value.index == index) {
            *record_count = record->value.count;
            if(*record_count) {
                furi_string_set(brute_force->current_record_name, record->key);
            }
            break;
        }
    }

    if(*record_count) {
        Storage* storage = furi_record_open(RECORD_STORAGE);
        brute_force->ff = flipper_format_buffered_file_alloc(storage);
        brute_force->current_signal = infrared_signal_alloc();
        brute_force->is_started = true;
        success =
            flipper_format_buffered_file_open_existing(brute_force->ff, brute_force->db_filename);
        if(!success) infrared_brute_force_stop(brute_force);
    }
    return success;
}

bool infrared_brute_force_is_started(const InfraredBruteForce* brute_force) {
    return brute_force->is_started;
}

void infrared_brute_force_stop(InfraredBruteForce* brute_force) {
    furi_assert(brute_force->is_started);
    furi_string_reset(brute_force->current_record_name);
    infrared_signal_free(brute_force->current_signal);
    flipper_format_free(brute_force->ff);
    brute_force->current_signal = NULL;
    brute_force->ff = NULL;
    brute_force->is_started = false;
    furi_record_close(RECORD_STORAGE);
}

bool infrared_brute_force_send_next(InfraredBruteForce* brute_force) {
    furi_assert(brute_force->is_started);

    const bool success = infrared_signal_search_by_name_and_read(
                             brute_force->current_signal,
                             brute_force->ff,
                             furi_string_get_cstr(brute_force->current_record_name)) ==
                         InfraredErrorCodeNone;
    if(success) {
        infrared_signal_transmit(brute_force->current_signal);
    }
    return success;
}

void infrared_brute_force_add_record(
    InfraredBruteForce* brute_force,
    uint32_t index,
    const char* name) {
    InfraredBruteForceRecord value = {.index = index, .count = 0};
    FuriString* key;
    key = furi_string_alloc_set(name);
    InfraredBruteForceRecordDict_set_at(brute_force->records, key, value);
    furi_string_free(key);
}

void infrared_brute_force_reset(InfraredBruteForce* brute_force) {
    furi_assert(!brute_force->is_started);
    InfraredBruteForceRecordDict_reset(brute_force->records);
}

size_t infrared_brute_force_get_button_count(const InfraredBruteForce* brute_force) {
    size_t size = InfraredBruteForceRecordDict_size(brute_force->records);
    return size;
}

const char*
    infrared_brute_force_get_button_name(const InfraredBruteForce* brute_force, size_t index) {
    if(index >= infrared_brute_force_get_button_count(brute_force)) {
        return NULL;
    }

    InfraredBruteForceRecordDict_it_t it;
    for(InfraredBruteForceRecordDict_it(it, brute_force->records);
        !InfraredBruteForceRecordDict_end_p(it);
        InfraredBruteForceRecordDict_next(it)) {
        // Dict elements are unordered, they may be shuffled while adding elements, so the
        // index used in add_record() may differ when iterating here, so we have to check
        // the stored index not "position" index
        const InfraredBruteForceRecordDict_itref_t* pair = InfraredBruteForceRecordDict_cref(it);
        if(pair->value.index == index) {
            const char* button_name = furi_string_get_cstr(pair->key);
            return button_name;
        }
    }

    return NULL; //just as fallback
}