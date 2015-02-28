#include <iostream>
#include <SFML/Audio.hpp>
#include <aquila/global.h>
#include <aquila/tools/TextPlot.h>
#include <aquila/transform/FftFactory.h>
#include <aquila/source/SignalSource.h>

using namespace std;

class KairosSampler : public sf::SoundRecorder {

    // input signal parameters
    const std::size_t size = 64;
    const Aquila::FrequencyType sampleFrequency = 44100;

    virtual bool onStart() { // optional
        // initialize whatever has to be done before the capture starts
        cout << "Started capturing" << endl;
        // return true to start the capture, or false to cancel it
        return true;
    }

    virtual bool onProcessSamples(const Int16* samples, std::size_t sampleCount) {
        Aquila::SignalSource source = Aquila::SignalSource(samples, sampleCount, sampleFrequency);

        // calculate the FFT
        auto fft = Aquila::FftFactory::getFft(size);
        Aquila::SpectrumType spectrum = fft->fft(source.toArray());

        double highestAmplitude = 0;
        double highestFrequency;
        for (int i = 0; i < size/2; ++i) {
            double freq = i * sampleFrequency / size;
            double amp = spectrum[i].real();
            if (freq > 16000 && amp > highestAmplitude) {
                highestAmplitude = spectrum[i].real();
                highestFrequency = freq;
            }
        }

        if (highestAmplitude > 16000) {
            cout << "Highest amplitude: " << highestAmplitude;
            cout << " Frequency: " << highestFrequency << endl;
        }

        // return true to continue the capture, or false to stop it
        return true;
    }

    virtual void onStop() { // Optional
        // clean up whatever has to be done after the capture is finished
    }
};