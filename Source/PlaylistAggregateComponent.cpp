/*
  ==============================================================================

    PlaylistAggregateComponent.cpp
    Created: 12 Aug 2020 9:59:38pm
    Author:  david

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistAggregateComponent.h"

//==============================================================================
PlaylistAggregateComponent::PlaylistAggregateComponent()	
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	addAndMakeVisible(this->playlistToolbar);
    //addAndMakeVisible(this->playlistGrid);
}

PlaylistAggregateComponent::~PlaylistAggregateComponent()
{
}

void PlaylistAggregateComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("PlaylistAggregateComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistAggregateComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //
    FlexBox controlLayout;
    controlLayout.flexWrap = FlexBox::Wrap::noWrap;
    controlLayout.flexDirection = FlexBox::Direction::column;
    controlLayout.items.add(FlexItem(static_cast<float>(getWidth()), 40.0f,playlistToolbar));
    //controlLayout.items.add(FlexItem(playlistGrid).withMinHeight(100).withMaxHeight(getHeight()));

    controlLayout.performLayout(getLocalBounds().toFloat());
    //this->playlistToolbar.setBounds(0, 0, getWidth(), getHeight());
}
