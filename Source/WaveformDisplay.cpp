/*
  ==============================================================================

    WaveformDisplay.cpp
    Created: 14 Mar 2020 3:50:16pm
    Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager & 	formatManagerToUse,
                                 AudioThumbnailCache & 	cacheToUse) :
                                 audioThumb(1000, formatManagerToUse, cacheToUse), 
                                 fileLoaded(false), 
                                 position{0}
                          
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

  audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

	//display the waveform
    g.setColour (Colours::orange);
    if(fileLoaded)
    {
      audioThumb.drawChannel(g, 
        getLocalBounds(), 
        0, 
        audioThumb.getTotalLength(), 
        0, 
        1.0f
      );
      g.setColour(Colours::lightgreen);
      g.drawRect( static_cast<int>(position * getWidth()), 0, 10, getHeight());
    }
    else 
    {
    	//otherwise display a message
		g.setFont (20.0f);
		g.drawText (
            "File not loaded...", 
            getLocalBounds(),
			Justification::centred, 
            true
        );   // draw some placeholder text
    }
}

void WaveformDisplay::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void WaveformDisplay::loadURL(URL audioURL)
{
  audioThumb.clear();
  fileLoaded  = audioThumb.setSource(new URLInputSource(audioURL));
  if (fileLoaded)
  {
    std::cout << "wfd: loaded! " << std::endl;
    repaint();
  }
  else {
    std::cout << "wfd: not loaded! " << std::endl;
  }

}

void WaveformDisplay::changeListenerCallback (ChangeBroadcaster *source)
{
    std::cout << "wfd: change received! " << std::endl;

    repaint();

}

void WaveformDisplay::setPositionRelative(double pos)
{
  if (pos != position)
  {
  	if (isnan(pos))
  	{
        position = 0;
  	}
    else
    {
        position = pos;
    }

    repaint();
  }

}

void WaveformDisplay::mouseDrag(const MouseEvent& event)
{
    if (!fileLoaded) return;

	//Calculate the new relative position
    double relativePosition = event.getPosition().getX() / static_cast<double>(getWidth());
	//Control overflows and underflows
    if (relativePosition < 0)
        relativePosition = 0;
    if (relativePosition > 1)
        relativePosition = 1;

    positionChangedBroadcaster.sendActionMessage(static_cast<String>(relativePosition));
}

void WaveformDisplay::mouseDown(const MouseEvent& event)
{
    if (!fileLoaded) return;

	//Set the mouse cursor to draggingHand
    setMouseCursor(MouseCursor::DraggingHandCursor);
	
    //Calculate the new relative position
    double relativePosition = event.getPosition().getX() / static_cast<double>(getWidth());
    //Control overflows and underflows
    if (relativePosition < 0)
        relativePosition = 0;
    if (relativePosition > 1)
        relativePosition = 1;

    positionChangedBroadcaster.sendActionMessage(static_cast<String>(relativePosition));
}

void WaveformDisplay::mouseUp(const MouseEvent& event)
{
	//Reset the cursor to Normal
    setMouseCursor(MouseCursor::NormalCursor);
}




