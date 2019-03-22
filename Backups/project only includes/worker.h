#ifndef _ELMA_WORKER_H
#define _ELMA_WORKER_H

#include "elma/elma.h" // Note installation directory for elma

#include "dead_state.h"
#include "idle_state.h"
#include "working_state.h"
#include "overlord.h"

namespace worker {

    using namespace std::chrono;
    using namespace elma;    

    //! A stop watch class, that inherits from StateMachine
    class Worker : public StateMachine {

        public:
        //! Make a new stopwatch
        Worker();

        //! Start the stopwatch
        void hire();

        //! Reset the stopwatch to zero and erase laps
        void fire();

        //! Stop the stopwatch
        void kill();

        //! Add a lap time to the list of lap times.
        //void lap();

        //! Get the time stored by the stopwatch
        //high_resolution_clock::duration value();

        //! Get a list of lap times
        //const vector<high_resolution_clock::duration>& laps() { return _laps; }

        private:

        // When overriding the StateMachine class, put state declarations here.
        Idle _idle;
        Working _working;
        Dead _dead

        // Other private variables
        //bool _running;
        //high_resolution_clock::time_point _start_time;
        //high_resolution_clock::duration _elapsed;
        //vector<high_resolution_clock::duration> _laps;

    };

}

#endif