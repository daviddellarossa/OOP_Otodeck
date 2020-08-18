/*
  ==============================================================================

    ExternalCallbackSliderListener.h
    Created: 16 Aug 2020 9:38:30am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class ExternalCallbackActionListener : public ActionListener
{

public:
    ExternalCallbackActionListener(
        const std::function<void(const String& message)>& callback
    ) : callback(callback)
    {

    }
    void actionListenerCallback(const String& message) override
    {
        this->callback(message);
    }
private:
    std::function<void(const String& message)> callback;
};
