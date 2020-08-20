/*
  ==============================================================================

    PlayerToolbar.h
    Created: 16 Aug 2020 8:26:56am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================

/// <summary>
/// Toolbar to control the Player
/// </summary>
class PlayerToolbar  :
	public juce::Component,
    public Button::Listener
{
public:
    PlayerToolbar();
    ~PlayerToolbar() override;

	//Overloads for the methods inherited from Component
    void paint (juce::Graphics&) override;
    void resized() override;

	//Overload for the method inherited from Button::Listener
    void buttonClicked(Button* button) override;

	//Broadcaster for the Play Event
    ActionBroadcaster PlayEventBroadcaster;
	//Broadcaster for the Pause Event
    ActionBroadcaster PauseEventBroadcaster;
	//Broadcaster for the Stop Event
    ActionBroadcaster StopEventBroadcaster;

private:

    /// <summary>
    /// Class that inherits from ToolbarItemFactory.
    /// This is a factory for the elements to be created an set in the toolbar
    /// </summary>
    class PlayerToolbarItemFactory : public ToolbarItemFactory
    {
    public:
        PlayerToolbarItemFactory() = default;

    	enum class PlayerToolbarItemIds
    	{
    		stop = 1,
    		play = 2,
    		pause = 3,
    	};

    	//Overloads for the virtual methods inherited from ToolbarItemFactory
        void getAllToolbarItemIds(Array <int>& ids) override;
        void getDefaultItemSet(Array <int>& ids) override;
        ToolbarItemComponent* createItem(int itemId) override;

    	//Sets the Listener to be invoked when a button is clicked
        void setButtonListener(Listener*);
    private:
    	//Array containing the icons to be shown as images forth e toolbar buttons
        OwnedArray <Drawable> iconsFromZipFile;
    	//Array containing the names of the icons
        StringArray iconNames;
    	//This method creates and returns the buttons created, based on the input values
        ToolbarButton* createButtonFromZipFileSVG(const int itemId, const String& text, const String& filename);
    	//Listener attached to the newly created button, which is invoked when the buttons are clicked
        Listener* buttonEventListener;
    };

	//Instance of a Toolbar class
    Toolbar toolbar;
	//Instance of a ToolbarItemFactory class
    PlayerToolbarItemFactory toolbarItemFactory;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerToolbar)
};
