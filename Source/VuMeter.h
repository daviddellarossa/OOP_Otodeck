/*
  ==============================================================================

    VuMeter.h
    Created: 19 Aug 2020 11:42:13pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
 *Structure Modeling the Levels used by the VuMeter
*/
struct Level
{
    double rmsLevel;
    double magnitude;
};

/// <summary>
/// VuMeter component that displays graphically the level of audio
/// This Component inherits from Timer too. This is required to poll the Atomic wrapper set in the audio thread, containing the values to be displayed with the VuMeter.
/// The Timer clicks trigger the thread-safe read of the current value in the Atomic variable the repaint of the component
/// </summary>
class VuMeter  :
	public juce::Component,
	public Timer
{
public:
    /// <summary>
    /// Constructor of the class Vumeter
    /// </summary>
    /// <param name="rmsLevel">Reference to the Level instance to get the values to display from</param>
    VuMeter(const Atomic<Level>& rmsLevel);
    ~VuMeter() override;

	// Overloads for virtual function of Component
    void paint (juce::Graphics&) override;
    void resized() override;

	//Sets the levels 
    void setLevel(Level level);
    
private:
    /// <summary>
    /// Returns a Rectangle where the VuMeter will be drawn.
    /// This takes into account the size of the component, as well as the margins, as well as the size set
    /// </summary>
    Rectangle<float> getRectangle() const ;

    /// <summary>
    /// Returns a Rectangle where to draw the coloured parts of the VuMeter bar
    /// </summary>
    /// <param name="range">Determines the size and position of the part</param>
    Rectangle<float> getColouredRectangle(const Range<float>& range) const;

    /// <summary>
    /// Reference to the thread-safe Atomic wrapper for the Level instance to use to draw the VuMeter
    /// </summary>
    const Atomic<Level>& atomicLevel;

	//Timer callback - part of the pattern to read an Atomic value across different threads
    void timerCallback() override;

    /// <summary>
    /// Relative Width of the VuMeter bar respect to the Width of the Component
    /// </summary>
    const float relativeWidth = 0.4;
    /// <summary>
    /// Relative Height of the VuMeter bar respect to the Height of the Component
    /// </summary>
    const float relativeHeight = 0.9;
    /// <summary>
    /// Relative boundaries on the Y axis for the Green bar.
    /// Start Value is the bottom edge, EndValue is the top edge
    /// </summary>
    const Range<float> relativeYBoundariesForGreenBar{0.0f, 0.5f};
    /// <summary>
    /// Relative boundaries on the Y axis for the Yellow bar.
    /// Start Value is the bottom edge, EndValue is the top edge
    /// </summary>
    const Range<float> relativeYBoundariesForYellowBar{ 0.5f, 2 / 3.0f };
    /// <summary>
    /// Relative boundaries on the Y axis for the Orange bar.
    /// Start Value is the bottom edge, EndValue is the top edge
    /// </summary>
    const Range<float> relativeYBoundariesForOrangeBar{ 2 / 3.0f, 5 / 6.0f };
    /// <summary>
    /// Relative boundaries on the Y axis for the Red bar.
    /// Start Value is the bottom edge, EndValue is the top edge
    /// </summary>
    const Range<float> relativeYBoundariesForRedBar{ 5 / 6.0f, 1 };
    /// <summary>
    /// Current Level of audio
    /// </summary>
    Level level;
    /// <summary>
    /// Multiplication factor for the VuMeter, to change the scale
    /// </summary>
    float gain = 2;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VuMeter)
};
