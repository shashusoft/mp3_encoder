#include "logger.h"
#include <memory>

Logger::Logger(const std::string& a_fileName)
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

Logger::~Logger()
{
        
}

void Logger::sRegisterInstance(Logger* a_instance)
{
    instance = a_instance;
    isExist  = true;
}
Logger* Logger::singleton()
{
    is (isExist)
    {
        return instance;
    }
    {
        std::cout << "Nullpointer return in Logger " << std::endl;
    }
}   

bool Logger::sExist()
{
    return isExist;
}

Logger* Logger::instance = nullptr;
bool Logger::isExist     = false;
