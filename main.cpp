typedef short Int16;

#include <SFML/System/Time.hpp>
#include "sampler.cpp"

using namespace std;

int main() {
    if (!KairosSampler::isAvailable()) {
        // error...
    }

    KairosSampler sampler;
    sampler.start();

    char c;
    while (cin >> c) {
        sampler.stop();
    }

//    const sf::SoundBuffer& buffer = sampler.getBuffer();
//    buffer.saveToFile("my_record.ogg");

    return 0;
}
 