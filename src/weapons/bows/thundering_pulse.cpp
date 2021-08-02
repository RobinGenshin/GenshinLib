#include "thundering_pulse.h"
#include "read_data.h"
#include "player.h"
#include "duration_decorator.h"
#include "linear_refine_stat_modifier.h"

ThunderingPulse::ThunderingPulse(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("ThunderingPulse Reforged")) {
	features.emplace("Thundering Pulse Atk Bonus", std::make_unique<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("ThunderingPulse R")));
	features.emplace("Thundering Pulse NT", std::make_unique<DurationDecorator<DynamicFeature>>
		(*this, Data::Get().get_feature_dict().at("Thundering Pulse NT")));
	features.emplace("Thundering Pulse BT", std::make_unique<DurationDecorator<DynamicFeature>>
		(*this, Data::Get().get_feature_dict().at("Thundering Pulse BT")));

	stats.emplace_back(
		std::make_pair(Stat::ELEMENTAL_DMG, std::make_shared<ThunderingPulseStatComponent>(*this))
	);
};

ThunderingPulse::ThunderingPulseStatComponent::ThunderingPulseStatComponent(ThunderingPulse& _tp) : tp(_tp) {};
float ThunderingPulse::ThunderingPulseStatComponent::get_value() {
	int stacks = 0;
	if (dynamic_cast<DurationDecorator<DynamicFeature>*>(tp.features.at("Thundering Pulse NT").get())->modifier_duration_remaining > 0) stacks++;
	if (dynamic_cast<DurationDecorator<DynamicFeature>*>(tp.features.at("Thundering Pulse ST").get())->modifier_duration_remaining > 0) stacks++;
	if (tp.player->energy < tp.player->character.get()->talent_data.at(Talent::BURST).get()->energy_cost) stacks++;

	float v;
	if (stacks == 3) v = 0.28f;
	else v = (stacks * 0.08f);
	v *= (1 + 0.25f * float(tp.player->refinement - 1));
	return v;
};
