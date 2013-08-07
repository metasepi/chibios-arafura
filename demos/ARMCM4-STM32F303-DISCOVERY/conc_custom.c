#include "rts/conc.h"

#define THREADS_STACK_SIZE 512
#define NUM_THREADS 2
static char pool_buf[(THD_WA_SIZE(THREADS_STACK_SIZE)) * NUM_THREADS];
static MEMORYPOOL_DECL(pool_descriptor, THD_WA_SIZE(THREADS_STACK_SIZE), NULL);


/* xxx ChibiOS/RT's Mutex does not support locking on interrupt. */
void
jhc_mutex_init(jhc_mutex_t *mutex)
{
	chMtxInit(mutex);
}

void
jhc_mutex_lock(jhc_mutex_t *mutex)
{
	chMtxLock(mutex);
}

void
jhc_mutex_unlock(jhc_mutex_t *mutex)
{
	jhc_mutex_t *unlocked = chMtxUnlock();
	if (unlocked != mutex) {
		abort();
	}
}

void
forkOS_createThread_init()
{
	chPoolInit(&pool_descriptor, THD_WA_SIZE(THREADS_STACK_SIZE), NULL);
	chPoolLoadArray(&pool_descriptor, (void *) pool_buf, NUM_THREADS);
}

jhc_threadid_t
forkOS_createThread(void *(*wrapper) (void *), void *entry, int *err)
{
	Thread *tid;
	tid = chThdCreateFromMemoryPool(&pool_descriptor, NORMALPRIO, (tfunc_t) wrapper, entry);
	if (NULL == tid) {
		abort();
	}
	return tid;
}
