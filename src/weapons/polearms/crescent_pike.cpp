#include "crescent_pike.h"
#include "read_data.h"
#include "on_hit_decorator.h"
#include "temporary_decorator.h"
#include "linear_refine_damage_event.h"

CrescentPike::CrescentPike(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Crescent Pike")) {
	features.emplace("Crescent Pike Trigger", std::make_unique<CrescentPikeTrigger>
		(*this, Data::Get().get_feature_dict().at("Crescent Pike Trigger")));

	features.emplace("Crescent Pike On-Hit", std::make_unique<OnHitDecorator<TemporaryDecorator<DynamicFeature>, LinearRefineDamageEvent>>
		("Crescent Pike On-Hit", *this, Data::Get().get_feature_dict().at("Crescent Pike On-Hit")));

	damage_data.emplace("Crescent Pike On-Hit", std::make_unique<DamageData>());
	DamageData& d = *damage_data.at("Crescent Pike On-Hit").get();
	d.damage = { {DamageScalingStat::ATK, {0.2f}} };
	d.element = Element::PHYSICAL;
	d.ticks = 1;
	d.times = { 0 };
	d.talent_type = Talent::null;
};

CrescentPike::CrescentPikeTrigger::CrescentPikeTrigger(Component& _component, FeatureData _data) : DynamicFeature(_component, _data) {};
void CrescentPike::CrescentPikeTrigger::Activate(Sim& sim) {
	DynamicFeature::Activate(sim);
	dynamic_cast<TemporaryDecorator<DynamicFeature>*>(component.features.at("Crescent Pike On-Hit").get())->TemporarilyEnable();
};