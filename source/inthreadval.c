#include "../include/inthreadval.h"
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

struct Inthreadval
{
    thrd_t thread;
    uint8_t is_running;
    uint32_t ms_interval;
    void (*callback)(void);
};

struct Inthreadval *inthreadval_create(void (*callback)(void), uint32_t ms_interval)
{
    struct Inthreadval *inthreadval = (struct Inthreadval *) malloc(sizeof(struct Inthreadval));

    if (!inthreadval)
    {
        fprintf(stderr, "inthreadval::error: Failed to allocate memory for inthreadval object\n");
        return NULL;
    }

    inthreadval->is_running = 0;
    inthreadval->callback = callback;
    inthreadval->ms_interval = ms_interval;

    return inthreadval;
}

void inthreadval_destroy(Inthreadval *inthreadval)
{
    if (inthreadval->is_running)
        inthreadval_stop(inthreadval);

    free(inthreadval);
}

int inthreadval_run(void *inthreadval_pointer)
{
    struct Inthreadval *inthreadval = (struct Inthreadval *) inthreadval_pointer;

    struct timespec ts;

    ts.tv_sec = inthreadval->ms_interval / 1000;
    ts.tv_nsec = (inthreadval->ms_interval % 1000) * 1000000;

    while (inthreadval->is_running)
    {
        inthreadval->callback();
        thrd_sleep(&ts, NULL);
    }

    return 0;
}

enum InthreadvalStatus inthreadval_start(Inthreadval *inthreadval)
{
    if (inthreadval->is_running)
        return INTHREADVAL_STATUS_ERROR_ALREADY_STARTED;

    inthreadval->is_running = 1;
    thrd_create(&inthreadval->thread, inthreadval_run, inthreadval);

    return INTHREADVAL_STATUS_OK;
}

enum InthreadvalStatus inthreadval_stop(Inthreadval *inthreadval)
{
    if (!inthreadval->is_running)
        return INTHREADVAL_STATUS_ERROR_NOT_STARTED;

    inthreadval->is_running = 0;
    thrd_join(inthreadval->thread, NULL);

    return INTHREADVAL_STATUS_OK;
}
