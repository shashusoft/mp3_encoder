#ifndef WAV_HEADER_H
#define WAV_HEADER_H

#include <vector>
#include <cstdint>
#include <string>
// lame library
#include <lame.h>

enum Channel
{
    Mono = 1,
    Stereo = 2
};

// source : http://soundfile.sapp.org/doc/WaveFormat/
struct WaveHeader
{
    char     ChunkID[4];          // Contains the letters "RIFF" in ASCII form
    uint32_t ChunkSize;
    char     Format[4];           // Contains the letters "fmt"
    char     Subchunk1ID[4];      // Contains the letters "WAVE "
    uint32_t Subchunk1Size; 
    uint16_t AudioFormat;
    uint16_t NumChannels;         // Mono = 1, Stereo = 2
    uint32_t SampleRate;          // SampleRate, 8000, 44100
    uint32_t ByteRate;            
    uint16_t BlockAlign;
    uint16_t BitsPerSample;       // 8 bits = 8, 16 bits = 16, etc.
    char     Subchunk2ID[4];      // Contains the letters "data"
    uint32_t Subchunk2Size;       // Number of Bytes in the data 
};

class WAVHandler
{
public:
    WAVHandler();
    virtual ~WAVHandler();
    void wavFileCollection(std::vector<std::string>& a_wavFileContainer);
    void readAndConvert(const std::string& a_file);

    std::vector<unsigned char> convertToMPThreeMono(lame_global_flags* globalSettings, std::vector<short> input);
    std::vector<unsigned char> convertToMPThreeStereo(lame_global_flags* globalSettings, std::vector<short> input);
private:
    WaveHeader m_waveHeader;
};

#endif


