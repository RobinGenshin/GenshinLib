#pragma once
#include "read_data.h"
#include "damage_data.h"
#include "skill_talent_event.h"

class Barbara : public GCharacter {
public:
	Barbara(Player* player);

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

	class A2 : public StaticFeature {
	public:
		A2(Barbara& barbara);
	};

	class A4 : public BuffDynamicFeature {
	public:
		A4(Barbara& barbara);
	};

	class C1 : public TalentData {
	public:
		C1(Barbara& barbara);
	};

	C1 c1;

	class C2 : public DynamicFeature {
	public:
		C2(Barbara& barbara);
		virtual void Activate(Sim& sim) override;
		std::vector<Barbara::Skill*> skills;
	};

	class C3 : public StaticFeature {
	public:
		C3(Barbara& barbara);
	};

	class C4 : public StaticFeature {
	public:
		C4(Barbara& barbara);
	};

	class C5 : public StaticFeature {
	public:
		C5(Barbara& barbara);
	};

	class C6 : public BuffDynamicFeature {
	public:
		C6(Barbara& barbara);
	};

private:
};
