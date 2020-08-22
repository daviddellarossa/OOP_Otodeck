/*
  ==============================================================================

    WaveformDisplay.h
    Created: 14 Mar 2020 3:50:16pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================

//UI Component that displays the waveform of the audio file being played.
//The content of this class is mostly the one created step by step during the course.
//However, a new addition has been made. It is now possible to change the position
//within the file, just dragging around the rectangle that marks the current position in the track.
//This makes the position slider redundant which in fact has been removed.
class WaveformDisplay :
	public Component, 
	public ChangeListener
{
public:
    /// <summary>
    /// Constructor for the class. Creates a new instance.
    /// </summary>
    /// <param name="formatManagerToUse">Reference to an instance of AudioFormatManager,
    /// required to open the current track and read its content</param>
    /// <param name="cacheToUse">Reference to an instance of AudioThumbnailCache</param>
    WaveformDisplay( AudioFormatManager & 	formatManagerToUse,
                    AudioThumbnailCache & 	cacheToUse );
	//Destructor
    ~WaveformDisplay();

	//Overloads for the virtual methods inherited from the Component class
    void paint (Graphics&) override;
    void resized() override;

	//Overload for the virtual method inherited from the ChangeListener class
    void changeListenerCallback (ChangeBroadcaster *source) override;

    /// <summary>
    /// Load the file pointed to by the input parameter, in order to display it
    /// </summary>
    /// <param name="audioURL">URL of the file to load</param>
    void loadURL(URL audioURL);

    /// <summary>
    /// Set the relative position of the playhead
    /// </summary>
    /// <param name="pos">New position relative to the track length</param>
    void setPositionRelative(double pos);

	//These events control the actions performed on the waveform component,
	// in order to control the position within the track
    void mouseDrag(const MouseEvent& event) override;
	void mouseDown(const MouseEvent& event) override;
	void mouseUp(const MouseEvent& event) override;

    /// <summary>
    /// Broadcaster that notifies when the position within the track has changed
    /// </summary>
    ActionBroadcaster positionChangedBroadcaster;

private:
	//Instance of an object of type AudioThumbnail
    AudioThumbnail audioThumb;
	//Says whether there is currently a track set up to display
    bool fileLoaded;
	//Keeps the current position in the file
    double position;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
