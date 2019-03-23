#ifndef _ELMA_MINION_STATES_H
#define _ELMA_MINION_STATES_H

#include "minion.h"

namespace overlord {

    using namespace std::chrono;
    using namespace elma;

    class Minion; 

    //! the idle state for Minions
    class Idle : public State {        
        public:
        //! build a new Idle state
        Idle() : State("idle") {}
        //! called when entering Idle state
        void entry(const Event&);
        //! called every update while in Idle state
        void during();      
        //! called when exiting Idle state
        void exit(const Event&);
        Minion& minion();        
    };
    //! the Traveling state for Minions
    class Traveling : public State {        
        public:
        //! build a new Traveling state
        Traveling() : State("traveling") {}
        //! called when entering Traveling state
        void entry(const Event&);
        //! called every update while in Traveling state
        void during() ;      
        //! called when exiting Traveling state
        void exit(const Event&);
        Minion& minion();        
    };
    //! the Fighting state for Minions
    class Fighting : public State {        
        public:
        //! build a new Fighting state
        Fighting() : State("fighting") {}
        //! called when entering Fighting state
        void entry(const Event&);
        //! called every update while in Fighting state
        void during() ;       
        //! called when exiting Fighting state    
        void exit(const Event&);
        Minion& minion();        
    };
    //! the Select state for Minions
    class Select : public State {        
        public:
        //! build a new Select state
        Select() : State("select") {}
        //! called when entering Select state
        void entry(const Event&);
        //! called every update while in Select state
        void during() {}            
        //! called when exiting Select state
        void exit(const Event&);
        Minion& minion();        
    };
    //! the Colide state for Minions
    class Colide : public State {        
        public:
        //! build a new Colide state
        Colide() : State("colide") {}
        //! called when entering Colide state
        void entry(const Event&);
        //! called every update while in Colide state
        void during() {emit(Event("collide_fight"));}            
        //! called when exiting Colide state
        void exit(const Event&);
        Minion& minion();        
    };
    //! the Idle_Check state for Minions
    class Idle_Check : public State {        
        public:
        //! build a new Idle_Select state
        Idle_Check() : State("idle_check") {}
        //! called when entering Idle_Select state
        void entry(const Event&);
        //! called every update while in Idle_Select state
        void during() {emit(Event("idle_check_idle"));}            
        //! called when exiting Idle_Select state
        void exit(const Event&);
        Minion& minion();        
    };
}

#endif