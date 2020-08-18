/*
  ==============================================================================

    ScratchAggregateComponent.h
    Created: 18 Aug 2020 7:52:11am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ScratchAggregateComponent  :
	public juce::Component,
    public Slider::Listener
{
public:
    ScratchAggregateComponent();
    ~ScratchAggregateComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(Slider* slider) override;

    ActionBroadcaster SpeedChangedBroadcaster;
private:
    Slider speedSlider;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ScratchAggregateComponent)
};
