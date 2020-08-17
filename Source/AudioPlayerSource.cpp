///*
//  ==============================================================================
//
//    AudioPlayerSource.cpp
//    Created: 17 Aug 2020 6:54:04pm
//    Author:  david
//
//  ==============================================================================
//*/
//
//#include "AudioPlayerSource.h"
//
//AudioPlayerSource::AudioPlayerSource()
//{
//    formatManager.registerBasicFormats();
//}
//AudioPlayerSource::~AudioPlayerSource()
//{
//
//}
//
//void AudioPlayerSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
//{
//    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
//    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
//}
//void AudioPlayerSource::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
//{
//    resampleSource.getNextAudioBlock(bufferToFill);
//
//}
//void AudioPlayerSource::releaseResources()
//{
//    transportSource.releaseResources();
//    resampleSource.releaseResources();
//}
//
//void AudioPlayerSource::loadURL(URL audioURL)
//{
//    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
//    if (reader != nullptr) // good file!
//    {
//        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader,
//            true));
//        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
//        readerSource.reset(newSource.release());
//    }
//}
//void AudioPlayerSource::setGain(double gain)
//{
//    if (gain < 0 || gain > 1.0)
//    {
//        std::cout << "AudioPlayerSource::setGain gain should be between 0 and 1" << std::endl;
//    }
//    else {
//        transportSource.setGain(gain);
//    }
//
//}
//void AudioPlayerSource::setSpeed(double ratio)
//{
//    if (ratio < 0 || ratio > 100.0)
//    {
//        std::cout << "AudioPlayerSource::setSpeed ratio should be between 0 and 100" << std::endl;
//    }
//    else {
//        resampleSource.setResamplingRatio(ratio);
//    }
//}
//void AudioPlayerSource::setPosition(double posInSecs)
//{
//    transportSource.setPosition(posInSecs);
//}
//
//void AudioPlayerSource::setPositionRelative(double pos)
//{
//    if (pos < 0 || pos > 1.0)
//    {
//        std::cout << "AudioPlayerSource::setPositionRelative pos should be between 0 and 1" << std::endl;
//    }
//    else {
//        double posInSecs = transportSource.getLengthInSeconds() * pos;
//        setPosition(posInSecs);
//    }
//}
//
//
//void AudioPlayerSource::start()
//{
//    transportSource.start();
//}
//void AudioPlayerSource::stop()
//{
//    transportSource.stop();
//}
//
//double AudioPlayerSource::getPositionRelative()
//{
//    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
//}