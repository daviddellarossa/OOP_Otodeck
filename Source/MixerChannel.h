/*
  ==============================================================================

    MixerChannel.h
    Created: 18 Aug 2020 7:42:28am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MixerChannel  : public juce::Component
{
public:
    MixerChannel();
    ~MixerChannel() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MixerChannel)
};
