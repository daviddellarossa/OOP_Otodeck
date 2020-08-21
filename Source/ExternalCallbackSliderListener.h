/*
  ==============================================================================

    ExternalCallbackListener.h
    Created: 18 Aug 2020 11:11:26pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
/// <summary>
/// Custom Listener inheriting from Slider::Listener.
/// It is made to execute an external function when the Listener is invoked
/// by calling the sliderValueChanged method.
/// The function to execute is passed in as constructor's input parameter
/// </summary>
class ExternalCallbackSliderListener : public Slider::Listener
{
public:
	/// <summary>
	/// Constructor for the class
	/// </summary>
	/// <param name="callback">Function to execute when the Listener is invoked</param>
	ExternalCallbackSliderListener(
		const std::function<void(double value)> callback
	) : callback(callback)
	{	}
    /// <summary>
    /// Invoked when a sliderValueChanged event happens. This method is usually invoked by a Broadcaster object
    /// </summary>
    /// <param name="slider">The slider control causing the value to change</param>
    virtual void sliderValueChanged(Slider* slider) override
	{
		this->callback(slider->getValue());
	}

private:
	//Contains the callback function to execute when the Listener is invoked
	std::function<void(double value)> callback;
};


