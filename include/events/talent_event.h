#pragma once
#include "damage_event.h"
#include "talent_data.h"
#include <algorithm>
#include <iostream>

class GCharacter;
class Sim;

class TalentEvent : public DamageEvent {
public:

	TalentEvent(Player& p, TalentData& data);
	TalentEvent(Player& p, TalentData& data, int t);
	virtual ~TalentEvent();

	virtual float get_use_time() = 0;

	virtual float CalculateChainTime(Sim& sim) = 0;
	virtual void InitialiseForSim(Sim& sim) override;
	virtual void ProcessEvent(Sim& sim) = 0;

	virtual float get_ratio(DamageScalingStat damageType, int tick) override = 0;

	virtual int get_pos();
	float get_time_to_swap();
	float get_time_to_cancel();
	virtual float get_time_to_attack();
	float get_time_to_skill();
	float get_time_to_burst();
};
