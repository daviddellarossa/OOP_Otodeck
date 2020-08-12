/*
  ==============================================================================

    PlaylistGridModel.h
    Created: 12 Aug 2020 10:01:01pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlaylistGridModel  : public juce::TableListBoxModel
{
public:
    PlaylistGridModel();
    ~PlaylistGridModel() override;



private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistGridModel)
};
