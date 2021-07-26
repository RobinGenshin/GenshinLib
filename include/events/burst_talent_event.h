#pragma once
#include "talent_event.h"

class BurstTalentEvent : public TalentEvent {
public:
	BurstTalentEvent(Player& p);
	virtual float get_use_time() override;


	virtual float CalculateChainTime(Sim& sim) override;
	void ProcessEvent(Sim& sim) override;
	virtual void PostProcessEvent(Sim& sim) override;
	void InitialiseForSim(Sim& sim) override;

	virtual float get_ratio(DamageScalingStat damageType, int tick) override;
};