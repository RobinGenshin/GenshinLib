#pragma once
#include "weapon.h"
#include "static_feature.h"
#include "linear_refine_stat_modifier.h"
#include "dynamic_feature.h"
#include "stat_modifier_decorator.h"

class Mistsplitter : public GWeapon {
public:
	Mistsplitter(Player* p);

	class EleBonus : public StatModifierDecorator<DynamicFeature,LinearRefineStatModifier> {
	public:
		EleBonus(Mistsplitter& ms);
	};

	class NormalTrigger : public DynamicFeature {
	public:
		NormalTrigger(Mistsplitter& ms);
		virtual void Activate(Sim& sim) override;
		float normal_timer;
	};

	class BurstTrigger : public DynamicFeature {
	public:
		BurstTrigger(Mistsplitter& ms);
		virtual void Activate(Sim& sim) override;
		float burst_timer;
	};

	class MistsplitterStatComponent : public StatComponent {
	public:
		MistsplitterStatComponent(Mistsplitter& ms);
		Mistsplitter& mistsplitter;
		float get_value() override;
	};
};