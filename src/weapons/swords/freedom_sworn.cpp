#include "freedom_sworn.h"
#include "read_data.h"
#include "linear_refine_stat_modifier.h"
#include "static_feature.h"
#include "stat_modifier_decorator.h"
#include "duration_decorator.h"

FreedomSworn::FreedomSworn(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Freedom Sworn")) {
	features.emplace("Freedom Sworn Static", std::make_unique<StaticFeature<LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Freedom Sworn Static")));
	features.emplace("Freedom Sworn Buff", std::make_unique<DurationDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>>
		(*this, Data::Get().get_feature_dict().at("Freedom Sworn Buff")));
	features.emplace("Freedom Sworn Trigger", std::make_unique<SigilOfRebellion>
		(*this));
}

FreedomSworn::SigilOfRebellion::SigilOfRebellion(FreedomSworn& fs) : DynamicFeature(fs, Data::Get().get_feature_dict().at("Freedom Sworn Trigger")) {};
void FreedomSworn::SigilOfRebellion::Activate(Sim& sim) {
	DynamicFeature::Activate(sim);
	stacks++;
	if (stacks == 2) {
		cd = 20;
		dynamic_cast<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>*>(component.features.at("Freedom Sworn Buff").get())->Activate(sim);
	};
};