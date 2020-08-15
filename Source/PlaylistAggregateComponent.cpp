/*
  ==============================================================================

    PlaylistAggregateComponent.cpp
    Created: 12 Aug 2020 9:59:38pm
    Author:  david

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistAggregateComponent.h"
#include "PlaylistGridModel.h"

//==============================================================================
PlaylistAggregateComponent::PlaylistAggregateComponent() :
	AddFileListener([this](const String& message) {AddFileCallback(message); }),
	AddFolderListener([this](const String& message) {AddFolderCallback(message); }),
	DeleteFilesListener([this](const String& message) {DeleteFilesCallback(message); }),
	LoadPlaylistListener([this](const String& message) {LoadPlaylistCallback(message); }),
	SavePlaylistListener([this](const String& message) {SavePlaylistCallback(message); })
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

void PlaylistAggregateComponent::AddFileCallback(const String& message)
{


    DBG(message);
    WildcardFileFilter wildcardFilter("*.mp3", String(), "Mp3 files");

    FileBrowserComponent browser(FileBrowserComponent::canSelectFiles | FileBrowserComponent::openMode | FileBrowserComponent::canSelectMultipleItems,
        File(),
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
            std::unique_ptr<AudioFormatReader> formatReader(formatManager.createReaderFor(selectedFile));

            PlaylistGrid::TrackModel track(
                selectedFile.getFileName(),
                selectedFile.getFullPathName(),
                formatReader->getFormatName(),
                formatReader->bitsPerSample,
                formatReader->numChannels,
                formatReader->sampleRate,
                formatReader->lengthInSamples
            );
            playlistGrid.addTrack(track);
    	}

    }
}

void PlaylistAggregateComponent::AddFolderCallback(const String& message)
{
    DBG(message);
}

void PlaylistAggregateComponent::DeleteFilesCallback(const String& message)
{
    DBG(message);
}

void PlaylistAggregateComponent::LoadPlaylistCallback(const String& message)
{
    DBG(message);
}

void PlaylistAggregateComponent::SavePlaylistCallback(const String& message)
{
    DBG(message);
}

