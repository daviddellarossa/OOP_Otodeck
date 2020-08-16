/*
  ==============================================================================

    PlayerAggregateComponent.h
    Created: 16 Aug 2020 8:14:25am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ExternalCallbackActionListener.h"
#include "PlayerToolbar.h"
#include "AudioPlayer.h"

//==============================================================================
/*
*/
class PlayerAggregateComponent  : public juce::Component
{
public:
    PlayerAggregateComponent();
    ~PlayerAggregateComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void PlayCallback(const String& message);
    void PauseCallback(const String& message);
    void StopCallback(const String& message);

    void setCurrentFile(String filePath);
    String getCurrentFile() const;

private:
    String currentFilePath;
    Label currentFileLabel;
    PlayerToolbar playerToolbar;
    AudioPlayer audioPlayer;

    ExternalCallbackActionListener StopListener;
    ExternalCallbackActionListener PlayListener;
    ExternalCallbackActionListener PauseListener;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerAggregateComponent)
};