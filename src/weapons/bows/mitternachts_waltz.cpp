#include "mitternachts_waltz.h"
#include "read_data.h"
#include "stat_modifier_decorator.h"
#include "duration_decorator.h"
#include "linear_refine_stat_modifier.h"

MitternachtsWaltz::MitternachtsWaltz(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Mitternachts Waltz")) {
	features.emplace("Mitternachts Waltz Normal Trigger", std::make_unique<DurationDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>>
		(*this, Data::Get().get_feature_dict().at("Mitternachts Waltz Normal Trigger")));
	features.emplace("Mitternachts Waltz Skill Trigger", std::make_unique<DurationDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>>
		(*this, Data::Get().get_feature_dict().at("Mitternachts Waltz Skill Trigger")));
};
