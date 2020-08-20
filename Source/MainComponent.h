/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PlaylistAggregateComponent.h"
#include "PlayerAggregateComponent.h"
#include "AudioPlayer.h"
#include "MixerChannel.h"
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

    void VolumeChangedCallback(const String& message, PlayerAggregateComponent& player);

    Atomic<Level> leftLevel;
    Atomic<Level> rightLevel;
private:

    TooltipWindow tooltipWindow;
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100}; 

    MixerAudioSource mixerSource;

    PlaylistAggregateComponent leftPlaylistComponent;
    PlaylistAggregateComponent rightPlaylistComponent;

    AudioPlayer leftPlayer;
    AudioPlayer rightPlayer;

    PlayerAggregateComponent leftPlayerComponent;
    PlayerAggregateComponent rightPlayerComponent;

	//Listeners from PlaylistAggregateComponent
    ExternalCallbackActionListener TrackSelectedToPlayLeftListener;
    ExternalCallbackActionListener TrackSelectedToPlayRightListener;

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
