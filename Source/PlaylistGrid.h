/*
  ==============================================================================

    PlaylistGrid.h
    Created: 12 Aug 2020 10:00:10pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlaylistGrid  : public juce::Component
{
public:
    PlaylistGrid();
    ~PlaylistGrid() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistGrid)
};
