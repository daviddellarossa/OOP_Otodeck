/*
  ==============================================================================

    PlaylistAggregateComponent.cpp
    Created: 12 Aug 2020 9:59:38pm
    Author:  david

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistAggregateComponent.h"

#include "FileFormatException.h"


//==============================================================================
PlaylistAggregateComponent::PlaylistAggregateComponent() :
	//initialization of the listeners to call the proper Callback function
	AddFileListener([this](const String& message) {AddFileCallback(message); }),
	AddFolderListener([this](const String& message) {AddFolderCallback(message); }),
	DeleteFilesListener([this](const String& message) {DeleteFilesCallback(message); }),
	LoadPlaylistListener([this](const String& message) {LoadPlaylistCallback(message); }),
	SavePlaylistListener([this](const String& message) {SavePlaylistCallback(message); }),
    OpenFileInPlayerListener([this](const String& message) {OpenFileInPlayerCallback(message); }),
    ItemDoubleClickedListener([this](const String& message) {ItemDoubleClickedCallback(message); }),
    searchTextChangedListener([this](const String& message) { SearchTextChangedCallback(message); })
{

	addAndMakeVisible(this->playlistToolbar);
    addAndMakeVisible(this->playlistGrid);
    addAndMakeVisible(this->searchBox);

    playlistToolbar.setBounds(0, 0, getWidth(), getHeight());
    searchBox.setBounds(0, 0, getWidth(), getHeight());
    searchBox.setTextToShowWhenEmpty("Search...", Colours::grey);
	
	//Register EventListeners to PlaylistToolbar Broadcasters
    playlistToolbar.AddFileEventBroadcaster.addActionListener(&AddFileListener);
    playlistToolbar.AddFolderEventBroadcaster.addActionListener(&AddFolderListener);
    playlistToolbar.DeleteFilesEventBroadcaster.addActionListener(&DeleteFilesListener);
    playlistToolbar.LoadPlaylistEventBroadcaster.addActionListener(&LoadPlaylistListener);
    playlistToolbar.SavePlaylistEventBroadcaster.addActionListener(&SavePlaylistListener);
    playlistToolbar.OpenFileInPlayerEventBroadcaster.addActionListener(&OpenFileInPlayerListener);

    playlistGrid.getGridBoxModel().ItemDoubleClickedEventBroadcaster.addActionListener(&ItemDoubleClickedListener);

	searchBox.addListener(&searchTextChangedListener);
}

PlaylistAggregateComponent::~PlaylistAggregateComponent()
{
}

void PlaylistAggregateComponent::paint (juce::Graphics& g)
{

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistAggregateComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistAggregateComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //
    //
    Grid layout;

    layout.templateColumns = {
    Grid::TrackInfo(2_fr),
    Grid::TrackInfo(1_fr),
    };

    layout.templateRows = {
        Grid::TrackInfo(32_px),
        Grid::TrackInfo(1_fr),
    };

    layout.items = {
        GridItem(playlistToolbar).withArea(1, 1, 2, 2),
        GridItem(searchBox).withArea(1, 2, 2, 3),
        GridItem(playlistGrid).withArea(2, 1, 3, 3),
    };
    layout.performLayout(getLocalBounds());

}

void PlaylistAggregateComponent::AddFileCallback(const String& message)
{
    DBG(message);
    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
	
    WildcardFileFilter wildcardFilter(formatManager.getWildcardForAllFormats(), String(), "Audio files");

    FileBrowserComponent browser(FileBrowserComponent::canSelectFiles | FileBrowserComponent::openMode | FileBrowserComponent::canSelectMultipleItems,
        File::getSpecialLocation(File::SpecialLocationType::userHomeDirectory).getFullPathName(),
        &wildcardFilter,
        nullptr);
    
    FileChooserDialogBox dialogBox("Open some audio files",
        "Please choose some audio files that you want to import in the playlist...",
        browser,
        false,
        Colours::lightgrey);


	
    if (dialogBox.show())
    {
    	for(int counter = 0; counter < browser.getNumSelectedFiles() ; ++counter)
    	{
            File selectedFile = browser.getSelectedFile(counter);
    		
            playlistGrid.addTrack(               
                PlaylistGrid::TrackModel::FromFile(browser.getSelectedFile(counter).getFullPathName(), formatManager)
            );
    	}
    }
}

void PlaylistAggregateComponent::AddFolderCallback(const String& message) const
{
	//Not implemented deliberately. Available for possible future expansion
    DBG(message);
}

void PlaylistAggregateComponent::DeleteFilesCallback(const String& message)
{
    playlistGrid.removeSelectedTracks();
}

void PlaylistAggregateComponent::LoadPlaylistCallback(const String& message)
{

    WildcardFileFilter wildcardFilter("*" + PLAYLISTFILEEXTENSION, String(), "Oto files");

    FileBrowserComponent browser(FileBrowserComponent::canSelectFiles | FileBrowserComponent::openMode,
        File(APPFOLDERFULLPATH()) ,
        &wildcardFilter,
        nullptr);

    FileChooserDialogBox dialogBox("Open an Oto playlist file",
        "Please choose a playlist to import...",
        browser,
        false,
        Colours::lightgrey);

    if (!dialogBox.show())
    {
        return;
    }

    AlertWindow::showOkCancelBox(AlertWindow::WarningIcon, "Otodecks",
        "The current playlist will be replaced permanently. Continue?");

    playlistGrid.clearTracks();

    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();

	
	auto playlistFileInputStream = browser.getSelectedFile(0).createInputStream();

    while(!playlistFileInputStream->isExhausted())
    {
        auto line = playlistFileInputStream->readNextLine();
        File trackFile(line);
        if(!trackFile.existsAsFile())
        {
            DBG(line << " is not a valid file.");
            continue;
        }
        try
        {
            playlistGrid.addTrack(
                PlaylistGrid::TrackModel::FromFile(trackFile.getFullPathName(), formatManager)
            );
        }catch(FileFormatException ex)
        {
            DBG("File Format exception: " << ex.file);
        }
    }
}

void PlaylistAggregateComponent::SavePlaylistCallback(const String& message) const
{
    WildcardFileFilter wildcardFilter("*" + PLAYLISTFILEEXTENSION, String(), "Oto files");

    auto appFolder = File(APPFOLDERFULLPATH());
	
    if (!appFolder.exists() && appFolder.createDirectory().failed())
    {
        AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Otodecks",
            "Unable to create the application folder " + appFolder.getFullPathName());
    }
	
    FileBrowserComponent browser(FileBrowserComponent::canSelectFiles | FileBrowserComponent::warnAboutOverwriting | FileBrowserComponent::saveMode,
        appFolder,
        &wildcardFilter,
        nullptr);

    FileChooserDialogBox dialogBox("Save an Oto playlist file",
        "Save the current playlist into an Oto file...",
        browser,
        true,
        Colours::lightgrey);

    if (!dialogBox.show())
    {
        return;
    }
    if(browser.getSelectedFile(0).create().failed())
    {
        AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Otodecks",
            "Unable to create the playlist file " + browser.getSelectedFile(0).getFullPathName());
        return;
    }

    auto tracks = this->playlistGrid.getTracks();
    std::stringstream ss;
    std::for_each(tracks->begin(), tracks->end(), [&ss](const PlaylistGrid::TrackModel track) { ss << track.toString() << '\n'; });
	
	if(browser.getSelectedFile(0).replaceWithText(ss.str()))
	{
        AlertWindow::showMessageBox(AlertWindow::InfoIcon, "Otodecks",
            "Playlist file created successfully\n" + browser.getSelectedFile(0).getFullPathName());
        return;
	}
	
    AlertWindow::showMessageBox(AlertWindow::WarningIcon, "Otodecks",
        "Unable to edit the playlist file " + browser.getSelectedFile(0).getFullPathName());
	
}

void PlaylistAggregateComponent::OpenFileInPlayerCallback(const String& message)
{
	
    auto selectedIndices = playlistGrid.getSelectedRowsIndices();
    if (selectedIndices.getNumRanges() == 0)
        return;
	
    TrackSelectedToPlayEventBroadcaster.sendActionMessage(playlistGrid.getTracks()->at(selectedIndices.getRange(0).getStart()).filePath);
}

void PlaylistAggregateComponent::ItemDoubleClickedCallback(const String& message) const
{
    TrackSelectedToPlayEventBroadcaster.sendActionMessage(message);
    DBG("File double-clicked: " << message);
}

void PlaylistAggregateComponent::SearchTextChangedCallback(const String& message)
{
    playlistGrid.setSearchText(message);
    DBG(message);
}

const String PlaylistAggregateComponent::APPFOLDERNAME{ "OtoDecks" };
const String PlaylistAggregateComponent::PLAYLISTFILEEXTENSION{ ".oto" };
const String PlaylistAggregateComponent::APPFOLDERFULLPATH()
{
    std::stringstream ss;
    ss << File::addTrailingSeparator(File::getSpecialLocation(File::SpecialLocationType::userApplicationDataDirectory).getFullPathName());
    ss << APPFOLDERNAME;
    return ss.str();
}