#include "skyward_blade.h"
#include "read_data.h"
#include "stat_modifier_decorator.h"
#include "on_hit_decorator.h"
#include "temporary_decorator.h"
#include "linear_refine_stat_modifier.h"
#include "linear_refine_damage_event.h"
#include "component.h"
#include "feature_data.h"

SkywardBlade::SkywardBlade(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Skyward Blade")) {

	features.emplace("Skyward Blade Static", std::make_unique<StaticFeature<LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Skyward Blade Static")));

	features.emplace("Skyward Blade Dynamic Buff", std::make_unique<StatModifierDecorator<Trigger, LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Skyward Blade Dynamic Buff")));

	features.emplace("Skyward Blade Dynamic Temp On-Hit", std::make_unique<OnHitDecorator<TemporaryDecorator<DynamicFeature>, LinearRefineDamageEvent>>
		("Skyward Blade Dynamic Temp On-Hit", *this, Data::Get().get_feature_dict().at("Skyward Blade Dynamic Temp On-Hit")));

	damage_data.emplace("Skyward Blade Dynamic Temp On-Hit", std::make_unique<DamageData>());
	DamageData& d = *damage_data.at("Skyward Blade Dynamic Temp On-Hit").get();
	d.damage = { {DamageScalingStat::ATK, {0.2f}} };
	d.element = Element::PHYSICAL;
	d.ticks = 1;
	d.times = {0};
	d.talent_type = Talent::null;
};

SkywardBlade::Trigger::Trigger(Component& _component, FeatureData _data) : DynamicFeature(_component, _data) {};
void SkywardBlade::Trigger::Activate(Sim& sim) {
	DynamicFeature::Activate(sim);
	dynamic_cast<TemporaryDecorator<DynamicFeature>*>(component.features.at("Skyward Blade Dynamic Temp On-Hit").get())->TemporarilyEnable();
};