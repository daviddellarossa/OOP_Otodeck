/*
  ==============================================================================

    PlayerToolbar.cpp
    Created: 16 Aug 2020 8:26:56am
    Author:  david

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayerToolbar.h"

//==============================================================================
PlayerToolbar::PlayerToolbar()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    toolbarItemFactory.setButtonListener(this);

    addAndMakeVisible(toolbar);
    toolbar.addDefaultItems(toolbarItemFactory);
    toolbar.setBounds(0, 0, getWidth(), getHeight());
}

PlayerToolbar::~PlayerToolbar()
{
}

void PlayerToolbar::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

}


void PlayerToolbar::buttonClicked(Button* button)
{
    auto toolbarButton = dynamic_cast<ToolbarButton*>(button);
    if (toolbarButton != nullptr)
    {
    	//Check which button has been clicked and invoke the relative broadcaster
    	switch(toolbarButton->getItemId())
    	{
            case static_cast<int>(PlayerToolbarItemFactory::PlayerToolbarItemIds::pause) :
                pauseEventBroadcaster.sendActionMessage("Pause");
                break;
            case static_cast<int>(PlayerToolbarItemFactory::PlayerToolbarItemIds::play) :
                playEventBroadcaster.sendActionMessage("Play");
                break;
            case static_cast<int>(PlayerToolbarItemFactory::PlayerToolbarItemIds::stop) :
                stopEventBroadcaster.sendActionMessage("Stop");
                break;
            default:
            break;
    	}
    }
}

void PlayerToolbar::PlayerToolbarItemFactory::getAllToolbarItemIds(Array<int>& ids)
{
    ids.add(static_cast<int>(PlayerToolbarItemIds::play));
    ids.add(static_cast<int>(PlayerToolbarItemIds::pause));
    ids.add(static_cast<int>(PlayerToolbarItemIds::stop));
    ids.add(separatorBarId);
    ids.add(spacerId);
    ids.add(flexibleSpacerId);
}

void PlayerToolbar::PlayerToolbarItemFactory::getDefaultItemSet(Array<int>& ids)
{
    ids.add(static_cast<int>(PlayerToolbarItemIds::play));
    ids.add(static_cast<int>(PlayerToolbarItemIds::pause));
    ids.add(spacerId);
    ids.add(static_cast<int>(PlayerToolbarItemIds::stop));
}

ToolbarItemComponent* PlayerToolbar::PlayerToolbarItemFactory::createItem(int itemId)
{
    switch (itemId)
    {
        case static_cast<int>(PlayerToolbarItemIds::play) :
            return createButtonFromZipFileSVG(
                itemId,
                "Play",
                "Run.svg"
            );
        case static_cast<int>(PlayerToolbarItemIds::pause) :
            return createButtonFromZipFileSVG(
                itemId,
                "Pause",
                "Pause.svg"
            );
        case static_cast<int>(PlayerToolbarItemIds::stop) :
            return createButtonFromZipFileSVG(
                itemId,
                "Stop",
                "Stop.svg"
            );

        default:
            return nullptr;
    }
}

void PlayerToolbar::PlayerToolbarItemFactory::setButtonListener(Listener* listener)
{
    this->buttonEventListener = listener;
}

ToolbarButton* PlayerToolbar::PlayerToolbarItemFactory::createButtonFromZipFileSVG(const int itemId, const String& text,
	const String& filename)
{
	//Load the icon from memory. The icons are expected to be in svg format
    if (iconsFromZipFile.size() == 0)
    {
        // If we've not already done so, load all the images from the zip file..
        MemoryInputStream iconsFileStream(BinaryData::Icons_zip, BinaryData::Icons_zipSize, false);
        ZipFile icons(&iconsFileStream, false);

        for (int i = 0; i < icons.getNumEntries(); ++i)
        {
            ScopedPointer<InputStream> svgFileStream(icons.createStreamForEntry(i));

            if (svgFileStream != 0)
            {
                iconNames.add(icons.getEntry(i)->filename);
                iconsFromZipFile.add(Drawable::createFromImageDataStream(*svgFileStream));
            }
        }
    }
    auto button = new ToolbarButton(
        itemId,
        text,
        iconsFromZipFile[iconNames.indexOf(filename)]->createCopy(),
        nullptr
    );

	//attach the tooltip to the button
    button->setTooltip(text);

	//attach the listener to the new button
    if (this->buttonEventListener != nullptr)
    {
        button->addListener(buttonEventListener);
    }
    return button;
}

void PlayerToolbar::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    toolbar.setBounds(0, 0, getWidth(), 30);
}
