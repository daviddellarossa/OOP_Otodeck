/*
  ==============================================================================

    ScratchAggregateComponent.cpp
    Created: 18 Aug 2020 7:52:11am
    Author:  david

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ScratchAggregateComponent.h"

//==============================================================================
ScratchAggregateComponent::ScratchAggregateComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    addAndMakeVisible(speedSlider);

    speedSlider.addListener(this);
    speedSlider.setNumDecimalPlacesToDisplay(2);
    speedSlider.setValue(mapFromLog10(1.0, 0.1, 10.0));
	speedSlider.setRange(0, 1);
}

ScratchAggregateComponent::~ScratchAggregateComponent()
{
}

void ScratchAggregateComponent::paint (juce::Graphics& g)
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
    g.drawText ("ScratchAggregateComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void ScratchAggregateComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    FlexBox layout;
    layout.flexDirection = FlexBox::Direction::column;
    layout.flexWrap = FlexBox::Wrap::noWrap;
    layout.items.add(FlexItem().withMinHeight(100).withMaxHeight(getHeight()).withFlex(1));
    layout.items.add(FlexItem(static_cast<float>(getWidth()), 64.0f, speedSlider));
    layout.performLayout(getLocalBounds().toFloat());
}

void ScratchAggregateComponent::sliderValueChanged(Slider* slider)
{
    double logaritmicValue = mapToLog10(slider->getValue(), 0.1, 10.0);
    this->SpeedChangedBroadcaster.sendActionMessage(std::to_string(logaritmicValue));
}
