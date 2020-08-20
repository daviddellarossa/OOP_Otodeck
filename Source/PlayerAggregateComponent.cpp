/*
  ==============================================================================

    PlayerAggregateComponent.cpp
    Created: 16 Aug 2020 8:14:25am
    Author:  david

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayerAggregateComponent.h"

//==============================================================================
PlayerAggregateComponent::PlayerAggregateComponent(
    AudioPlayer& audioPlayer,
    AudioFormatManager& formatManager,
    AudioThumbnailCache& cache) :
	audioPlayer(audioPlayer),
    formatManager(formatManager),
    waveformDisplay(formatManager, cache),
    StopListener([this](const String& message) {StopCallback(message); }),
    PlayListener([this](const String& message) {PlayCallback(message); }),
	PauseListener([this](const String& message) {PauseCallback(message); }),
    PositionChangedListener([this](const String& message) {positionChangedCallback(message); })
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(this->playerToolbar);
    addAndMakeVisible(this->currentTrackLabel);
    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(speedSlider);
	
    playerToolbar.setBounds(0, 0, getWidth(), getHeight());
    currentTrackLabel.setBounds(0, 0, getWidth(), getHeight());
    waveformDisplay.setBounds(0, 0, getWidth(), getHeight());

	//Plug the broadcaster of playerToolbar to their respective Listeners
    playerToolbar.PlayEventBroadcaster.addActionListener(&PlayListener);
    playerToolbar.PauseEventBroadcaster.addActionListener(&PauseListener);
    playerToolbar.StopEventBroadcaster.addActionListener(&StopListener);

	//Plug the broadcaster of waveformDisplay to its respective Listener
    waveformDisplay.PositionChangedBroadcaster.addActionListener(&PositionChangedListener);

    //Configure the speedSlider control
    speedSlider.addListener(this);
    speedSlider.setNumDecimalPlacesToDisplay(2);
    speedSlider.setRange(0, 2);
    speedSlider.setValue(mapFromLog10(1.0, 0.1, 10.0) * 2);
    speedSlider.setTooltip("Speed");
    speedSlider.setNumDecimalPlacesToDisplay(2);

    startTimer(100);

    currentTrackLabel.setText("No track selected", NotificationType::dontSendNotification);
}

PlayerAggregateComponent::~PlayerAggregateComponent()
{
    stopTimer();
}

void PlayerAggregateComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
}

void PlayerAggregateComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    Grid layout;
    layout.templateColumns = {
        Grid::TrackInfo(1_fr),
        Grid::TrackInfo(1_fr),
    };

    layout.templateRows = {
        Grid::TrackInfo(32_px),
        Grid::TrackInfo(1_fr),
    	Grid::TrackInfo(32_px),
    };

    layout.items = {
        GridItem(currentTrackLabel).withArea(1, 1, 2, 3),
        GridItem(waveformDisplay).withArea(2, 1, 3, 3),
        GridItem(playerToolbar).withArea(3, 1, 4, 2),
        GridItem(speedSlider).withArea(3, 2, 4, 3).withMargin(GridItem::Margin{0, 0, 0, 10}),
    };

    layout.performLayout(getLocalBounds());
}

void PlayerAggregateComponent::PlayCallback(const String& message)
{
    this->audioPlayer.start();
    DBG(message);
}

void PlayerAggregateComponent::PauseCallback(const String& message)
{
    this->audioPlayer.stop();
    DBG(message);
}

void PlayerAggregateComponent::StopCallback(const String& message)
{
    this->audioPlayer.stop();
    this->audioPlayer.setPosition(0.0);
    DBG(message);
}

void PlayerAggregateComponent::positionChangedCallback(const String& message)
{
    this->audioPlayer.setPositionRelative(message.getDoubleValue());
}

void PlayerAggregateComponent::setCurrentTrack(String filePath)
{
    File track(filePath);
	if(track.existsAsFile())
	{
        this->currentTrackPath = filePath;
        this->currentTrackLabel.setText(currentTrackPath, dontSendNotification);
		this->audioPlayer.loadURL(URL{track});
        waveformDisplay.loadURL(URL{ track });
	}
}

String PlayerAggregateComponent::getCurrentTrack() const
{
    return this->currentTrackPath;
}

void PlayerAggregateComponent::timerCallback()
{
    waveformDisplay.setPositionRelative(
        audioPlayer.getPositionRelative());
}

bool PlayerAggregateComponent::isInterestedInFileDrag(const StringArray& files)
{
	//Player accepts only one file at the time
    if (files.size() != 1) return false;

    File file(files[0]);
    return formatManager.findFormatForFileExtension(file.getFileExtension());
}

void PlayerAggregateComponent::filesDropped(const StringArray& files, int x, int y)
{
	if(files.size() == 1)
	{
        File file(files[0]);
            if (!formatManager.findFormatForFileExtension(file.getFileExtension()))
            {
	            return;
            }
        this->setCurrentTrack(files[0]);
	}
}

void PlayerAggregateComponent::setSpeed(double speed)
{
    audioPlayer.setSpeed(speed);
}

void PlayerAggregateComponent::setGain(double gain)
{
    audioPlayer.setGain(gain);
}
void PlayerAggregateComponent::sliderValueChanged(Slider* slider)
{
    double logaritmicValue = mapToLog10(slider->getValue() / 2, 0.1, 10.0);
    this->audioPlayer.setSpeed(logaritmicValue);
}
