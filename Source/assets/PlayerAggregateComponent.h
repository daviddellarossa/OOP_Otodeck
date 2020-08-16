/*
  ==============================================================================

    PlayerAggregateComponent.h
    Created: 16 Aug 2020 8:14:25am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlayerAggregateComponent  : public juce::Component
{
public:
    PlayerAggregateComponent();
    ~PlayerAggregateComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerAggregateComponent)
};
