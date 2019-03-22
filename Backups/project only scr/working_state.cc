#include <iostream>
#include <chrono>
#include <vector>

#include "worker.h"

using namespace std::chrono;
using namespace elma;
using namespace worker;

Worker&Working:: worker() { return (Worker&) state_machine(); }

void Working::entry(const Event& e) {
    
}

void Working::exit(const Event& e) {
    
}
