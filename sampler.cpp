#include <iostream>
#include <SFML/Audio.hpp>
#include <aquila/global.h>
#include <aquila/tools/TextPlot.h>
#include <aquila/transform/FftFactory.h>
#include <aquila/source/SignalSource.h>
#include "aquila/source/WaveFile.h"
#include "aquila/source/window/HammingWindow.h"

using namespace std;

class KairosSampler : public sf::SoundRecorder {

    const std::size_t size = 2048;
    const Aquila::FrequencyType sampleFrequency = 44100;

    const double freqThreshold = 17000;
    const double amplThreshold = 5000;

    virtual bool onStart() { // optional
        sf::Time interval = sf::milliseconds(500);
        setProcessingInterval(interval);
        cout << "Started capturing" << endl;
        return true;
    }

    virtual bool onProcessSamples(const Int16* samples, std::size_t sampleCount) {
        Aquila::SignalSource source = Aquila::SignalSource(samples, sampleCount, sampleFrequency);
//
//        Aquila::TextPlot plt("Input signal");
//        plt.plot(source);

        Aquila::HammingWindow hamming(size);
        auto product = source * hamming;
//
//        plt.setTitle("Hamming product");
//        plt.plot(product);

//        Aquila::SpectrumType hamming = Aquila::SpectrumType(size);
//        for (int i = 0; i < size; ++i) {
//            hamming.push_back(0.53836 - 0.46164 * std::cos(2.0 * M_PI * i / double(size - 1)));
//        }

        // calculate the FFT
        auto fft = Aquila::FftFactory::getFft(size);
        Aquila::SpectrumType spectrum = fft->fft(product.toArray());


        double highestAmplitude = 0;
        double highestFrequency;
        int peakBin;
        for (int i = 0; i < size/2; ++i) {
            double freq = i * sampleFrequency / size;
            double ampl = spectrum[i].real();
            if (freq > freqThreshold && ampl > highestAmplitude) {
                highestAmplitude = ampl;
                highestFrequency = freq;
                peakBin = i;
            }
        }


        if (highestAmplitude > amplThreshold) {
            cout << "Highest amplitude: " << highestAmplitude;
            cout << " Frequency: " << highestFrequency << endl;

            int binCount = 0;
            while(spectrum[peakBin-binCount].real() > highestAmplitude*0.1) {
                binCount++;
            }
            if (binCount > 3) cout << "Left shift!" << endl;

            binCount = 0;
            while(spectrum[peakBin+binCount].real() > highestAmplitude*0.1) {
                binCount++;
            }
            if (binCount > 3) cout << "Right shift!" << endl;
        }

        // return true to continue the capture, or false to stop it
        return true;
    }

    virtual void onStop() { // Optional
        // clean up whatever has to be done after the capture is finished
    }

};