/*
  ==============================================================================

    PlaylistAggregateComponent.h
    Created: 12 Aug 2020 9:59:38pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PlaylistMediator.h"
#include "PlaylistGrid.h"
#include "PlaylistToolbar.h"

//==============================================================================
/*
*/
class PlaylistAggregateComponent  : public juce::Component
{
public:
    PlaylistAggregateComponent();
    ~PlaylistAggregateComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    PlaylistMediator playlistMediator;
    PlaylistGrid playlistGrid;
    PlaylistToolbar playlistToolbar;
    //FlexBox flexBox;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistAggregateComponent)
};
