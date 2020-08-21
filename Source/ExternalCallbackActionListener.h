/*
  ==============================================================================

    ExternalCallbackSliderListener.h
    Created: 16 Aug 2020 9:38:30am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
/// <summary>
/// Custom Listener inheriting from ActionListener.
/// It is aimed at executing an external function when the Listener is invoked
/// by calling the actionListenerCallback method.
/// The function to execute is passed in as constructor's input parameter
/// </summary>
class ExternalCallbackActionListener : public ActionListener
{
public:
    /// <summary>
    /// Constructor for the class
    /// </summary>
    /// <param name="callback">Function to execute when the Listener is invoked</param>
    ExternalCallbackActionListener(
        const std::function<void(const String& message)>& callback
    ) : callback(callback)
    {  }

    /// <summary>
    /// This method is invoked to activate the Listener. It executes the callback function passed in as constructor parameter
    /// </summary>
    /// <param name="message">Message passed in by the caller of the method, usually a Broadcaster,
    /// containing information about the action.</param>
    void actionListenerCallback(const String& message) override
    {
        this->callback(message);
    }
private:
	//Contains the callback function to execute when the Listener is invoked
    std::function<void(const String& message)> callback;
};
