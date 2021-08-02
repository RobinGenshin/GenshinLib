#include "mistsplitter.h"
#include "read_data.h"
#include "player.h"
#include "duration_decorator.h"

Mistsplitter::Mistsplitter(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Mistsplitter Reforged")) {
	features.emplace("Mistsplitter Elemental Bonus", std::make_unique<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Mistsplitter R")));
	features.emplace("Mistsplitter NT", std::make_unique<DurationDecorator<DynamicFeature>>
		(*this, Data::Get().get_feature_dict().at("Mistsplitter NT")));
	features.emplace("Mistsplitter BT", std::make_unique<DurationDecorator<DynamicFeature>>
		(*this, Data::Get().get_feature_dict().at("Mistsplitter BT")));

	stats.emplace_back(
		std::make_pair(Stat::ELEMENTAL_DMG, std::make_shared<MistsplitterStatComponent>(*this))
	);
};

Mistsplitter::MistsplitterStatComponent::MistsplitterStatComponent(Mistsplitter& ms) : mistsplitter(ms) {};
float Mistsplitter::MistsplitterStatComponent::get_value() {
	int stacks = 0;
	if (dynamic_cast<DurationDecorator<DynamicFeature>*>(mistsplitter.features.at("Mistsplitter NT").get())->modifier_duration_remaining > 0) stacks++;
	if (dynamic_cast<DurationDecorator<DynamicFeature>*>(mistsplitter.features.at("Mistsplitter BT").get())->modifier_duration_remaining > 0) stacks++;
	if (mistsplitter.player->energy < mistsplitter.player->character.get()->talent_data.at(Talent::BURST).get()->energy_cost) stacks++;

	float v;
	if (stacks == 3) v = 0.28f;
	else v = (stacks * 0.08f);
	v *= (1 + 0.25f * float(mistsplitter.player->refinement - 1));
	return v;
};
