/*
  ==============================================================================

    AudioPlayer.h
    Created: 16 Aug 2020 8:26:02am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AudioPlayerSource.h"

//==============================================================================
/*
*/
class AudioPlayer  : public juce::AudioSource
{
public:
    AudioPlayer(AudioFormatManager& _formatManager);
    ~AudioPlayer() = default;
	
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void loadURL(URL audioURL);
    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);


    void start();
    void stop();

    /** get the relative position of the playhead */
    double getPositionRelative();

private:
    AudioFormatManager& formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
	
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayer)
};
