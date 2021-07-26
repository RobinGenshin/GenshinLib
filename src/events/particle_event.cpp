#include "particle_event.h"
#include "sim.h"

ParticleEvent::ParticleEvent(Player& p, Element _element, float _amount) : AbstractEvent(p), element(_element), amount(_amount) {

};

float ParticleEvent::get_event_time() {
	return _initial_time + 1.25;
}

void ParticleEvent::ProcessEvent(Sim& sim) {
	for (auto& i : sim.players) {
		float field_mult = 1;
		float element_mult = 1;
		if (!(*(i.get()) == *sim.current_player)) field_mult = 0.6;
		if (i.get()->character.get()->character_element == element) element_mult = 3;
		i.get()->energy += amount * field_mult * element_mult;
	};
};

std::vector<std::string> ParticleEvent::get_triggers() {
	return std::vector<std::string>{"particle"};
};

void ParticleEvent::PostProcessEvent(Sim& sim) {
	for (auto& i : sim.events) {
		if (*dynamic_cast<ParticleEvent*>(i.get()) == *this)
			sim.events.erase(std::remove(sim.events.begin(), sim.events.end(), i), sim.events.end());
	};
}