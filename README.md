********************
Project: Cinemo Assignment
Developer: Atish Patange
Date: 21.07.2020
Contact: patangeatish@simple-robot.de
********************

wav file source: https://www2.cs.uic.edu/~i101/SoundFiles/

TASK : Write a C/C++ commandline application that encodes a set of WAV files to MP3

Requirements:

(1) application is called with pathname as argument, e.g. <applicationname> F:\MyWavCollection all WAV-files contained directly in that folder are to be encoded to MP3

(2) use all available CPU cores for the encoding process in an efficient way by utilizing multi-threading

(3) statically link to lame encoder library

(4) application should be compilable and runnable on Windows and Linux

(5) the resulting MP3 files are to be placed within the same directory as the source WAV files, the filename extension should be changed appropriately to .MP3

(6) non-WAV files in the given folder shall be ignored

(7) multithreading shall be implemented in a portable way, for example using POSIX pthreads.

(8) frameworks such as Boost or Qt shall not be used

(9) the LAME encoder should be used with reasonable standard settings (e.g. quality based encoding with quality level "good")


Build and Run:


------------
Windows

------------

configure and generate makefile using CMake GUI (CMake 3.18.0)

mingw32-make

cd bin

./mp3_encoder .

------------

Linux

------------

cmake .

make

cd bin

./mp3_encoder .

------------

Tested on

------------

Linux Mint, GNU 7.5.0, C++17
Windows 10, CMake GUI 3.18, Mingw32-make, GCC, C++17 

