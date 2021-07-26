#include "abstract_event.h"
#include "sim.h"
#include "player.h"


AbstractEvent::AbstractEvent(Player& player) : _player(player) {};
AbstractEvent::~AbstractEvent() {};

float AbstractEvent::get_initial_time() { return _initial_time; };
void AbstractEvent::set_initial_time(float t) { _initial_time = t; };

Player& AbstractEvent::get_player() { return _player; };

void AbstractEvent::InitialiseForSim(Sim& sim) { 
	set_initial_time(sim.current_time); 
};

void AbstractEvent::ProcessEvent(Sim& sim) {
	sim.PassTime(get_event_time() - sim.current_time);
};

void AbstractEvent::PostProcessEvent(Sim& sim) {
	for (auto& i : sim.events) {
		if (*i.get() == *this)
			sim.events.erase(std::remove(sim.events.begin(), sim.events.end(), i), sim.events.end());
	};
};