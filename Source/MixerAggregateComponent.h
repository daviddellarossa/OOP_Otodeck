/*
  ==============================================================================

    MixerAggregateComponent.h
    Created: 18 Aug 2020 7:42:57am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "ExternalCallbackSliderListener.h"
#include "MixerChannel.h"

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

    void volumeChangedCallback(double value, ActionBroadcaster& broadcaster) const;

    ActionBroadcaster LeftVolumeChangedBroadcaster;
    ActionBroadcaster RightVolumeChangedBroadcaster;

private:

    ExternalCallbackSliderListener LeftVolumeChangedListener;
    ExternalCallbackSliderListener RightVolumeChangedListener;

    MixerChannel leftChannel;
    MixerChannel rightChannel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MixerAggregateComponent)
};
