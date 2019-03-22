#include <chrono>
#include <vector>

#include "worker.h"

using namespace std::chrono;
using namespace elma;
using namespace worker;

Worker::Worker() : StateMachine("worker") {

    // Define state machine initial states and transitions here
    set_initial(_idle);
    set_propagate(false);
    add_transition("hire", _idle, _working);
    add_transition("fire", _working, _idle);            
    add_transition("kill", _idle, _dead);
    add_transition("kill", _working, _dead);

    // Make sure we start in the right condition
    reset();
}




void Worker::hire(){
        return;
}

void Worker::fire(){
        return;
}

void Worker::kill(){
        return;
}





/*high_resolution_clock::duration StopWatch::value() {
    if ( current().name() == "on" ) {
        return high_resolution_clock::now() - _start_time + _elapsed;
    } else {
        return _elapsed;
    }
}*/

/*void StopWatch::begin() {
    _start_time = high_resolution_clock::now();
}

void StopWatch::reset() {
    _elapsed = high_resolution_clock::duration::zero();
    _laps.clear();
}

void StopWatch::stop() {
    _elapsed += high_resolution_clock::now() - _start_time;
}

void StopWatch::lap() {
    _laps.insert(_laps.begin(), value());
}*/