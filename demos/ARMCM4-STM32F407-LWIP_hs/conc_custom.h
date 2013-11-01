#ifndef CONC_CUSTOM_H
#define CONC_CUSTOM_H
#include "ch.h"
#include "jhc_rts_header.h"

#define jhc_threadid_t          Thread *
#define jhc_mutex_t             Mutex

void forkOS_createThread_init(void);

#endif /* CONC_CUSTOM_H */
