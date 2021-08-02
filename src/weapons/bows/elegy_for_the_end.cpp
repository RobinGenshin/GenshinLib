#include "elegy_for_the_end.h"
#include "read_data.h"
#include "linear_refine_stat_modifier.h"
#include "static_feature.h"
#include "stat_modifier_decorator.h"
#include "duration_decorator.h"

ElegyForTheEnd::ElegyForTheEnd(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Elegy For The End")) {
	features.emplace("Elegy For The End Static", std::make_unique<StaticFeature<LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Elegy For The End Static")));
	features.emplace("Elegy For The End Buff", std::make_unique<DurationDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>>
		(*this, Data::Get().get_feature_dict().at("Elegy For The End Buff")));
	features.emplace("Elegy For The End Trigger", std::make_unique<SigilOfRebellion>
		(*this));
};

ElegyForTheEnd::SigilOfRebellion::SigilOfRebellion(ElegyForTheEnd& fs) : DynamicFeature(fs, Data::Get().get_feature_dict().at("Elegy For The End Trigger")) {};
void ElegyForTheEnd::SigilOfRebellion::Activate(Sim& sim) {
	DynamicFeature::Activate(sim);
	stacks++;
	if (stacks == 4) {
		cd = 20;
		dynamic_cast<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>*>(component.features.at("Elegy For The End Buff").get())->Activate(sim);
	};
};