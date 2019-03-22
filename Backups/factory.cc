#include <unistd.h>
#include "factory.h"
#include "minion.h"
#include <chrono>

using namespace overlord;
using namespace std::chrono;

Factory::Factory(
    Channel& mns,
    Channel& odr
) : Process("making minions"),
    _minions(mns),
    _orders(odr)
{};

void Factory::init() {
    _minions.flush();
    _orders.flush();
}

void Factory::update() {
    if (_orders.nonempty()){
        //read order
        //push minion to _minions
    }
}