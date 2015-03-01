#include <iostream>
#include <SFML/Audio.hpp>

#include <aquila/transform/FftFactory.h>
#include <unistd.h>
#include "aquila/global.h"
#include "aquila/source/WaveFile.h"
#include "aquila/tools/TextPlot.h"


using namespace std;

int main(int argc, char *argv[])
{
    const std::size_t SIZE = 2048;

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("/Users/ian/ClionProjects/Doppler/wtf.wav"))
        return -1;

//    sf::Sound sound;
//    sound.setBuffer(buffer);
//    sound.play();
//
//    sleep(10);

    Aquila::SignalSource source = Aquila::SignalSource(buffer.getSamples(), buffer.getSampleCount(), buffer.getSampleRate());

    // calculate the FFT
    auto fft = Aquila::FftFactory::getFft(SIZE);
    Aquila::SpectrumType spectrum = fft->fft(source.toArray());

    Aquila::TextPlot plt("Spectrum");
    plt.plotSpectrum(spectrum);

    return 0;
}