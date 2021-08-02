#include "hamayumi.h"
#include "read_data.h"
#include "static_feature.h"
#include "linear_refine_stat_modifier.h"
#include "player.h"
#include "character.h"

Hamayumi::Hamayumi(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Hamayumi")) {
	features.emplace("Hamayumi Static", std::make_unique<StaticFeature<HamayumiStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Hamayumi Static")));
};

Hamayumi::HamayumiStatModifier::HamayumiStatModifier(float val, AbstractFeature* feature) : StatModifier(val, feature) {};
float Hamayumi::HamayumiStatModifier::Value() {
	float v = StatModifier::Value();
	if (feature->component.player->energy == feature->component.player->character.get()->get_talent_data(Talent::BURST).energy_cost) v *= 2;
	return v;
};