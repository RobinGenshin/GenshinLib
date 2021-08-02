#include "staff_of_homa.h"
#include "read_data.h"
#include "player.h"

StaffOfHoma::StaffOfHoma(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Staff of Homa")) {
	features.emplace("Staff of Homa Static", std::make_unique<StaticFeature<HPConversionModifier>>
		(*this, Data::Get().get_feature_dict().at("Staff of Homa Static"), *this));
};

StaffOfHoma::HPConversionModifier::HPConversionModifier(float val, AbstractFeature* f, StaffOfHoma& _homa) : homa(_homa), StatModifier(0, f) {}
float StaffOfHoma::HPConversionModifier::Value() {
	int& r = homa.player->refinement;
	float hp = homa.player->get_stat(Stat::BASE_HP) * homa.player->get_stat(Stat::PCT_HP) + homa.player->get_stat(Stat::FLAT_HP);
	return hp * (0.018f + (r - 1) * 0.004f);
};