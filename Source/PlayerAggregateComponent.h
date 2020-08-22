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
    /// Constructor for the class. Creates an instance of the class
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

    /// <summary>
    /// Sets the new current track for the player to the file pointed to by filePath
    /// </summary>
    /// <param name="filePath">Message describing the event</param>
    void setCurrentTrack(String filePath);
    /// <summary>
    /// Returns the current track set in the player
    /// </summary>
    /// <returns>The full path of the current  track</returns>
    String getCurrentTrack() const;

    /// <summary>
    /// Callback invoked when the timer ticks. Used to synchronize the current position in the WaveformDisplay component
    /// </summary>
    void timerCallback() override;

	//Override for the virtual methods of FileDragAndDropTarget
    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;
	
    /// <summary>
    /// Set the speed of the player to the value speed
    /// </summary>
    /// <param name="speed">New speed for the player</param>
    void setSpeed(double speed);
    /// <summary>
    /// Set the gain of the player to the value gain
    /// </summary>
    /// <param name="gain">New gain for the player</param>
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
    ExternalCallbackActionListener stopListener;
	//Listener for the Play event
    ExternalCallbackActionListener playListener;
	//Listener for the Pause event. Pause keeps the same position in the track
    ExternalCallbackActionListener pauseListener;
    //Listener for the PositionChanged event
    ExternalCallbackActionListener positionChangedListener;

    //Callbacks invoked by the Listeners when certain events are triggered

	/// <summary>
	/// Callback invoked when a Play event is triggered. This event is triggered when the user clicks on the Play button on the UI
	/// </summary>
	/// <param name="message">Message describing the event</param>
    void playCallback(const String& message);
    /// <summary>
    /// Callback invoked when a Pause event is triggered. This event is triggered when the user clicks on the Pause button on the UI
    /// </summary>
    /// <param name="message">Message describing the event</param>
    void pauseCallback(const String& message);
    /// <summary>
    /// Callback invoked when a Stop event is triggered. This event is triggered when the user clicks on the Stop button on the UI
    /// </summary>
    /// <param name="message">Message describing the event</param>
    void stopCallback(const String& message);
    /// <summary>
    /// Callback invoked when a positionChanged event is triggered. This event is triggered when the user moves the position slider on the UI
    /// </summary>
    /// <param name="message">Message describing the event</param>
    void positionChangedCallback(const String& message);

	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerAggregateComponent)
};
