/*
  ==============================================================================

    PlaylistGrid.h
    Created: 12 Aug 2020 10:00:10pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlaylistGrid  : public juce::Component
{
public:
    PlaylistGrid();
    ~PlaylistGrid() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    class PlaylistTableListBoxModel : public TableListBoxModel
    {
    public:
        PlaylistTableListBoxModel(const std::shared_ptr<std::vector<std::string>> trackTitles);
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
        const std::shared_ptr<std::vector<std::string>> trackTitles;
    };

private:

    std::shared_ptr<std::vector<std::string>> trackTitles;
    TableListBox playlistDataGrid;
    PlaylistTableListBoxModel playlistDataGridBoxModel;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistGrid)
};
