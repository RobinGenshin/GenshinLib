#include "skyward_harp.h"
#include "read_data.h"
#include "player.h"

SkywardHarp::SkywardHarp(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Skyward Harp")) {
	features.emplace("Skyward Harp On-Hit", std::make_unique<SkywardHarpTrigger>
		(*this, Data::Get().get_feature_dict().at("Skyward Harp On-Hit")));

	damage_data.emplace("Skyward Harp On-Hit", std::make_unique<DamageData>());
	DamageData& d = *damage_data.at("Skyward Harp On-Hit").get();
	d.damage = { {DamageScalingStat::ATK, {1.25f}} };
	d.element = Element::PHYSICAL;
	d.ticks = 1;
	d.times = { 0 };
	d.talent_type = Talent::null;
};

SkywardHarp::SkywardHarpTrigger::SkywardHarpTrigger(Component& _component, FeatureData _data) 
	: PercentageDecorator<OnHitDecorator<DynamicFeature, DamageEvent>>(0, "Skyward Harp On-Hit", _component, _data) {};

void SkywardHarp::SkywardHarpTrigger::ActivatePct(Sim& sim) {
	PercentageDecorator<OnHitDecorator<DynamicFeature, DamageEvent>>::ActivatePct(sim);
	cd = 4.5f - component.player->refinement * 0.5f;
};

float SkywardHarp::SkywardHarpTrigger::get_pct() {
	return component.player->get_stat(Stat::CRIT_RATE);
};