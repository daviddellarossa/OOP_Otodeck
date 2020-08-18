/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"
#include "PlaylistAggregateComponent.h"
#include "PlayerAggregateComponent.h"
#include "AudioPlayer.h"
#include "MixerAggregateComponent.h"
#include "ScratchAggregateComponent.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

    void TrackSelectedToPlayCallback(const String& message, PlayerAggregateComponent& player);

    void SpeedChangedCallback(const String& message, PlayerAggregateComponent& player);

private:
    //==============================================================================
    // Your private member variables go here...
     
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100}; 

    MixerAudioSource mixerSource;
    MixerAggregateComponent mixerPanelComponent;

    PlaylistAggregateComponent leftPlaylistComponent;
    PlaylistAggregateComponent rightPlaylistComponent;

    AudioPlayer leftPlayer;
    AudioPlayer rightPlayer;

    DeckGUI deckGUI1{ &leftPlayer, formatManager, thumbCache };
    DeckGUI deckGUI2{ &rightPlayer, formatManager, thumbCache };
    PlayerAggregateComponent leftPlayerComponent;
    PlayerAggregateComponent rightPlayerComponent;

    ScratchAggregateComponent leftScratchDock;
    ScratchAggregateComponent rightScratchDock;

    ExternalCallbackActionListener TrackSelectedToPlayLeftListener;
    ExternalCallbackActionListener TrackSelectedToPlayRightListener;
    ExternalCallbackActionListener SpeedChangedLeftListener;
    ExternalCallbackActionListener SpeedChangedRightListener;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
