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
/// It is made to execute an external function when the Listener is invoked.
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
	
    void actionListenerCallback(const String& message) override
    {
        this->callback(message);
    }
private:
    std::function<void(const String& message)> callback;
};
