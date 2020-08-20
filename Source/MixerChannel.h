/*
  ==============================================================================

    MixerChannel.h
    Created: 18 Aug 2020 7:42:28am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ExternalCallbackSliderListener.h"

typedef ExternalCallbackSliderListener Listener;

/// <summary>
/// Implements a single channel of a Mixer.
/// This component aggregates a Slider to control the Volume and a ToggleButton to control the Mute
/// Whenever one of these Components has a change in value, the VolumeChangeBroadcaster is invoked,
/// sending out the current volume after the change
/// </summary>
class MixerChannel  :
	public juce::Component,
    public ToggleButton::Listener,
    public Slider::Listener
{
public:
    MixerChannel();
    ~MixerChannel() override;

	//Overrides for the Component's virtual functions
    void paint (juce::Graphics&) override;
    void resized() override;

	//Set the Volume to value
    void setVolume(double value);
	//Return the current Volume
    double getVolume() const;

	//Overrides for the ToggleButton virtual methods
    void buttonStateChanged(Button*) override;
    void buttonClicked(Button*) override;

	//Overrides for the Slider virtual methods
    void sliderValueChanged(Slider* slider) override;

	//Broadcaster invoked when a change in volume happens
    ActionBroadcaster VolumeChangedBroadcaster;
private:
	//Volume slider component
    Slider volumeSlider;
	//Mute toggle button component
    ToggleButton muteButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MixerChannel)
};



