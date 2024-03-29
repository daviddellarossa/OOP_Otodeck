/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() :
    leftPlayer(formatManager),
    rightPlayer(formatManager),
    leftPlayerComponent(leftPlayer, formatManager, thumbCache),
    rightPlayerComponent(rightPlayer, formatManager, thumbCache),
    trackSelectedToPlayLeftListener([this](const String& message) { trackSelectedToPlayCallback(message, this->leftPlayerComponent); }),
    trackSelectedToPlayRightListener([this](const String& message) { trackSelectedToPlayCallback(message, this->rightPlayerComponent); }),
    leftVolumeChangedListener([this](const String& message) { volumeChangedCallback(message, leftPlayerComponent); }),
    rightVolumeChangedListener([this](const String& message) { volumeChangedCallback(message, rightPlayerComponent); }) ,
	leftVuMeter(leftLevel, "L"),
	rightVuMeter(rightLevel, "R")
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (1200, 600);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }  
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }

    formatManager.registerBasicFormats();

    addAndMakeVisible(tooltipWindow);
    addAndMakeVisible(leftPlaylistComponent);
    addAndMakeVisible(rightPlaylistComponent);
    addAndMakeVisible(leftPlayerComponent);
    addAndMakeVisible(rightPlayerComponent);
    addAndMakeVisible(leftChannel);
    addAndMakeVisible(leftVuMeter);
    addAndMakeVisible(rightChannel);
    addAndMakeVisible(rightVuMeter);

	//Set initial volume on MixerChannels
    leftChannel.setVolume(1.0);
    rightChannel.setVolume(1.0);

	//Attach Listeners to PlaylistAggregateComponents' Broadcasters
    leftPlaylistComponent.trackSelectedToPlayEventBroadcaster.addActionListener(&trackSelectedToPlayLeftListener);
    rightPlaylistComponent.trackSelectedToPlayEventBroadcaster.addActionListener(&trackSelectedToPlayRightListener);

	//Attach Listeners to MixerChannels' Broadcasters
	leftChannel.volumeChangedBroadcaster.addActionListener(&leftVolumeChangedListener);
    rightChannel.volumeChangedBroadcaster.addActionListener(&rightVolumeChangedListener);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    leftPlayer.prepareToPlay(samplesPerBlockExpected, sampleRate);
    rightPlayer.prepareToPlay(samplesPerBlockExpected, sampleRate);	
    
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    mixerSource.addInputSource(&leftPlayer, false);
    mixerSource.addInputSource(&rightPlayer, false);
 }
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);

	//Calculate levels for VuMeters
	//Execute the calculation only if there is at least one player running
	if(leftPlayer.isPlaying() || rightPlayer.isPlaying())
	{
        const auto leftRmsLevel = bufferToFill.buffer->getRMSLevel(0, bufferToFill.startSample, bufferToFill.numSamples);
        const auto rightRmsLevel = bufferToFill.buffer->getRMSLevel(1, bufferToFill.startSample, bufferToFill.numSamples);
        const auto leftMagnitude = bufferToFill.buffer->getMagnitude(0, bufferToFill.startSample, bufferToFill.numSamples);
        const auto rightMagnitude = bufferToFill.buffer->getMagnitude(0, bufferToFill.startSample, bufferToFill.numSamples);
		//Set the values in the thread-safe Atomic wrapper to be read from the VuMeters, which run in a different thread
        leftLevel.set({ leftRmsLevel, leftMagnitude });
        rightLevel.set({ rightRmsLevel, rightMagnitude });
	}else
	{
		//If there is nothing playing, set the levels to 0
        leftLevel.set({ 0.0, 0.0 });
        rightLevel.set({ 0.0, 0.0 });
	}
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
    leftPlayer.releaseResources();
    rightPlayer.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    Array<Grid::TrackInfo> columns;

    Grid controlLayout;
    controlLayout.justifyContent = Grid::JustifyContent::spaceAround;
    controlLayout.alignContent = Grid::AlignContent::spaceAround;
    controlLayout.justifyItems = Grid::JustifyItems::center;
    controlLayout.alignItems = Grid::AlignItems::center;
	
    controlLayout.templateColumns = {
        Grid::TrackInfo(1_fr),
        Grid::TrackInfo(64_px),
        Grid::TrackInfo(32_px),
        Grid::TrackInfo(32_px),
        Grid::TrackInfo(64_px),
        Grid::TrackInfo(1_fr)
    };

    controlLayout.templateRows = {
		Grid::TrackInfo(1_fr),
        Grid::TrackInfo(1_fr),
    };

    controlLayout.items = {
        GridItem(leftChannel).withArea(1, 2, 2, 3),
        GridItem(leftVuMeter).withArea(1, 3, 2, 4).withJustifySelf(GridItem::JustifySelf::center).withAlignSelf(GridItem::AlignSelf::center),
        GridItem(rightVuMeter).withArea(1, 4, 2, 5).withJustifySelf(GridItem::JustifySelf::center).withAlignSelf(GridItem::AlignSelf::center),
        GridItem(rightChannel).withArea(1, 5, 2, 6),
        GridItem(leftPlayerComponent).withArea(1, 1, 2, 2),
		GridItem(rightPlayerComponent).withArea(1, 6, 2, 7),
        GridItem(leftPlaylistComponent).withArea(2, 1, 3, 4),
        GridItem(rightPlaylistComponent).withArea(2, 4, 3, 7),
    };

    controlLayout.performLayout(getLocalBounds());
}

void MainComponent::trackSelectedToPlayCallback(const String& message, PlayerAggregateComponent& player) 
{
    player.setCurrentTrack(message);
}

void MainComponent::volumeChangedCallback(const String& message, PlayerAggregateComponent& player)
{
    player.setGain(message.getDoubleValue());
}

