#ifndef _ELMA_OVERLORD_H
#define _ELMA_OVERLORD_H

#include <iostream>
#include <chrono>
#include <vector>
#include <ncurses.h>
#include <vector>
#include "minion.h"

namespace overlord {

    using namespace std::chrono;
    using namespace elma;
    using namespace overlord;

    //! An Overlord class, that inherits from Process
    class Overlord : public Process {

        public:

        //! Create a new Overlord
        //! \param std::vector<Minion*>& a vector of pointers to the minion in the manager
        Overlord(std::vector<Minion*>&);

        //! Initialization called by manager before starting
        void init() ;

        //! Initialization called by manager befor running
        void start() {}

        //! Initialization called by manager at scheduled frequency while running
        void update();

        //! Initialization called by manager when finished running
        void stop() {}

        private:
        std::vector<Minion*> _minions;

        void draw_minion(Minion&);
        void draw_debug_info(Minion&);
        void draw_pen();
        void handle_click(int, int);
        void check_collisions();
        void select_minion(int,int);

        bool toggle = false;
        int _selection = -1;
    };

}

#endif