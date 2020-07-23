#include "thread_handler.h"

// system
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <iostream>

// user
#include "wav.h"
#include "logger.h"

#define LOG Logger::singleton()

int ThreadHandler::noOfWaveFile = 0;
pthread_mutex_t lock;

template<class Input, class Function, class Pointer>
void generateThreads(Input count, Function f, Pointer pntr)
{
    pthread_t threadID[count];
    int statusContainer[count] = {0};
    int joinCount = 0;
    
    while (count > 0)
    {
        pthread_create(&threadID[count], NULL, f, pntr);
        count--;
        joinCount++;
    }
    while(joinCount > 0)
    {
        statusContainer[joinCount] = pthread_join(threadID[joinCount], nullptr);
        joinCount--;
    }
    int threadCounter = 1;
    for (auto i : statusContainer)
    {
        std::string status = "";
        if(i == 0)  status = "finished"; else status = " has error";
        std::cout << "Thread number " << threadCounter << " " << status <<  std::endl;
        threadCounter++;
    }
}

ThreadHandler::ThreadHandler(std::vector<std::string> &a_container)
    : m_waveContainer(a_container)
{
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        LOG->report<ERROR>("Mutex init failed "); 
        std::cout << "Mutex init has failed" << std::endl;
    }
    int supThread = supportedThreadCount();
    m_waveHandler = new WAVHandler;
    if (supThread < (int)m_waveContainer.size())
    {
        int rem         = (int)m_waveContainer.size() - supThread;
        m_remainingFile = rem;
    }
    std::cout << " m_waveContainer.size() " << m_waveContainer.size() << " supThread " << supThread;
    ThreadHandler::noOfWaveFile = m_waveContainer.size() - 1;
    generateThreads(m_waveContainer.size() - 1, newThread, this);
    pthread_mutex_destroy(&lock);
}

ThreadHandler::~ThreadHandler()
{
    delete m_waveHandler;
}

int ThreadHandler::supportedThreadCount()
{
#ifdef _WIN32
  SYSTEM_INFO system_info;
  GetSystemInfo(&system_info);
  return system_info.dwNumberOfProcessors;
#else
  return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}

void ThreadHandler::setRemainingFile(const int& a_value)
{
    m_remainingFile = a_value;
}

void *ThreadHandler::newThread(void *a_value)
{
    pthread_mutex_lock(&lock);
    auto pntr = reinterpret_cast<ThreadHandler*>(a_value);
    if (ThreadHandler::noOfWaveFile > 0)
    {
        pntr->m_waveHandler->readAndConvert(pntr->m_waveContainer[ThreadHandler::noOfWaveFile]);
    }
    std::cout << "Thread Number -> " << ThreadHandler::noOfWaveFile << std::endl;
    LOG->report<STATUS>("Thread started "); 
    ThreadHandler::noOfWaveFile--;
    pthread_mutex_unlock(&lock);
    return NULL;
}

