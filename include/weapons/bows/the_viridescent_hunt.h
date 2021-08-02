#pragma once
#include "weapon.h"
#include "percentage_decorator.h"
#include "on_hit_decorator.h"
#include "dynamic_feature.h"
#include "linear_refine_damage_event.h"

class TheViridescentHunt : public GWeapon {
public:
	TheViridescentHunt(Player* p);

	class VHTrigger : public PercentageDecorator<OnHitDecorator<DynamicFeature, LinearRefineDamageEvent>> {
	public:
		VHTrigger(Component& _component, FeatureData _data);
		virtual void ActivatePct(Sim& sim) override;
	};
};
