#ifndef INTHREADVAL_H
#define INTHREADVAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

enum InthreadvalStatus
{
    INTHREADVAL_STATUS_OK,
    INTHREADVAL_STATUS_ERROR_ALREADY_STARTED,
    INTHREADVAL_STATUS_ERROR_NOT_STARTED,
};

typedef struct Inthreadval Inthreadval;

/**
 * @brief Creates a new Inthreadval instance
 * @return The newly created instance
 **/
extern Inthreadval *inthreadval_create(void (*callback)(void), uint32_t ms_interval);

/**
 * @brief Destroys a Inthreadval instance and frees memory
 **/
extern void inthreadval_destroy(Inthreadval *inthreadval);

/**
 * @brief Creates a new thread and starts running the user defined function at a specified interval
 * @return Whether the thread is already running (INTHREADVAL_STATUS_ERROR_ALREADY_STARTED) or it was
 *successfully started (INTHREADVAL_STATUS_OK)
 **/
extern enum InthreadvalStatus inthreadval_start(Inthreadval *inthreadval);

/**
 * @brief Stops a created thread from running
 * @return Whether the thread is already stopped (INTHREADVAL_STATUS_ERROR_NOT_STARTED) or it was
 *successfully stopped (INTHREADVAL_STATUS_OK)
 **/
extern enum InthreadvalStatus inthreadval_stop(Inthreadval *inthreadval);

#ifdef __cplusplus
}
#endif

#endif // INTHREADVAL_H
