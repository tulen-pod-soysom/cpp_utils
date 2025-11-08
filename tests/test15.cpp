#include "signal_processing/signal_processing_utils.hpp"
#include "testing/utils.hpp"
#include <fstream>
#include <io/wav.hpp>
#include <signal_processing/signals.hpp>

int main()
{
    auto v = signals::generate_saw(44100, 44100*64,1,100,0);
    auto v2 = signals::generate_sine(44100, 44100*64,1,50,0);

    v = vec_ops::mul(v,v2);


    std::ofstream output("test.wav");
    output << generate_wav(v,2.0,44100);
    utils::print("test");
}