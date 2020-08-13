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

 //   std::unique_ptr<XmlElement> svgXmlAddDocument(XmlDocument::parse(BinaryData::AddDocument_16x_svg)); // GET THE SVG AS A XML
 //   auto svgAddDocument = Drawable::createFromSVG(*svgXmlAddDocument); // GET THIS AS DRAWABLE
 //   
 //   
 //   ImageFileFormat::loadFrom(*svgAddDocument);
	////addFileButton.setButtonText("AddFile");
 //   addAndMakeVisible(*svgAddDocument);
 //   auto image = getImageFromAssets("imagename.ext");
 //   deleteFilesButton.setImages(true, true, true,
 //       image, 0.7f, Colours::transparentBlack,
 //       image, 1.0f, Colours::transparentBlack,
 //       image, 1.0f, Colours::transparentBlack,
 //       0.5f);

 //   addAndMakeVisible(this->addFileButton);
 //   addAndMakeVisible(this->addFolderButton);
 //   addAndMakeVisible(this->deleteFilesButton);
 //   addAndMakeVisible(this->loadPlaylistButton);
 //   addAndMakeVisible(this->savePlaylistButton);



    //toolbar.setStyle(Toolbar::ToolbarItemStyle::iconsWithText);

	
    addAndMakeVisible(&toolbar);
    toolbar.addDefaultItems(toolbarItemFactory);
}

PlaylistToolbar::~PlaylistToolbar()
{
}

void PlaylistToolbar::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistToolbar", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistToolbar::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //FlexBox controlLayout;
    //controlLayout.flexWrap = FlexBox::Wrap::noWrap;
    //controlLayout.flexDirection = FlexBox::Direction::row;
    //controlLayout.items.add(FlexItem(32.0f, 32.0f, this->addFileButton));
    //controlLayout.items.add(FlexItem(32.0f, 32.0f, this->addFolderButton));
    //controlLayout.items.add(FlexItem(32.0f, 32.0f, this->deleteFilesButton));
    //controlLayout.items.add(FlexItem(32.0f, 32.0f, this->loadPlaylistButton));
    //controlLayout.items.add(FlexItem(32.0f, 32.0f, this->savePlaylistButton));

    //controlLayout.performLayout(getLocalBounds().toFloat());
}

void PlaylistToolbar::PlaylistToolbarItemFactory::getAllToolbarItemIds(Array<int>& ids)
{
    ids.add(static_cast<int>(PlaylistToolbarItemIds::addFile));
    ids.add(static_cast<int>(PlaylistToolbarItemIds::addFolder));
    ids.add(static_cast<int>(PlaylistToolbarItemIds::deleteFiles));
    ids.add(static_cast<int>(PlaylistToolbarItemIds::loadPlaylist));
    ids.add(static_cast<int>(PlaylistToolbarItemIds::savePlaylist));
    ids.add(separatorBarId);
    ids.add(spacerId);
    ids.add(flexibleSpacerId);
}

void PlaylistToolbar::PlaylistToolbarItemFactory::getDefaultItemSet(Array<int>& ids)
{
    ids.add(static_cast<int>(PlaylistToolbarItemIds::addFile));
    ids.add(static_cast<int>(PlaylistToolbarItemIds::addFolder));
    ids.add(static_cast<int>(PlaylistToolbarItemIds::deleteFiles));
    ids.add(separatorBarId);
    ids.add(static_cast<int>(PlaylistToolbarItemIds::loadPlaylist));
    ids.add(static_cast<int>(PlaylistToolbarItemIds::savePlaylist));
}

ToolbarItemComponent* PlaylistToolbar::PlaylistToolbarItemFactory::createItem(int itemId)
{
	switch(itemId)
	{
        case static_cast<int>(PlaylistToolbarItemIds::addFile) :
            createButtonFromZipFileSVG(
				static_cast<int>(PlaylistToolbarItemIds::addFile),
                "Add file",
                "AddFile.svg"
            );
            break;
        case static_cast<int>(PlaylistToolbarItemIds::addFolder) :
            createButtonFromZipFileSVG(
                static_cast<int>(PlaylistToolbarItemIds::addFolder),
                "Add folder",
                "AddFolder.svg"
            );
            break;
		case static_cast<int>(PlaylistToolbarItemIds::deleteFiles) :
            createButtonFromZipFileSVG(
                static_cast<int>(PlaylistToolbarItemIds::deleteFiles),
                "Delete files",
                "Delete.svg"
            );
            break;
		case static_cast<int>(PlaylistToolbarItemIds::loadPlaylist) :
            createButtonFromZipFileSVG(
                static_cast<int>(PlaylistToolbarItemIds::loadPlaylist),
                "Load playlist",
                "LoadPlaylist.svg"
            );
            break;
		case static_cast<int>(PlaylistToolbarItemIds::savePlaylist) :
            createButtonFromZipFileSVG(
                static_cast<int>(PlaylistToolbarItemIds::savePlaylist),
                "Save playlist",
                "SavePlaylist.svg"
            );
            break;
		default:
            return nullptr;
	}
}

std::unique_ptr<ToolbarButton> PlaylistToolbar::PlaylistToolbarItemFactory::createButtonFromZipFileSVG(const int itemId,
	const String& text, const String& filename)
{
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

    return std::unique_ptr<ToolbarButton>{new ToolbarButton(
        itemId,
        text,
        iconsFromZipFile[iconNames.indexOf(filename)]->createCopy(),
        0
    )};
}
