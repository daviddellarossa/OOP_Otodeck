///*
//  ==============================================================================
//
//    PlaylistGridModel.h
//    Created: 12 Aug 2020 10:01:01pm
//    Author:  david
//
//  ==============================================================================
//*/
//
//#pragma once
//
//#include <JuceHeader.h>
//
////==============================================================================
///*
//*/
//class PlaylistGridModel  : public juce::TableListBoxModel
//{
//public:
//
//
//    PlaylistGridModel() = default;
//    ~PlaylistGridModel() override = default;
//
//    int getNumRows() override;
//
//    void paintRowBackground(
//        Graphics&,
//        int rowNumber,
//        int width,
//        int height,
//        bool rowIsSelected
//    ) override;
//
//    void paintCell(
//        Graphics&,
//        int rowNumber,
//        int columnId,
//        int width,
//        int height,
//        bool rowIsSelected
//    ) override;
//
//    virtual void cellClicked(int rowNumber, int columnId, const MouseEvent&) override;
//
//    Component* refreshComponentForCell(
//        int rowNumber,
//        int columnId,
//        bool isRowSelected,
//        Component* existingComponentToUpdate
//    ) override;
//
//
//
//
//
//	
//private:
//    std::vector<TrackModel> trackTitles;
//	
//    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistGridModel)
//};
