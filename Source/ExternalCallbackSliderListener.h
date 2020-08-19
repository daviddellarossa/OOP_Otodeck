/*
  ==============================================================================

    ExternalCallbackListener.h
    Created: 18 Aug 2020 11:11:26pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ExternalCallbackSliderListener : public Slider::Listener
{

public:
	ExternalCallbackSliderListener(
		const std::function<void(double value)> callback
	) : callback(callback)
	{
		
	}

    virtual void sliderValueChanged(Slider* slider) override
	{
		this->callback(slider->getValue());
	}

private:
    std::function<void(double value)> callback;
};


