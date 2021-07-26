#pragma once
#include <vector>
#include <string>

struct EventInfoDelegate {
	EventInfoDelegate() = delete;
	EventInfoDelegate(std::string _event_type, float _event_time) : event_type(_event_type), event_time(_event_time) {};
	std::string event_type;
	float event_time;
};

struct DamageEventInfoDelegate : public EventInfoDelegate {
	float damage_dealt;
	std::string damage_element;
	std::vector<std::string> reactions;
};

struct ParticleEventInfoDelegate : public EventInfoDelegate {
	ParticleEventInfoDelegate(float t) : EventInfoDelegate("particle", t) {};
	std::string particle_element;
	std::string particle_amount;
};