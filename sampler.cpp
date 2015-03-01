typedef short Int16;
#include <stdio.h>
# include <sys/types.h>
#include <unistd.h>
#include <signal.h>
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
    const std::size_t size      = 2048;
    const Aquila::FrequencyType sampleFrequency = 44100;
    const int MAX_SAMPLES       = 1000;
    const int HAMMING_WINDOW    = 2048;
    const int DEBUG_LEVEL       = 2;
    const int IGNORE            = 10;
    const int CALIBRATION       = 6;
    const int SAMPLE            = 3;
    const int MAX_CYCLES        = 200;
    double avgRightHighAcceptance   = 70;
    double avgRightLowAcceptance    = 60;
    double avgLeftHighAcceptance    = 70;
    double avgLeftLowAcceptance     = 50;
    
    //const sf::Time INTERVAL     = sf::Milliseconds(50);7

    double freqThreshold = 17000;
    double amplThreshold = 5000;
    
    pair<double, double> rangeValues;
    pair<double, double> rangeIndexes;
    vector< vector< pair<double, double> > > rangeArray;
    
    //pair< vector<int>, vector<int> > accumulative;
    
    int cycles = 0;
    
    double targetFreq           = 18933;
    double targetFreqAcceptance = 40;
    double rangeWidth           = 1000;
    
    double validSampling        = 10;
    
    bool isHooked               = false;
    
    vector<double> arrAvgLeft;
    vector<double> arrAvgLeftLow;
    double avgLeft = 0;
    double avgLeftLow = 0;
    
    vector<double> arrAvgRight;
    vector<double> arrAvgRightLow;
    double avgRight = 0;
    double avgRightLow = 0;
    
    
    bool isLeft  = true;
    bool isRight = true;
    int leftAvgLowSamples   = CALIBRATION;
    int leftAvgSamples      = SAMPLE;
    
    int ignored             = IGNORE;
    
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
        
        // Set the range
        rangeValues.first = targetFreq - rangeWidth;
        rangeValues.second = targetFreq + rangeWidth;
        
        rangeIndexes.first = -1;
        rangeIndexes.second = -1;
        
        rangeArray = vector< vector< pair<double, double> > >(MAX_SAMPLES);
        arrAvgLeftLow = vector<double>(CALIBRATION);
        arrAvgRightLow = vector<double>(CALIBRATION);
        arrAvgLeft = vector<double>(SAMPLE);
        arrAvgRight = vector<double>(SAMPLE);
        
        //setProcessingInterval(INTERVAL);
        
        return true;
    }

    virtual bool onProcessSamples(const Int16* samples, std::size_t sampleCount) {
        Aquila::SignalSource source = Aquila::SignalSource(samples, sampleCount, sampleFrequency);

        // calculate the FFT
        auto fft = Aquila::FftFactory::getFft(size);
        Aquila::SpectrumType spectrum = fft->fft(source.toArray());

        // Hamming Window
        Aquila::HammingWindow hamming(HAMMING_WINDOW);
        std::transform(
                std::begin(spectrum),
                std::end(spectrum),
                std::begin(hamming),
                std::begin(spectrum),
                [] (Aquila::ComplexType x, Aquila::ComplexType y) { return x * y; }
        );

        if (ignored > 0) {
            ignored--;
        } else {
            // Filter
            double highestAmplitude = 0;
            double highestFrequency;
            for (int i = 0, j = 0; i < size/2; ++i) {
                
                double freq = i * sampleFrequency / size;
                double ampl = spectrum[i].real();
                
                // Max peak
                if (freq > freqThreshold and ampl > highestAmplitude) {
                    highestAmplitude = ampl;
                    highestFrequency = freq;
                }
                
                // Slice
                if (freq >= rangeValues.first and freq <= rangeValues.second) {
                    if (rangeIndexes.first == -1) rangeIndexes.first = i;
                    
                    pair<double, double> p;
                    p.first     = ampl;
                    p.second    = freq;
                    
                    rangeArray[cycles].push_back(p);
                    
                    ++j;
                } else if (rangeIndexes.second == -1 and rangeIndexes.first != -1 and freq >= rangeValues.first and freq > rangeValues.second) {
                    rangeIndexes.second = i;
                }
                
            }
            
            // Check segmentations fault
            if (rangeIndexes.first == -1) rangeIndexes.second = 0;
            if (rangeIndexes.second == -1) rangeIndexes.second = size/2 - 1;
            
            // TODO: Not erase everything sensitive???
            if (cycles > 0 and (cycles-1 >= (int)rangeArray.size()  || (int)rangeArray[(cycles==0 ? 0 : cycles-1)].size() == 0)) {
                cycles = 0;            
                if (DEBUG_LEVEL > 1) cout << "RESETED" << endl;
                
            }
            else ++cycles;
            
            
            if (DEBUG_LEVEL > 3) cout << "CYCLE: " << cycles << endl;
            if (MAX_CYCLES > 0 and cycles >= MAX_CYCLES) {
                if (DEBUG_LEVEL > 1) cout << "RESETED_HARD" << endl;
                vector< pair<double, double> > p = rangeArray[0];
                rangeArray.clear();
                cycles = 0;
                leftAvgLowSamples = CALIBRATION;
                rangeArray = vector< vector< pair<double, double> > >(MAX_SAMPLES);
                rangeArray.push_back(p);
            }
            
            // TODO: Check not 1 or 0
            if (highestFrequency > targetFreq - targetFreqAcceptance and highestFrequency < targetFreq + targetFreqAcceptance) {
                isHooked = true;
            } else {
                isHooked = false;
            }
            
            // So: - rangeIndexes the i of the frequencies
            //     - rangeArray[cycle] the pair of (amplitude, frequency)
            //     - highestAmplitude the peak
            //     - highestFrequency the freq
            if (DEBUG_LEVEL > 2) cout << "Sample: (" << (rangeIndexes.first * sampleFrequency / size) << "," 
                << (rangeIndexes.second * sampleFrequency / size) << ") with: " 
                << highestAmplitude << " at " << highestFrequency << "Hz. " 
                << (isHooked ? "(HOOKED)" : "(MISSING)") << endl;
            
            if (leftAvgLowSamples > 0) {
                if (DEBUG_LEVEL > 1) cout << "Stay quiet! Calibrating... ("<< leftAvgLowSamples <<")" << endl;
                if (isHooked)
                    leftAvgLowSamples--;
                else if (DEBUG_LEVEL > 1) 
                    cout << "Please start the " << targetFreq << "Hz source." << endl;
                
                double thisLeftAvg = 0.0;
                double thisRightAvg = 0.0;
                int lta = 0;
                int rta = 0;
                
                for (int i = 0; i < rangeArray[(cycles==0 ? 0 : cycles-1)].size(); i++) {
                    if (DEBUG_LEVEL > 5) cout << "Goes to ("<<  rangeArray[(cycles==0 ? 0 : cycles-1)][i].second  <<")" << endl;
                    if (rangeArray[(cycles==0 ? 0 : cycles-1)][i].second < targetFreq - targetFreqAcceptance) {
                        // We are on the left
                        thisLeftAvg += rangeArray[(cycles==0 ? 0 : cycles-1)][i].first;
                        lta++;
                        if (DEBUG_LEVEL > 5) cout << "Left..." << endl;
                    } else if (rangeArray[(cycles==0 ? 0 : cycles-1)][i].second > targetFreq + targetFreqAcceptance) {
                        thisRightAvg += rangeArray[(cycles==0 ? 0 : cycles-1)][i].first;
                        rta++;
                        if (DEBUG_LEVEL > 5) cout << "Right..." << endl;
                    }
                }
                
                if ((lta == 0 or rta == 0) and leftAvgLowSamples < CALIBRATION) leftAvgLowSamples++;
                else {
                
                    arrAvgLeftLow[leftAvgLowSamples] = (double)thisLeftAvg/(double)lta;
                    arrAvgRightLow[leftAvgLowSamples] = (double)thisRightAvg/(double)rta;
                    if (DEBUG_LEVEL > 2) cout << "Avg! L("<< arrAvgLeftLow[leftAvgLowSamples] <<" on "<<leftAvgLowSamples<<") and R("<< arrAvgRightLow[leftAvgLowSamples] <<" on "<<leftAvgLowSamples<<")" << endl;
                    
                    if (leftAvgLowSamples == 0) {
                        double lsum = 0;
                        double rsum = 0;
                        for (int i = 0; i < CALIBRATION; i++) {
                            lsum += arrAvgLeftLow[i];
                            rsum += arrAvgRightLow[i];
                            if (DEBUG_LEVEL > 2) cout << "Calibrating! L("<< lsum <<") and R("<< rsum <<")" << endl;
                        }
                        avgLeftLow = (double)lsum/(double)CALIBRATION;
                        avgRightLow = (double)rsum/(double)CALIBRATION;
                        
                        if (DEBUG_LEVEL > 1) cout << "Calibrated! L("<< avgLeftLow <<") and R("<< avgRightLow <<")" << endl << endl;
                        
                        cycles = 0;
                        
                        // TODO: Odd things
                        avgLeft     = avgLeftLow + avgLeftHighAcceptance /*+ avgLeftLowAcceptance*/;
                        avgRight    = avgRightLow + avgRightHighAcceptance /*+ avgRightLowAcceptance*/;
                        
                        isHooked = false;
                    }
                    
                }
            } else if (isHooked) {
                // Average
                if (leftAvgSamples > 0) {
                    leftAvgSamples--;
                    
                    double thisLeftAvg = 0.0;
                    double thisRightAvg = 0.0;
                    int lta = 0;
                    int rta = 0;
                    
                    for (int i = 0; i < rangeArray[(cycles==0 ? 0 : cycles-1)].size(); i++) {
                        if (DEBUG_LEVEL > 5) cout << "Goes to ("<<  rangeArray[(cycles==0 ? 0 : cycles-1)][i].second  <<")" << endl;
                        if (rangeArray[(cycles==0 ? 0 : cycles-1)][i].second < targetFreq - targetFreqAcceptance) {
                            thisLeftAvg += (rangeArray[(cycles==0 ? 0 : cycles-1)][i].first < avgLeftLow - avgLeftLowAcceptance) ? avgLeftLow : rangeArray[(cycles==0 ? 0 : cycles-1)][i].first;
                            lta++;
                            if (DEBUG_LEVEL > 5) cout << "Left..." << endl;
                        } else if (rangeArray[(cycles==0 ? 0 : cycles-1)][i].second > targetFreq + targetFreqAcceptance) {
                            thisRightAvg += (rangeArray[(cycles==0 ? 0 : cycles-1)][i].first < avgRightLow - avgRightLowAcceptance) ? avgRightLow : rangeArray[(cycles==0 ? 0 : cycles-1)][i].first;
                            rta++;
                            if (DEBUG_LEVEL > 5) cout << "Right..." << endl;
                        }
                    }
                    
                    if (lta == 0 or rta == 0) {
                        leftAvgSamples++;
                        //cycles--;
                    } else {
                        arrAvgLeft[leftAvgSamples] = (double)thisLeftAvg/(double)lta;
                        arrAvgRight[leftAvgSamples] = (double)thisRightAvg/(double)rta;
                        if (DEBUG_LEVEL > 4) cout << "Averaged! L("<< thisLeftAvg <<"/"<<lta<<") and R("<< thisRightAvg <<"/"<<rta<<")" << endl;
                        
                        if (leftAvgSamples == 0) {
                            double lsum = 0;
                            double rsum = 0;
                            for (int i = 0; i < SAMPLE; i++) {
                                lsum += arrAvgLeft[i];
                                rsum += arrAvgRight[i];
                            }
                            avgLeft = (double)lsum/(double)SAMPLE;
                            avgRight = (double)rsum/(double)SAMPLE;
                            
                            if (DEBUG_LEVEL > 1) cout << "Sampled! L("<< avgLeft <<"/"<<avgLeftLow<<") and R("
                                << avgRight <<"/"<<avgRightLow<<")" << endl << endl;
                            
                            
                            
                            // The Masterplan - Oasis
                            if (avgLeft - avgLeftHighAcceptance > avgLeftLow + avgLeftLowAcceptance) {
                                isLeft = true;
                            } else {
                                isLeft = false;
                            }
                            if (avgRight - avgRightHighAcceptance > avgRightLow + avgRightLowAcceptance) {
                                isRight = true;
                            } else {
                                isRight = false;
                            }
                        }
                    }
                } else {
                    leftAvgSamples = SAMPLE;
                    
                    if (isLeft) {
                        cout << "Going up!" << endl;
                        kill(getpid(), SIGUSR1);
                    }
                    if (isRight) {
                        cout << "Going down!" << endl;
                        kill(getpid(), SIGUSR2);
                    }
                    if (isLeft and isRight) {
                        cout << "Go away daemon!" << endl;
                    }
                }
                
                
                
            }
        }
            
            
            
        
        // return true to continue the capture, or false to stop it
        return true;
    }

    virtual void onStop() { // Optional
        // clean up whatever has to be done after the capture is finished
    }
};