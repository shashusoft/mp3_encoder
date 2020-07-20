#ifndef LOGGER_H
#define LOGGER_H

#include <string.h>
#include <fstream>
#include <ctime>

enum MESSAGETYPE
{
    ERROR,
    STATUS
};

class Logger
{
public:
    Logger(const std::string& a_fileName)
    {
        m_file.open(a_fileName, std::ofstream::out | std::ofstream::trunc);
        if (!m_file)      
        {
            std::cout << ":File could not be created " << std::endl;
        }
        else
        {
            m_file << "<version 1.0> " << std::endl;
        }
    }

    virtual ~Logger()
    {
        
    }

    template<MESSAGETYPE T>
    void report(const std::string& a_message)    
    {
        std::string messageType = "";
        switch (T)
        {
            case ERROR:
                messageType = "ERROR";
                break;

            case STATUS:
                messageType = "STATUS";
                break;
        }
        std::time_t now = time(0);
        std::tm* localTime = std::localtime(&now);
        m_file << localTime->tm_year << localTime->tm_mon << localTime->tm_mday << "::" 
               << localTime->tm_hour << localTime->tm_min << localTime->tm_sec << "::" 
               << messageType << "::"
               << a_message 
               << std::endl;
    }    
private:
    std::ofstream m_file;
};

#endif
