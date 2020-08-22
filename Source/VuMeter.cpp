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
VuMeter::VuMeter(
    const Atomic<Level>& level,
    const String label
) : atomicLevel(level), label(label)
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

    // To draw the VuMeter, the various coloured bars will be drawn one on top of the other
	// The height and location of each bar is calculated in the getColouredRectangle,based on the range passed as input

    //Draw the green bar
    g.setColour(Colours::green);
    g.fillRect(getColouredRectangle(relativeYBoundariesForGreenBar));

	//draw the yellow bar
    g.setColour(Colours::yellow);
    g.fillRect(getColouredRectangle(relativeYBoundariesForYellowBar));

	//draw the orange bar
    g.setColour(Colours::orange);
    g.fillRect(getColouredRectangle(relativeYBoundariesForOrangeBar));

	//draw the red bar
    g.setColour(Colours::red);
    g.fillRect(getColouredRectangle(relativeYBoundariesForRedBar));

	//draw the white bar
    g.setColour(Colours::white);
    g.drawRect(getRectangle());

	//only display the label if the height of the controller is greater than a minimum value
	if(getHeight() > minimumHeightForDisplayingLabels)
		g.drawText(label, getWidth() / 2 - 5, 10, 10, 10, Justification::centredBottom, false);

}

void VuMeter::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void VuMeter::setLevel(Level level)
{
    this->level = level;
    this->repaint();
}

Rectangle<float> VuMeter::getRectangle() const
{
    return Rectangle<float>(
        getWidth() * (1 - relativeWidth) / 2,
        getHeight() * (1 - relativeHeight) / 2,
        getWidth() * relativeWidth,
        getHeight() * relativeHeight
    );
}


Rectangle<float> VuMeter::getColouredRectangle(const Range<float>& range) const
{
    //IMPORTANT: To understand how this algorithm works, please consider the following:
	// . The Y axis has its origin on the top margin of the control, whereas the VuMeter has its lowest value on the bottom.
	//      This requires some math to correctly calculate the position and the size of the coloured bar
	// . Each bar has its bottom boundary always fixed at the position given by its range.startValue, no matter what.
	//   The top boundary depends on the input level. If this input is zero, the top boundary will be equal to the bottom boundary,
	//   and no bar will be displayed. If the input is below the range.startValue, no bar will be displayed. If the input is higher than
	//   the startValue, a bar of height equal to (endValue-startValue)*totalHeight will be drawn.

	
	//get the box containing the VuMeter
    const auto baseRectangle = getRectangle();
    auto rectangle(baseRectangle);

	//Calculate the level to display, considering the multiplying factor of the gain
    auto level = this->level.rmsLevel * this->gain;
	//if overflow, trim the value
    if (level > 1) level = 1;

	//yRelative is the relative position of the top boundary.
	//As the Y axis has its origin on the top margin of the control, this value changes at every read
    float yRelative = 0.0f;

	
    if (level == 0) {
    	//if level is ), the top boundary will be equal to the bottom boundary: no bar drawn
        yRelative = range.getStart();
    }
    else if (level > range.getEnd())
    {
    	//if level is higher than the endValue for the bar, the getEnd value of the Range will be used,
    	//drawing a bar with the max possible height, given by range.getEnd -range. getStart
        yRelative = range.getEnd();
    }
    else if (level > range.getStart())
    {
    	//if level is higher than the startValue, but lower than the endValue, the actual top boundary will be determined by the level
        yRelative = level;
    }

	//Calculate the absolute Y position, considering the proportion of the VuMeter bar respect to the Component size, and the margin
    rectangle.setY(baseRectangle.getY() + baseRectangle.getHeight() * (1 - yRelative));
	//Calculate the height of the bar, determined only by the max height of the VuMeter,
	//the start position of the coloured bar and the previously calculated top boundary
    rectangle.setHeight(baseRectangle.getHeight() * (yRelative - range.getStart()));
	
    return rectangle;
}

void VuMeter::timerCallback()
{
    setLevel(atomicLevel.get());
}
