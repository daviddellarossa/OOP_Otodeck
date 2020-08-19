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
	TrackSelectedToPlayLeftListener([this](const String& message) { TrackSelectedToPlayCallback(message, this->leftPlayerComponent); }),
    TrackSelectedToPlayRightListener([this](const String& message) { TrackSelectedToPlayCallback(message, this->rightPlayerComponent); }),
    SpeedChangedLeftListener([this](const String& message) { SpeedChangedCallback(message, leftPlayerComponent); }),
    SpeedChangedRightListener([this](const String& message) { SpeedChangedCallback(message, rightPlayerComponent); }),
    LeftVolumeChangedListener([this](const String& message) { VolumeChangedCallback(message, leftPlayerComponent); }),
    RightVolumeChangedListener([this](const String& message) { VolumeChangedCallback(message, rightPlayerComponent); }),
    leftPlayerComponent(leftPlayer, formatManager, thumbCache),
    rightPlayerComponent(rightPlayer, formatManager, thumbCache)


{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (1200, 900);

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
    addAndMakeVisible(mixerPanelComponent);
    addAndMakeVisible(leftPlaylistComponent);
    addAndMakeVisible(rightPlaylistComponent);
    addAndMakeVisible(leftPlayerComponent);
    addAndMakeVisible(rightPlayerComponent);
    addAndMakeVisible(leftScratchDock);
    addAndMakeVisible(rightScratchDock);

    //leftPlaylistComponent.setBounds(0, getHeight() / 2, getWidth(), getHeight() / 2);
    formatManager.registerBasicFormats();

    leftPlaylistComponent.TrackSelectedToPlayEventBroadcaster.addActionListener(&TrackSelectedToPlayLeftListener);
    rightPlaylistComponent.TrackSelectedToPlayEventBroadcaster.addActionListener(&TrackSelectedToPlayRightListener);

    leftScratchDock.SpeedChangedBroadcaster.addActionListener(&SpeedChangedLeftListener);
    rightScratchDock.SpeedChangedBroadcaster.addActionListener(&SpeedChangedRightListener);

    mixerPanelComponent.LeftVolumeChangedBroadcaster.addActionListener(&LeftVolumeChangedListener);
    mixerPanelComponent.RightVolumeChangedBroadcaster.addActionListener(&RightVolumeChangedListener);

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
    controlLayout.templateColumns = {
        Grid::TrackInfo(1_fr),
        Grid::TrackInfo(1_fr),
        Grid::TrackInfo(1_fr),
        Grid::TrackInfo(1_fr)
    };

    controlLayout.templateRows = {
		Grid::TrackInfo(1_fr),
        Grid::TrackInfo(3_fr),
		Grid::TrackInfo(1_fr),
        Grid::TrackInfo(2_fr),
		Grid::TrackInfo(3_fr),
    };

    controlLayout.items = {

        GridItem(leftScratchDock).withArea(2, 1, 4, 2),
		GridItem(rightScratchDock).withArea(2, 4, 4, 5),

        GridItem(mixerPanelComponent).withArea(1, 2, 4, 4),

        GridItem(leftPlayerComponent).withArea(4, 1, 4, 3),
		GridItem(rightPlayerComponent).withArea(4, 3, 4, 5),

        GridItem(leftPlaylistComponent).withArea(5, 1, 5, 3),
        GridItem(rightPlaylistComponent).withArea(5, 3, 5, 5),

    };

    controlLayout.performLayout(getLocalBounds());

}

void MainComponent::TrackSelectedToPlayCallback(const String& message, PlayerAggregateComponent& player) 
{
    player.setCurrentTrack(message);
}

void MainComponent::SpeedChangedCallback(const String& message, PlayerAggregateComponent& player)
{
	
    player.setSpeed(message.getDoubleValue());
}

void MainComponent::VolumeChangedCallback(const String& message, PlayerAggregateComponent& player)
{
    player.setGain(message.getDoubleValue());
}

