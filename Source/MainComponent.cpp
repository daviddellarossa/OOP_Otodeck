/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() :
    TrackSelectedToPlayLeftListener([this](const String& message) { TrackSelectedToPlayCallback(message, this->leftPlayer); }),
    TrackSelectedToPlayRightListener([this](const String& message) { TrackSelectedToPlayCallback(message, this->rightPlayer); })
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

    addAndMakeVisible(deckGUI1); 
    addAndMakeVisible(deckGUI2);
    addAndMakeVisible(leftPlaylist);
    addAndMakeVisible(rightPlaylist);
    addAndMakeVisible(leftPlayer);
    addAndMakeVisible(rightPlayer);

    //leftPlaylist.setBounds(0, getHeight() / 2, getWidth(), getHeight() / 2);
    formatManager.registerBasicFormats();

    leftPlaylist.TrackSelectedToPlayEventBroadcaster.addActionListener(&TrackSelectedToPlayLeftListener);
    rightPlaylist.TrackSelectedToPlayEventBroadcaster.addActionListener(&TrackSelectedToPlayRightListener);

}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    
    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);

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
    player1.releaseResources();
    player2.releaseResources();
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
        GridItem(deckGUI1).withArea(1, 1, 3, 3),
		GridItem(deckGUI2).withArea(1, 3, 3, 5),

        GridItem(leftPlayer).withArea(4, 1, 4, 3),
		GridItem(rightPlayer).withArea(4, 3, 4, 5),

        GridItem(leftPlaylist).withArea(5, 1, 5, 3),
        GridItem(rightPlaylist).withArea(5, 3, 5, 5),

    };

    controlLayout.performLayout(getLocalBounds());
    //deckGUI1.setBounds(0, 0, getWidth()/2, getHeight()/2);
    //deckGUI2.setBounds(getWidth()/2, 0, getWidth()/2, getHeight()/2);
    //leftPlaylist.setBounds(0, getHeight() / 2, getWidth(), getHeight() / 2);
    //leftPlayer.setBounds(0, getHeight() / 2, getWidth(), getHeight() / 2);

}

void MainComponent::TrackSelectedToPlayCallback(const String& message, PlayerAggregateComponent& player) 
{
    player.setCurrentTrack(message);
}
//void MainComponent::TrackSelectedToPlayRightCallback(const String& message) const
//{
//}
