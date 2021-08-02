#include "the_viridescent_hunt.h"
#include "read_data.h"
#include "player.h"

TheViridescentHunt::TheViridescentHunt(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("The Viridescent Hunt")) {
	features.emplace("The Viridescent Hunt On-Hit", std::make_unique<VHTrigger>
		(*this, Data::Get().get_feature_dict().at("The Viridescent Hunt On-Hit")));

	damage_data.emplace("The Viridescent Hunt On-Hit", std::make_unique<DamageData>());
	DamageData& d = *damage_data.at("The Viridescent Hunt On-Hit").get();
	d.damage = { {DamageScalingStat::ATK, {0.4f,0.4f,0.4f,0.4f,0.4f,0.4f,0.4f,0.4f}} };
	d.element = Element::PHYSICAL;
	d.ticks = 8;
	d.times = { 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f, 3.5f, 4.0f};
	d.talent_type = Talent::null;
};

TheViridescentHunt::VHTrigger::VHTrigger(Component& _component, FeatureData _data)
	: PercentageDecorator<OnHitDecorator<DynamicFeature, LinearRefineDamageEvent>>(0.5f, "The Viridescent Hunt On-Hit", _component, _data) {};

void TheViridescentHunt::VHTrigger::ActivatePct(Sim& sim) {
	PercentageDecorator<OnHitDecorator<DynamicFeature, LinearRefineDamageEvent>>::ActivatePct(sim);
	cd = float(15 - component.player->refinement);
};