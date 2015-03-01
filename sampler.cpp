#include <iostream>
#include <SFML/Audio.hpp>
#include <aquila/global.h>
#include <aquila/tools/TextPlot.h>
#include <aquila/transform/FftFactory.h>
#include <aquila/source/SignalSource.h>
#include "aquila/source/window/HammingWindow.h"

using namespace std;

class KairosSampler : public sf::SoundRecorder {

    // input signal parameters
    const std::size_t size = 2048;
    const Aquila::FrequencyType sampleFrequency = 44100;

    const double freqThreshold = 17000;
    const double amplThreshold = 5000;

    int cycles = 0;

//    double mLeftAvg;
//    double mRightAvg;
//
//    double mLeftAvgs[5] = {};
//    double mRightAvgs[5] = {};
//
//    bool mLeftShift = false;
//    bool mRightShift = false;

//    bool firstRun = true;

    virtual bool onStart() { // optional
        cout << "Started capturing" << endl;
        return true;
    }

    virtual bool onProcessSamples(const Int16* samples, std::size_t sampleCount) {
        Aquila::SignalSource source = Aquila::SignalSource(samples, sampleCount, sampleFrequency);

        // calculate the FFT
        auto fft = Aquila::FftFactory::getFft(size);
        Aquila::SpectrumType spectrum = fft->fft(source.toArray());

        Aquila::HammingWindow hamming(2048);
        std::transform(
                std::begin(spectrum),
                std::end(spectrum),
                std::begin(hamming),
                std::begin(spectrum),
                [] (Aquila::ComplexType x, Aquila::ComplexType y) { return x * y; }
        );


        double highestAmplitude = 0;
        double highestFrequency;
        for (int i = 0; i < size/2; ++i) {
            double freq = i * sampleFrequency / size;
            double ampl = spectrum[i].real();
            if (freq > freqThreshold && ampl > highestAmplitude) {
                highestAmplitude = ampl;
                highestFrequency = freq;
            }
        }


        if (highestAmplitude > amplThreshold) {
            cout << "Highest amplitude: " << highestAmplitude;
            cout << " Frequency: " << highestFrequency << endl;
//
//            int leftMargin = (highestFrequency-1000)*size/sampleFrequency;
//            int peak = highestFrequency*size/sampleFrequency;
//            int rightMargin = (highestFrequency+1000)*size/sampleFrequency;
//
//            double leftSum = 0;
//            for (int i = leftMargin; i < peak; i++) {
//                leftSum += spectrum[i].real();
//            }
//            double leftAvg = leftSum / (peak - leftMargin);
//
//            double rightSum = 0;
//            for (int i = peak; i < rightMargin; i++) {
//                rightSum += spectrum[i].real();
//            }
//            double rightAvg = rightSum / (rightMargin - peak);
//
//            if (firstRun) {
//                mLeftAvg = leftAvg;
//                mRightAvg = rightAvg;
//                firstRun = false;
//            } else {
//                mLeftAvgs[cycles] = leftAvg;
//                mRightAvgs[cycles] = rightAvg;

//                cout << "Cycles: " << cycles << endl;

                if (cycles >= 4) {
                    Aquila::TextPlot plt("Input signal");
                    plt.plot(source);

                    plt.setTitle("Input spectrum");
                    plt.plotSpectrum(spectrum);

//                    int leftFails = 0;
//                    int rightFails = 0;
//                    for (int i = 0; i < 5; ++i) {
//                        if (mLeftAvgs[i] - mLeftAvg > 1000) leftFails++;
//                        if (mRightAvgs[i] - mRightAvg > 1000) rightFails++;
//                    }
//                    if (leftFails < 2) {
//                        cout << "Left shift!" << endl;
//                    }
//                    if (rightFails < 2) {
//                        cout << "Right shift!" << endl;
//                    }
//
                    cycles = 0;
                } else {
                    cycles++;
                }
//            }
        }

        // return true to continue the capture, or false to stop it
        return true;
    }

    virtual void onStop() { // Optional
        // clean up whatever has to be done after the capture is finished
    }
};