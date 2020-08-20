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
    TrackSelectedToPlayLeftListener([this](const String& message) { TrackSelectedToPlayCallback(message, this->leftPlayerComponent); }),
    TrackSelectedToPlayRightListener([this](const String& message) { TrackSelectedToPlayCallback(message, this->rightPlayerComponent); }),
    LeftVolumeChangedListener([this](const String& message) { VolumeChangedCallback(message, leftPlayerComponent); }),
    RightVolumeChangedListener([this](const String& message) { VolumeChangedCallback(message, rightPlayerComponent); }) ,
	leftVuMeter(leftLevel),
	rightVuMeter(rightLevel)


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

    addAndMakeVisible(tooltipWindow);
    addAndMakeVisible(leftPlaylistComponent);
    addAndMakeVisible(rightPlaylistComponent);
    addAndMakeVisible(leftPlayerComponent);
    addAndMakeVisible(rightPlayerComponent);
    addAndMakeVisible(leftChannel);
    addAndMakeVisible(leftVuMeter);
    addAndMakeVisible(rightChannel);
    addAndMakeVisible(rightVuMeter);

    leftChannel.setVolume(1.0);
    rightChannel.setVolume(1.0);
	
    formatManager.registerBasicFormats();

    leftPlaylistComponent.TrackSelectedToPlayEventBroadcaster.addActionListener(&TrackSelectedToPlayLeftListener);
    rightPlaylistComponent.TrackSelectedToPlayEventBroadcaster.addActionListener(&TrackSelectedToPlayRightListener);

	leftChannel.VolumeChangedBroadcaster.addActionListener(&LeftVolumeChangedListener);
    rightChannel.VolumeChangedBroadcaster.addActionListener(&RightVolumeChangedListener);
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

	if(leftPlayer.isPlaying() || rightPlayer.isPlaying())
	{
        if (true) {
            const auto leftRmsLevel = bufferToFill.buffer->getRMSLevel(0, bufferToFill.startSample, bufferToFill.numSamples);
            const auto rightRmsLevel = bufferToFill.buffer->getRMSLevel(1, bufferToFill.startSample, bufferToFill.numSamples);
            const auto leftMagnitude = bufferToFill.buffer->getMagnitude(0, bufferToFill.startSample, bufferToFill.numSamples);
            const auto rightMagnitude = bufferToFill.buffer->getMagnitude(0, bufferToFill.startSample, bufferToFill.numSamples);
            leftLevel.set({ leftRmsLevel, leftMagnitude });
            rightLevel.set({ rightRmsLevel, rightMagnitude });
        }
	}else
	{
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

    // You can add your drawing code here!
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

void MainComponent::TrackSelectedToPlayCallback(const String& message, PlayerAggregateComponent& player) 
{
    player.setCurrentTrack(message);
}

void MainComponent::VolumeChangedCallback(const String& message, PlayerAggregateComponent& player)
{
    player.setGain(message.getDoubleValue());
}

