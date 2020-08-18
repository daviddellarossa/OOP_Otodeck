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

#include "ExternalCallbackSliderListener.h"

typedef ExternalCallbackSliderListener Listener;

class MixerChannel  :
	public juce::Component
{
public:
    MixerChannel(Listener* volumeChanged);
    ~MixerChannel() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setVolume(double value);
    double getVolume() const;

private:
    Slider volumeSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MixerChannel)
};
