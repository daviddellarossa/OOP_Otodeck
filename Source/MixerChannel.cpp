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

    volumeSlider.setSliderStyle(Slider::LinearVertical);
    volumeSlider.addListener(this);
    volumeSlider.setRange(0.0, 1.0);
    volumeSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    volumeSlider.setTooltip("Volume");
	
    muteButton.setBounds(0, 0, getWidth(), getHeight());
    muteButton.setTooltip("Mute");
    //muteButton.setButtonText("Mute");
    muteButton.addListener(this);
}

MixerChannel::~MixerChannel()
{
}

void MixerChannel::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour (juce::Colours::white);
    //g.setFont (14.0f);
    //g.drawText ("MixerChannel", getLocalBounds(),
    //            juce::Justification::centred, true);   // draw some placeholder text
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

double MixerChannel::getVolume() const
{
    return this->volumeSlider.getValue();
}

void MixerChannel::buttonStateChanged(Button*)
{
    VolumeChangedBroadcaster.sendActionMessage(std::to_string(getVolume()));
}

void MixerChannel::buttonClicked(Button*)
{
}

void MixerChannel::sliderValueChanged(Slider* slider)
{
    VolumeChangedBroadcaster.sendActionMessage(std::to_string(getVolume()));
}

inline double MixerChannel::getVolume()
{
    return volumeSlider.getValue() * (muteButton.getToggleState() ? 0 : 1);
}