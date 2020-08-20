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

/// <summary>
/// Aggregate Component containing all the UI parts needed to make the player
/// </summary>
class PlayerAggregateComponent  :
	public juce::Component,
	public Timer,
    public FileDragAndDropTarget,
    public Slider::Listener
{
public:
    /// <summary>
    /// Create an instance of the class
    /// </summary>
    /// <param name="audioPlayer">Reference to an instance of audioPlayer</param>
    /// <param name="formatManager">Reference to an instance of AudioFormatManager</param>
    /// <param name="cache">Reference to an instance of AudioThumbnailCache</param>
    PlayerAggregateComponent(
        AudioPlayer& audioPlayer, 
        AudioFormatManager& formatManager,
        AudioThumbnailCache& cache
    );
    ~PlayerAggregateComponent() override;

	//Overloads for the methods inherited from Component
    void paint (juce::Graphics&) override;
    void resized() override;

	//Callbacks invoked by the Listeners when certain events are triggered
	//Callback invoked when a Play event is triggered. This event is triggered when the user clicks on the Play button on the UI
    void PlayCallback(const String& message);
    //Callback invoked when a Pause event is triggered. This event is triggered when the user clicks on the Pause button on the UI
    void PauseCallback(const String& message);
    //Callback invoked when a Stop event is triggered. This event is triggered when the user clicks on the Stop button on the UI
    void StopCallback(const String& message);
    //Callback invoked when a positionChanged event is triggered. This event is triggered when the user moves the position slider on the UI
    void positionChangedCallback(const String& message);
    //Sets the new current track for the player to the file pointed to by filePath
    void setCurrentTrack(String filePath);
	//Returns the current track set in the player
    String getCurrentTrack() const;

	//Callback invoked when the timer ticks.
    void timerCallback() override;

	//Override for the virtual methods of FileDragAndDropTarget
    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;
	
	//Set the speed of the player to the value speed
    void setSpeed(double speed);
	//Set the gain of the player to the value gain
    void setGain(double gain);

	//Override for the virtual method of Slider::Listener
	//The value set in the slider is treated logarithmically.
	//The range for the slider is 0 to 2, where 0 is one tenth of the normal speed, 1 is normal speed, 2 is 10 times the normal speed
    void sliderValueChanged(Slider* slider) override;

private:
	//Full path of the current track in the player
    String currentTrackPath;
	//Label displaying the current track in the player
    Label currentTrackLabel;
	//Toolbar component for the player. It shows the buttons Play, Pause, Stop
    PlayerToolbar playerToolbar;
	//Reference to an instance of AudioPlayer. This is created and configured by the caller of this class.
    AudioPlayer& audioPlayer;
    //Reference to an instance of AudioFormatManager. This is created and configured by the caller of this class.
    AudioFormatManager& formatManager;
	//UI Component that displays the waveform of the current file
    WaveformDisplay waveformDisplay;
	//UI Component to control the speed of the player
    Slider speedSlider;

	//Listener for the Stop event. Stop resets the position to the beginning of the track
    ExternalCallbackActionListener StopListener;
	//Listener for the Play event
    ExternalCallbackActionListener PlayListener;
	//Listener for the Pause event. Pause keeps the same position in the track
    ExternalCallbackActionListener PauseListener;
    //Listener for the PositionChanged event
    ExternalCallbackActionListener PositionChangedListener;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerAggregateComponent)
};
