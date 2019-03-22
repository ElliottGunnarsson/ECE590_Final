#ifndef _ELMA_FACTORY_H
#define _ELMA_FACTORY_H

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

    class Factory : public Process {

        public:

        Factory(Channel& mns,
                Channel& odr);

        void init();
        void start() {}
        void update();
        void stop() {}

        private:
        Channel& _minions = channel("minions");
        Channel& _orders = channel("orders");
    };

}

#endif