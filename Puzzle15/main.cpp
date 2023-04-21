#include <iostream>
#include "Headers/State.h"
#include "Headers/Algorithms.h"
#include <chrono>
#include <unordered_set>

int main() {
    

    auto start = std::chrono::high_resolution_clock::now();
    //State* initial = new State(0xedf7cb95602148a3ULL);
    State* initial = create_random_state();
    a_star(initial);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout <<"program wykonywał się: "<<duration.count() <<"s"<< std::endl;
}