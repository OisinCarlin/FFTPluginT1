/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FFTPluginT1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FFTPluginT1AudioProcessorEditor (FFTPluginT1AudioProcessor&);
    ~FFTPluginT1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override
    //=========== ADDED =======================
    {
        titleLabel   .setBounds (10,  10, getWidth() - 20,  30);
//        inputText    .setBounds (100, 50, getWidth() - 110, 20);
        
        uppercaseLabel    .setBounds (getWidth() / 8, 50, getWidth() - 110, 20);
        uppercaseText.setBounds (getWidth() / 8, 80, getWidth() - 210, 20);
        
        updateFundamentalButton.setBounds(getWidth() / 6, getHeight() / 4 * 3, 100, 50);
        
    }
    //=========== ADDED =======================
    ;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    
    //=========== ADDED =======================
    juce::Label titleLabel;
    juce::Label inputLabel;
    juce::Label inputText;
    juce::Label uppercaseLabel;
    juce::Label uppercaseText;
    
    juce::TextButton updateFundamentalButton {"Update Fundamental"};
    
//    juce::TextButton
    //=========== ADDED =======================
    
    FFTPluginT1AudioProcessor& audioProcessor;
   

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FFTPluginT1AudioProcessorEditor)
};
