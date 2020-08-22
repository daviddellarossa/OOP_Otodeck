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

/// <summary>
/// Component that displays and controls the toolbar for the Playlist control
/// </summary>
class PlaylistToolbar  :
	public juce::Component,
    public Button::Listener
{
public:
    /// <summary>
    /// Constructor for the class. Creates an instance of the class
    /// </summary>
    PlaylistToolbar();
	
    ~PlaylistToolbar() override;

	//Overloads for the virtual methods inherited from the Component class
    void paint (juce::Graphics&) override;
    void resized() override;
	//=====================================================================

	//Overload for the virtual method inherited from the Button::Listener class
    void buttonClicked(Button* button) override;

	//Broadcaster for the events generated by the Toolbar buttons

    /// <summary>
    /// Broadcaster for the Add File event
    /// </summary>
    ActionBroadcaster addFileEventBroadcaster;
    /// <summary>
    /// Broadcaster for the Add Folder event
    /// </summary>
    ActionBroadcaster addFolderEventBroadcaster;
    /// <summary>
    /// Broadcaster for the Delete Files event
    /// </summary>
    ActionBroadcaster deleteFilesEventBroadcaster;
    /// <summary>
    /// Broadcaster for the Load Playlist event
    /// </summary>
    ActionBroadcaster loadPlaylistEventBroadcaster;
    /// <summary>
    /// Broadcaster for the Save Playlist event
    /// </summary>
    ActionBroadcaster savePlaylistEventBroadcaster;
    /// <summary>
    /// Broadcaster for the Open File In Player event
    /// </summary>
    ActionBroadcaster openFileInPlayerEventBroadcaster;
private:
    /// <summary>
    /// Factory for the PlaylistToolbar
    /// </summary>
    class PlaylistToolbarItemFactory : public ToolbarItemFactory
        {
        public:
            PlaylistToolbarItemFactory() = default;

            /// <summary>
			/// Enumeration of the available Toolbar buttons
			/// </summary>
            enum class PlaylistToolbarItemIds
            {
                addFile = 1,
                addFolder = 2,
                deleteFiles = 3,
                loadPlaylist = 4,
                savePlaylist = 5,
                openFileInPlayer = 6
            };

    		//Overloads for the virtual methods inherited from the base class
            void getAllToolbarItemIds(Array <int>& ids) override;
            void getDefaultItemSet(Array <int>& ids) override;
            ToolbarItemComponent* createItem(int itemId) override;
    	
            /// <summary>
            /// Listener to manage the events generated on the new buttons
            /// </summary>
            /// <param name="listener">Pointer to a listener.
            /// This instance is created and controlled outside of the class</param>
            void setButtonListener(Listener* listener);
        private:
    		//List of icons
            OwnedArray <Drawable> iconsFromZipFile;
    		//List of names of the icons
            StringArray iconNames;
            //This method creates and returns the buttons created, based on the input values
            ToolbarButton* createButtonFromZipFileSVG(const int itemId, const String& text, const String& filename);
            //Listener attached to the newly created button, which is invoked when the buttons are clicked
            Listener* buttonEventListener;
    };

    //Instance of a Toolbar class
    Toolbar toolbar;
    //Instance of a ToolbarItemFactory class
    PlaylistToolbarItemFactory toolbarItemFactory;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistToolbar)
};
