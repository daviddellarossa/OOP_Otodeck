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
/*
*/
class PlayerToolbar  :
	public juce::Component,
    public Button::Listener
{
public:
    PlayerToolbar();
    ~PlayerToolbar() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void buttonClicked(Button* button) override;

    ActionBroadcaster PlayEventBroadcaster;
    ActionBroadcaster PauseEventBroadcaster;
    ActionBroadcaster StopEventBroadcaster;

private:

    class PlayerToolbarItemFactory : public ToolbarItemFactory
    {
    public:
        PlayerToolbarItemFactory() = default;

    	enum class PlayerToolbarItemIds
    	{
    		stop = 0,
    		play = 1,
    		pause = 2,
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
    PlayerToolbarItemFactory toolbarItemFactory;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerToolbar)
};
