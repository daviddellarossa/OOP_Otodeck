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

/// <summary>
/// This Component implements a playlist grid
/// </summary>
class PlaylistGrid  :
	public juce::Component,
	public FileDragAndDropTarget
{
public:
    PlaylistGrid();
    ~PlaylistGrid() override;

	//Overloads for the virtual methods inherited by the Component class
    void paint (juce::Graphics&) override;
    void resized() override;

    /// <summary>
    /// Class containing all the information related to a track
    /// </summary>
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

        /// <summary>
        /// Loads an audio file and returns a TrackModel instance based on the file information
        /// </summary>
        /// <param name="filepath">Path of the file to open</param>
        /// <param name="formatReader">Reference to an instance of AudioFormatManager, needed to read the audio file</param>
        /// <returns>New TrackModel instance containing the information about the audio file</returns>
        static TrackModel FromFile(const String& filepath, AudioFormatManager& formatReader);
    };

    /// <summary>
    /// TableListBoxModel implementation for the Playlist grid
    /// </summary>
    class PlaylistTableListBoxModel : public TableListBoxModel
    {
    public:
        /// <summary>
        /// Creates an instance of the class.
        /// </summary>
        /// <param name="trackTitles">Pointer to an array containing the list of tracks to display.
        /// This list is controlled by the parent class</param>
        PlaylistTableListBoxModel(const std::shared_ptr<std::vector<TrackModel>> trackTitles);

    	//Overrides for the virtual methods inherited from the TableListBoxModel class
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

        //Override for the double-click event on a cell of the grid
        void cellDoubleClicked(int rowNumber, int columnId, const MouseEvent&) override;
    	
        Component* refreshComponentForCell(
            int rowNumber,
            int columnId,
            bool isRowSelected,
            Component* existingComponentToUpdate
        ) override;

    	//Pointer to an array containing the list of tracks
        const std::shared_ptr<std::vector<TrackModel>> tracks;

    	//Broadcaster for the ItemDoubleClicked event
        ActionBroadcaster ItemDoubleClickedEventBroadcaster;
    	//Contains the search text inputted in the Search text field
        String searchText;
    };

    /// <summary>
    /// Add a new track to the Track array
    /// </summary>
    void addTrack(TrackModel track);
    /// <summary>
    /// Remove the selected track from the array. Only one file at a time is selectable.
    /// </summary>
    void removeSelectedTracks();
    /// <summary>
    /// Returns the indices of the selected rows. At the moment only on file at a time is selectable.
    /// </summary>
    SparseSet<int> getSelectedRowsIndices();
    /// <summary>
    /// Return the list tracks as a vector of instances of TrackModel
    /// </summary>
    std::shared_ptr<std::vector<TrackModel>> getTracks() const;
    /// <summary>
    /// Clear the track list
    /// </summary>
    void clearTracks();

	//Overloads for the virtual methods inherited from the FileDragAndDropTarget class
    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;

	//Set the Search text
    void setSearchText(String text);

    /// <summary>
    /// Reference to an instance of PlaylistTableListBoxModel
    /// </summary>
    /// <returns></returns>
    PlaylistTableListBoxModel& getGridBoxModel();

private:
    AudioFormatManager formatManager;
	//List of tracks
    std::shared_ptr<std::vector<TrackModel>> tracks;
	//Component displaying the actual data grid
    TableListBox playlistDataGrid;
	//Instance of TableListBoxModel
    PlaylistTableListBoxModel playlistDataGridBoxModel;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistGrid)
};
