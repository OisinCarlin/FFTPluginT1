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
    titleLabel.setText ("Tuner", juce::dontSendNotification);
    titleLabel.setColour (juce::Label::textColourId, juce::Colours::lightgreen);
    titleLabel.setJustificationType (juce::Justification::centred);
    
    addAndMakeVisible (fundamentalFreqLabel);
    fundamentalFreqLabel.setText ("Fundamental Frequency (Hz):", juce::dontSendNotification);
    fundamentalFreqLabel.setColour (juce::Label::textColourId, juce::Colours::orange);
    fundamentalFreqLabel.setJustificationType (juce::Justification::left);
    
    addAndMakeVisible (fundamentalFreqText);
    fundamentalFreqText.setColour (juce::Label::backgroundColourId, juce::Colours::darkblue);
    fundamentalFreqText.setJustificationType (juce::Justification::left);
    
    addAndMakeVisible (tuningLabel);
    tuningLabel.setText ("Tuning:", juce::dontSendNotification);
    tuningLabel.setColour (juce::Label::textColourId, juce::Colours::orange);
    tuningLabel.setJustificationType (juce::Justification::left);
    
    addAndMakeVisible (pitchLetter);
    pitchLetter.setColour (juce::Label::backgroundColourId, juce::Colours::darkblue);
    pitchLetter.setJustificationType (juce::Justification::left);
    
    // ======== UPDATE BUTTON WITH ON-CLICK UPDATE OF FUNDAMENTAL FREQUENCY & CONVERSION TO PITCH NOTE TO DISPLAY ========
    
    addAndMakeVisible(updateFundamentalButton);
    updateFundamentalButton.setClickingTogglesState(true);
    updateFundamentalButton.onClick = [this] {
        
        // Assign audioProcessor.fftValue (fundamental frequency) to a local variable for Pitch Note Conversion
        freqValue = audioProcessor.fftValue;
        
        if ((freqValue >= c0lowerBoundary && freqValue <= c0upperBoundary) ||
            (freqValue >= c1lowerBoundary && freqValue <= c1upperBoundary) ||
            (freqValue >= c2lowerBoundary && freqValue <= c2upperBoundary) ||
            (freqValue >= c3lowerBoundary && freqValue <= c3upperBoundary) ||
            (freqValue >= c4lowerBoundary && freqValue <= c4upperBoundary) ||
            (freqValue >= c5lowerBoundary && freqValue <= c5upperBoundary) ||
            (freqValue >= c6lowerBoundary && freqValue <= c6upperBoundary) ||
            (freqValue >= c7lowerBoundary && freqValue <= c7upperBoundary) ||
            (freqValue >= c8lowerBoundary && freqValue <= c8upperBoundary) ||
            (freqValue >= c9lowerBoundary && freqValue <= c9upperBoundary) ||
            (freqValue >= c10lowerBoundary && freqValue <= c10upperBoundary)
            )
        {
            pitchLetter.setText("C", juce::dontSendNotification);
        } else
            if ((freqValue >= csharp0lowerBoundary && freqValue <= csharp0upperBoundary) ||
                (freqValue >= csharp1lowerBoundary && freqValue <= csharp1upperBoundary) ||
                (freqValue >= csharp2lowerBoundary && freqValue <= csharp2upperBoundary) ||
                (freqValue >= csharp3lowerBoundary && freqValue <= csharp3upperBoundary) ||
                (freqValue >= csharp4lowerBoundary && freqValue <= csharp4upperBoundary) ||
                (freqValue >= csharp5lowerBoundary && freqValue <= csharp5upperBoundary) ||
                (freqValue >= csharp6lowerBoundary && freqValue <= csharp6upperBoundary) ||
                (freqValue >= csharp7lowerBoundary && freqValue <= csharp7upperBoundary) ||
                (freqValue >= csharp8lowerBoundary && freqValue <= csharp8upperBoundary) ||
                (freqValue >= csharp9lowerBoundary && freqValue <= csharp9upperBoundary) ||
                (freqValue >= csharp10lowerBoundary && freqValue <= csharp10upperBoundary)
                )
            {
                pitchLetter.setText("C# / Db", juce::dontSendNotification);
            } else
                if ((freqValue >= d0lowerBoundary && freqValue <= d0upperBoundary) ||
                    (freqValue >= d1lowerBoundary && freqValue <= d1upperBoundary) ||
                    (freqValue >= d2lowerBoundary && freqValue <= d2upperBoundary) ||
                    (freqValue >= d3lowerBoundary && freqValue <= d3upperBoundary) ||
                    (freqValue >= d4lowerBoundary && freqValue <= d4upperBoundary) ||
                    (freqValue >= d5lowerBoundary && freqValue <= d5upperBoundary) ||
                    (freqValue >= d6lowerBoundary && freqValue <= d6upperBoundary) ||
                    (freqValue >= d7lowerBoundary && freqValue <= d7upperBoundary) ||
                    (freqValue >= d8lowerBoundary && freqValue <= d8upperBoundary) ||
                    (freqValue >= d9lowerBoundary && freqValue <= d9upperBoundary) ||
                    (freqValue >= d10lowerBoundary && freqValue <= d10upperBoundary)
                    )
                {
                    pitchLetter.setText("D", juce::dontSendNotification);
                } else
                    if ((freqValue >= dsharp0lowerBoundary && freqValue <= dsharp0upperBoundary) ||
                        (freqValue >= dsharp1lowerBoundary && freqValue <= dsharp1upperBoundary) ||
                        (freqValue >= dsharp2lowerBoundary && freqValue <= dsharp2upperBoundary) ||
                        (freqValue >= dsharp3lowerBoundary && freqValue <= dsharp3upperBoundary) ||
                        (freqValue >= dsharp4lowerBoundary && freqValue <= dsharp4upperBoundary) ||
                        (freqValue >= dsharp5lowerBoundary && freqValue <= dsharp5upperBoundary) ||
                        (freqValue >= dsharp6lowerBoundary && freqValue <= dsharp6upperBoundary) ||
                        (freqValue >= dsharp7lowerBoundary && freqValue <= dsharp7upperBoundary) ||
                        (freqValue >= dsharp8lowerBoundary && freqValue <= dsharp8upperBoundary) ||
                        (freqValue >= dsharp9lowerBoundary && freqValue <= dsharp9upperBoundary) ||
                        (freqValue >= dsharp10lowerBoundary && freqValue <= dsharp10upperBoundary)
                        )
                    {
                        pitchLetter.setText("D# / Eb", juce::dontSendNotification);
                    } else
                        if ((freqValue >= e0lowerBoundary && freqValue <= e0upperBoundary) ||
                            (freqValue >= e1lowerBoundary && freqValue <= e1upperBoundary) ||
                            (freqValue >= e2lowerBoundary && freqValue <= e2upperBoundary) ||
                            (freqValue >= e3lowerBoundary && freqValue <= e3upperBoundary) ||
                            (freqValue >= e4lowerBoundary && freqValue <= e4upperBoundary) ||
                            (freqValue >= e5lowerBoundary && freqValue <= e5upperBoundary) ||
                            (freqValue >= e6lowerBoundary && freqValue <= e6upperBoundary) ||
                            (freqValue >= e7lowerBoundary && freqValue <= e7upperBoundary) ||
                            (freqValue >= e8lowerBoundary && freqValue <= e8upperBoundary) ||
                            (freqValue >= e9lowerBoundary && freqValue <= e9upperBoundary) ||
                            (freqValue >= e10lowerBoundary && freqValue <= e10upperBoundary)
                            )
                        {
                            pitchLetter.setText("E", juce::dontSendNotification);
                        } else
                            if ((freqValue >= f0lowerBoundary && freqValue <= f0upperBoundary) ||
                                (freqValue >= f1lowerBoundary && freqValue <= f1upperBoundary) ||
                                (freqValue >= f2lowerBoundary && freqValue <= f2upperBoundary) ||
                                (freqValue >= f3lowerBoundary && freqValue <= f3upperBoundary) ||
                                (freqValue >= f4lowerBoundary && freqValue <= f4upperBoundary) ||
                                (freqValue >= f5lowerBoundary && freqValue <= f5upperBoundary) ||
                                (freqValue >= f6lowerBoundary && freqValue <= f6upperBoundary) ||
                                (freqValue >= f7lowerBoundary && freqValue <= f7upperBoundary) ||
                                (freqValue >= f8lowerBoundary && freqValue <= f8upperBoundary) ||
                                (freqValue >= f9lowerBoundary && freqValue <= f9upperBoundary) ||
                                (freqValue >= f10lowerBoundary && freqValue <= f10upperBoundary)
                                )
                            {
                                pitchLetter.setText("F", juce::dontSendNotification);
                            } else
                                if ((freqValue >= fsharp0lowerBoundary && freqValue <= fsharp0upperBoundary) ||
                                    (freqValue >= fsharp1lowerBoundary && freqValue <= fsharp1upperBoundary) ||
                                    (freqValue >= fsharp2lowerBoundary && freqValue <= fsharp2upperBoundary) ||
                                    (freqValue >= fsharp3lowerBoundary && freqValue <= fsharp3upperBoundary) ||
                                    (freqValue >= fsharp4lowerBoundary && freqValue <= fsharp4upperBoundary) ||
                                    (freqValue >= fsharp5lowerBoundary && freqValue <= fsharp5upperBoundary) ||
                                    (freqValue >= fsharp6lowerBoundary && freqValue <= fsharp6upperBoundary) ||
                                    (freqValue >= fsharp7lowerBoundary && freqValue <= fsharp7upperBoundary) ||
                                    (freqValue >= fsharp8lowerBoundary && freqValue <= fsharp8upperBoundary) ||
                                    (freqValue >= fsharp9lowerBoundary && freqValue <= fsharp9upperBoundary) ||
                                    (freqValue >= fsharp10lowerBoundary && freqValue <= fsharp10upperBoundary)
                                    )
                                {
                                    pitchLetter.setText("F# / Gb", juce::dontSendNotification);
                                } else
                                    if ((freqValue >= g0lowerBoundary && freqValue <= g0upperBoundary) ||
                                        (freqValue >= g1lowerBoundary && freqValue <= g1upperBoundary) ||
                                        (freqValue >= g2lowerBoundary && freqValue <= g2upperBoundary) ||
                                        (freqValue >= g3lowerBoundary && freqValue <= g3upperBoundary) ||
                                        (freqValue >= g4lowerBoundary && freqValue <= g4upperBoundary) ||
                                        (freqValue >= g5lowerBoundary && freqValue <= g5upperBoundary) ||
                                        (freqValue >= g6lowerBoundary && freqValue <= g6upperBoundary) ||
                                        (freqValue >= g7lowerBoundary && freqValue <= g7upperBoundary) ||
                                        (freqValue >= g8lowerBoundary && freqValue <= g8upperBoundary) ||
                                        (freqValue >= g9lowerBoundary && freqValue <= g9upperBoundary) ||
                                        (freqValue >= g10lowerBoundary && freqValue <= g10upperBoundary)
                                        )
                                    {
                                        pitchLetter.setText("G", juce::dontSendNotification);
                                    } else
                                        if ((freqValue >= gsharp0lowerBoundary && freqValue <= gsharp0upperBoundary) ||
                                            (freqValue >= gsharp1lowerBoundary && freqValue <= gsharp1upperBoundary) ||
                                            (freqValue >= gsharp2lowerBoundary && freqValue <= gsharp2upperBoundary) ||
                                            (freqValue >= gsharp3lowerBoundary && freqValue <= gsharp3upperBoundary) ||
                                            (freqValue >= gsharp4lowerBoundary && freqValue <= gsharp4upperBoundary) ||
                                            (freqValue >= gsharp5lowerBoundary && freqValue <= gsharp5upperBoundary) ||
                                            (freqValue >= gsharp6lowerBoundary && freqValue <= gsharp6upperBoundary) ||
                                            (freqValue >= gsharp7lowerBoundary && freqValue <= gsharp7upperBoundary) ||
                                            (freqValue >= gsharp8lowerBoundary && freqValue <= gsharp8upperBoundary) ||
                                            (freqValue >= gsharp9lowerBoundary && freqValue <= gsharp9upperBoundary) ||
                                            (freqValue >= gsharp10lowerBoundary && freqValue <= gsharp10upperBoundary)
                                            )
                                        {
                                            pitchLetter.setText("G# / Ab", juce::dontSendNotification);
                                        } else
                                            if ((freqValue >= a0lowerBoundary && freqValue <= a0upperBoundary) ||
                                                (freqValue >= a1lowerBoundary && freqValue <= a1upperBoundary) ||
                                                (freqValue >= a2lowerBoundary && freqValue <= a2upperBoundary) ||
                                                (freqValue >= a3lowerBoundary && freqValue <= a3upperBoundary) ||
                                                (freqValue >= a4lowerBoundary && freqValue <= a4upperBoundary) ||
                                                (freqValue >= a5lowerBoundary && freqValue <= a5upperBoundary) ||
                                                (freqValue >= a6lowerBoundary && freqValue <= a6upperBoundary) ||
                                                (freqValue >= a7lowerBoundary && freqValue <= a7upperBoundary) ||
                                                (freqValue >= a8lowerBoundary && freqValue <= a8upperBoundary) ||
                                                (freqValue >= a9lowerBoundary && freqValue <= a9upperBoundary) ||
                                                (freqValue >= a10lowerBoundary && freqValue <= a10upperBoundary)
                                                )
                                            {
                                                pitchLetter.setText("A", juce::dontSendNotification);
                                            } else
                                                if ((freqValue >= asharp0lowerBoundary && freqValue <= asharp0upperBoundary) ||
                                                    (freqValue >= asharp1lowerBoundary && freqValue <= asharp1upperBoundary) ||
                                                    (freqValue >= asharp2lowerBoundary && freqValue <= asharp2upperBoundary) ||
                                                    (freqValue >= asharp3lowerBoundary && freqValue <= asharp3upperBoundary) ||
                                                    (freqValue >= asharp4lowerBoundary && freqValue <= asharp4upperBoundary) ||
                                                    (freqValue >= asharp5lowerBoundary && freqValue <= asharp5upperBoundary) ||
                                                    (freqValue >= asharp6lowerBoundary && freqValue <= asharp6upperBoundary) ||
                                                    (freqValue >= asharp7lowerBoundary && freqValue <= asharp7upperBoundary) ||
                                                    (freqValue >= asharp8lowerBoundary && freqValue <= asharp8upperBoundary) ||
                                                    (freqValue >= asharp9lowerBoundary && freqValue <= asharp9upperBoundary) ||
                                                    (freqValue >= asharp10lowerBoundary && freqValue <= asharp10upperBoundary)
                                                    )
                                                {
                                                    pitchLetter.setText("A# / Bb", juce::dontSendNotification);
                                                } else
                                                    if ((freqValue >= b0lowerBoundary && freqValue <= b0upperBoundary) ||
                                                        (freqValue >= b1lowerBoundary && freqValue <= b1upperBoundary) ||
                                                        (freqValue >= b2lowerBoundary && freqValue <= b2upperBoundary) ||
                                                        (freqValue >= b3lowerBoundary && freqValue <= b3upperBoundary) ||
                                                        (freqValue >= b4lowerBoundary && freqValue <= b4upperBoundary) ||
                                                        (freqValue >= b5lowerBoundary && freqValue <= b5upperBoundary) ||
                                                        (freqValue >= b6lowerBoundary && freqValue <= b6upperBoundary) ||
                                                        (freqValue >= b7lowerBoundary && freqValue <= b7upperBoundary) ||
                                                        (freqValue >= b8lowerBoundary && freqValue <= b8upperBoundary) ||
                                                        (freqValue >= b9lowerBoundary && freqValue <= b9upperBoundary) ||
                                                        (freqValue >= b10lowerBoundary && freqValue <= b10upperBoundary)
                                                        )
                                                    {
                                                        pitchLetter.setText("B", juce::dontSendNotification);
                                                    } else
                                                    {
                                                        pitchLetter.setText("-", juce::dontSendNotification);
                                                    }
        
        // ================ UPDATE FUNDAMENTAL FREQUENCY TO DISPLAY ================
        
        fundamentalFreqText.setText (std::to_string(audioProcessor.fftValue),
                                     juce::dontSendNotification);
        
    };

}

FFTPluginT1AudioProcessorEditor::~FFTPluginT1AudioProcessorEditor()
{
}


void FFTPluginT1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    
}



// ============== MOVED TO HEADER FILE =============
//void FFTPluginT1AudioProcessorEditor::resized()
//{
//    
//    // This is generally where you'll want to lay out the positions of any
//    // subcomponents in your editor..
//    
//    
//}
// =================================================
