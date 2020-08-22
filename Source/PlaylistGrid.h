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
    /// <summary>
    /// Constructor for the class. Creates an instance of the class
    /// </summary>
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
        /// <summary>
        /// Constructor for the class used to quickly create a new instance
        /// </summary>
        /// <param name="fileName">File name of the track</param>
        /// <param name="filePath">Full path of the file</param>
        /// <param name="formatName">Name of the file format</param>
        /// <param name="bitsPerSample">Quality of the sample</param>
        /// <param name="numChannels">Number of channels available</param>
        /// <param name="sampleRate">Sample rate of the track</param>
        /// <param name="lengthInSamples">Length in samples</param>
        TrackModel(
            const String& fileName,
            const String& filePath,
            const String& formatName,
            unsigned bitsPerSample,
            unsigned numChannels,
            double sampleRate,
            int64 lengthInSamples
        );
        /// <summary>
        /// File name of the track
        /// </summary>
        String fileName;
    	/// <summary>
    	/// Full path of the file
    	/// </summary>
    	String filePath;
        /// <summary>
        /// Name of the file format
        /// </summary>
        String formatName;
        /// <summary>
        /// Quality of the sample
        /// </summary>
        unsigned bitsPerSample;
        /// <summary>
        /// Number of channels available
        /// </summary>
        unsigned numChannels;
        /// <summary>
        /// Sample rate of the track
        /// </summary>
        double sampleRate;
        /// <summary>
        /// Length in samples
        /// </summary>
        int64 lengthInSamples;
    	/// <summary>
    	/// Calculate the length of the track in seconds
    	/// </summary>
    	/// <returns>Length in seconds</returns>
    	unsigned lengthInSeconds() const;
    	/// <summary>
    	/// Return a meaningful string that describes the instance
    	/// </summary>
    	/// <returns>String describing the instance</returns>
    	String toString() const;

        /// <summary>
        /// Loads an audio file and returns a TrackModel instance based on the file information
        /// </summary>
        /// <param name="filePath">Path of the file to open</param>
        /// <param name="formatReader">Reference to an instance of AudioFormatManager, needed to read the audio file</param>
        /// <returns>New TrackModel instance containing the information about the audio file</returns>
        static TrackModel fromFile(const String& filePath, AudioFormatManager& formatReader);
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

        /// <summary>
        /// Pointer to an array containing the list of tracks
        /// </summary>
        const std::shared_ptr<std::vector<TrackModel>> tracks;

        /// <summary>
        /// Broadcaster for the ItemDoubleClicked event
        /// </summary>
        ActionBroadcaster itemDoubleClickedEventBroadcaster;
        /// <summary>
        /// Contains the search text inputted in the Search text field
        /// </summary>
        String searchText;
    };

	/// <summary>
	/// Add a new track to the Track array
	/// </summary>
	/// <param name="track">Track to add to the list of tracks</param>
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

    /// <summary>
    /// Set the Search text received by the toolbar in the grid, so to highlight the file colour for the matches
    /// </summary>
    /// <param name="text">Text to search for in the file names contained in the track list</param>
    void setSearchText(String text);

    /// <summary>
    /// Reference to an instance of PlaylistTableListBoxModel
    /// </summary>
    /// <returns>A reference to an instance of PlaylistTableListBoxModel</returns>
    PlaylistTableListBoxModel& getGridBoxModel();

private:
	//Instance of AudioFormatManager
    AudioFormatManager formatManager;
	//List of tracks
    std::shared_ptr<std::vector<TrackModel>> tracks;
	//Component displaying the actual data grid
    TableListBox playlistDataGrid;
	//Instance of TableListBoxModel
    PlaylistTableListBoxModel playlistDataGridBoxModel;
	
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistGrid)
};
