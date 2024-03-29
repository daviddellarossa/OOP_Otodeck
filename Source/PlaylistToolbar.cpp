/*
  ==============================================================================

    PlaylistToolbar.cpp
    Created: 12 Aug 2020 10:01:26pm
    Author:  david

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistToolbar.h"
#include <memory>

//==============================================================================
PlaylistToolbar::PlaylistToolbar()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    toolbarItemFactory.setButtonListener(this);
    
    addAndMakeVisible(toolbar);
    toolbar.addDefaultItems(toolbarItemFactory);
    toolbar.setBounds(0, 0, getWidth(), getHeight());
}

PlaylistToolbar::~PlaylistToolbar()
{
}

void PlaylistToolbar::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void PlaylistToolbar::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    toolbar.setBounds(0, 0, getWidth(), 30);
}

void PlaylistToolbar::buttonClicked(Button* button)
{
    auto toolbarButton = dynamic_cast<ToolbarButton*>(button);
	if(toolbarButton != nullptr)
	{
        //Invoke the proper Broadcaster for the event 
		switch(toolbarButton->getItemId())
		{
            case static_cast<int>(PlaylistToolbarItemFactory::PlaylistToolbarItemIds::addFile) :
                addFileEventBroadcaster.sendActionMessage("Add Files");
            break;
            case static_cast<int>(PlaylistToolbarItemFactory::PlaylistToolbarItemIds::addFolder) :
                addFolderEventBroadcaster.sendActionMessage("Add Folder");
            break;
            case static_cast<int>(PlaylistToolbarItemFactory::PlaylistToolbarItemIds::deleteFiles) :
                deleteFilesEventBroadcaster.sendActionMessage("Delete File");
            break;
            case static_cast<int>(PlaylistToolbarItemFactory::PlaylistToolbarItemIds::loadPlaylist) :
                loadPlaylistEventBroadcaster.sendActionMessage("Load Playlist");
            break;
            case static_cast<int>(PlaylistToolbarItemFactory::PlaylistToolbarItemIds::savePlaylist) :
                savePlaylistEventBroadcaster.sendActionMessage("Save Playlist");
            break;
            case static_cast<int>(PlaylistToolbarItemFactory::PlaylistToolbarItemIds::openFileInPlayer) :
                openFileInPlayerEventBroadcaster.sendActionMessage("Open File In Player");
                break;
            default:
            break;
		}
	}
}

void PlaylistToolbar::PlaylistToolbarItemFactory::getAllToolbarItemIds(Array<int>& ids)
{
    ids.add(static_cast<int>(PlaylistToolbarItemIds::addFile));
    ids.add(static_cast<int>(PlaylistToolbarItemIds::addFolder));
    ids.add(static_cast<int>(PlaylistToolbarItemIds::deleteFiles));
    ids.add(static_cast<int>(PlaylistToolbarItemIds::loadPlaylist));
    ids.add(static_cast<int>(PlaylistToolbarItemIds::savePlaylist));
    ids.add(static_cast<int>(PlaylistToolbarItemIds::openFileInPlayer));
    ids.add(separatorBarId);
    ids.add(spacerId);
    ids.add(flexibleSpacerId);
}

void PlaylistToolbar::PlaylistToolbarItemFactory::getDefaultItemSet(Array<int>& ids)
{
    ids.add(static_cast<int>(PlaylistToolbarItemIds::addFile));
    ids.add(static_cast<int>(PlaylistToolbarItemIds::deleteFiles));
    ids.add(separatorBarId);
    ids.add(flexibleSpacerId);
    ids.add(separatorBarId);
    ids.add(static_cast<int>(PlaylistToolbarItemIds::openFileInPlayer));
    ids.add(separatorBarId);
    ids.add(flexibleSpacerId);
    ids.add(separatorBarId);
    ids.add(static_cast<int>(PlaylistToolbarItemIds::loadPlaylist));
    ids.add(static_cast<int>(PlaylistToolbarItemIds::savePlaylist));
}

ToolbarItemComponent* PlaylistToolbar::PlaylistToolbarItemFactory::createItem(int itemId)
{
	switch(itemId)
	{
        case static_cast<int>(PlaylistToolbarItemIds::addFile) :
            return createButtonFromZipFileSVG(
                itemId,
                "Add file",
                "AddFile.svg"
            );
        case static_cast<int>(PlaylistToolbarItemIds::addFolder) :
            return createButtonFromZipFileSVG(
                itemId,
                "Add folder",
                "AddFolder.svg"
            );
		case static_cast<int>(PlaylistToolbarItemIds::deleteFiles) :
            return createButtonFromZipFileSVG(
                itemId,
                "Delete files",
                "Delete.svg"
            );
		case static_cast<int>(PlaylistToolbarItemIds::loadPlaylist) :
            return createButtonFromZipFileSVG(
                itemId,
                "Load playlist",
                "LoadPlaylist.svg"
            );
		case static_cast<int>(PlaylistToolbarItemIds::savePlaylist) :
            return createButtonFromZipFileSVG(
                itemId,
                "Save playlist",
                "SavePlaylist.svg"
            );
            case static_cast<int>(PlaylistToolbarItemIds::openFileInPlayer) :
                return createButtonFromZipFileSVG(
                    itemId,
                    "Open File in player",
                    "LoadFileInPlayer.svg"
                );

		default:
            return nullptr;
	}
}

void PlaylistToolbar::PlaylistToolbarItemFactory::setButtonListener(Listener* listener)
{
    this->buttonEventListener = listener;
}

ToolbarButton* PlaylistToolbar::PlaylistToolbarItemFactory::createButtonFromZipFileSVG(const int itemId,
                                                                                       const String& text, const String& filename)
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
    if(this->buttonEventListener != nullptr)
    {
        button->addListener(buttonEventListener);
    }
    return button;
}
