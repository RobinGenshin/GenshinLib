#pragma once
#include "read_data.h"
#include "static_feature.h"
#include "stat_modifier_decorator.h"
#include "temporary_decorator.h"
#include "damage_data.h"
#include "burst_talent_event.h"

class Albedo : public GCharacter {
public:
	Albedo(Player* player);
	int c2_stacks = 0;

	class TBData : public TalentData {
	public:
		TBData();
	};

	class Burst : public BurstTalentEvent {
	public:
		Burst(Player& p);
		virtual float get_ratio(DamageScalingStat stat, int tick) override;
		virtual void InitialiseForSim(Sim& sim) override;
	private:
		int c2_stacks;
	};

	class TransientBlossom : public DamageEvent {
	public:
		TransientBlossom(Player& player, TalentData& td);
		virtual std::vector<std::string> get_triggers() override;
		virtual void ProcessEvent(Sim& sim) override;
		virtual float get_ratio(DamageScalingStat damageType, int tick) override;
	};

	class SkillCast : public DynamicFeature {
	public:
		SkillCast(Albedo& albedo);
		virtual void Activate(Sim& sim) override;
	};
	
	class SkillTrigger : public TemporaryDecorator<DynamicFeature> {
	public:
		SkillTrigger(Albedo& albedo);
		virtual void Activate(Sim& sim) override;
	};

	class A2 : public StaticFeature<> {
	public:
		A2(Albedo& albedo);
	};

	class A4 : public StatModifierDecorator<DynamicFeature> {
	public:
		A4(Albedo& albedo);
	};

	class C1 : public DynamicFeature {
	public:
		C1(Albedo& albedo);
		virtual void Activate(Sim& sim) override;
	};

	class C2 : public DynamicFeature {
	public:
		C2(Albedo& albedo);
		virtual void Activate(Sim& sim) override;
	};

	class C3 : public StaticFeature<> {
	public:
		C3(Albedo& albedo);
	};

	class C4 : public StatModifierDecorator<DynamicFeature> {
	public:
		C4(Albedo& albedo);
	};

	class C5 : public StaticFeature<> {
	public:
		C5(Albedo& albedo);
	};

	class C6 : public StatModifierDecorator<DynamicFeature> {
	public:
		C6(Albedo& albedo);
	};

private:
};
