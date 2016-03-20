/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class Vibrato2pluginAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    Vibrato2pluginAudioProcessorEditor (Vibrato2pluginAudioProcessor&);
    ~Vibrato2pluginAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    class ParameterSlider;
    
    Label  amplitudeLabel, frequencyLabel;
    ScopedPointer<ParameterSlider> amplitudeSlider, frequencySlider;
    
    Vibrato2pluginAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Vibrato2pluginAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED