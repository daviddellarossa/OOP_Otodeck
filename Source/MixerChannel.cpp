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
MixerChannel::MixerChannel(Listener* _volumeChangedListener)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(volumeSlider);

    volumeSlider.setSliderStyle(Slider::LinearVertical);
    volumeSlider.addListener(_volumeChangedListener);
    volumeSlider.setRange(0.0, 1.0);
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

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("MixerChannel", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void MixerChannel::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    Grid layout;
	
    layout.templateColumns = {
    Grid::TrackInfo(2_fr),
    Grid::TrackInfo(1_fr),
    };

    layout.templateRows = {
	    Grid::TrackInfo(2_fr),
	    Grid::TrackInfo(1_fr),
	    Grid::TrackInfo(1_fr),
	    Grid::TrackInfo(1_fr),
	    Grid::TrackInfo(1_fr),
    };

    layout.items = {
        GridItem(volumeSlider).withArea(1, 2, 6, 3),
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
