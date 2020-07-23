#ifndef THREAD_HANDLER_H
#define THREAD_HANDLER_H

#include <vector>
#include <string>

class WAVHandler;

class ThreadHandler
{
public:
    ThreadHandler(std::vector<std::string>& a_container);
    virtual ~ThreadHandler();

    int supportedThreadCount();
    void setRemainingFile(const int &a_value);

    static void* newThread(void *a_value);

public:
    std::vector<std::string> m_waveContainer;
    WAVHandler* m_waveHandler = nullptr;

    int m_remainingFile = 0;
    static int noOfWaveFile;
};

#endif // THREAD_HANDLER_H
