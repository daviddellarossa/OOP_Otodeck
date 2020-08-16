/*
  ==============================================================================

    PlayerAggregateComponent.cpp
    Created: 16 Aug 2020 8:14:25am
    Author:  david

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlayerAggregateComponent.h"

//==============================================================================
PlayerAggregateComponent::PlayerAggregateComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

PlayerAggregateComponent::~PlayerAggregateComponent()
{
}

void PlayerAggregateComponent::paint (juce::Graphics& g)
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
    g.drawText ("PlayerAggregateComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlayerAggregateComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
