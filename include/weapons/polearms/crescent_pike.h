#pragma once
#include "weapon.h"
#include "dynamic_feature.h"

class CrescentPike : public GWeapon {
public:
	CrescentPike(Player* p);

	class CrescentPikeTrigger : public DynamicFeature {
	public:
		CrescentPikeTrigger(Component& _component, FeatureData _data);
		virtual void Activate(Sim& sim);
	};
};