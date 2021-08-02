#pragma once
#include "weapon.h"
#include "dynamic_feature.h"

class Component;
struct FeatureData;

class SkywardBlade : public GWeapon {
public:
	SkywardBlade(Player* p);

	class Trigger : public DynamicFeature {
	public:
		Trigger(Component& _component, FeatureData _data);
		virtual void Activate(Sim& sim) override;
	};
};