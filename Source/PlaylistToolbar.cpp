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

    std::unique_ptr<XmlElement> svgXmlAddDocument(XmlDocument::parse(BinaryData::AddDocument_16x_svg)); // GET THE SVG AS A XML
    auto svgAddDocument = Drawable::createFromSVG(*svgXmlAddDocument); // GET THIS AS DRAWABLE

	
	addFileButton.setButtonText("AddFile");
    //addAndMakeVisible(*svgAddDocument);
    addAndMakeVisible(this->addFileButton);
    addAndMakeVisible(this->addFolderButton);
    addAndMakeVisible(this->deleteFilesButton);
    addAndMakeVisible(this->loadPlaylistButton);
    addAndMakeVisible(this->savePlaylistButton);

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
    FlexBox controlLayout;
    controlLayout.flexWrap = FlexBox::Wrap::noWrap;
    controlLayout.flexDirection = FlexBox::Direction::row;
    controlLayout.items.add(FlexItem(32.0f, 32.0f, this->addFileButton));
    controlLayout.items.add(FlexItem(32.0f, 32.0f, this->addFolderButton));
    controlLayout.items.add(FlexItem(32.0f, 32.0f, this->deleteFilesButton));
    controlLayout.items.add(FlexItem(32.0f, 32.0f, this->loadPlaylistButton));
    controlLayout.items.add(FlexItem(32.0f, 32.0f, this->savePlaylistButton));

    controlLayout.performLayout(getLocalBounds().toFloat());
}
