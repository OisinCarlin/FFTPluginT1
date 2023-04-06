/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
 */

// ================ FFT CONVERSION CLASS ======================================

/*
   FFT Class - Credit: Florian Mrugalla
    GitHub: https://github.com/Mrugalla
    YouTube: https://www.youtube.com/watch?v=7ldQWYjWinU&t=1203s
 */
class FFT {
public:
    enum WindowType {
        NoWindowing,
        LinearType,
        SineType
    };
    
    // Constructor
    FFT(int order = 10, int windowType = SineType) :
    m_order(order),
    m_size(1 << m_order),
    m_size2(2 * m_size),
    m_sizeHalf(m_size / 2),
    m_sizeHalfF(float(m_sizeHalf)),
    m_sizeDiv(1.f / float(m_size)), // changed m_sizeMaxDiv to m_sizeMaxInv
    m_sizeMaxInv(1.f / float(m_size - 1)), // changed m_sizeMaxDiv to m_sizeMaxInv
    m_sizeMaxInvPi(m_sizeMaxInv * juce::MathConstants<float>::pi), // changed m_sizeMaxDiv to m_sizeMaxInv
    m_fifo(m_size),
    m_fftData(m_size2),
    m_fifoIdx(0),
    m_forwardFFT(order),
    m_windowType(windowType),
    m_sampleRate(1.f),
    m_sampleRateSizeMaxInv(1.f)
    {
        
    }
    
    // in prepareToPlay
    void setSampleRate(const double& sampleRate) {
        m_sampleRate = float(sampleRate);
        m_sampleRateSizeMaxInv = m_sampleRate * m_sizeMaxInv; // changed m_sizeMaxDiv to m_sizeMaxInv
    }
    
    // get sample from processBlock
    void pushSampleIntoFifo(const float& sample) {
        if (m_fifoIdx == m_size) {
            std::fill(std::next(m_fftData.begin(), m_size), m_fftData.end(), 0.f); // this clears stuff
            std::copy(m_fifo.begin(), m_fifo.end(), m_fftData.begin());
            m_forwardFFT.performFrequencyOnlyForwardTransform(m_fftData.data());
            m_fifoIdx = 0;
        }
        
        float windowAmp;
        switch (m_windowType) {
            case LinearType:
                windowAmp = m_fifoIdx < m_sizeHalf ?
                float(2 * m_fifoIdx) * m_sizeMaxInv :
                2.f - float(2 * m_fifoIdx) * m_sizeMaxInv;
                break;
            case SineType:
                windowAmp = std::sin(float(m_fifoIdx) * m_sizeMaxInvPi);
                break;
            default:
                // No Windowing
                windowAmp = 1.f;
                break;
        }
        m_fifo[m_fifoIdx] = sample * windowAmp;
        ++m_fifoIdx;
    }
    
    // returns frequency where magnitude is max
    const float& getFundamentalFrequency() {
        float index = 0.f;
        float max = 0.f;
        float absSample;
        for (auto i = 0; i < m_sizeHalf; ++i){
            absSample = std::abs(m_fftData[i]);
            if (max < absSample) {
                max = absSample;
                index = i;
            }
        }
        return m_sampleRateSizeMaxInv * index;
    }
    
    
private:
    int m_order, m_size, m_size2, m_sizeHalf;
    float m_sizeHalfF, m_sizeDiv, m_sizeMaxInv, m_sizeMaxInvPi; // changed m_sizeMaxDiv to m_sizeMaxInv
    std::vector<float> m_fifo, m_fftData;
    int m_fifoIdx;
    juce::dsp::FFT m_forwardFFT;
    int m_windowType;
    float m_sampleRate, m_sampleRateSizeMaxInv;
    
};

//==============================================================================

class FFTPluginT1AudioProcessor  : public juce::AudioProcessor
#if JucePlugin_Enable_ARA
, public juce::AudioProcessorARAExtension
#endif
{
public:
    //==============================================================================
    FFTPluginT1AudioProcessor();
    ~FFTPluginT1AudioProcessor() override;
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif
    
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    //==============================================================================
    const juce::String getName() const override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    
    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    
    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    // Instanciate FFT Conversion class for use in PluginProcessor
    FFT fft { 12, FFT::SineType }; // fft order, imageWidth, imageHeight, windowType
    
    // PluginProcessor variable to store Fundamental Frequency
    float fftValue = fft.getFundamentalFrequency();
    
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FFTPluginT1AudioProcessor)
};
