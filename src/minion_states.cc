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
        std::get<0>(minion().get_coords()) + rand()%2,
        std::get<1>(minion().get_coords()) + rand()%2));
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

Minion& Select:: minion() { return (Minion&) state_machine(); }
void Select::entry(const Event& e) {
    if ( e.name() == "idle_check" & !minion().selected() ){
        emit(Event("idle_check"));
        emit(Event("idle"));
    }else if ( e.name() == "travel_check" & !minion().selected() ){
        emit(Event("travel_check"));
        emit(Event("travel"));
    }
}
void Select::exit(const Event& e) {}

Minion& Colide:: minion() { return (Minion&) state_machine(); }
void Colide::entry(const Event& e) {
    if ( e.name() == "idle_colide" & !minion().selected_colide() ){
        emit(Event("idle_colide"));
        emit(Event("colide_idle"));
    }else if ( e.name() == "travel_colide" & !minion().selected_colide() ){
        emit(Event("travel_colide"));
        emit(Event("colide_travel"));
    }else if ( e.name() == "select_colide" & !minion().selected_colide() ){
        emit(Event("select_colide"));
        emit(Event("colide_select"));
    }
    
}
void Colide::exit(const Event& e) {}
