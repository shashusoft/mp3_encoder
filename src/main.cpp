#include <iostream>
#include <string.h>
#include <exception>
#include <stdlib.h>
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include <dirent.h>
#include<vector>
// user
#include "thread_handler.h"
#include "logger.h"

#define LOG Logger::singleton()

struct CommandArguments
{
    const char* m_help       = "--help";
    const char* m_currPath   = ".";
    const char* m_bin        = "/bin";
    const char* m_extSlash   = "/bin/";
    const char*  m_exactFile = "wav";
};

std::string getCurrentDirectory() {
   char buff[FILENAME_MAX]; 
   char* ret = GetCurrentDir(buff, FILENAME_MAX );
   if (ret == NULL)
   {
       LOG->report<ERROR_MSG>("Unable to open current directory "); 
       std::cout << ":Unable to open current directory" << std::endl;         
   }
   else
   {
       LOG->report<STATUS_MSG>("Current directory opened");    
   }
   std::string currentDirectory(buff);
   return currentDirectory;
}

int main(int argc, char* argv[])
{
    int wavFileCounter        = 0;
    bool isExactWavFilePath   = false;
    Logger logger("log.txt");
    Logger::sRegisterInstance(logger);
    std::vector<std::string> waveContainer;
    CommandArguments cmdArg;
    try
    {
        if (argc != 2)
        {
            std::cout << std::endl;
            std::cout << "********************"                         << std::endl;
            std::cout << ":Path to *.wav file missing "                 << std::endl;
            std::cout << ":Type ./mp3_encoder --help for further help " << std::endl;
            std::cout << "********************"                         << std::endl;
            LOG->report<ERROR_MSG>("File name entered incorrectly");
            std::cout << std::endl;
            exit(EXIT_FAILURE);
        }
        else if (strcmp(argv[1], cmdArg.m_help) == 0)
        {
            std::cout << std::endl;
            std::cout << "********************" << std::endl;
            std::cout << "Usage: "              << std::endl << "./mp3_encoder --help" << std::endl << "./mp3_encoder <path to *.wave file> " << std::endl;
            std::cout << "********************" << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << std::endl;
            std::cout << "********************"                                       << std::endl;
            std::cout << "Welcome to MP3 Encoder"                                     << std::endl;
            std::cout << "Developer @Atish Patange"                                   << std::endl;
            std::cout << "As Assignment by Cinemo GmbH"                               << std::endl;
            std::cout << "Contact patangeatish@simple-robot.de"                       << std::endl;
            std::cout << "Repository: https://github.com/shashusoft/mp3_encoder.git " << std::endl;
            std::cout << "Location of *.wav files : /bin/*.wav "                      << std::endl;
            std::cout << "Location of converted *.mp3 files : /bin/*.mp3 "            << std::endl;
            std::cout << "********************" << std::endl;
            std::cout << std::endl;

            std::string path = argv[1];
            if (strcmp(path.c_str(), cmdArg.m_currPath) == 0)
            {
                path = getCurrentDirectory();
            }
            if (strcmp(path.c_str(), cmdArg.m_bin) == 0)
            {
                path = getCurrentDirectory() + "/bin/";
            }
            if (strcmp(path.c_str(), cmdArg.m_extSlash) == 0)
            {
                path = getCurrentDirectory() + "/bin/";
            }
            if (path.substr(path.find_last_of(".") + 1) == cmdArg.m_exactFile)
            {
                isExactWavFilePath = true;
                std::cout << "WAV file found -> " << path << std::endl;
                wavFileCounter++;
            }
            // validate wave file
            if (!isExactWavFilePath)
            {
                // Read content of all directory
                DIR *dir;
                struct dirent *direntStruct;
                if ((dir = opendir (path.c_str())) != NULL) 
                {
                    // Print all the files and directories within directory
                    while ((direntStruct = readdir (dir)) != NULL) 
                    {
                        std::string fileName = direntStruct->d_name;
                        if(fileName.substr(fileName.find_last_of(".") + 1) == "wav") 
                        {
                            std::cout << "WAV file found -> " << fileName << std::endl;
                            waveContainer.push_back(fileName);
                            wavFileCounter++;
                        } 
                        else 
                        {
                            //std::cout << "No..." << fileName << std::endl;
                        }
                    }
                closedir (dir);
                }
            }
            if (wavFileCounter == 0)
            {
                LOG->report<STATUS_MSG>("No wav file found");
                std::cout << ":No WAV file found. WAV files available at /bin/ "                                << std::endl;
                std::cout << ":Exiting application, please try again with ./mp3_encoder <path to *.wav file> " << std::endl;
                exit(EXIT_FAILURE);
            }
            else
            {
                LOG->report<STATUS_MSG>("wav files found ");
                std::cout << ":Number of WAV files -> " <<  wavFileCounter << std::endl;
                std::cout << "-----"                    << std::endl;
                ThreadHandler threadHandler(waveContainer);
            }
        }
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << std::endl;
        LOG->report<ERROR_MSG>("Exception occured ");
    }
}
