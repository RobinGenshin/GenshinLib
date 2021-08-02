#pragma once
#include "read_data.h"
#include "static_feature.h"
#include "stat_modifier_decorator.h"
#include "temporary_decorator.h"
#include "damage_data.h"
#include "skill_talent_event.h"

class Amber : public GCharacter {
public:
	Amber(Player* player);

	TalentData& get_talent_data(Talent talentName) override;

	class Skill : public SkillTalentEvent {
	public:
		Skill(Player& p);

		float detonation_time;

		float get_ratio(DamageScalingStat statType, int tick) override;
		void Detonate(Sim& sim);
		bool detonated = false;
		float get_event_time() override;
		void InitialiseForSim(Sim& sim) override;
		void ProcessEvent(Sim& sim) override;
	};

	class C1 : public TalentData {
	public:
		C1(Amber& amber);
	};

	C1 c1;

	class C2 : public DynamicFeature {
	public:
		C2(Amber& amber);
		virtual void Activate(Sim& sim) override;
		std::vector<Amber::Skill*> skills;
	};

private:
};
