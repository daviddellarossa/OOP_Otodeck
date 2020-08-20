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
    WaveformDisplay( AudioFormatManager & 	formatManagerToUse,
                    AudioThumbnailCache & 	cacheToUse );
    ~WaveformDisplay();

	//Overloads for the virtual methods inherited from the Component class
    void paint (Graphics&) override;
    void resized() override;

	//Overload for the virtual method inherited from the ChangeListener class
    void changeListenerCallback (ChangeBroadcaster *source) override;

	//Load the file pointed to by the input parameter, in order to display it
    void loadURL(URL audioURL);

    /** set the relative position of the playhead*/
    void setPositionRelative(double pos);

	//These events control the actions performed on the waveform component,
	// in order to control the position within the track
    void mouseDrag(const MouseEvent& event) override;
	void mouseDown(const MouseEvent& event) override;
	void mouseUp(const MouseEvent& event) override;

	//Broadcaster that notifies when the position within the track has changed
    ActionBroadcaster PositionChangedBroadcaster;

private:
    AudioThumbnail audioThumb;
	//Says whether there is currently a track set up to display
    bool fileLoaded;
	//Keeps the current position in the file
    double position;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
