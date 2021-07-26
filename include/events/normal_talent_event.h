#pragma once
#include "talent_event.h"
#include "talent_scaling.h"
#include "player.h"

class NormalTalentEvent : public TalentEvent {
public:
	NormalTalentEvent(Player& p);
	NormalTalentEvent(Player& p, int ticks);
	virtual float get_use_time() override;

	int get_pos() override;
	virtual float CalculateChainTime(Sim& sim) override;

	float get_time_to_attack() override;
	void ProcessEvent(Sim& sim) override;
	void InitialiseForSim(Sim& sim) override;

	virtual float get_ratio(DamageScalingStat damageType, int tick) override;
};