/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

using std::string;


class FFTPluginT1AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    FFTPluginT1AudioProcessorEditor (FFTPluginT1AudioProcessor&);
    ~FFTPluginT1AudioProcessorEditor() override;
    
    void paint (juce::Graphics&) override;
    void resized() override
    {
        titleLabel   .setBounds (10,  10, getWidth() - 20,  30);
        
        fundamentalFreqLabel.setBounds (getWidth() / 8, 50, getWidth() - 110, 20);
        fundamentalFreqText.setBounds (getWidth() / 8, 80, getWidth() - 210, 20);
        
        updateFundamentalButton.setBounds(getWidth() / 6, getHeight() / 4 * 3, 100, 50);
        
        tuningLabel.setBounds(getWidth() / 8, 130, getWidth() - 110, 20);
        pitchLetter.setBounds (getWidth() / 8, 180, getWidth() - 210, 20);
    };
    
private:
    
    //======================= LABEL DECLARATIONS =======================
    juce::Label titleLabel;
    
    juce::Label fundamentalFreqLabel;
    juce::Label fundamentalFreqText;
    
    juce::Label pitchLetter;
    juce::Label tuningLabel;
    
    // ======== FUNDAMENTAL FREQ VALUE FOR PITCH NOTE CONVERSION ========
    float freqValue;
    
    // ============= NOTE 2 FREQUENCIES IN HERTZ ========================
    float c2 = 65.4064;
    float csharp2 = 69.2957;
    float d2 = 73.4162;
    float dsharp2 = 77.7817;
    float e2 = 82.4069;
    float f2 = 87.3071;
    float fsharp2 = 92.4986;
    float g2 = 97.9989;
    float gsharp2 = 103.8262;
    float a2 = 110.0000;
    float asharp2 = 116.5409;
    float b2 = 123.4708;
    
    // ============= NOTE 2 BOUNDARIES CALCULATIONS ========================
    float c2lowerBoundary = c2 - ((c2 - 61.74) / 2);
    float c2upperBoundary = c2 + ((csharp2 - c2) / 2);
    
    float csharp2lowerBoundary = csharp2 - ((csharp2 - c2) / 2);
    float csharp2upperBoundary = csharp2 + ((d2 - csharp2) / 2);
    
    float d2lowerBoundary = d2 - ((d2 - csharp2) / 2);
    float d2upperBoundary = d2 + ((dsharp2 - d2) / 2);
    
    float dsharp2lowerBoundary = dsharp2 - ((dsharp2 - d2) / 2);
    float dsharp2upperBoundary = dsharp2 + ((e2 - dsharp2) / 2);
    
    float e2lowerBoundary = e2 - ((e2 - dsharp2) / 2);
    float e2upperBoundary = e2 + ((f2 - e2) / 2);
    
    float f2lowerBoundary = f2 - ((f2 - e2) / 2);
    float f2upperBoundary = f2 + ((fsharp2 - f2) / 2);
    
    float fsharp2lowerBoundary = fsharp2 - ((fsharp2 - f2) / 2);
    float fsharp2upperBoundary = fsharp2 + ((g2 - fsharp2) / 2);
    
    float g2lowerBoundary = g2 - ((g2 - fsharp2) / 2);
    float g2upperBoundary = g2 + ((gsharp2 - g2) / 2);
    
    float gsharp2lowerBoundary = gsharp2 - ((gsharp2 - g2) / 2);
    float gsharp2upperBoundary = gsharp2 + ((a2 - gsharp2) / 2);
    
    float a2lowerBoundary = a2 - ((a2 - gsharp2) / 2);
    float a2upperBoundary = a2 + ((asharp2 - a2) / 2);
    
    float asharp2lowerBoundary = asharp2 - ((asharp2 - a2) / 2);
    float asharp2upperBoundary = asharp2 + ((b2 - asharp2) / 2);
    
    float b2lowerBoundary = b2 - ((b2 - asharp2) / 2);
    float b2upperBoundary = b2 + ((130.8128 - b2) / 2);
    
    
    // ========= CONVERT TO NOTE 0 BOUNDARY VALUES ==================
    float c0lowerBoundary = c2lowerBoundary / 4;
    float c0upperBoundary = c2upperBoundary / 4;
    
    float csharp0lowerBoundary = csharp2lowerBoundary / 4;
    float csharp0upperBoundary = csharp2upperBoundary / 4;
    
    float d0lowerBoundary = d2lowerBoundary / 4;
    float d0upperBoundary = d2upperBoundary / 4;
    
    float dsharp0lowerBoundary = dsharp2lowerBoundary / 4;
    float dsharp0upperBoundary = dsharp2upperBoundary / 4;
    
    float e0lowerBoundary = e2lowerBoundary / 4;
    float e0upperBoundary = e2upperBoundary / 4;
    
    float f0lowerBoundary = f2lowerBoundary / 4;
    float f0upperBoundary = f2upperBoundary / 4;
    
    float fsharp0lowerBoundary = fsharp2lowerBoundary / 4;
    float fsharp0upperBoundary = fsharp2upperBoundary / 4;
    
    float g0lowerBoundary = g2lowerBoundary / 4;
    float g0upperBoundary = g2upperBoundary / 4;
    
    float gsharp0lowerBoundary = gsharp2lowerBoundary / 4;
    float gsharp0upperBoundary = gsharp2upperBoundary / 4;
    
    float a0lowerBoundary = a2lowerBoundary / 4;
    float a0upperBoundary = a2upperBoundary / 4;
    
    float asharp0lowerBoundary = asharp2lowerBoundary / 4;
    float asharp0upperBoundary = asharp2upperBoundary / 4;
    
    float b0lowerBoundary = b2lowerBoundary / 4;
    float b0upperBoundary = b2upperBoundary / 4;
    
    // ========= CONVERT TO NOTE 1 BOUNDARY VALUES ==================
    float c1lowerBoundary = c2lowerBoundary / 2;
    float c1upperBoundary = c2upperBoundary / 2;
    
    float csharp1lowerBoundary = csharp2lowerBoundary / 2;
    float csharp1upperBoundary = csharp2upperBoundary / 2;
    
    float d1lowerBoundary = d2lowerBoundary / 2;
    float d1upperBoundary = d2upperBoundary / 2;
    
    float dsharp1lowerBoundary = dsharp2lowerBoundary / 2;
    float dsharp1upperBoundary = dsharp2upperBoundary / 2;
    
    float e1lowerBoundary = e2lowerBoundary / 2;
    float e1upperBoundary = e2upperBoundary / 2;
    
    float f1lowerBoundary = f2lowerBoundary / 2;
    float f1upperBoundary = f2upperBoundary / 2;
    
    float fsharp1lowerBoundary = fsharp2lowerBoundary / 2;
    float fsharp1upperBoundary = fsharp2upperBoundary / 2;
    
    float g1lowerBoundary = g2lowerBoundary / 2;
    float g1upperBoundary = g2upperBoundary / 2;
    
    float gsharp1lowerBoundary = gsharp2lowerBoundary / 2;
    float gsharp1upperBoundary = gsharp2upperBoundary / 2;
    
    float a1lowerBoundary = a2lowerBoundary / 2;
    float a1upperBoundary = a2upperBoundary / 2;
    
    float asharp1lowerBoundary = asharp2lowerBoundary / 2;
    float asharp1upperBoundary = asharp2upperBoundary / 2;
    
    float b1lowerBoundary = b2lowerBoundary / 2;
    float b1upperBoundary = b2upperBoundary / 2;
    
    
    // ========= CONVERT TO NOTE 3 BOUNDARY VALUES ==================
    float c3lowerBoundary = c2lowerBoundary * 2;
    float c3upperBoundary = c2upperBoundary * 2;
    
    float csharp3lowerBoundary = csharp2lowerBoundary * 2;
    float csharp3upperBoundary = csharp2upperBoundary * 2;
    
    float d3lowerBoundary = d2lowerBoundary * 2;
    float d3upperBoundary = d2upperBoundary * 2;
    
    float dsharp3lowerBoundary = dsharp2lowerBoundary * 2;
    float dsharp3upperBoundary = dsharp2upperBoundary * 2;
    
    float e3lowerBoundary = e2lowerBoundary * 2;
    float e3upperBoundary = e2upperBoundary * 2;
    
    float f3lowerBoundary = f2lowerBoundary * 2;
    float f3upperBoundary = f2upperBoundary * 2;
    
    float fsharp3lowerBoundary = fsharp2lowerBoundary * 2;
    float fsharp3upperBoundary = fsharp2upperBoundary * 2;
    
    float g3lowerBoundary = g2lowerBoundary * 2;
    float g3upperBoundary = g2upperBoundary * 2;
    
    float gsharp3lowerBoundary = gsharp2lowerBoundary * 2;
    float gsharp3upperBoundary = gsharp2upperBoundary * 2;
    
    float a3lowerBoundary = a2lowerBoundary * 2;
    float a3upperBoundary = a2upperBoundary * 2;
    
    float asharp3lowerBoundary = asharp2lowerBoundary * 2;
    float asharp3upperBoundary = asharp2upperBoundary * 2;
    
    float b3lowerBoundary = b2lowerBoundary * 2;
    float b3upperBoundary = b2upperBoundary * 2;
    
    
    // ========= CONVERT TO NOTE 4 BOUNDARY VALUES ==================
    float c4lowerBoundary = c2lowerBoundary * 4;
    float c4upperBoundary = c2upperBoundary * 4;
    
    float csharp4lowerBoundary = csharp2lowerBoundary * 4;
    float csharp4upperBoundary = csharp2upperBoundary * 4;
    
    float d4lowerBoundary = d2lowerBoundary * 4;
    float d4upperBoundary = d2upperBoundary * 4;
    
    float dsharp4lowerBoundary = dsharp2lowerBoundary * 4;
    float dsharp4upperBoundary = dsharp2upperBoundary * 4;
    
    float e4lowerBoundary = e2lowerBoundary * 4;
    float e4upperBoundary = e2upperBoundary * 4;
    
    float f4lowerBoundary = f2lowerBoundary * 4;
    float f4upperBoundary = f2upperBoundary * 4;
    
    float fsharp4lowerBoundary = fsharp2lowerBoundary * 4;
    float fsharp4upperBoundary = fsharp2upperBoundary * 4;
    
    float g4lowerBoundary = g2lowerBoundary * 4;
    float g4upperBoundary = g2upperBoundary * 4;
    
    float gsharp4lowerBoundary = gsharp2lowerBoundary * 4;
    float gsharp4upperBoundary = gsharp2upperBoundary * 4;
    
    float a4lowerBoundary = a2lowerBoundary * 4;
    float a4upperBoundary = a2upperBoundary * 4;
    
    float asharp4lowerBoundary = asharp2lowerBoundary * 4;
    float asharp4upperBoundary = asharp2upperBoundary * 4;
    
    float b4lowerBoundary = b2lowerBoundary * 4;
    float b4upperBoundary = b2upperBoundary * 4;
    
    
    // ========= CONVERT TO NOTE 5 BOUNDARY VALUES ==================
    float c5lowerBoundary = c2lowerBoundary * 8;
    float c5upperBoundary = c2upperBoundary * 8;
    
    float csharp5lowerBoundary = csharp2lowerBoundary * 8;
    float csharp5upperBoundary = csharp2upperBoundary * 8;
    
    float d5lowerBoundary = d2lowerBoundary * 8;
    float d5upperBoundary = d2upperBoundary * 8;
    
    float dsharp5lowerBoundary = dsharp2lowerBoundary * 8;
    float dsharp5upperBoundary = dsharp2upperBoundary * 8;
    
    float e5lowerBoundary = e2lowerBoundary * 8;
    float e5upperBoundary = e2upperBoundary * 8;
    
    float f5lowerBoundary = f2lowerBoundary * 8;
    float f5upperBoundary = f2upperBoundary * 8;
    
    float fsharp5lowerBoundary = fsharp2lowerBoundary * 8;
    float fsharp5upperBoundary = fsharp2upperBoundary * 8;
    
    float g5lowerBoundary = g2lowerBoundary * 8;
    float g5upperBoundary = g2upperBoundary * 8;
    
    float gsharp5lowerBoundary = gsharp2lowerBoundary * 8;
    float gsharp5upperBoundary = gsharp2upperBoundary * 8;
    
    float a5lowerBoundary = a2lowerBoundary * 8;
    float a5upperBoundary = a2upperBoundary * 8;
    
    float asharp5lowerBoundary = asharp2lowerBoundary * 8;
    float asharp5upperBoundary = asharp2upperBoundary * 8;
    
    float b5lowerBoundary = b2lowerBoundary * 8;
    float b5upperBoundary = b2upperBoundary * 8;
    
    
    // ========= CONVERT TO NOTE 6 BOUNDARY VALUES ==================
    float c6lowerBoundary = c2lowerBoundary * 16;
    float c6upperBoundary = c2upperBoundary * 16;
    
    float csharp6lowerBoundary = csharp2lowerBoundary * 16;
    float csharp6upperBoundary = csharp2upperBoundary * 16;
    
    float d6lowerBoundary = d2lowerBoundary * 16;
    float d6upperBoundary = d2upperBoundary * 16;
    
    float dsharp6lowerBoundary = dsharp2lowerBoundary * 16;
    float dsharp6upperBoundary = dsharp2upperBoundary * 16;
    
    float e6lowerBoundary = e2lowerBoundary * 16;
    float e6upperBoundary = e2upperBoundary * 16;
    
    float f6lowerBoundary = f2lowerBoundary * 16;
    float f6upperBoundary = f2upperBoundary * 16;
    
    float fsharp6lowerBoundary = fsharp2lowerBoundary * 16;
    float fsharp6upperBoundary = fsharp2upperBoundary * 16;
    
    float g6lowerBoundary = g2lowerBoundary * 16;
    float g6upperBoundary = g2upperBoundary * 16;
    
    float gsharp6lowerBoundary = gsharp2lowerBoundary * 16;
    float gsharp6upperBoundary = gsharp2upperBoundary * 16;
    
    float a6lowerBoundary = a2lowerBoundary * 16;
    float a6upperBoundary = a2upperBoundary * 16;
    
    float asharp6lowerBoundary = asharp2lowerBoundary * 16;
    float asharp6upperBoundary = asharp2upperBoundary * 16;
    
    float b6lowerBoundary = b2lowerBoundary * 16;
    float b6upperBoundary = b2upperBoundary * 16;
    
    
    // ========= CONVERT TO NOTE 7 BOUNDARY VALUES ==================
    float c7lowerBoundary = c2lowerBoundary * 32;
    float c7upperBoundary = c2upperBoundary * 32;
    
    float csharp7lowerBoundary = csharp2lowerBoundary * 32;
    float csharp7upperBoundary = csharp2upperBoundary * 32;
    
    float d7lowerBoundary = d2lowerBoundary * 32;
    float d7upperBoundary = d2upperBoundary * 32;
    
    float dsharp7lowerBoundary = dsharp2lowerBoundary * 32;
    float dsharp7upperBoundary = dsharp2upperBoundary * 32;
    
    float e7lowerBoundary = e2lowerBoundary * 32;
    float e7upperBoundary = e2upperBoundary * 32;
    
    float f7lowerBoundary = f2lowerBoundary * 32;
    float f7upperBoundary = f2upperBoundary * 32;
    
    float fsharp7lowerBoundary = fsharp2lowerBoundary * 32;
    float fsharp7upperBoundary = fsharp2upperBoundary * 32;
    
    float g7lowerBoundary = g2lowerBoundary * 32;
    float g7upperBoundary = g2upperBoundary * 32;
    
    float gsharp7lowerBoundary = gsharp2lowerBoundary * 32;
    float gsharp7upperBoundary = gsharp2upperBoundary * 32;
    
    float a7lowerBoundary = a2lowerBoundary * 32;
    float a7upperBoundary = a2upperBoundary * 32;
    
    float asharp7lowerBoundary = asharp2lowerBoundary * 32;
    float asharp7upperBoundary = asharp2upperBoundary * 32;
    
    float b7lowerBoundary = b2lowerBoundary * 32;
    float b7upperBoundary = b2upperBoundary * 32;
    
    
    // ========= CONVERT TO NOTE 8 BOUNDARY VALUES ==================
    float c8lowerBoundary = c2lowerBoundary * 64;
    float c8upperBoundary = c2upperBoundary * 64;
    
    float csharp8lowerBoundary = csharp2lowerBoundary * 64;
    float csharp8upperBoundary = csharp2upperBoundary * 64;
    
    float d8lowerBoundary = d2lowerBoundary * 64;
    float d8upperBoundary = d2upperBoundary * 64;
    
    float dsharp8lowerBoundary = dsharp2lowerBoundary * 64;
    float dsharp8upperBoundary = dsharp2upperBoundary * 64;
    
    float e8lowerBoundary = e2lowerBoundary * 64;
    float e8upperBoundary = e2upperBoundary * 64;
    
    float f8lowerBoundary = f2lowerBoundary * 64;
    float f8upperBoundary = f2upperBoundary * 64;
    
    float fsharp8lowerBoundary = fsharp2lowerBoundary * 64;
    float fsharp8upperBoundary = fsharp2upperBoundary * 64;
    
    float g8lowerBoundary = g2lowerBoundary * 64;
    float g8upperBoundary = g2upperBoundary * 64;
    
    float gsharp8lowerBoundary = gsharp2lowerBoundary * 64;
    float gsharp8upperBoundary = gsharp2upperBoundary * 64;
    
    float a8lowerBoundary = a2lowerBoundary * 64;
    float a8upperBoundary = a2upperBoundary * 64;
    
    float asharp8lowerBoundary = asharp2lowerBoundary * 64;
    float asharp8upperBoundary = asharp2upperBoundary * 64;
    
    float b8lowerBoundary = b2lowerBoundary * 64;
    float b8upperBoundary = b2upperBoundary * 64;
    
    
    // ========= CONVERT TO NOTE 9 BOUNDARY VALUES ==================
    float c9lowerBoundary = c2lowerBoundary * 128;
    float c9upperBoundary = c2upperBoundary * 128;
    
    float csharp9lowerBoundary = csharp2lowerBoundary * 128;
    float csharp9upperBoundary = csharp2upperBoundary * 128;
    
    float d9lowerBoundary = d2lowerBoundary * 128;
    float d9upperBoundary = d2upperBoundary * 128;
    
    float dsharp9lowerBoundary = dsharp2lowerBoundary * 128;
    float dsharp9upperBoundary = dsharp2upperBoundary * 128;
    
    float e9lowerBoundary = e2lowerBoundary * 128;
    float e9upperBoundary = e2upperBoundary * 128;
    
    float f9lowerBoundary = f2lowerBoundary * 128;
    float f9upperBoundary = f2upperBoundary * 128;
    
    float fsharp9lowerBoundary = fsharp2lowerBoundary * 128;
    float fsharp9upperBoundary = fsharp2upperBoundary * 128;
    
    float g9lowerBoundary = g2lowerBoundary * 128;
    float g9upperBoundary = g2upperBoundary * 128;
    
    float gsharp9lowerBoundary = gsharp2lowerBoundary * 128;
    float gsharp9upperBoundary = gsharp2upperBoundary * 128;
    
    float a9lowerBoundary = a2lowerBoundary * 128;
    float a9upperBoundary = a2upperBoundary * 128;
    
    float asharp9lowerBoundary = asharp2lowerBoundary * 128;
    float asharp9upperBoundary = asharp2upperBoundary * 128;
    
    float b9lowerBoundary = b2lowerBoundary * 128;
    float b9upperBoundary = b2upperBoundary * 128;
    
    
    // ========= CONVERT TO NOTE 10 BOUNDARY VALUES ==================
    float c10lowerBoundary = c2lowerBoundary * 256;
    float c10upperBoundary = c2upperBoundary * 256;
    
    float csharp10lowerBoundary = csharp2lowerBoundary * 256;
    float csharp10upperBoundary = csharp2upperBoundary * 256;
    
    float d10lowerBoundary = d2lowerBoundary * 256;
    float d10upperBoundary = d2upperBoundary * 256;
    
    float dsharp10lowerBoundary = dsharp2lowerBoundary * 256;
    float dsharp10upperBoundary = dsharp2upperBoundary * 256;
    
    float e10lowerBoundary = e2lowerBoundary * 256;
    float e10upperBoundary = e2upperBoundary * 256;
    
    float f10lowerBoundary = f2lowerBoundary * 256;
    float f10upperBoundary = f2upperBoundary * 256;
    
    float fsharp10lowerBoundary = fsharp2lowerBoundary * 256;
    float fsharp10upperBoundary = fsharp2upperBoundary * 256;
    
    float g10lowerBoundary = g2lowerBoundary * 256;
    float g10upperBoundary = g2upperBoundary * 256;
    
    float gsharp10lowerBoundary = gsharp2lowerBoundary * 256;
    float gsharp10upperBoundary = gsharp2upperBoundary * 256;
    
    float a10lowerBoundary = a2lowerBoundary * 256;
    float a10upperBoundary = a2upperBoundary * 256;
    
    float asharp10lowerBoundary = asharp2lowerBoundary * 256;
    float asharp10upperBoundary = asharp2upperBoundary * 256;
    
    float b10lowerBoundary = b2lowerBoundary * 256;
    float b10upperBoundary = b2upperBoundary * 256;
    
    
    
    // =============== UPDATE BUTTON DECLARATION ==================
    juce::TextButton updateFundamentalButton {"Update"};
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FFTPluginT1AudioProcessor& audioProcessor;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FFTPluginT1AudioProcessorEditor)
};
