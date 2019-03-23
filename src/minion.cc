#include <chrono>
#include <vector>

#include "minion.h"

#include <tuple>
using std::tuple;
using std::make_tuple;
using std::get;


using namespace std::chrono;
using namespace elma;
using namespace overlord;

Minion::Minion(
            tuple<int,int> coords,
            double attck,
            double defence,
            double efficientcy,
            int speed,
            int reach
) : StateMachine("minon") {

         _attck = attck;
         _defence = defence;
         _efficientcy = efficientcy;
         _speed = speed;
         _reach = reach;
         _coords = coords;
         _target = coords;

    // Define state machine initial states and transitions here
    set_initial(_idle);
    set_propagate(false);
    add_transition("idle_check", _idle, _select);
    add_transition("travel_check", _traveling, _select);
    add_transition("fight_check", _fighting, _select);
    add_transition("idle", _select, _idle);
    add_transition("travel", _select, _traveling);
    add_transition("travel_colide", _traveling, _collide);
    add_transition("idle_colide", _idle, _collide);
    //add_transition("select_colide", _select, _collide);
    add_transition("colide_travel", _collide, _traveling);
    add_transition("colide_idle", _collide, _idle);
    //add_transition("colide_select", _collide, _select);
    
    add_transition("idle_select", _traveling, _idle_select);
    add_transition("idle", _idle_select, _idle);
    add_transition("idle_travel", _idle_select, _traveling);

    add_transition("fight", _collide, _fighting);
    //add_transition("fight_colide", _fighting, _collide);

}

void Minion::add_collision(Minion* mn){
        _collisions.push_back(mn);
        select_colide();
        emit(Event("idle_colide"));
        emit(Event("travel_colide"));
        emit(Event("select_colide"));
        unselect_colide();
};


void Minion::move_minion(){
_move_calls++;

    int compx = get<0>(_coords) - get<0>(_target);
    int compy = get<1>(_coords) - get<1>(_target);
    int tempx = get<0>(_coords);
    int tempy = get<1>(_coords);
     
    if(compx>0){
        if(tempx>3){
                tempx = get<0>(_coords) - _speed;
        }else{
            _xtrim = 0;
        }
    }else if(compx<0){
        if(tempx<50-_size_height){
                tempx = get<0>(_coords) + _speed;
        }else{
            _xtrim = -1;
        }
    }

    if(compy>0){
        if(tempy>3){
                tempy = get<1>(_coords) - _speed;
        }else{
            _ytrim = 0;
        }
    }else if(compy<0){
        if(tempy<90-_size_width){
                tempy = get<1>(_coords) + _speed;
        }else{
            _ytrim = -1;
        }
    }
        _coords = make_tuple(tempx,tempy);
    
    if(current().name() == "traveling" & compx == 0 & compx ==0){
        select_idle();
        emit(Event("idle_select"));
        emit(Event("idle"));
        unselect_idle();
    }    
    
    
    return;
}
