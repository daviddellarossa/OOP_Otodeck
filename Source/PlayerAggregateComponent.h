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
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class PlayerAggregateComponent  : public juce::Component, public Timer
{
public:
    PlayerAggregateComponent(
        AudioPlayer& audioPlayer, 
        AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse
    );
    ~PlayerAggregateComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void PlayCallback(const String& message);
    void PauseCallback(const String& message);
    void StopCallback(const String& message);

    void positionChangedCallback(const String& message);

    void setCurrentTrack(String filePath);
    String getCurrentTrack() const;

    void timerCallback() override;

private:
    String currentTrackPath;
    Label currentTrackLabel;
    PlayerToolbar playerToolbar;
    AudioPlayer& audioPlayer;

    WaveformDisplay waveformDisplay;

    ExternalCallbackActionListener StopListener;
    ExternalCallbackActionListener PlayListener;
    ExternalCallbackActionListener PauseListener;

    ExternalCallbackActionListener PositionChangedListener;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerAggregateComponent)
};
