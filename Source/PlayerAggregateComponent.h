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
class PlayerAggregateComponent  :
	public juce::Component,
	public Timer,
    public FileDragAndDropTarget
{
public:
    PlayerAggregateComponent(
        AudioPlayer& audioPlayer, 
        AudioFormatManager& formatManager,
        AudioThumbnailCache& cache
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

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

private:
    String currentTrackPath;
    Label currentTrackLabel;
    PlayerToolbar playerToolbar;
    AudioPlayer& audioPlayer;
    AudioFormatManager& formatManager;
    WaveformDisplay waveformDisplay;

    ExternalCallbackActionListener StopListener;
    ExternalCallbackActionListener PlayListener;
    ExternalCallbackActionListener PauseListener;

    ExternalCallbackActionListener PositionChangedListener;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerAggregateComponent)
};
