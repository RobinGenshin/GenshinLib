#include "skyward_blade.h"
#include "read_data.h"
#include "stat_modifier_decorator.h"
#include "on_hit_decorator.h"
#include "linear_refine_stat_modifier.h"

SkywardBlade::SkywardBlade(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Skyward Blade")) {
	features.emplace("Skyward Blade Static", std::make_unique<StaticFeature<LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Skyward Blade Static")));
	features.emplace("Skyward Blade Dynamic Buff", std::make_unique<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Skyward Blade Dynamic Buff")));
	//dynamic_features.emplace("Skyward Blade Dynamic Temp On-Hit", std::make_unique<OnHitDecorator<TempDynamicFeature, DamageEvent>>(
	//	"Skyward Blade Dynamic Temp On-Hit", *this, Data::Get().get_feature_dict().at("Skyward Blade Dynamic Temp On-Hit")));

	damage_data.emplace("Skyward Blade Dynamic Temp On-Hit", std::make_unique<DamageData>());
	DamageData& d = *damage_data.at("Skyward Blade Dynamic Temp On-Hit").get();
	d.damage = { {DamageScalingStat::ATK, {0.2f}} };
	d.element = Element::PHYSICAL;
	d.ticks = 1;
	d.times = {0};
	d.talent_type = Talent::null;
};