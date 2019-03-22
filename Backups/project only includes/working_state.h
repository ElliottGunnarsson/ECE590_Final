#ifndef _ELMA_WORKER_WORKING_H
#define _ELMA_WORKER_WORKING_H

#include "worker.h"

namespace worker {

    using namespace std::chrono;
    using namespace elma;

    class worker;  // Declare containing class so it can be refered to here
                      // before it is defined in stopwatch.h 

    //! The on state of the stopwatch
    class Working : public State {        

        public:
        //! Build a new on state
        Working() : State("working") {}
        void entry(const Event& e) {}
        void during() {}

        //! Perform actions required when switching from off to on
        //! \param e The event that triggered the transition        
        void exit(const Event&);

        Worker& worker();        

    };

}

#endif