#include <iostream>
#include <chrono>
#include <vector>
#include <random>
#include <tuple>

#include "minion.h"

using namespace std::chrono;
using namespace elma;
using namespace overlord;
using std::tuple; 
using std::make_tuple; 

Minion& Idle:: minion() { return (Minion&) state_machine(); }
void Idle::entry(const Event& e) {}
void Idle::exit(const Event& e) {}
void Idle::during() {
    minion().set_target(make_tuple(
        std::get<0>(minion().get_coords()) + rand()%2 + minion().get_xtrim(),
        std::get<1>(minion().get_coords()) + rand()%2 + minion().get_ytrim()));
    minion().move_minion();
}

Minion& Traveling:: minion() { return (Minion&) state_machine(); }
void Traveling::entry(const Event& e) {}
void Traveling::exit(const Event& e) {}
void Traveling::during() {
    minion().move_minion();
}

Minion& Fighting:: minion() { return (Minion&) state_machine(); }
void Fighting::entry(const Event& e) {}
void Fighting::exit(const Event& e) {}
void Fighting::during() {
    /*minion().set_target(make_tuple(
        std::get<0>(minion().get_coords()) + rand()%2,
        std::get<1>(minion().get_coords()) + rand()%2));*/
    minion().move_minion();
}

Minion& Select:: minion() { return (Minion&) state_machine(); }
void Select::entry(const Event& e) {
    if ( e.name() == "idle_select" & !minion().selected() ){
        emit(Event("idle_select"));
        emit(Event("select_idle"));
    }else if ( e.name() == "travel_select" & !minion().selected() ){
        emit(Event("travel_select"));
        emit(Event("select_travel"));
    }else if ( e.name() == "fight_select" & !minion().selected() ){
        emit(Event("fight_select"));
        emit(Event("select_fight"));
    }
}
void Select::exit(const Event& e) {}

Minion& Colide:: minion() { return (Minion&) state_machine(); }
void Colide::entry(const Event& e) {
    if ( e.name() == "idle_collide" & !minion().selected_colide() ){
        emit(Event("idle_collide"));
        emit(Event("collide_idle"));
    }else if ( e.name() == "travel_collide" & !minion().selected_colide() ){
        emit(Event("travel_collide"));
        emit(Event("collide_travel"));
    /*}else if ( e.name() == "select_colide" & !minion().selected_colide() ){
        emit(Event("select_colide"));
        emit(Event("colide_select"));*/
    }else if ( e.name() == "fight_collide" & !minion().selected_colide() ){
        emit(Event("fight_collide"));
        emit(Event("collide_fight"));
    }
    
}
void Colide::exit(const Event& e) {}

Minion& Idle_Check:: minion() { return (Minion&) state_machine(); }
void Idle_Check::entry(const Event& e) {
    if ( e.name() == "travel_idle_check" & !minion().selected_idle() ){
        emit(Event("travel_idle_check"));
        emit(Event("idle_check_travel"));
    }/*else if ( e.name() == "fight_select" & !minion().selected_idle() ){
        emit(Event("fight_select"));
        emit(Event("idle_travel"));*/
    
}
void Idle_Check::exit(const Event& e) {}