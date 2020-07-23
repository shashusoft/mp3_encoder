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

Logger* Logger::singleton()
{
    if (!exist())
    {
        std::shared_ptr<Logger> logger(new Logger("txt"));
        instance = logger.get();
    }
    return instance;
}   

bool Logger::exist()
{
    return isExist;
}

Logger* Logger::instance = nullptr;
bool Logger::isExist     = false;
