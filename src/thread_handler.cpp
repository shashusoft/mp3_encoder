#include "thread_handler.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <pthread.h>
#include <iostream>

#include "wav.h"

int ThreadHandler::glCountr = 12;
pthread_mutex_t lock;

template<class Input, class Function, class Pointer>
void parallelFun(Input count, Function f, Pointer pntr)
{
    pthread_t threadID[count];
    int joinCount = 0;
    while (count > 0)
    {
        pthread_create(&threadID[count], NULL, f, pntr);
        count--;
        joinCount++;
    }
    while(joinCount > 0)
    {
        pthread_join(threadID[joinCount], nullptr);
        joinCount--;
    }
}

ThreadHandler::ThreadHandler(std::vector<std::string> &a_container)
    : m_waveContainer(a_container)
{
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
    }
    int supThread         = supportedThreadCount();
    int leftFileToProcess = 0;
    m_waveHandler = new WAVHandler;
    if (supThread < (int)m_waveContainer.size())
    {
        int rem = (int)m_waveContainer.size() - supThread;
        m_remainingFile = rem;
    }
    parallelFun((int)m_waveContainer.size(), newThread, this);
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
    if (ThreadHandler::glCountr > 0)
    {
        pntr->m_waveHandler->readAndConvert(pntr->m_waveContainer[ThreadHandler::glCountr]);
    }
    std::cout << ThreadHandler::glCountr << std::endl;
    ThreadHandler::glCountr--;
    pthread_mutex_unlock(&lock);
}

