/*
  ==============================================================================

    PlaylistAggregateComponent.h
    Created: 12 Aug 2020 9:59:38pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PlaylistGrid.h"
#include "PlaylistToolbar.h"
#include "ExternalCallbackActionListener.h"

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

    void AddFileCallback(const String& message);
    void AddFolderCallback(const String& message) const;
    void DeleteFilesCallback(const String& message);
    void LoadPlaylistCallback(const String& message);
    void SavePlaylistCallback(const String& message) const;

    void ItemDoubleClickedCallback(const String& message) const;

    ActionBroadcaster TrackSelectedToPlayEventBroadcaster;
private:


    PlaylistGrid::TrackModel convertFileToTrack(const File& selectedFile, const std::unique_ptr<AudioFormatReader>& formatReader);

    const static String APPFOLDERNAME;
    const static String PLAYLISTFILEEXTENSION;
    const static String APPFOLDERFULLPATH();
	
    PlaylistGrid playlistGrid;
    PlaylistToolbar playlistToolbar;
	
    ExternalCallbackActionListener AddFileListener;
    ExternalCallbackActionListener AddFolderListener;
    ExternalCallbackActionListener DeleteFilesListener;
    ExternalCallbackActionListener LoadPlaylistListener;
    ExternalCallbackActionListener SavePlaylistListener;

    ExternalCallbackActionListener ItemDoubleClickedListener;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistAggregateComponent)
};
