#include "wav.h"
// system
#include <iostream>
#include <fstream>
#include <memory>
// user
#include "logger.h"

#define LOG Logger::singleton()

const std::string ext = {"mp3"};
const size_t LAME_GOOD = 4;

struct deleteLameEncoder
{
  void operator()(lame_global_flags* a_globalFlag) const { lame_close(a_globalFlag); }
};

WAVHandler::WAVHandler()
{
    
}

WAVHandler::~WAVHandler()
{

}

std::vector<unsigned char> WAVHandler::convertToMPThreeMono(lame_global_flags* globalSettings, std::vector<short> input)
{
    LOG->report<STATUS_MSG>("Coverting wav mono to mp3 "); 
    std::vector<unsigned char> buffer;
    buffer.resize(input.size() * 5 / 4 + 7200);
    int encoded_size = lame_encode_buffer(globalSettings, input.data(), input.data(), static_cast<int>(input.size()), buffer.data(), static_cast<int>(buffer.size()));
    if (encoded_size < 0)
      return {};
    encoded_size += lame_encode_flush(globalSettings, buffer.data() + encoded_size, static_cast<int>(buffer.size() - encoded_size));
    return { buffer.begin(), buffer.begin() + encoded_size };
}

std::vector<unsigned char> WAVHandler::convertToMPThreeStereo(lame_global_flags* globalSettings, std::vector<short> input)
{
    LOG->report<STATUS_MSG>("Coverting wav stereo to mp3 ");
    std::vector<unsigned char> buffer;
    buffer.resize(input.size() * 5 / 4 + 7200);
    int encoded_size = lame_encode_buffer_interleaved(globalSettings, input.data(), static_cast<int>(input.size() / 2), buffer.data(), static_cast<int>(buffer.size()));
    if (encoded_size < 0)
      return {};
    encoded_size += lame_encode_flush(globalSettings, buffer.data() + encoded_size, static_cast<int>(buffer.size() - encoded_size));
    return{ buffer.begin(), buffer.begin() + encoded_size };
}

void WAVHandler::readAndConvert(const std::string &a_file)
{
    LOG->report<STATUS_MSG>("received file for read and convert ");
    std::ifstream fh;
    fh.open(a_file, std::ios_base::binary);
    fh.read((char*)&m_waveHeader.ChunkID, sizeof(m_waveHeader.ChunkID));
    fh.read((char*)&m_waveHeader.ChunkSize, sizeof(m_waveHeader.ChunkSize));
    fh.read((char*)&m_waveHeader.Format, sizeof(m_waveHeader.Format));
    fh.read((char*)&m_waveHeader.Subchunk1ID, sizeof(m_waveHeader.Subchunk1ID));
    fh.read((char*)&m_waveHeader.Subchunk1Size, sizeof(m_waveHeader.Subchunk1Size));
    fh.read((char*)&m_waveHeader.AudioFormat, sizeof(m_waveHeader.AudioFormat));
    fh.read((char*)&m_waveHeader.NumChannels, sizeof(m_waveHeader.NumChannels));
    fh.read((char*)&m_waveHeader.SampleRate, sizeof(m_waveHeader.SampleRate));
    fh.read((char*)&m_waveHeader.ByteRate, sizeof(m_waveHeader.ByteRate));
    fh.read((char*)&m_waveHeader.BlockAlign, sizeof(m_waveHeader.BlockAlign));
    fh.read((char*)&m_waveHeader.BitsPerSample, sizeof(m_waveHeader.BitsPerSample));
    fh.read((char*)&m_waveHeader.Subchunk2ID, sizeof(m_waveHeader.Subchunk2ID));
    fh.read((char*)&m_waveHeader.Subchunk2Size, sizeof(m_waveHeader.Subchunk2Size));
    std::string output(a_file);
    output.replace(output.end() - ext.length(), output.end(), ext);
    std::cout << " #Input file -> "   << a_file                      <<                      std::endl                           << " #Output file -> "  << output                     << std::endl;
    std::cout << "*****Header***** " << std::endl; 
    std::cout << " #ChunkID: "       << m_waveHeader.ChunkID         << " #ChunkSize: "     << m_waveHeader.ChunkSize            << " #Format: "         << m_waveHeader.Format        << " "        
              << " #Subchunk1ID: "   << m_waveHeader.Subchunk1ID     << " #Subchunk1Size: " << m_waveHeader.Subchunk1Size        << " #AudioFormat: "    << m_waveHeader.AudioFormat   << " "        << std::endl
              << " #NumChannels: "   << m_waveHeader.NumChannels     << " #SampleRate: "    << m_waveHeader.SampleRate           << " #ByteRate: "       << m_waveHeader.ByteRate      << " "        
              << " #BlockAlign: "    << m_waveHeader.BlockAlign      << " #BitsPerSample: " << m_waveHeader.BitsPerSample        << " #Subchunk2ID: "    << m_waveHeader.Subchunk2ID   << " "        << std::endl
              << " #Subchunk2Size: " << m_waveHeader.Subchunk2Size   << " " << std::endl;
    //bool isSuccess = convertToMPThree(it);
    auto const bytesPerSample = m_waveHeader.BitsPerSample / 8;
    auto const numberOfSamples = m_waveHeader.Subchunk2Size / bytesPerSample;
    std::vector<short> samples;
    samples.resize(numberOfSamples);
    std::unique_ptr<lame_global_flags, deleteLameEncoder> lameSettings(lame_init());
    if (lame_set_in_samplerate(lameSettings.get(), m_waveHeader.SampleRate) != 0)
    {
        std::cout <<  "Sample rate not initialised" << std::endl;
    }
    if (lame_set_num_channels(lameSettings.get(), static_cast<int>(m_waveHeader.NumChannels )) != 0)
    {
        std::cout <<  "Number of channels not initialised" << std::endl;
    }
    if (lame_set_quality(lameSettings.get(), LAME_GOOD) != 0)
    {
        std::cout <<  "MP3 quality not initialised" << std::endl;
    }
    if (lame_init_params(lameSettings.get()) != 0)
    {
        std::cout <<  "Parameters not initialised" << std::endl;
    }
    if (!fh.read(reinterpret_cast<char*>(samples.data()), m_waveHeader.Subchunk2Size))
    {
        std::cout << "Error in setting data size" << std::endl;
    }
    fh.close();
    std::vector<unsigned char> mp3Stream;
    switch (m_waveHeader.NumChannels)
    {
    case Mono:
        mp3Stream = convertToMPThreeMono(lameSettings.get(), samples);
        break;
    case Stereo:
        mp3Stream = convertToMPThreeStereo(lameSettings.get(), samples);
        break;
    default:
        break;
    }
    std::ofstream mp3{ output, std::ofstream::binary };
    mp3.write(reinterpret_cast<char const*>(mp3Stream.data()), mp3Stream.size());
    std::cout << "-----" << std::endl;
}
