#pragma once
#include "weapon.h"
#include "dynamic_feature.h"

class TheFlute : public GWeapon {
public:
	TheFlute(Player* p);

	class TheFluteTrigger : public DynamicFeature {
	public:
		TheFluteTrigger(Component& _component, FeatureData _data);
		virtual void Activate(Sim& sim) override;
		int stacks = 0;
	};
};