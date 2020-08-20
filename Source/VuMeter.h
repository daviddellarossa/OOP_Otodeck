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
*/
struct Level
{
    double rmsLevel;
    double magnitude;
};

class VuMeter  : public juce::Component, public Timer
{
public:
    VuMeter(const Atomic<Level>& rmsLevel);
    ~VuMeter() override;


	
    void paint (juce::Graphics&) override;
    void resized() override;
    void setLevel(Level level);
    
private:
    Rectangle<float> getRectangle() const ;
    Rectangle<float> getGreenRectangle() const;
	
    const Atomic<Level>& atomicLevel;
	
    virtual void timerCallback() override;

    const float width = 0.1;
    const float height = 0.9;
    const Range<float> green{0.0, 0.5};
    const Range<float> yellow{ 0.5, 2 / 3 };
    const Range<float> orange{ 2 / 3, 5 / 6 };
    const Range<float> red{ 5 / 6, 1 };
    double rmsLevel;
    double magnitude;
    float gain = 2;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VuMeter)
};
