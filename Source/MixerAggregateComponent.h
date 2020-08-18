/*
  ==============================================================================

    MixerAggregateComponent.h
    Created: 18 Aug 2020 7:42:57am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class MixerAggregateComponent  : public juce::Component
{
public:
    MixerAggregateComponent();
    ~MixerAggregateComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MixerAggregateComponent)
};
