/*
  ==============================================================================

    PlaylistGrid.cpp
    Created: 12 Aug 2020 10:00:10pm
    Author:  david

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistGrid.h"

#include "FileFormatException.h"

//==============================================================================
PlaylistGrid::PlaylistGrid() :
    tracks{new std::vector<TrackModel>()},
	playlistDataGridBoxModel(this->tracks)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(playlistDataGrid);
    playlistDataGrid.setModel(&playlistDataGridBoxModel);
	
    playlistDataGrid.getHeader().addColumn("Track title", 1, 400);
    playlistDataGrid.getHeader().addColumn("Length", 2, 80);
    playlistDataGrid.getHeader().addColumn("Sample rate", 3, 100);

    formatManager.registerBasicFormats();
}

PlaylistGrid::~PlaylistGrid()
{
}

void PlaylistGrid::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

}

void PlaylistGrid::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    playlistDataGrid.setBounds(0, 0, getWidth(), getHeight());
}

void PlaylistGrid::addTrack(TrackModel track)
{
	for(auto iterator = tracks->begin(); iterator < tracks->end(); ++iterator)
	{
        if (iterator->filePath == track.filePath)
        {
            DBG("File already in playlist");
            return;
        }
	}
    tracks->push_back(track);
    this->playlistDataGrid.updateContent();
}

void PlaylistGrid::removeSelectedTracks()
{
    auto index = playlistDataGrid.getSelectedRow();
	
	if(index < tracks->size())
	{
        auto iterator = tracks->begin();
        iterator += index;
        tracks->erase(iterator);
	}
    this->playlistDataGrid.updateContent();
}

SparseSet<int> PlaylistGrid::getSelectedRowsIndices()
{
    return playlistDataGrid.getSelectedRows();
}

void PlaylistGrid::clearTracks()
{
    this->tracks->clear();
    this->playlistDataGrid.updateContent();
}

bool PlaylistGrid::isInterestedInFileDrag(const StringArray& files)
{
    if (files.size() == 0) return false;
    bool result = true;

    for (auto fileString : files)
    {
        File file(fileString);
        result &= (formatManager.findFormatForFileExtension(file.getFileExtension()) != nullptr);
    }
	
    return result;
}

void PlaylistGrid::filesDropped(const StringArray& files, int x, int y)
{
    if (files.size() == 0) return;
    for (auto fileString : files)
    {
        File file(fileString);
        if(formatManager.findFormatForFileExtension(file.getFileExtension()))
        {
            addTrack(TrackModel::fromFile(fileString, formatManager));
        }
    }
}

void PlaylistGrid::setSearchText(String text)
{
    playlistDataGridBoxModel.searchText = text;
    this->repaint();
}

PlaylistGrid::PlaylistTableListBoxModel& PlaylistGrid::getGridBoxModel()
{
    return this->playlistDataGridBoxModel;
}


std::shared_ptr<std::vector<PlaylistGrid::TrackModel>> PlaylistGrid::getTracks()const
{
    return this->tracks;
}

PlaylistGrid::PlaylistTableListBoxModel::PlaylistTableListBoxModel(const std::shared_ptr<std::vector<TrackModel>> trackTitles) : tracks(trackTitles)
{

}

int PlaylistGrid::PlaylistTableListBoxModel::getNumRows()
{
    return tracks->size();
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
    const auto track = tracks->at(rowNumber);
    const int hours = static_cast<int>(track.lengthInSeconds() / 3600);
    const int minutes = static_cast<int>(track.lengthInSeconds() / 60);
    const int seconds = static_cast<int>(track.lengthInSeconds() % 60);
    std::stringstream text;
	
	switch(columnId)
	{
    case 1:
        text << track.fileName;
        break;
    case 2:
		//Build a string for the length of the file
        text
			<< std::setfill('0') << std::setw(2) << hours << ":"
			<< std::setfill('0') << std::setw(2) <<minutes << ":"
			<< std::setfill('0') << std::setw(2) << seconds;
        break;
    case 3:
        text << track.sampleRate;
        break;
    default:
        break;
	}

	if(searchText.length()> 0 && track.fileName.contains(searchText))
	{
        graphics.setColour(Colours::red);
	}
	
    graphics.drawText(
        text.str(), 
        2,
        0,
        width - 4,
        height,
        Justification::centredLeft,
        true
    );
}


void PlaylistGrid::PlaylistTableListBoxModel::cellDoubleClicked(int rowNumber, int columnId, const MouseEvent& event)
{
    itemDoubleClickedEventBroadcaster.sendActionMessage(this->tracks.get()->at(rowNumber).filePath);
}

Component* PlaylistGrid::PlaylistTableListBoxModel::refreshComponentForCell(int rowNumber, int columnId,
	bool isRowSelected, Component* existingComponentToUpdate)
{
    return  existingComponentToUpdate;
}
unsigned PlaylistGrid::TrackModel::lengthInSeconds() const
{
    if (sampleRate != 0)
        return lengthInSamples / sampleRate;
    else
        return 0;
}

String PlaylistGrid::TrackModel::toString() const
{
    return this->filePath;
}

PlaylistGrid::TrackModel PlaylistGrid::TrackModel::fromFile(const String& filePath, AudioFormatManager& formatManager)
{
    File selectedFile(filePath);
    std::unique_ptr<AudioFormatReader> formatReader(formatManager.createReaderFor(selectedFile));

    if (formatReader == nullptr)
        throw FileFormatException{ selectedFile.getFullPathName() };
	
    PlaylistGrid::TrackModel track(
        selectedFile.getFileName(),
        selectedFile.getFullPathName(),
        formatReader->getFormatName(),
        formatReader->bitsPerSample,
        formatReader->numChannels,
        formatReader->sampleRate,
        formatReader->lengthInSamples
    );
    return track;
}

PlaylistGrid::TrackModel::TrackModel(
    const String& fileName,
    const String& filePath,
    const String& formatName,
    unsigned bitsPerSample,
    unsigned numChannels,
    double sampleRate,
    int64 lengthInSamples
) :
	fileName { fileName },
    filePath{ filePath },
    formatName{ formatName },
    bitsPerSample{ bitsPerSample },
    numChannels{ numChannels },
    sampleRate{ sampleRate },
    lengthInSamples{ lengthInSamples }
{
}
