#include "primordial_jade_cutter.h"
#include "read_data.h"
#include "player.h"

PrimordialJadeCutter::PrimordialJadeCutter(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Primordial Jade Cutter")) {
	features.emplace("Primordial Jade Cutter Static", std::make_unique<StaticFeature<PrimordialJadeCutter::HPConversionModifier>>
		(*this, Data::Get().get_feature_dict().at("Primordial Jade Cutter Static"), *this));
};

PrimordialJadeCutter::HPConversionModifier::HPConversionModifier(float val, AbstractFeature* feature, PrimordialJadeCutter& _pjc) : pjc(_pjc), StatModifier(val, feature) {};
float PrimordialJadeCutter::HPConversionModifier::Value() {
	int& r = pjc.player->refinement;
	float hp = pjc.player->get_stat(Stat::BASE_HP) * pjc.player->get_stat(Stat::PCT_HP) + pjc.player->get_stat(Stat::FLAT_HP);
	return 0.012f * hp * (1 + (r - 1) * 0.25f);
};