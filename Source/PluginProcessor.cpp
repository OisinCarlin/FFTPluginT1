/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//#include "HDLFFT.h"

//==============================================================================
FFTPluginT1AudioProcessor::FFTPluginT1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

FFTPluginT1AudioProcessor::~FFTPluginT1AudioProcessor()
{
}

//==============================================================================
const juce::String FFTPluginT1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool FFTPluginT1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool FFTPluginT1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool FFTPluginT1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double FFTPluginT1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int FFTPluginT1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int FFTPluginT1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void FFTPluginT1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String FFTPluginT1AudioProcessor::getProgramName (int index)
{
    return {};
}

void FFTPluginT1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void FFTPluginT1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    
    
    fft.setSampleRate(sampleRate);
    osc.setSampleRate(sampleRate);
}

void FFTPluginT1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool FFTPluginT1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void FFTPluginT1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    auto chInv = 1.f / float(buffer.getNumChannels());
    
    osc.setFreq(fft.getFundamentalFrequency());
    this->fftValue = fft.getFundamentalFrequency(); //Added
    
    for (auto s = 0; s < buffer.getNumSamples(); ++s) {
        auto sample = 0.f;
        for(auto ch = 0; ch < buffer.getNumChannels(); ++ch) {
            auto* channelData = buffer.getReadPointer(ch, s);
            sample += *channelData;
        }
        sample *= chInv;
        fft.pushSampleIntoFifo(sample);
        
        /*
        osc.process(sample);
        for(auto ch = 0; ch < buffer.getNumChannels(); ++ch) {
            auto* channelData = buffer.getWritePointer(ch, s);
            *channelData = osc.getWave(osc.WFSqr);
        }
        */
    }
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }

    
    
        
    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
//    for (int channel = 0; channel < totalNumInputChannels; ++channel)
//    {
//        auto* channelData = buffer.getWritePointer (channel);
//        // ..do something to the data...
//    }
}

//==============================================================================
bool FFTPluginT1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* FFTPluginT1AudioProcessor::createEditor()
{
    return new FFTPluginT1AudioProcessorEditor (*this);
}

//==============================================================================
void FFTPluginT1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void FFTPluginT1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new FFTPluginT1AudioProcessor();
}
