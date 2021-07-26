#pragma once
#include "talent_event.h"

class ChargedTalentEvent : public TalentEvent {
public:
	ChargedTalentEvent(Player& p);
	ChargedTalentEvent(Player& p, int ticks);
	virtual float get_use_time() override;

	virtual int get_pos() override;
	virtual float CalculateChainTime(Sim& sim) override;
	void ProcessEvent(Sim& sim) override;
	void InitialiseForSim(Sim& sim) override;

	virtual float get_ratio(DamageScalingStat damageType, int tick) override;
};