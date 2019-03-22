#include <iostream>
#include <chrono>
#include <vector>

#include "worker.h"

using namespace std::chrono;
using namespace elma;
using namespace worker;

Worker&Dead:: worker() { return (Worker&) state_machine(); }

void Dead::entry(const Event& e) {
    
}

void Dead::exit(const Event& e) {
    
}
