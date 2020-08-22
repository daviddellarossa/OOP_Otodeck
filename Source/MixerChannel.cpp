/*
  ==============================================================================

    MixerChannel.cpp
    Created: 18 Aug 2020 7:42:28am
    Author:  david

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MixerChannel.h"

class ExternalCallbackSliderListener;
//==============================================================================
MixerChannel::MixerChannel()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(volumeSlider);
    addAndMakeVisible(muteButton);

	//Set the initial values for the volume slider
    volumeSlider.setSliderStyle(Slider::LinearVertical);
    volumeSlider.addListener(this);
    volumeSlider.setRange(0.0, 1.0);
    volumeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    volumeSlider.setTooltip("Volume");

	//Set initial values for the mute button
    muteButton.setBounds(0, 0, getWidth(), getHeight());
    muteButton.setTooltip("Mute");
    muteButton.addListener(this);
}

MixerChannel::~MixerChannel()
{
}

void MixerChannel::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void MixerChannel::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    Grid layout;
	
    layout.alignContent = Grid::AlignContent::spaceEvenly;
    layout.justifyContent = Grid::JustifyContent::spaceEvenly;
    layout.justifyItems = Grid::JustifyItems::center;
    layout.alignItems = Grid::AlignItems::center;
	
    layout.templateColumns = {
		Grid::TrackInfo(24_px),
    };

    layout.templateRows = {
	    Grid::TrackInfo(5_fr),
	    Grid::TrackInfo(1_fr),
    };
	
    layout.items = {
        GridItem(volumeSlider).withArea(1, 1, 2, 2).withAlignSelf(GridItem::AlignSelf::center).withWidth(24.0).withMargin(GridItem::Margin{20, 0, 0, 0}),
        GridItem(muteButton).withArea(2, 1, 3, 2).withAlignSelf(GridItem::AlignSelf::center).withWidth(24.0),
    };

    layout.performLayout(getLocalBounds());
}

void MixerChannel::setVolume(double value)
{
    this->volumeSlider.setValue(value);
}

void MixerChannel::buttonStateChanged(Button*)
{
    volumeChangedBroadcaster.sendActionMessage(std::to_string(getVolume()));
}

void MixerChannel::buttonClicked(Button*)
{
}

void MixerChannel::sliderValueChanged(Slider* slider)
{
    volumeChangedBroadcaster.sendActionMessage(std::to_string(getVolume()));
}
 double MixerChannel::getVolume() const
{
	//return the volumeSlider value if muteButton is off, otherwise return 0
     if (muteButton.getToggleState() == true)
         return 0;
     else
         return volumeSlider.getValue();
}