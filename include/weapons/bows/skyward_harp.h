#pragma once
#include "weapon.h"
#include "percentage_decorator.h"
#include "dynamic_feature.h"
#include "on_hit_decorator.h"
#include "linear_refine_damage_event.h"

class SkywardHarp : public GWeapon {
public:
	SkywardHarp(Player* p);

	class SkywardHarpTrigger : public PercentageDecorator<OnHitDecorator<DynamicFeature, DamageEvent>> {
	public:
		SkywardHarpTrigger(Component& _component, FeatureData _data);
		virtual void ActivatePct(Sim& sim) override;
		virtual float get_pct() override;
	};
};
