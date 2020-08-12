/*
  ==============================================================================

    PlaylistToolbar.h
    Created: 12 Aug 2020 10:01:26pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlaylistToolbar  : public juce::Component
{
public:
    PlaylistToolbar();
    ~PlaylistToolbar() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    ImageButton addFileButton;
    ImageButton addFolderButton;
    ImageButton deleteFilesButton;
    ImageButton savePlaylistButton;
    ImageButton loadPlaylistButton;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistToolbar)
};
