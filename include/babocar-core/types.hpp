#pragma once

#include <stdint.h>

namespace babocar {

typedef float float32_t;
typedef double float64_t;

/**
 * @brief Defines pin states.
 */
enum class PinState : uint8_t {
    RESET = 0,      // Reset state.
    SET             // Set state.
};

/**
 * @brief Status for operations
 */
enum class Status : uint32_t {
    OK = 0,         // OK.
    ERROR,          // Unknown error.
    BUSY,           // Resource busy.
    TIMEOUT,        // Waiting has reached timeout.
    INVALID_ID,     // Invalid identifier detected.
    INVALID_DATA,   // Invalid data detected.
    NO_NEW_DATA,    // No new data is available.
    BUFFER_FULL     // Buffer is full.
};

/**
 * @brief Checks is status is ok.
 * @param status
 * @return True if status is ok.
 */
bool isOk(Status status);

/** @brief Gets status as string.
 * @param status The status to convert to string.
 * @returns The status as string.
 */
const char* getStatusString(Status status);

/**
 * @brief Defines rotation direction.
 */
enum class RotationDir : int32_t {
    LEFT  = 1,
    CENTER = 0,
    RIGHT = -1
};

/**
 * @brief Defines bit order.
 */
enum class BitOrder : uint8_t {
	LITTLE_ENDIAN_ = 0,
	BIG_ENDIAN_
};

/**
 * @brief Defines sign of a number;
 */
enum class Sign : int32_t {
    POSITIVE = 1,
    NEUTRAL = 0,
    NEGATIVE = -1
};
} // namespace babocar
