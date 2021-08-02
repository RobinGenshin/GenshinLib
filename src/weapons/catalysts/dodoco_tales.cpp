#include "dodoco_tales.h"
#include "read_data.h"
#include "duration_decorator.h"
#include "stat_modifier_decorator.h"
#include "dynamic_feature.h"
#include "linear_refine_stat_modifier.h"

DodocoTales::DodocoTales(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Dodoco Tales")) {
	features.emplace("Dodoco Normal Trigger", std::make_unique<DurationDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>>
		(*this, Data::Get().get_feature_dict().at("Dodoco Normal Trigger")));
	features.emplace("Dodoco Charged Trigger", std::make_unique<DurationDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>>
		(*this, Data::Get().get_feature_dict().at("Dodoco Charged Trigger")));
};