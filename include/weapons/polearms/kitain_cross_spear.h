#pragma once
#include "weapon.h"
#include "abstract_event.h"
#include "dynamic_feature.h"

class KitainCrossSpear : public GWeapon {
public:
	KitainCrossSpear(Player* p);

	class Trigger : public DynamicFeature {
	public:
		Trigger(Component& _component, FeatureData _data);
		virtual void Activate(Sim& sim) override;
	};

	class EnergyEvent : public AbstractEvent {
	public:
		EnergyEvent(Player& p, float dt, int energy);
		virtual float get_event_time() override;
		virtual std::vector<std::string> get_triggers() override { return {}; };
		virtual void ProcessEvent(Sim& sim) override;
	private:
		float dt;
		int energy;
	};
};
