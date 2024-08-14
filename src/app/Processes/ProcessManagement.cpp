#include <iostream>
#include "ProcessManagement.hpp"
#include <unistd.h>
#include <cstring>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include "../encryptDecrypt/cryptoAlgo.hpp"
#include <sys/mman.h>
#include <atomic>
#include <semaphore.h>
ProcessManagement::ProcessManagement() {

 sem_t* itemsSemaphore = sem_open("/items_semaphore", O_CREAT, 0666, 0);
 sem_t* emptySlotsSemaphore = sem_open("/empty_slots_semaphore", O_CREAT, 0666, 1000);
// 0666 for the permission to group for create and read & write .
shmFd = shm_open (SHM_NAME , O_CREAT | O_RDWR , 0666 , 0) ; 
// for Giving the size 
ftruncate(shmFd, sizeof(SharedMemory));
// static_cast indicate the void (it can be any type as we kpw shared memory can be shared with any entity)
    sharedMem = static_cast<SharedMemory *>(mmap(nullptr, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0));
    sharedMem->front = 0;
    sharedMem->rear = 0;
    sharedMem->size.store(0);
}
ProcessManagement::~ProcessManagement() {
    munmap(sharedMem, sizeof(SharedMemory));
    shm_unlink(SHM_NAME);
}
bool ProcessManagement::submitToQueue(unique_ptr<TaskStruct> task) {
   sem_wait(emptySlotsSemaphore);
    std::unique_lock<std::mutex> lock(queueLock);

    if (sharedMem->size.load() >= 1000) {
        return false;
    }
     if (sharedMem->size.load() >= 1000) {
        return false;
    }
    // copy in memory 
    strcpy(sharedMem->tasks[sharedMem->rear], task->toString().c_str());
    sharedMem->rear = (sharedMem->rear + 1) % 1000;
    sharedMem->size.fetch_add(1);
     lock.unlock();
    sem_post(itemsSemaphore);
    int pid = fork();
    if (pid < 0) {
        return false;
    } else if (pid == 0) {
        executeTask();
        exit(0);
        // parent process does not wait for the termination of child process
        // They will run Multiprocessing to improve the performance.
        // If You want the Wait so there is sys call wait(pid) karke  
        exit(0);
    }
    return true;
}

void ProcessManagement::executeTasks() {
    // front se nikal rahe for the execution
      sem_wait(itemsSemaphore);
    std::unique_lock<std::mutex> lock(queueLock);
     char taskStr[256];
    strcpy(taskStr, sharedMem->tasks[sharedMem->front]);
    sharedMem->front = (sharedMem->front + 1) % 1000;
    sharedMem->size.fetch_sub(1);
    lock.unlock();
    sem_post(emptySlotsSemaphore);

    executeCryption(taskStr);
    // while (!taskQueue.empty()) {
    //     std::unique_ptr<Task> taskToExecute = std::move(taskQueue.front());
    //     taskQueue.pop();
    //     std::cout << "Executing task: " << taskToExecute->toString() << std::endl;
    //     // Add a breakpoint here in VS Code
    //     executeCryption(taskToExecute->toString());
    // }
}

