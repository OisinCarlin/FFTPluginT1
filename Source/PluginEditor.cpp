/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
FFTPluginT1AudioProcessorEditor::FFTPluginT1AudioProcessorEditor (FFTPluginT1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    
    setSize (400, 300);
    
    // ================ ADDED ==================================
    addAndMakeVisible (titleLabel);
    titleLabel.setFont (juce::Font (16.0f, juce::Font::bold));
    titleLabel.setText ("Click in the white box to enter some text...", juce::dontSendNotification);
    titleLabel.setColour (juce::Label::textColourId, juce::Colours::lightgreen);
    titleLabel.setJustificationType (juce::Justification::centred);

    addAndMakeVisible (inputLabel);
    inputLabel.setText ("Text input:", juce::dontSendNotification);
    inputLabel.attachToComponent (&inputText, true);
    inputLabel.setColour (juce::Label::textColourId, juce::Colours::orange);
    inputLabel.setJustificationType (juce::Justification::right);

    addAndMakeVisible (uppercaseLabel);
    uppercaseLabel.setText ("Uppercase:", juce::dontSendNotification);
    uppercaseLabel.attachToComponent (&uppercaseText, true);
    uppercaseLabel.setColour (juce::Label::textColourId, juce::Colours::orange);
    uppercaseLabel.setJustificationType (juce::Justification::right);

    addAndMakeVisible (uppercaseText);
    uppercaseText.setColour (juce::Label::backgroundColourId, juce::Colours::darkblue);
    
    
    addAndMakeVisible (inputText);
    inputText.setEditable (true);
    inputText.setColour (juce::Label::backgroundColourId, juce::Colours::darkblue);
//    inputText.onTextChange = [this] { uppercaseText.setText (inputText.getText().toUpperCase(), juce::dontSendNotification); };
    inputText.onTextChange = [this] { uppercaseText.setText (std::to_string(audioProcessor.fftValue), juce::dontSendNotification); };
    // ================ ADDED ==================================
    

}

FFTPluginT1AudioProcessorEditor::~FFTPluginT1AudioProcessorEditor()
{
}

//==============================================================================
void FFTPluginT1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    
    
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);

}


// ============== REMOVED =============
//void FFTPluginT1AudioProcessorEditor::resized()
//{
//    
//    // This is generally where you'll want to lay out the positions of any
//    // subcomponents in your editor..
//    
//    
//}
// ============== REMOVED =============
