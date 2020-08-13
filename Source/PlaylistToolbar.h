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
	class PlaylistToolbarItemFactory : public ToolbarItemFactory
	{
	public:
        PlaylistToolbarItemFactory() = default;

        enum class PlaylistToolbarItemIds
        {
	        addFile = 1,
        	addFolder = 2,
        	deleteFiles = 3,
        	loadPlaylist = 4,
        	savePlaylist = 5
        };

        void getAllToolbarItemIds(Array <int>& ids);
        void getDefaultItemSet(Array <int>& ids);
        ToolbarItemComponent* createItem(int itemId);
	private:
        OwnedArray <Drawable> iconsFromZipFile;
        StringArray iconNames;
        std::unique_ptr<ToolbarButton> createButtonFromZipFileSVG(const int itemId, const String& text, const String& filename);
	};
    //TextButton addFileButton{"AddFile"};
    //TextButton addFolderButton{"AddFolder"};
    //ImageButton deleteFilesButton;
    //ImageButton savePlaylistButton;
    //ImageButton loadPlaylistButton;
    Toolbar toolbar;
    PlaylistToolbarItemFactory toolbarItemFactory;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistToolbar)
};
