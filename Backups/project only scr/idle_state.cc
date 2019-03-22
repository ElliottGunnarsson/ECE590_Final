#include <iostream>
#include <chrono>
#include <vector>

#include "worker.h"

using namespace std::chrono;
using namespace elma;
using namespace worker;

Worker&Idle:: worker() { return (Worker&) state_machine(); }

void Idle::entry(const Event& e) {
    
}

void Idle::exit(const Event& e) {
    
}
