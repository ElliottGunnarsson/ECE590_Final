#include <iostream>
#include <chrono>
#include <vector>
#include <ncurses.h>
#include <tuple>

#include "minion.h"

using namespace std::chrono;
using namespace elma;
using namespace overlord;

int main() {

    //create a manager to update the game pices
    Manager m;

    //create your army of minions with individual stats
    Minion Peter(std::make_tuple(5,10),       //starting position
                 1,                            //attack
                 1,                            //defence
                 1,                            //efficientcy
                 1,                            //speed
                 1);                           //reach
    
    Minion Cottontail(std::make_tuple(15,10),  //starting position
                 1,                            //attack
                 1,                            //defence
                 1,                            //efficientcy
                 1,                            //speed
                 1);                           //reach
    
    Minion Benjamin(std::make_tuple(25,10),    //starting position
                 1,                            //attack
                 1,                            //defence
                 1,                            //efficientcy
                 1,                            //speed
                 1);                           //reach
    
    Minion Lily(std::make_tuple(35,10),        //starting position
                 1,                            //attack
                 1,                            //defence
                 1,                            //efficientcy
                 1,                            //speed
                 1);                           //reach
    
    Minion Flopsy(std::make_tuple(43,10),      //starting position
                 1,                            //attack
                 1,                            //defence
                 1,                            //efficientcy
                 1,                            //speed
                 1);                           //reach

    //add the addresses to a pointer vector
    std::vector<Minion*> _minions = {&Peter,
                                    &Cottontail,
                                    &Benjamin,
                                    &Lily,
                                    &Flopsy};

    //create the user interfave
    Overlord ov(_minions);
    
    //schedule all your minions or they won't update
    for(int i=0;i<_minions.size();i++){
        m.schedule(*_minions[i], 10_ms);
    }

    //schedule the overlord and run the game
    m.schedule(ov, 100_ms)
     .init()
     .run();

    endwin();     

}