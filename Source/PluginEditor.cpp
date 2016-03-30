/*
  ==============================================================================

    This file was auto-generated by the Introjucer!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

class Vibrato2pluginAudioProcessorEditor::ParameterSlider   : public Slider,
                                                              private Timer
{
public:
    ParameterSlider (AudioProcessorParameter& p)
    : Slider (p.getName (256)), param (p)
    {
        setRange (0.0, 1.0, 0.0);
        startTimerHz (30);
        updateSliderPos();
    }
    
    void valueChanged() override
    {
        param.setValueNotifyingHost ((float) Slider::getValue());
    }
    
    void timerCallback() override       { updateSliderPos(); }
    
    void startedDragging() override     { param.beginChangeGesture(); }
    void stoppedDragging() override     { param.endChangeGesture();   }
    
    double getValueFromText (const String& text) override   { return param.getValueForText (text); }
    String getTextFromValue (double value) override         { return param.getText ((float) value, 1024); }
    
    void updateSliderPos()
    {
        const float newValue = param.getValue();
        
        if (newValue != (float) Slider::getValue() && ! isMouseButtonDown())
            Slider::setValue (newValue);
    }
    
    AudioProcessorParameter& param;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterSlider)
};



//==============================================================================
Vibrato2pluginAudioProcessorEditor::Vibrato2pluginAudioProcessorEditor (Vibrato2pluginAudioProcessor& p)
    : AudioProcessorEditor (&p),
      amplitudeLabel(String::empty, "Vibrato Ampl"),
      frequencyLabel(String::empty, "Vibrato Freq"),
      processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
//    //Give plugin a name
//    pluginName.setText("Chan Yin");
//    addAndMakeVisible(pluginName);
    
    //Instantiate Sliders
    addAndMakeVisible(amplitudeSlider = new ParameterSlider ( *p.getParamLocal(0) ));
    amplitudeSlider->setSliderStyle (Slider::Rotary);

    addAndMakeVisible(frequencySlider = new ParameterSlider ( *p.getParamLocal(1) ));
    frequencySlider->setSliderStyle (Slider::Rotary);
    
    
    //Labels to Sliders
    amplitudeLabel.attachToComponent(amplitudeSlider, false);
    frequencyLabel.attachToComponent(frequencySlider, false);

    //Instantiate bypass button
    bypassButton.setButtonText("Bypass");
    addAndMakeVisible(bypassButton);
    bypassButton.addListener(this);
    
    
    
    setSize (400, 300);
}


Vibrato2pluginAudioProcessorEditor::~Vibrato2pluginAudioProcessorEditor()
{
}

//==============================================================================
void Vibrato2pluginAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.setFont (Font("Times New Roman", 18.0f, Font::bold | Font::italic));
    g.drawText("Chan Yin Plugin", proportionOfWidth(0.4f), proportionOfHeight(0.1f), proportionOfWidth(0.3f), proportionOfHeight(0.15f), true);
}

void Vibrato2pluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    Rectangle<int> r (getLocalBounds().reduced (8));
    
    r.removeFromTop (100);
    Rectangle<int> sliderArea (r.removeFromTop (50));
    
    amplitudeSlider->setBounds (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth() / 2)));
    frequencySlider->setBounds (sliderArea.removeFromLeft (jmin (180, sliderArea.getWidth())));
    
    bypassButton.setBounds(proportionOfWidth (0.1f), proportionOfHeight (0.800f), proportionOfWidth (0.2500f), proportionOfHeight (0.0600f));
    

}

void Vibrato2pluginAudioProcessorEditor:: sliderValueChanged(Slider *slider) {
    
}

void Vibrato2pluginAudioProcessorEditor:: buttonClicked(Button* buttonIsClicked) {
    if (buttonIsClicked == &bypassButton) {
        bypassButtonState = bypassButton.getToggleState();
        processor.setBypass(bypassButtonState);
    }
}