#pragma once
#include "abstract_event.h"
#include "damage_data.h"
#include <map>
#include <component.h>
#include <vector>
#include <iostream>
#include "amplifying_reaction.h"

class Sim;
class Component;
class Player;
class DamageEvent;

struct Snapshots {

	Snapshots() = delete;
	Snapshots(Player& p, DamageEvent& d);

	float ATK;
	float HP;
	float DEF;
	float CR;
	float CD;
	float DMG;
};

class DamageEvent : public AbstractEvent {
public:
	DamageData& data;
	float hitlag_time = 0;
	const int ticks;

	DamageEvent(Player& e, DamageData& dd);
	DamageEvent(Player& e, DamageData& dd, int t);

	std::string name;

	bool snapshot = true;
	std::unique_ptr<Snapshots> snapshots = nullptr;
	std::vector<bool> ticks_used;
	std::vector<AmplifyingReaction> amp_reaction;

	inline int get_tick();

	void IncrementTick();

	virtual ~DamageEvent();
	virtual float get_ratio(DamageScalingStat damageType, int tick);
	virtual float get_event_time() override;
	virtual std::vector<std::string> get_triggers() override;

	void CheckAttenuation(Sim& sim);
	virtual void InitialiseForSim(Sim& sim) override;
	virtual void ProcessEvent(Sim& sim) override;
	virtual void PostProcessEvent(Sim& sim) override;
};