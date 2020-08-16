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
    PlaylistGrid::TrackModel convertFileToTrack(const File& selectedFile, const std::unique_ptr<AudioFormatReader>& formatReader);

    void AddFileCallback(const String& message);
    void AddFolderCallback(const String& message);
    void DeleteFilesCallback(const String& message);
    void LoadPlaylistCallback(const String& message);
    void SavePlaylistCallback(const String& message);


private:

    class PlaylistActionListener : public ActionListener
    {
      
    public:
        PlaylistActionListener(
            const std::function<void(const String& message)>& callback
        ) : callback(callback)
        {

        }
        void actionListenerCallback(const String& message) override
        {
            this->callback(message);
        }
    private:
        std::function<void(const String& message)> callback;
    };

    const static String APPFOLDERNAME;
    const static String PLAYLISTFILEEXTENSION;
    const static String APPFOLDERFULLPATH();
	
    PlaylistGrid playlistGrid;
    PlaylistToolbar playlistToolbar;
	
    PlaylistActionListener AddFileListener;
    PlaylistActionListener AddFolderListener;
    PlaylistActionListener DeleteFilesListener;
    PlaylistActionListener LoadPlaylistListener;
    PlaylistActionListener SavePlaylistListener;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistAggregateComponent)
};
