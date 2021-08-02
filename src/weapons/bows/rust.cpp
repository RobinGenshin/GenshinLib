#include "rust.h"
#include "read_data.h"
#include "stat_modifier_decorator.h"
#include "linear_refine_stat_modifier.h"

Rust::Rust(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Rust")) {
	features.emplace("Rust Static", std::make_unique<StaticFeature<LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Rust Static")));
};
