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
    thread_func_args->thread_complete_success = false;
    DEBUG_LOG("THREAD STARTED");
    usleep(thread_func_args->wait_to_obtain_ms*1000);

    if(pthread_mutex_lock(thread_func_args->mutex) !=0)
    {
        ERROR_LOG("Mutex cannot be locked");
        thread_func_args->thread_complete_success = false; 
    }
    else
    {
        DEBUG_LOG("Mutex locked");
        usleep(thread_func_args->wait_to_release_ms*1000);
        if(pthread_mutex_unlock(thread_func_args->mutex) != 0)
        {
            ERROR_LOG("Mutex still locked");
            thread_func_args->thread_complete_success = false;
        }
        else
        {
            thread_func_args->thread_complete_success = true;
            DEBUG_LOG("THREAD FINISHED");
        }
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

    struct thread_data *t_data = (struct thread_data *) malloc(sizeof (struct thread_data));
    
    if (t_data == NULL) {
        ERROR_LOG("Could not allocate thread_data");
        return false;
    }
    t_data->mutex = mutex;
    t_data->wait_to_obtain_ms = wait_to_obtain_ms;
    t_data->wait_to_release_ms = wait_to_release_ms;
    t_data->thread_complete_success = false;

    if (pthread_create(thread, NULL, threadfunc, t_data) !=0) {
        ERROR_LOG("Could not create thread");
        return false;
    }

    return true;

}

