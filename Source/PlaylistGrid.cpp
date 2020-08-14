/*
  ==============================================================================

    PlaylistGrid.cpp
    Created: 12 Aug 2020 10:00:10pm
    Author:  david

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistGrid.h"

//==============================================================================
PlaylistGrid::PlaylistGrid() :
    trackTitles{new std::vector<std::string>()},
	playlistDataGridBoxModel(this->trackTitles)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(playlistDataGrid);
    playlistDataGrid.setModel(&playlistDataGridBoxModel);
	
    playlistDataGrid.getHeader().addColumn("Track title", 1, 400);
    playlistDataGrid.getHeader().addColumn("", 2, 200);

	//Mock values inserted into the list
    trackTitles->push_back("Track 1");
    trackTitles->push_back("Track 2");
    trackTitles->push_back("Track 3");
    trackTitles->push_back("Track 4");
}

PlaylistGrid::~PlaylistGrid()
{
}

void PlaylistGrid::paint (juce::Graphics& g)
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
    g.drawText ("PlaylistGrid", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistGrid::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    playlistDataGrid.setBounds(0, 0, getWidth(), getHeight());
}

PlaylistGrid::PlaylistTableListBoxModel::PlaylistTableListBoxModel(const std::shared_ptr<std::vector<std::string>> trackTitles) : trackTitles(trackTitles)
{
    //this->trackTitles = trackTitles;
}

int PlaylistGrid::PlaylistTableListBoxModel::getNumRows()
{
    return trackTitles->size();
}

void PlaylistGrid::PlaylistTableListBoxModel::paintRowBackground(Graphics& graphics, int rowNumber, int width, int height,
                                                                 bool rowIsSelected)
{
    if (rowIsSelected)
    {
        graphics.fillAll(Colours::orange);
    }
    else
    {
        graphics.fillAll(Colours::darkgrey);
    }
}

void PlaylistGrid::PlaylistTableListBoxModel::paintCell(Graphics& graphics, int rowNumber, int columnId, int width, int height,
	bool rowIsSelected)
{
    graphics.drawText(
        trackTitles->at(rowNumber), // we will change this later
        2,
        0,
        width - 4,
        height,
        Justification::centredLeft,
        true
    );
}

void PlaylistGrid::PlaylistTableListBoxModel::cellClicked(int rowNumber, int columnId, const MouseEvent&)
{
    DBG("Cell clicked");
}

Component* PlaylistGrid::PlaylistTableListBoxModel::refreshComponentForCell(int rowNumber, int columnId,
	bool isRowSelected, Component* existingComponentToUpdate)
{
    //if (columnId == 2)
    //{
    //    if (existingComponentToUpdate == nullptr)
    //    {
    //        TextButton* btn = new TextButton("play");
    //        btn->addListener(this);
    //        String id{ std::to_string(rowNumber) };
    //        btn->setComponentID(id);

    //        existingComponentToUpdate = btn;
    //    }
    //}
    return  existingComponentToUpdate;
}
