/*
  ==============================================================================

    AudioPlayer.h
    Created: 16 Aug 2020 8:26:02am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AudioPlayer  : public juce::Component
{
public:
    AudioPlayer();
    ~AudioPlayer() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayer)
};
