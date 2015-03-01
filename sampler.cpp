#include <iostream>
#include <SFML/Audio.hpp>
#include <aquila/global.h>
#include <aquila/tools/TextPlot.h>
#include <aquila/transform/FftFactory.h>
#include <aquila/source/SignalSource.h>
#include <aquila/source/window/HammingWindow.h>
#include "aquila/source/WaveFile.h"

using namespace std;

class KairosSampler : public sf::SoundRecorder {

    const std::size_t size = 2048;
    const Aquila::FrequencyType sampleFrequency = 44100;

    const double freqThreshold = 17000;
    const double amplThreshold = 50000;

    virtual bool onStart() { // optional
        sf::Time interval = sf::milliseconds(100);
        setProcessingInterval(interval);
        cout << "Started capturing" << endl;
        return true;
    }

    virtual bool onProcessSamples(const Int16* samples, std::size_t sampleCount) {
        Aquila::SignalSource source = Aquila::SignalSource(samples, sampleCount, sampleFrequency);

//        Aquila::HammingWindow hamming(size);
//        auto product = source * hamming;

        // calculate the FFT
        auto fft = Aquila::FftFactory::getFft(size);
        Aquila::SpectrumType spectrum = fft->fft(source.toArray());


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

//        if (highestAmplitude > amplThreshold) {
//            cout << "Highest amplitude: " << highestAmplitude;
//            cout << " Frequency: " << highestFrequency << endl;

            int bins = 50;

            double secondPeakAmpl = 0;
            double secondPeakFreq;
            for (int i = 2; i < bins; ++i) {
                double ampl = spectrum[peakBin-i].real();
                if (ampl > secondPeakAmpl) {
                    secondPeakAmpl = ampl;
                    secondPeakFreq = (peakBin-i) * sampleFrequency / size;
                };
            }
//            cout << secondPeakAmpl << " " << secondPeakFreq << endl;
            if (secondPeakAmpl > highestAmplitude*0.4) {
                cout << "Left shift!!!" << endl << endl;
                system("./scrollup.sh");
            }

            secondPeakAmpl = 0;
            secondPeakFreq = 0;
            for (int i = 2; i < bins; ++i) {
                double ampl = spectrum[peakBin+i].real();
                if (ampl > secondPeakAmpl) {
                    secondPeakAmpl = ampl;
                    secondPeakFreq = (peakBin+i) * sampleFrequency / size;
                };
            }
//            cout << secondPeakAmpl << " " << secondPeakFreq << endl;
            if (secondPeakAmpl > highestAmplitude*0.4) {
                cout << "Right shift!!!" << endl << endl;
                system("./scrolldown.sh");
            }

//        }

        return true;
    }

    virtual void onStop() { // Optional
    }

};