#include <babocar-core/types.hpp>

const char* bcr::getStatusString(Status status) {

    static const char *STR_OK            = "OK";
    static const char *STR_ERROR         = "ERROR";
    static const char *STR_BUSY          = "BUSY";
    static const char *STR_TIMEOUT       = "TIMEOUT";
    static const char *STR_INVALID_ID    = "INVALID_ID";
    static const char *STR_INVALID_DATA  = "INVALID_DATA";
    static const char *STR_NO_NEW_DATA   = "NO_NEW_DATA";
    static const char *STR_BUFFER_FULL   = "BUFFER_FULL";
    static const char *STR_unknown       = "unknown error";

    const char *result;
    switch (status) {
        case Status::OK:            result = STR_OK;            break;
        case Status::ERROR:         result = STR_ERROR;         break;
        case Status::BUSY:          result = STR_BUSY;          break;
        case Status::TIMEOUT:       result = STR_TIMEOUT;       break;
        case Status::INVALID_ID:    result = STR_INVALID_ID;    break;
        case Status::INVALID_DATA:  result = STR_INVALID_DATA;  break;
        case Status::NO_NEW_DATA:   result = STR_NO_NEW_DATA;   break;
        case Status::BUFFER_FULL:   result = STR_BUFFER_FULL;   break;
        default:                    result = STR_unknown;       break;
    }
    return result;
}
