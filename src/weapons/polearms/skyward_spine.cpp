#include "skyward_spine.h"
#include "read_data.h"
#include "static_feature.h"
#include "linear_refine_stat_modifier.h"
#include "percentage_decorator.h"
#include "on_hit_decorator.h"
#include "linear_refine_damage_event.h"

SkywardSpine::SkywardSpine(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Skyward Spine")) {

	features.emplace("Skyward Spine Static Linear Refine", std::make_unique<StaticFeature<LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Skyward Spine Static Linear Refine")));
	features.emplace("Skyward Spine Static", std::make_unique<StaticFeature<StatModifier>>
		(*this, Data::Get().get_feature_dict().at("Skyward Spine Static")));
	features.emplace("Skyward Spine On-Hit", std::make_unique<PercentageDecorator<OnHitDecorator<DynamicFeature, LinearRefineDamageEvent>>>
		(0.5f, "Skyward Spine On-Hit", 0.375f, *this, Data::Get().get_feature_dict().at("Skyward Spine On-Hit")));

	damage_data.emplace("Skyward Spine On-Hit", std::make_unique<DamageData>());
	DamageData& d = *damage_data.at("Skyward Spine On-Hit").get();
	d.damage = { {DamageScalingStat::ATK, {0.4f}} };
	d.element = Element::PHYSICAL;
	d.ticks = 1;
	d.times = { 0 };
	d.talent_type = Talent::null;
};