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
class PlaylistToolbar  :
	public juce::Component,
    public Button::Listener
{
public:
    PlaylistToolbar();
    ~PlaylistToolbar() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(Button* button) override;

    ActionBroadcaster AddFileEventBroadcaster;
    ActionBroadcaster AddFolderEventBroadcaster;
    ActionBroadcaster DeleteFilesEventBroadcaster;
    ActionBroadcaster LoadPlaylistEventBroadcaster;
    ActionBroadcaster SavePlaylistEventBroadcaster;
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

            void getAllToolbarItemIds(Array <int>& ids) override;
            void getDefaultItemSet(Array <int>& ids) override;
            ToolbarItemComponent* createItem(int itemId) override;
            void setButtonListener(Listener*);
        private:
            OwnedArray <Drawable> iconsFromZipFile;
            StringArray iconNames;
            ToolbarButton* createButtonFromZipFileSVG(const int itemId, const String& text, const String& filename);
            Listener* buttonEventListener;
    };

    Toolbar toolbar;
    PlaylistToolbarItemFactory toolbarItemFactory;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistToolbar)
};
