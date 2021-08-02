#include "amenoma_kageuchi.h"
#include "read_data.h"
#include "player.h"
#include "sim.h"
#include "feature_data.h"


AmenomaKageuchi::AmenomaKageuchi(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Amenoma Kageuchi")) {
	features.emplace("Amenoma Kageuchi Skill Trigger", std::make_unique<AmenomaKageuchi::SkillTrigger>
		(*this, Data::Get().get_feature_dict().at("Amenoma Kageuchi Skill Trigger")));
	features.emplace("Amenoma Kageuchi Burst Trigger", std::make_unique<AmenomaKageuchi::BurstTrigger>
		(*this, Data::Get().get_feature_dict().at("Amenoma Kageuchi Burst Trigger")));
};

AmenomaKageuchi::SkillTrigger::SkillTrigger(Component& _component, FeatureData _data) : AggregateStackableDecorator<DynamicFeature>(_component, _data) {};
void AmenomaKageuchi::SkillTrigger::Activate(Sim& sim) {
	DynamicFeature::Activate(sim);
	stacks = std::max(3, stacks + 1);
};

AmenomaKageuchi::EnergyEvent::EnergyEvent(Player& p, int i) : AbstractEvent(p), stacks(i) {};
float AmenomaKageuchi::EnergyEvent::get_event_time() {
	return _initial_time + 2.0f;
};

AmenomaKageuchi::BurstTrigger::BurstTrigger(Component& _component, FeatureData _data) : DynamicFeature(_component, _data) {};
void AmenomaKageuchi::BurstTrigger::Activate(Sim& sim) {
	DynamicFeature::Activate(sim);
	sim.AddEvent(std::make_shared<EnergyEvent>
		(*component.player, dynamic_cast<SkillTrigger*>(component.features.at("Amenoma Kageuchi Skill Trigger").get())->stacks));
	dynamic_cast<SkillTrigger*>(component.features.at("Amenoma Kageuchi Skill Trigger").get())->stacks = 0;
};

void AmenomaKageuchi::EnergyEvent::ProcessEvent(Sim& sim) {
	AbstractEvent::ProcessEvent(sim);
	_player.energy += 6 * stacks * (1 + (_player.refinement - 1) * 0.25f);
};

std::vector<std::string> AmenomaKageuchi::EnergyEvent::get_triggers() {
	return std::vector<std::string>{};
};