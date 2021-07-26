#include "talent_event.h"
#include "sim.h"
#include "talent_scaling.h"

TalentEvent::TalentEvent(Player& p, TalentData& data) : DamageEvent(p, data) {};
TalentEvent::TalentEvent(Player& p, TalentData& data, int t) : DamageEvent(p, data, t) {};
TalentEvent::~TalentEvent() {};


void TalentEvent::InitialiseForSim(Sim& sim) {
	DamageEvent::InitialiseForSim(sim);
}


int TalentEvent::get_pos() {
	return 0;
}

float TalentEvent::get_time_to_swap() {
	return dynamic_cast<TalentData&>(data).time_to_swap.at(get_pos());
}

float TalentEvent::get_time_to_cancel() {
	return dynamic_cast<TalentData&>(data).time_to_cancel.at(get_pos());
}

float TalentEvent::get_time_to_attack() {
	return dynamic_cast<TalentData&>(data).time_to_attack.at(get_pos());
};

float TalentEvent::get_time_to_skill() {
	return dynamic_cast<TalentData&>(data).time_to_skill.at(get_pos());
};

float TalentEvent::get_time_to_burst() {
	return dynamic_cast<TalentData&>(data).time_to_burst.at(get_pos());
};

