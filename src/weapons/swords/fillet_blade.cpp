#include "fillet_blade.h"
#include "read_data.h"
#include "percentage_decorator.h"
#include "on_hit_decorator.h"
#include "linear_refine_damage_event.h"
#include "player.h"

FilletBlade::FilletBlade(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Fillet Blade")) {
	features.emplace("Fillet Blade On-Hit", std::make_unique<FilletBladeOnHit>
		("Fillet Blade On-Hit", *this, Data::Get().get_feature_dict().at("Fillet Blade On-Hit")));

	damage_data.emplace("Fillet Blade On-Hit", std::make_unique<DamageData>());
	DamageData & d = *damage_data.at("Fillet Blade On-Hit").get();
	d.damage = { {DamageScalingStat::ATK, {2.0f}} };
	d.element = Element::PHYSICAL;
	d.ticks = 1;
	d.times = { 0 };
	d.talent_type = Talent::null;
};


FilletBlade::FilletBladeOnHit::FilletBladeOnHit(std::string key, Component& _component, FeatureData _data)
	: PercentageDecorator<OnHitDecorator<DynamicFeature, LinearRefineDamageEvent>>(0.5f, key, 0.1666f, _component, _data) {};
void FilletBlade::FilletBladeOnHit::ActivatePct(Sim& sim) {
	PercentageDecorator<OnHitDecorator<DynamicFeature, LinearRefineDamageEvent>>::ActivatePct(sim);
	cd = 16 - component.player->refinement;
};