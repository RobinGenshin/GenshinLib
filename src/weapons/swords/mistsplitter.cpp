#include "mistsplitter.h"
#include "read_data.h"
#include "player.h"

Mistsplitter::Mistsplitter(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Mistsplitter Reforged")) {
	features.emplace("Mistsplitter Elemental Bonus", std::make_unique<Mistsplitter::EleBonus>(*this));
	features.emplace("Mistsplitter NT", std::make_unique<Mistsplitter::NormalTrigger>(*this));
	features.emplace("Mistsplitter BT", std::make_unique<Mistsplitter::BurstTrigger>(*this));

	stats.emplace_back(
		std::make_pair(Stat::ELEMENTAL_DMG, std::make_shared<MistsplitterStatComponent>(*this))
	);
};

Mistsplitter::EleBonus::EleBonus(Mistsplitter& ms) : StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>
(ms, Data::Get().get_feature_dict().at("Mistsplitter R"), 0.25f) {};

Mistsplitter::NormalTrigger::NormalTrigger(Mistsplitter& ms) : DynamicFeature(ms, Data::Get().get_feature_dict().at("Mistsplitter NT")), normal_timer(0) {};
void Mistsplitter::NormalTrigger::Activate(Sim& sim) {
	normal_timer = 5.0f;
};

Mistsplitter::BurstTrigger::BurstTrigger(Mistsplitter& ms) : DynamicFeature(ms, Data::Get().get_feature_dict().at("Mistsplitter BT")), burst_timer(0) {};
void Mistsplitter::BurstTrigger::Activate(Sim& sim) {
	burst_timer = 10.0f;
};

Mistsplitter::MistsplitterStatComponent::MistsplitterStatComponent(Mistsplitter& ms) : mistsplitter(ms) {};
float Mistsplitter::MistsplitterStatComponent::get_value() {
	int stacks = 0;
	if (dynamic_cast<Mistsplitter::NormalTrigger*>(mistsplitter.features.at("Mistsplitter NT").get())->normal_timer > 0) stacks++;
	if (dynamic_cast<Mistsplitter::BurstTrigger*>(mistsplitter.features.at("Mistsplitter BT").get())->burst_timer > 0) stacks++;
	if (mistsplitter.player->energy < mistsplitter.player->character.get()->talent_data.at(Talent::BURST).get()->energy_cost) stacks++;

	if (stacks == 3) return 0.28;
	else return (stacks * 0.08);
}
