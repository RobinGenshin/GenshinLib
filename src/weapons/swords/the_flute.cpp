#include "the_flute.h"
#include "read_data.h"
#include "sim.h"
#include "linear_refine_damage_event.h"

TheFlute::TheFlute(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("The Flute")) {
	features.emplace("The Flute Trigger", std::make_unique<TheFluteTrigger>
		(*this, Data::Get().get_feature_dict().at("The Flute Trigger")));

	damage_data.emplace("The Flute On-Hit", std::make_unique<DamageData>());
	DamageData& d = *damage_data.at("The Flute On-Hit").get();
	d.damage = { {DamageScalingStat::ATK, {1.0f}} };
	d.element = Element::PHYSICAL;
	d.ticks = 1;
	d.times = { 0 };
	d.talent_type = Talent::null;
};

TheFlute::TheFluteTrigger::TheFluteTrigger(Component& _component, FeatureData _data) : DynamicFeature(_component, _data) {};
void TheFlute::TheFluteTrigger::Activate(Sim& sim) {
	DynamicFeature::Activate(sim);
	stacks++;
	if (stacks == 5) {
		sim.AddEvent(std::make_shared<LinearRefineDamageEvent>(*component.player, *component.damage_data.at("The Flute On-Hit").get(), 0.25f));
		stacks = 0;
	};
};