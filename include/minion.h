#ifndef _ELMA_MINION_H
#define _ELMA_MINION_H

#include "elma/elma.h" // Note installation directory for elma
#include <vector>
#include "minion_states.h"
#include "overlord.h"
#include <tuple>

namespace overlord {

    using namespace std::chrono;
    using namespace elma;   
    using std::tuple; 

    //! A Minion class, that inherits from StateMachine
    class Minion : public StateMachine {

        public:
        //! Create a new Minion. Stats default to 1
        //! \param coords a tuple with initial x y coorfdnate data. defaults to 0,0
        //! \param attack attack stat 
        //! \param defence defence stat
        //! \param efficientcy how fast resource is harvested
        //! \param speed movement speed
        //! \param reach how far away minion can attack
        Minion(
            tuple<int,int> coords = std::make_tuple(0,0),
            double attck = 1,
            double defence = 1,
            double efficientcy = 1,
            int speed = 1,
            int reach = 1
        );

        //! move the minion closer to the the target by 1 speed unit
        void move_minion();

        //! return current position
        //! \return tuple with x,y position
        tuple<int,int> get_coords() {return _coords;};

        //! return target position
        //! \return tuple with x,y target position
        tuple<int,int> get_coords_target() {return _target;};
        
        //! set the target position
        //! \param tg tuple of target position
        void set_target(tuple<int,int> tg){_target = tg;};
        
        //! used internally by overlord to reset the collsion checker
        void clear_collisions(){_collisions.erase(_collisions.begin(),_collisions.end());};
        
        //! add a pointer to the list of minions within reach
        //! \param Minion* the minion that is in collision
        void add_collision(Minion*);

        //! returns how manny minions are in reach
        //! \return number of minions in colision vector
        int collisions(){return _collisions.size();};

        //! used for debugging
        //! \return return number of times move update was called
        int get_move_calls(){return _move_calls;};

        //! used internally for colision detection
        //! \return minion height
        int get_size_height(){return _size_height;};

        //! used internally for colision detection
        //! \return minion width
        int get_size_width(){return _size_width;};

        //! uned to indicate selected minion
        void select(){_selected = true;};
        //! uned to indicate selected minion
        void unselect(){_selected = false;};
        //! uned to indicate selected minion
        //! \return true if minion is selected my user
        bool selected(){return _selected;};

        //! used internally be colison detector. needed for state machine transition
        void select_colide(){_selected_colide = true;};
        //! used internally be colison detector. needed for state machine transition
        void unselect_colide(){_selected_colide = false;};
        //! used internally be colison detector. needed for state machine transition
        //! \return true if colition is recently detected.
        bool selected_colide(){return _selected_colide;};

        //! used internally be idle detector. needed for state machine transition
        void select_idle(){_selected_idle = true;};
        //! used internally be idle detector. needed for state machine transition
        void unselect_idle(){_selected_idle = false;};
        //! used internally be idle detector. needed for state machine transition
        //! \return true if colition is recently detected.
        bool selected_idle(){return _selected_idle;};

        //! used internally by AI
        //! \return returns direction of drift
        int get_xtrim(){return _xtrim;};

        //! used internally by AI
        //! \return returns direction of drift
        int get_ytrim(){return _ytrim;};

        private:

        // When overriding the StateMachine class, put state declarations here.
        Idle _idle;
        Traveling _traveling;
        Fighting _fighting;
        Select _select;
        Colide _collide;
        Idle_Check _idle_check;

        // Other private variables
        double _attck;
        double _defence;
        double _efficientcy;
        int _speed;
        int _reach;

        double _resource;
        tuple<int,int> _coords;
        tuple<int,int> _target;
        
        int _move_calls = 0;
        int _size_height = 3;
        int _size_width = 4;
        
        std::vector<Minion*> _collisions;
        bool _selected = false;
        bool _selected_colide = false;
        bool _selected_idle = false;

        int _xtrim = 0;
        int _ytrim = 0;
    };

}

#endif