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
	public juce::Component,
    public ToggleButton::Listener,
    public Slider::Listener
{
public:
    MixerChannel();
    ~MixerChannel() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setVolume(double value);
    double getVolume() const;

    virtual void buttonStateChanged(Button*) override;
    virtual void buttonClicked(Button*) override;
    virtual void sliderValueChanged(Slider* slider) override;
	
    ActionBroadcaster VolumeChangedBroadcaster;

private:
    Slider volumeSlider;
    ToggleButton muteButton;

    double getVolume();
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MixerChannel)
};



