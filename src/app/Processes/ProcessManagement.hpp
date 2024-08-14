#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include "TaskStruct.hpp"
#include <memory>
#include <mutex>
#include <atomic>
#include <semaphore.h>


using namespace std ;
// Intialization 
//------------------------------------------------------------------------------------------
// Submit to Queue 
// Queue intialization
// Execute/consume task 
//------------------------------------------------------------------------------------------

class ProcessManagment {
    public :
    
   ProcessManagment() ;
       sem_t* itemsSemaphore;
    sem_t* emptySlotsSemaphore;
   bool SubmitToQueue(unique_ptr<TaskStruct> task) ; 
   void executeTask();
   private: 
   // queue<unique_ptr<TaskStruct>> taskQueue ; 
     struct SharedMemory {
        atomic<int> size;
        char tasks[1000][256];
        int front;
        int rear;

        void printSharedMemory() {
            cout<<size<<endl ;
            cout<<front<<endl;
            cout<<rear<<endl ;
        }

    };
    SharedMemory* sharedMem;
    int shmFd;
    const char* SHM_NAME = "/my_queue";
    

};
#endif 

