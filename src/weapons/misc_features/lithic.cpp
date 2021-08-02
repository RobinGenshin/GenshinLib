#include "lithic.h"
#include "component.h"
#include "player.h"
#include "team.h"

LithicStatModifier::LithicStatModifier(float val, AbstractFeature* feature, Component& c, float ratio) : comp(c), LinearRefineStatModifier(val, feature, ratio) {};
float LithicStatModifier::Value() {
	int liyue = 0;
	for (auto& i : comp.player->team.players) {
		if (i.get()->character.get()->region == Region::LIYUE) liyue++;
	};
	return liyue * LinearRefineStatModifier::Value();
};