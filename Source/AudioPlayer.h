/*
  ==============================================================================

    AudioPlayer.h
    Created: 16 Aug 2020 8:26:02am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================

/// <summary>
/// AudioPlayer implements the actual player. It exposes the functionalities to
/// control the audio playback
/// </summary>
class AudioPlayer  :
	public juce::AudioSource
{
public:
    /// <summary>
    /// Creates an instance of the class
    /// </summary>
    /// <param name="_formatManager">Reference to an instance of AudioFormatManager</param>
    AudioPlayer(AudioFormatManager& _formatManager);

	//Overrides for the virtual methods of AudioSource class
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    /// <summary>
    /// Load the file pointed to by the input parameter and makes it ready to play
    /// </summary>
    /// <param name="audioURL">Full path of the audio file to play</param>
    void loadURL(URL audioURL);
    /// <summary>
    /// Set the gain of player
    /// </summary>
    /// <param name="gain">New value to set the gain to</param>
    void setGain(double gain);
    /// <summary>
    /// Set the speed of playback of the player
    /// </summary>
    /// <param name="ratio">New speed for the player in terms of ratio to the normal speed</param>
    void setSpeed(double ratio);
    /// <summary>
    /// Set the new position in the audio file where to start reproducing
    /// </summary>
    /// <param name="posInSecs">New position in the file, expressed in seconds</param>
    void setPosition(double posInSecs);
    /// <summary>
    /// Set the new position in the audio file where to start reproducing
    /// </summary>
    /// <param name="pos">New position relative to the lenght of the file. 0 is the beginning, 1 is the end</param>
    void setPositionRelative(double pos);
    /// <summary>
    /// Returns whether the player is actually playing.
    /// </summary>
    /// <returns></returns>
    bool isPlaying();

    /// <summary>
    /// Start the player
    /// </summary>
    void start();
    /// <summary>
    /// Stop the player
    /// </summary>
    void stop();

    /// <summary>
    /// Get the relative position of the playhead
    /// </summary>
    /// <returns>Relative position of the playhead</returns>
    double getPositionRelative();

private:
	//Reference to an instance of AudioFormatManager. Passed in as constructor parameter
    AudioFormatManager& formatManager;
	//Pointer to an AudioFormatReaderSource instance.
    std::unique_ptr<AudioFormatReaderSource> readerSource;
	//Instance of AudioTransportSource
    AudioTransportSource transportSource;
	//Instance of ResamplingAudioSource
    ResamplingAudioSource resampleSource{ &transportSource, false, 2 };
	
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayer)
};
