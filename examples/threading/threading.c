#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;

    struct thread_data* thread_func_args = (struct thread_data *) thread_param;

    if(pthread_mutex_init(thread_func_args->mutex) !=0)
    {
        thread_func_args->thread_complete_success = false;
        return thread_param;
    }

    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */

     thread_data *t_data = (thread_data*)malloc(sizeof(thread_data));
     t_data->thread = thread;
     t_data->mutex = mutex;
     t_data->wait_to_obtain_ms = wait_to_obtain_ms;
     t_data->wait_to_release_ms = wait_to_release_ms;

     thread_data *t_data2 = threadfunc(t_data);
     return t_data2->thread_complete_success;

}

