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
    Rectangle<float> getColouredRectangle(const Range<float>& range) const;

    const Atomic<Level>& atomicLevel;
	
    virtual void timerCallback() override;

    const float width = 0.4;
    const float height = 0.9;
    const Range<float> green{0.0f, 0.5f};
    const Range<float> yellow{ 0.5f, 2 / 3.0f };
    const Range<float> orange{ 2 / 3.0f, 5 / 6.0f };
    const Range<float> red{ 5 / 6.0f, 1 };
    double rmsLevel;
    double magnitude;
    float gain = 2;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VuMeter)
};
