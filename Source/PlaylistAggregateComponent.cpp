/*
  ==============================================================================

    PlaylistAggregateComponent.cpp
    Created: 12 Aug 2020 9:59:38pm
    Author:  david

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistAggregateComponent.h"


//==============================================================================
PlaylistAggregateComponent::PlaylistAggregateComponent() :
	AddFileListener([this](const String& message) {AddFileCallback(message); }),
	AddFolderListener([this](const String& message) {AddFolderCallback(message); }),
	DeleteFilesListener([this](const String& message) {DeleteFilesCallback(message); }),
	LoadPlaylistListener([this](const String& message) {LoadPlaylistCallback(message); }),
	SavePlaylistListener([this](const String& message) {SavePlaylistCallback(message); }),
    ItemDoubleClickedListener([this](const String& message) {ItemDoubleClickedCallback(message); })
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	addAndMakeVisible(this->playlistToolbar);
    addAndMakeVisible(this->playlistGrid);
    playlistToolbar.setBounds(0, 0, getWidth(), getHeight());

	//Register EventListeners to PlaylistToolbar Broadcasters
    playlistToolbar.AddFileEventBroadcaster.addActionListener(&AddFileListener);
    playlistToolbar.AddFolderEventBroadcaster.addActionListener(&AddFolderListener);
    playlistToolbar.DeleteFilesEventBroadcaster.addActionListener(&DeleteFilesListener);
    playlistToolbar.LoadPlaylistEventBroadcaster.addActionListener(&LoadPlaylistListener);
    playlistToolbar.SavePlaylistEventBroadcaster.addActionListener(&SavePlaylistListener);

    playlistGrid.getGridBoxModel().ItemDoubleClickedEventBroadcaster.addActionListener(&ItemDoubleClickedListener);
}

PlaylistAggregateComponent::~PlaylistAggregateComponent()
{
}

void PlaylistAggregateComponent::paint (juce::Graphics& g)
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
    g.drawText ("PlaylistAggregateComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistAggregateComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //
    FlexBox controlLayout;
    controlLayout.flexWrap = FlexBox::Wrap::noWrap;
    controlLayout.flexDirection = FlexBox::Direction::column;
    controlLayout.items.add(FlexItem(static_cast<float>(getWidth()), 32.0f,playlistToolbar));
    controlLayout.items.add(FlexItem(playlistGrid).withMinHeight(100).withMaxHeight(getHeight()).withFlex(1));
    controlLayout.performLayout(getLocalBounds().toFloat());
   

}

PlaylistGrid::TrackModel PlaylistAggregateComponent::convertFileToTrack(const File& selectedFile, const std::unique_ptr<AudioFormatReader>& formatReader)
{
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

void PlaylistAggregateComponent::AddFileCallback(const String& message)
{


    DBG(message);
    WildcardFileFilter wildcardFilter("*.mp3", String(), "Mp3 files");

    FileBrowserComponent browser(FileBrowserComponent::canSelectFiles | FileBrowserComponent::openMode | FileBrowserComponent::canSelectMultipleItems,
        File::getSpecialLocation(File::SpecialLocationType::userHomeDirectory).getFullPathName(),
        &wildcardFilter,
        nullptr);
    
    FileChooserDialogBox dialogBox("Open some audio files",
        "Please choose some audio files that you want to import in the playlist...",
        browser,
        false,
        Colours::lightgrey);


    AudioFormatManager formatManager;
    formatManager.registerBasicFormats();
	
    if (dialogBox.show())
    {
    	for(int counter = 0; counter < browser.getNumSelectedFiles() ; ++counter)
    	{
            File selectedFile = browser.getSelectedFile(counter);

            playlistGrid.addTrack(
                convertFileToTrack(
	                browser.getSelectedFile(counter), 
	                std::unique_ptr<AudioFormatReader>(formatManager.createReaderFor(selectedFile))
                )
            );
    	}

    }
}

void PlaylistAggregateComponent::AddFolderCallback(const String& message) const
{
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

        playlistGrid.addTrack(
            convertFileToTrack(
                trackFile,
                std::unique_ptr<AudioFormatReader>(formatManager.createReaderFor(trackFile))
            )
        );
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

void PlaylistAggregateComponent::ItemDoubleClickedCallback(const String& message) const
{
    TrackSelectedToPlayEventBroadcaster.sendActionMessage(message);
    DBG("File double-clicked: " << message);
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