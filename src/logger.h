#ifndef LOGGER_H
#define LOGGER_H

#include <string.h>
#include <fstream>
#include <ctime>
#include <iostream>

enum MESSAGETYPE
{
    ERROR_MSG,
    STATUS_MSG
};

class Logger
{
public:
    Logger(const std::string& a_fileName);
    virtual ~Logger();

    template<MESSAGETYPE T>
    void inline report(const std::string& a_message)    
    {
        std::string messageType = "";
        switch (T)
        {
            case ERROR_MSG:
                messageType = "ERROR";
            break;

            case STATUS_MSG:
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
    static void sRegisterInstance(Logger* a_instance);
    static Logger* singleton();   
    static bool sExist();

private:
    std::ofstream m_file;
    static Logger* instance;
    static bool isExist;
};


#endif
