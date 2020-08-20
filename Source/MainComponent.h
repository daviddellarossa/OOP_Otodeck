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
class MainComponent final :
    public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
	//Override of virtual methods from AudioAppComponent
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
	//Override of virtual methods from Component
    void paint (Graphics& g) override;
    void resized() override;
    //==============================================================================

	//Thread-safe wrapper for Level, used to send the current audio levels to the left VuMeter
    Atomic<Level> leftLevel;
    //Thread-safe wrapper for Level, used to send the current audio levels to the right VuMeter
    Atomic<Level> rightLevel;
private:
    //TooltipWindow manager used to display tooltip info when hovering on UI controls
    TooltipWindow tooltipWindow;
	
    AudioFormatManager formatManager;
    AudioThumbnailCache thumbCache{100}; 
    MixerAudioSource mixerSource;
	
    //Aggregate components containing all the parts making up the playlist UI controls.
    PlaylistAggregateComponent leftPlaylistComponent;
    PlaylistAggregateComponent rightPlaylistComponent;

	//Audio players
    AudioPlayer leftPlayer;
    AudioPlayer rightPlayer;

	//Aggregate components containing all the parts making up the player UI controls
    PlayerAggregateComponent leftPlayerComponent;
    PlayerAggregateComponent rightPlayerComponent;

	//Listener invoked by the left PlaylistAggregateComponent when there is a change of selected track
    ExternalCallbackActionListener TrackSelectedToPlayLeftListener;
    //Listener invoked by the right PlaylistAggregateComponent when there is a change of selected track
    ExternalCallbackActionListener TrackSelectedToPlayRightListener;

    //Listener invoked by the left MixerChannel when there is a change in volume 
    ExternalCallbackActionListener LeftVolumeChangedListener;
    //Listener invoked by the right MixerChannel when there is a change in volume 
    ExternalCallbackActionListener RightVolumeChangedListener;

	//Left instance of MixerChannel
    MixerChannel leftChannel;
    //Right instance of MixerChannel
    MixerChannel rightChannel;

	//Left instance of VuMeter
    VuMeter leftVuMeter;
    //Right instance of VuMeter
	VuMeter rightVuMeter;

    //Callback method invoked when a track is selected
    void TrackSelectedToPlayCallback(const String& message, PlayerAggregateComponent& player);

    //Callback method invoked when the volume changes
    void VolumeChangedCallback(const String& message, PlayerAggregateComponent& player);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
