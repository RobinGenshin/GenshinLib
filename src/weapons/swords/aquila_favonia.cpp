#include "aquila_favonia.h"
#include "read_data.h"
#include "linear_refine_stat_modifier.h"
#include "on_hit_decorator.h"
#include "linear_refine_damage_event.h"

AquilaFavonia::AquilaFavonia(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Aquila Favonia")) {
	features.emplace("Aquila Favonia Static", std::make_unique<StaticFeature<LinearRefineStatModifier>>(
		*this, Data::Get().get_feature_dict().at("Aquila Favonia Static")));

	features.emplace("Aquila Favonia On-Hit", std::make_unique<OnHitDecorator<DynamicFeature, LinearRefineDamageEvent>>
		("Aquila Favonia On-Hit", 0.15f, *this, Data::Get().get_feature_dict().at("Aquila Favonia On-Hit")));

	damage_data.emplace("Aquila Favonia On-Hit", std::make_unique<DamageData>());
	DamageData& d = *damage_data.at("Aquila Favonia On-Hit").get();
	d.damage = { {DamageScalingStat::ATK, {2.0f}} };
	d.element = Element::PHYSICAL;
	d.ticks = 1;
	d.times = { 0 };
	d.talent_type = Talent::null;
};