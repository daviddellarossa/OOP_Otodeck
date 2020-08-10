/*
  ==============================================================================

    PlaylistComponent.h
    Created: 9 Aug 2020 10:33:58pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlaylistComponent :
	public juce::Component,
	public TableListBoxModel,
    public Button::Listener
{
public:
    PlaylistComponent();
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    int getNumRows() override;

    void paintRowBackground(
        Graphics&, 
        int rowNumber, 
        int width, 
        int height, 
        bool rowIsSelected
    ) override;

    void paintCell(
        Graphics&, 
        int rowNumber, 
        int columnId, 
        int width, 
        int height, 
        bool rowIsSelected
    ) override;

    virtual void cellClicked(int rowNumber, int columnId, const MouseEvent&) override;

    Component* refreshComponentForCell(
        int rowNumber, 
        int columnId, 
        bool isRowSelected, 
        Component* existingComponentToUpdate
    ) override;

    void buttonClicked(Button* button) override;

private:
    TableListBox tableComponent;
    std::vector<std::string> trackTitles;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
