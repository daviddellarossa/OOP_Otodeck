///*
//  ==============================================================================
//
//    AudioPlayerSource.h
//    Created: 17 Aug 2020 6:54:04pm
//    Author:  david
//
//  ==============================================================================
//*/
//
//#pragma once
//#include <JuceHeader.h>
//
//class AudioPlayerSource : public AudioSource {
//public:
//
//    AudioPlayerSource();
//    ~AudioPlayerSource();
//
//    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
//    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
//    void releaseResources() override;
//
//    void loadURL(URL audioURL);
//    void setGain(double gain);
//    void setSpeed(double ratio);
//    void setPosition(double posInSecs);
//    void setPositionRelative(double pos);
//
//
//    void start();
//    void stop();
//
//    /** get the relative position of the playhead */
//    double getPositionRelative();
//
//private:
//    AudioFormatManager formatManager;
//    std::unique_ptr<AudioFormatReaderSource> readerSource;
//    AudioTransportSource transportSource;
//    ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
//
//};
