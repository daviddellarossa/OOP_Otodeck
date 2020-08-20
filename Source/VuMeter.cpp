/*
  ==============================================================================

    VuMeter.cpp
    Created: 19 Aug 2020 11:42:13pm
    Author:  david

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VuMeter.h"

//==============================================================================
VuMeter::VuMeter(const Atomic<Level>& level) : atomicLevel(level)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    this->startTimer(100);
	
}

VuMeter::~VuMeter()
{
    this->stopTimer();
}

void VuMeter::paint (juce::Graphics& g)
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
    //g.drawText ("VuMeter", getLocalBounds(),
    //            juce::Justification::centred, true);   // draw some placeholder text

    g.setColour(Colours::green);
    g.fillRect(getColouredRectangle(green));

    g.setColour(Colours::yellow);
    g.fillRect(getColouredRectangle(yellow));
	
    g.setColour(Colours::orange);
    g.fillRect(getColouredRectangle(orange));
	
    g.setColour(Colours::red);
    g.fillRect(getColouredRectangle(red));
	
    g.setColour(Colours::white);
    g.drawRect(getRectangle());



}

void VuMeter::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void VuMeter::setLevel(Level level)
{
    //return;
    this->rmsLevel = level.rmsLevel;
    this->magnitude = level.magnitude;

    this->repaint();
}

Rectangle<float> VuMeter::getRectangle() const
{
    return Rectangle<float>(
        getWidth() * (1 - width) / 2,
        getHeight() * (1 - height) / 2,
        getWidth() * width,
        getHeight() * height
    );
}

Rectangle<float> VuMeter::getColouredRectangle(const Range<float>& range) const
{
    const auto baseRectangle = getRectangle();
    auto rectangle(baseRectangle);

    auto level = this->rmsLevel * this->gain;
    if (level > 1) level = 1;

    float yRelative = 0.0f;

    if (level == 0) {
        yRelative = range.getStart();
    }
    else if (level > range.getEnd())
    {
        yRelative = range.getEnd();
    }
    else if (level > range.getStart())
    {
        yRelative = level;
    }
    rectangle.setY(baseRectangle.getY() + baseRectangle.getHeight() * (1 - yRelative));
    rectangle.setHeight(baseRectangle.getHeight() * (yRelative - range.getStart()));
    return rectangle;
}

void VuMeter::timerCallback()
{
    setLevel(atomicLevel.get());
}
