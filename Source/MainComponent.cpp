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
    //SpeedChangedLeftListener([this](const String& message) { SpeedChangedCallback(message, leftPlayerComponent); }),
    //SpeedChangedRightListener([this](const String& message) { SpeedChangedCallback(message, rightPlayerComponent); }),
    LeftVolumeChangedListener([this](const String& message) { VolumeChangedCallback(message, leftPlayerComponent); }),
    //RightVolumeChangedListener([this](const String& message) { VolumeChangedCallback(message, rightPlayerComponent); }),
    leftPlayerComponent(leftPlayer, formatManager, thumbCache),
    rightPlayerComponent(rightPlayer, formatManager, thumbCache) ,
	leftVuMeter(leftLevel)
    //LeftVolumeChangedListener1([this](double value) { volumeChangedCallback1(value); }),
    //leftChannel(&LeftVolumeChangedListener1)


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
    //addAndMakeVisible(mixerPanelComponent);
    addAndMakeVisible(leftPlaylistComponent);
    addAndMakeVisible(rightPlaylistComponent);
    addAndMakeVisible(leftPlayerComponent);
    addAndMakeVisible(rightPlayerComponent);
    //addAndMakeVisible(leftScratchDock);
    //addAndMakeVisible(rightScratchDock);
    addAndMakeVisible(leftChannel);
    addAndMakeVisible(leftVuMeter);
	
    leftChannel.setVolume(1.0);
    //leftPlaylistComponent.setBounds(0, getHeight() / 2, getWidth(), getHeight() / 2);
    formatManager.registerBasicFormats();

    leftPlaylistComponent.TrackSelectedToPlayEventBroadcaster.addActionListener(&TrackSelectedToPlayLeftListener);
    rightPlaylistComponent.TrackSelectedToPlayEventBroadcaster.addActionListener(&TrackSelectedToPlayRightListener);

    //leftScratchDock.SpeedChangedBroadcaster.addActionListener(&SpeedChangedLeftListener);
    //rightScratchDock.SpeedChangedBroadcaster.addActionListener(&SpeedChangedRightListener);

    //mixerPanelComponent.LeftVolumeChangedBroadcaster.addActionListener(&LeftVolumeChangedListener);
    //mixerPanelComponent.RightVolumeChangedBroadcaster.addActionListener(&RightVolumeChangedListener);

	leftChannel.VolumeChangedBroadcaster.addActionListener(&LeftVolumeChangedListener);

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
    //const MessageManagerLock mmLock;

	if(leftPlayer.isPlaying() || rightPlayer.isPlaying())
	{
        if (true) {
            auto leftRmsLevel = bufferToFill.buffer->getRMSLevel(0, bufferToFill.startSample, bufferToFill.numSamples/2);
            auto rightLevel = bufferToFill.buffer->getRMSLevel(1, bufferToFill.startSample, bufferToFill.numSamples);
            auto leftMagnitude = bufferToFill.buffer->getMagnitude(0, bufferToFill.startSample, bufferToFill.numSamples/2);
            auto rightMagnitude = bufferToFill.buffer->getMagnitude(0, bufferToFill.startSample, bufferToFill.numSamples);
            //VuMeter::Level level{ leftLevel, leftMagnitude };
            leftLevel.set({ leftRmsLevel, leftMagnitude });
        	//leftVuMeter.setLevel(leftLevel);
        }
	}else
	{
        leftLevel.set({ 0.0, 0.0 });
        //leftVuMeter.setLevel(0.0);
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
        Grid::TrackInfo(3_fr),
        Grid::TrackInfo(1_fr),
        Grid::TrackInfo(1_fr),
        Grid::TrackInfo(3_fr)
    };

    controlLayout.templateRows = {
		Grid::TrackInfo(1_fr),
        Grid::TrackInfo(1_fr),
		//Grid::TrackInfo(1_fr),
  //      Grid::TrackInfo(2_fr),
		//Grid::TrackInfo(3_fr),
    };

    controlLayout.items = {

        //      GridItem(leftScratchDock).withArea(2, 1, 4, 2),
              //GridItem(rightScratchDock).withArea(2, 4, 4, 5),

        //      GridItem(mixerPanelComponent).withArea(1, 2, 4, 4),

        GridItem(leftChannel).withArea(1, 2, 2, 3),
        GridItem(leftVuMeter).withArea(1, 3, 2, 4).withJustifySelf(GridItem::JustifySelf::center).withAlignSelf(GridItem::AlignSelf::center),


        GridItem(leftPlayerComponent).withArea(1, 1, 2, 2),
		GridItem(rightPlayerComponent).withArea(1, 4, 2, 5),

        GridItem(leftPlaylistComponent).withArea(2, 1, 3, 3),
        GridItem(rightPlaylistComponent).withArea(2, 3, 3, 5),

    };

    controlLayout.performLayout(getLocalBounds());

}

void MainComponent::TrackSelectedToPlayCallback(const String& message, PlayerAggregateComponent& player) 
{
    player.setCurrentTrack(message);
}

//void MainComponent::SpeedChangedCallback(const String& message, PlayerAggregateComponent& player)
//{
//	
//    player.setSpeed(message.getDoubleValue());
//}

void MainComponent::VolumeChangedCallback(const String& message, PlayerAggregateComponent& player)
{
    player.setGain(message.getDoubleValue());
}

void MainComponent::audioCallback(AudioIODeviceCallback* newCallback)
{
	
}

//void MainComponent::volumeChangedCallback1(double value)
//{
//    leftPlayer.setGain(value);
//
//}

