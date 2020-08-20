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
#include "VuMeter.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent :
    public AudioAppComponent

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

    //void SpeedChangedCallback(const String& message, PlayerAggregateComponent& player);

    void VolumeChangedCallback(const String& message, PlayerAggregateComponent& player);

    void audioCallback(AudioIODeviceCallback* newCallback);

    //void volumeChangedCallback1(double value);

    Atomic<Level> leftLevel;
    Atomic<Level> rightLevel;
private:
    //==============================================================================
    // Your private member variables go here...

    TooltipWindow tooltipWindow;
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100}; 

    MixerAudioSource mixerSource;
    //MixerAggregateComponent mixerPanelComponent;

    PlaylistAggregateComponent leftPlaylistComponent;
    PlaylistAggregateComponent rightPlaylistComponent;

    AudioPlayer leftPlayer;
    AudioPlayer rightPlayer;

    //DeckGUI deckGUI1{ &leftPlayer, formatManager, thumbCache };
    //DeckGUI deckGUI2{ &rightPlayer, formatManager, thumbCache };
    PlayerAggregateComponent leftPlayerComponent;
    PlayerAggregateComponent rightPlayerComponent;

    //ScratchAggregateComponent leftScratchDock;
    //ScratchAggregateComponent rightScratchDock;

	//Listeners from PlaylistAggregateComponent
    ExternalCallbackActionListener TrackSelectedToPlayLeftListener;
    ExternalCallbackActionListener TrackSelectedToPlayRightListener;

	//Listeners from ScratchAggregateComponent
    //ExternalCallbackActionListener SpeedChangedLeftListener;
    //ExternalCallbackActionListener SpeedChangedRightListener;

	//Listener for MixerAggregateComponent
    ExternalCallbackActionListener LeftVolumeChangedListener;
    ExternalCallbackActionListener RightVolumeChangedListener;

    MixerChannel leftChannel;
    MixerChannel rightChannel;
    //ExternalCallbackSliderListener LeftVolumeChangedListener1;

    VuMeter leftVuMeter;
    VuMeter rightVuMeter;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
