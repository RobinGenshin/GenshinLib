#pragma once
#include "weapon.h"
#include "dynamic_feature.h"
#include "abstract_event.h"
#include "aggregate_stackable_decorator.h"

class Component;
struct FeatureData;
class EnergyEvent;

class AmenomaKageuchi : public GWeapon {
public:
	AmenomaKageuchi(Player* p);

	class SkillTrigger : public AggregateStackableDecorator<DynamicFeature> {
	public:
		SkillTrigger(Component& _component, FeatureData _data);
		virtual void Activate(Sim& sim) override;
		int stacks = 0;
	};

	class EnergyEvent : public AbstractEvent {
	public:
		EnergyEvent() = delete;
		EnergyEvent(Player& p, int i);
		virtual float get_event_time() override;
		virtual std::vector<std::string> get_triggers() override;
		virtual void ProcessEvent(Sim& sim) override;
		int stacks;
	};

	class BurstTrigger : public DynamicFeature {
	public:
		BurstTrigger(Component& _component, FeatureData _data);
		virtual void Activate(Sim& sim) override;
	};
};