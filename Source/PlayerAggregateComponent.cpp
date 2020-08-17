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
    AudioFormatManager& formatManagerToUse,
    AudioThumbnailCache& cacheToUse) :
    audioPlayer(audioPlayer),
    waveformDisplay(formatManagerToUse, cacheToUse),
    StopListener([this](const String& message) {StopCallback(message); }),
    PlayListener([this](const String& message) {PlayCallback(message); }),
	PauseListener([this](const String& message) {PauseCallback(message); }),
    PositionChangedListener([this](const String& message) {positionChangedCallback(message); })
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(this->playerToolbar);
    //addAndMakeVisible(this->audioPlayer);
    addAndMakeVisible(this->currentTrackLabel);
    addAndMakeVisible(waveformDisplay);
	
    playerToolbar.setBounds(0, 0, getWidth(), getHeight());
    currentTrackLabel.setBounds(0, 0, getWidth(), getHeight());
    waveformDisplay.setBounds(0, 0, getWidth(), getHeight());
	
    playerToolbar.PlayEventBroadcaster.addActionListener(&PlayListener);
    playerToolbar.PauseEventBroadcaster.addActionListener(&PauseListener);
    playerToolbar.StopEventBroadcaster.addActionListener(&StopListener);

    waveformDisplay.PositionChangedBroadcaster.addActionListener(&PositionChangedListener);

    startTimer(100);
}

PlayerAggregateComponent::~PlayerAggregateComponent()
{
    stopTimer();
}

void PlayerAggregateComponent::paint (juce::Graphics& g)
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
    g.drawText ("PlayerAggregateComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlayerAggregateComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    FlexBox controlLayout;
    controlLayout.flexWrap = FlexBox::Wrap::noWrap;
    controlLayout.flexDirection = FlexBox::Direction::column;
    controlLayout.items.add(FlexItem(getWidth(), 32.0f, currentTrackLabel));
    controlLayout.items.add(FlexItem(waveformDisplay).withMinHeight(100).withMaxHeight(getHeight()).withFlex(1));
    controlLayout.items.add(FlexItem(static_cast<float>(getWidth()), 32.0f, playerToolbar));
    controlLayout.performLayout(getLocalBounds().toFloat());
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
    //DBG("New relative position: " << message.getDoubleValue());
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
    //std::cout << "DeckGUI::timerCallback" << std::endl;
    waveformDisplay.setPositionRelative(
        audioPlayer.getPositionRelative());
}