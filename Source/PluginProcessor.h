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


class HDLFFT {
public:
    enum WindowType {
        NoWindowing,
        LinearType,
        SineType
    };
    
    // Constructor
    HDLFFT(int order = 10, int windowType = SineType) :
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
    
    // returns frequencey where magnitude is max
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

class HDLFFTOsc{
private:
    struct Osc {
        Osc() : m_sampleRate2Inv(0.f), m_inc(0.f), m_idx(0.f){}
        void setSampleRate(const float& sampleRate) {m_sampleRate2Inv = 2.f / sampleRate; }
        void setFreq(const float& freq) { m_inc = freq * m_sampleRate2Inv; }
        void process() {
            m_idx += m_inc;
            if (m_idx > 1.f)
                m_idx -= 2.f;
        }
        const float& getSin() { return std::sin(m_idx * juce::MathConstants<float>::pi); }
        const float& getSaw() { return m_idx; }
        const float& getSqr() { return m_idx < 0.f ? -1.f : 1.f; }
        float m_sampleRate2Inv, m_inc, m_idx;
    };
    
    struct EnvelopeFollower {
        EnvelopeFollower(float attack = .7f, float release = .7f) :
        m_idx(0.f),
        m_cycle(0.f),
        m_attack(attack),
        m_release(release),
        m_sampleRate(0.f),
        m_envelope(0.f)
        
        {
            setAttack(attack);
            setRelease(release);
        }
        
        void setAttack(const float& attack){ m_attack = 1.f - attack; }
        void setRelease(const float& release){ m_release = 1.f - release; }
        void setSampleRate(const float& sampleRate) { m_sampleRate = sampleRate; }
        void setFreq(const float& freq) { m_cycle = m_sampleRate / freq; }
        const float& getEnvelope(float sample, bool saturated = false) {
            sample = std::abs(sample);
            if (m_envelope < sample) {
                m_envelope += m_attack * (sample - m_envelope);
                m_idx = 0.f;
            }
            else {
                if(m_idx < m_cycle) {
                    ++m_idx;
                }
                else {
                    m_envelope += m_release * (sample - m_envelope);
                    m_idx -= m_cycle;
                }
            }
            if (saturated)
                return std::tanh(2.f * m_envelope);
            return m_envelope;
        }
        
        float m_idx, m_cycle, m_attack, m_release, m_sampleRate, m_envelope;
    };
    
public:
    enum WaveForms {
        WFSine,
        WFSaw,
        WFSqr
    };
    
    HDLFFTOsc(float filter = .5f, juce::Range<float> frequencyRange = juce::Range<float>(80.f, 19000.f)) :
        m_filter(filter),
        m_freq(0.f),
        m_envelope(0.f),
        m_frequencyRange(frequencyRange)
    
    {
        setFilter(filter);
    }
    
    void setFilter(float filter) { m_filter = filter; }
    void setSampleRate(const double& sampleRate) {
        auto m_sampleRate = float(sampleRate);
        osc.setSampleRate(m_sampleRate);
        env.setSampleRate(m_sampleRate);
    }
    void setFreq(const float& freq) {
        if(!(freq > m_frequencyRange.getEnd() || freq < m_frequencyRange.getStart()))
            m_freq += m_filter * (freq - m_freq);
        osc.setFreq(m_freq);
        env.setFreq(m_freq);
    }
   void process(const float& sample = 1.f){
        osc.process();
        m_envelope = env.getEnvelope(sample);
    }
   const float& getWave(WaveForms wf = WFSine) {
        switch (wf) {
            case WFSine: return osc.getSin() * m_envelope;
            case WFSaw: return osc.getSaw() * m_envelope;
            case WFSqr: return osc.getSqr() * m_envelope;
            default: return osc.getSin() * m_envelope;
                
        }
    }

private:
   float m_filter, m_freq, m_envelope;
    juce::Range<float> m_frequencyRange;
    Osc osc;
    EnvelopeFollower env;
};
    
//    class HDLFFTVisual {
//    public:
//        enum WindowType {
//
//        };
//
//        HDLFFTVisual(int order = 10, int imageWidth = 512, int imageHeight = 512, int windowType = HDLFFT::SineType){}
//
//        // in prepareToPlay
//        void setSampleRate(const double& sampleRate){
//        m_sampleRate =  float(sampleRate);
//            m_sampleRateSizeMaxInv = m_sampleRate * m_sizeMaxInv;
//        }
//
//        // in resized (optional)
//        void setImageBounds(juce::Rectangle<int> bounds) {setImageBounds(bounds.getWidth(), bounds.getHeight());}
//
//        // in paint
//        void draw(juce::Graphics& g, juce::Rectangle<float> bounds){ g.drawImage(m_image, bounds);}
//
//        // get sample from processBlock
//        void pushSampleIntoFifo(const float& sample){}
//
//        // returns frequency where magnitude is max
//        const float& getFundamentalFrequency() {}
//
//        // returns true if repaint() should be called from timerCallback() in editor
//        bool shouldRepaint(){};
//
//    };


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
    
    HDLFFT fft { 12, HDLFFT::SineType }; // fft order, imageWidth, imageHeight, windowType
    float fftValue = fft.getFundamentalFrequency();
private:
    HDLFFTOsc osc;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FFTPluginT1AudioProcessor)
};
