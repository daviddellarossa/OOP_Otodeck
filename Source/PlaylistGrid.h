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


    class TrackModel
    {
    public:
        TrackModel() = default;

        TrackModel(
            const String& fileName,
            const String& filePath,
            const String& formatName,
            unsigned bitsPerSample,
            unsigned numChannels,
            double sampleRate,
            int64 lengthInSamples
        );

        String fileName;
        String filePath;
        String formatName;
        unsigned bitsPerSample;
        unsigned numChannels;
        double sampleRate;
        int64 lengthInSamples;
        unsigned lengthInSeconds() const;
        String toString() const;
    };

    class PlaylistTableListBoxModel : public TableListBoxModel
    {
    public:
        PlaylistTableListBoxModel(const std::shared_ptr<std::vector<TrackModel>> trackTitles);
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

        //virtual void cellClicked(int rowNumber, int columnId, const MouseEvent&) override;

        void cellDoubleClicked(int rowNumber, int columnId, const MouseEvent&) override;
    	
        Component* refreshComponentForCell(
            int rowNumber,
            int columnId,
            bool isRowSelected,
            Component* existingComponentToUpdate
        ) override;
        const std::shared_ptr<std::vector<TrackModel>> tracks;

        ActionBroadcaster ItemDoubleClickedEventBroadcaster;
    };

    void addTrack(TrackModel track);
    void removeSelectedTracks();
    SparseSet<int> getSelectedRowsIndices();
    std::shared_ptr<std::vector<TrackModel>> getTracks() const;
    void clearTracks();

    PlaylistTableListBoxModel& getGridBoxModel();

private:

    std::shared_ptr<std::vector<TrackModel>> tracks;
    TableListBox playlistDataGrid;
    PlaylistTableListBoxModel playlistDataGridBoxModel;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistGrid)
};
