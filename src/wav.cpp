#include "wav.h"
#include <iostream>
#include <fstream>
#include <memory>


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
    std::vector<unsigned char> buffer;
    buffer.resize(input.size() * 5 / 4 + 7200);
    int encoded_size = lame_encode_buffer_interleaved(globalSettings, input.data(), static_cast<int>(input.size() / 2), buffer.data(), static_cast<int>(buffer.size()));
    if (encoded_size < 0)
      return {};
    encoded_size += lame_encode_flush(globalSettings, buffer.data() + encoded_size, static_cast<int>(buffer.size() - encoded_size));
    return{ buffer.begin(), buffer.begin() + encoded_size };
}

void WAVHandler::wavFileCollection(std::vector<std::string>& a_wavFileContainer)
{

}

void WAVHandler::readAndConvert(const std::string &a_file)
{
    std::ifstream fh;
    fh.open(a_file, std::ios_base::binary);
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
    std::string output(a_file);
    output.replace(output.end() - ext.length(), output.end(), ext);
    std::cout << "input file -> " << a_file << " output file -> " << output << std::endl;
    std::cout << " ChunkID "       << waveHeader.ChunkID         << " ChunkSize "     << waveHeader.ChunkSize            << " Format "      << waveHeader.Format        << " "
              << " Subchunk1ID "   << waveHeader.Subchunk1ID     << " Subchunk1Size " << waveHeader.Subchunk1Size        << " AudioFormat " << waveHeader.AudioFormat   << " "
              << " NumChannels "   << waveHeader.NumChannels     << " SampleRate "    << waveHeader.SampleRate           << " ByteRate "    << waveHeader.ByteRate      << " "
              << " BlockAlign "    << waveHeader.BlockAlign      << " BitsPerSample " << waveHeader.BitsPerSample        << " Subchunk2ID " << waveHeader.Subchunk2ID   << " "
              << " Subchunk2Size " << waveHeader.Subchunk2Size   << " " << std::endl;
    //bool isSuccess = convertToMPThree(it);
    auto const bytesPerSample = waveHeader.BitsPerSample / 8;
    auto const numberOfSamples = waveHeader.Subchunk2Size / bytesPerSample;
    std::vector<short> samples;
    samples.resize(numberOfSamples);
    std::unique_ptr<lame_global_flags, deleteLameEncoder> lameSettings(lame_init());
    if (lame_set_in_samplerate(lameSettings.get(), waveHeader.SampleRate) != 0)
    {
        std::cout <<  "Sample rate not initialised" << std::endl;
    }
    if (lame_set_num_channels(lameSettings.get(), static_cast<int>(waveHeader.NumChannels )) != 0)
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
    if (!fh.read(reinterpret_cast<char*>(samples.data()), waveHeader.Subchunk2Size))
    {
        std::cout << "Error in setting data size" << std::endl;
    }
    fh.close();
    std::vector<unsigned char> mp3Stream;
    switch (waveHeader.NumChannels)
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
