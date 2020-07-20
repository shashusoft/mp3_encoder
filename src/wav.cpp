#include "wav.h"
#include <iostream>
#include <fstream>
#include <lame/lame.h>

size_t PCM_SIZE = 8192;
size_t MP3_SIZE = 8192;
const size_t bytes_per_sample = 2 * sizeof(int16_t); // stereo signal, 16 bits

WAVHandler::WAVHandler()
{

}

WAVHandler::~WAVHandler()
{

}

bool WAVHandler::convertToMPThree(const std::string& input)
{
    const size_t IN_SAMPLERATE = 44100; // default sample-rate
    const size_t PCM_SIZE = 50000;
    const size_t MP3_SIZE = 50000;
    const size_t LAME_GOOD = 4;
    int16_t pcm_buffer[PCM_SIZE * 2];
    unsigned char mp3_buffer[MP3_SIZE];
    const size_t bytes_per_sample = 2 * sizeof(int16_t); // stereo signal, 16 bits
    const std::string ext = {"mp3"};

    std::string output(input);
    output.replace(output.end() - ext.length(), output.end(), ext);
    std::ifstream wav;
    std::ofstream mp3;

    wav.exceptions(std::ifstream::failbit);
    mp3.exceptions(std::ifstream::failbit);
    try {
        wav.open(input, std::ios_base::binary);
        mp3.open(output, std::ios_base::binary);
    }
    catch (std::ifstream::failure e) {
        std::cout << "Error opening input/output file: " << std::endl;
        return false;
    }

    lame_t lame = lame_init();
    lame_set_in_samplerate(lame, IN_SAMPLERATE);
    lame_set_VBR(lame, vbr_default);
    lame_set_VBR_q(lame, LAME_GOOD);

    if (lame_init_params(lame) < 0) {
        wav.close();
        mp3.close();
        return false;
    }

    while (wav.good()) {
        int write = 0;
        wav.read(reinterpret_cast<char*>(pcm_buffer), sizeof(pcm_buffer));
        int read = wav.gcount() / bytes_per_sample;
        if (read == 0)
            write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
        else
            write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);
        mp3.write(reinterpret_cast<char*>(mp3_buffer), write);
    }

    wav.close();
    mp3.close();

    lame_close(lame);
    return true;
}

bool WAVHandler::convertToMPThree_p(const std::string& input)
{
   return true;
}

void WAVHandler::readWavFile(std::vector<std::string>& a_wavFileContainer)
{
    const std::string ext = {"mp3"};
    const size_t LAME_GOOD = 4;
    
    for (auto it : a_wavFileContainer)
    {
        std::fstream fh;
        fh.open(it, std::fstream::in | std::fstream::binary);
        fh.read((char*)&waveHeader.ChunkID, sizeof(waveHeader.ChunkID));
        fh.read((char*)&waveHeader.ChunkSize, sizeof(waveHeader.ChunkSize));
        fh.read((char*)&waveHeader.Format, sizeof(waveHeader.Format));
        fh.read((char*)&waveHeader.Subchunk1ID, sizeof(waveHeader.Subchunk1ID));
        fh.read((char*)&waveHeader.Subchunk1Size, sizeof(waveHeader.Subchunk1Size));
        fh.read((char*)&waveHeader.AudioFormat, sizeof(waveHeader.AudioFormat));
        fh.read((char*)&waveHeader.NumChannels, sizeof(waveHeader.NumChannels));
        fh.read((char*)&waveHeader.SampleRate, sizeof(waveHeader.SampleRate));
        fh.read((char*)&waveHeader.ByteRate, sizeof(waveHeader.ByteRate));
        fh.read((char*)&waveHeader.BlockAlign, sizeof(waveHeader.BlockAlign));
        fh.read((char*)&waveHeader.BitsPerSample, sizeof(waveHeader.BitsPerSample));
        fh.read((char*)&waveHeader.Subchunk2ID, sizeof(waveHeader.Subchunk2ID));
        fh.read((char*)&waveHeader.Subchunk2Size, sizeof(waveHeader.Subchunk2Size));
        fh.close();
        std::string output(it);
        output.replace(output.end() - ext.length(), output.end(), ext);
        std::cout << "input file -> " << it << " output file -> " << output << std::endl;
        std::cout << " ChunkID "       << waveHeader.ChunkID         << " ChunkSize "     << waveHeader.ChunkSize            << " Format "      << waveHeader.Format        << " "
                  << " Subchunk1ID "   << waveHeader.Subchunk1ID     << " Subchunk1Size " << waveHeader.Subchunk1Size        << " AudioFormat " << waveHeader.AudioFormat   << " "
                  << " NumChannels "   << waveHeader.NumChannels     << " SampleRate "    << waveHeader.SampleRate           << " ByteRate "    << waveHeader.ByteRate      << " "
                  << " BlockAlign "    << waveHeader.BlockAlign      << " BitsPerSample " << waveHeader.BitsPerSample        << " Subchunk2ID " << waveHeader.Subchunk2ID   << " "
                  << " Subchunk2Size " << waveHeader.Subchunk2Size   << " " << std::endl;       
        //bool isSuccess = convertToMPThree(it);

        int read, write;
        FILE *pcm = fopen(it.c_str(), "rb");
        FILE *mp3 = fopen(output.c_str(), "wb");

        const int PCM_SIZE = 8192;
        const int MP3_SIZE = 8192;

        short int pcm_buffer[PCM_SIZE * 2];
        unsigned char mp3_buffer[MP3_SIZE];

        lame_t lame = lame_init();
        lame_set_in_samplerate(lame, waveHeader.SampleRate);
        lame_set_VBR(lame, vbr_default);
        lame_init_params(lame);

        do {
        read = fread(pcm_buffer, 2*sizeof(short int), PCM_SIZE, pcm);
        if (read == 0)
            write = lame_encode_flush(lame, mp3_buffer, MP3_SIZE);
        else
            write = lame_encode_buffer_interleaved(lame, pcm_buffer, read, mp3_buffer, MP3_SIZE);
        fwrite(mp3_buffer, write, 1, mp3);
        } while (read != 0);

        lame_close(lame);
        fclose(mp3);
        fclose(pcm);

        std::cout << "-----" << std::endl;
    }
}  
