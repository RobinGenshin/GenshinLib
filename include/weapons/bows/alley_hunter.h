#pragma once
#include "weapon.h"
#include "stat_modifier.h"
#include "dynamic_feature.h"
#include "stat_modifier_decorator.h"

class AlleyHunter : public GWeapon {
public:
	AlleyHunter(Player* p);

	class AlleyHunterStatModifier : public StatModifier {
	public:
		AlleyHunterStatModifier(float val, AbstractFeature* feature);
		float dmg_pct = 0.2f;
		float field_timer = 0;
		float Value() override { return dmg_pct; };
	};

	class AlleyHunterFeature : public StatModifierDecorator<DynamicFeature, AlleyHunterStatModifier> {
	public:
		AlleyHunterFeature(Component& _component, FeatureData _data);
		virtual void PassTime(float dt) override;
	};
};
