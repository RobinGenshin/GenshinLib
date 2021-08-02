#include "alley_hunter.h"
#include "player.h"
#include "sim.h"

AlleyHunter::AlleyHunter(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Alley Hunter")) {
	features.emplace("Alley Hunter Dynamic", std::make_unique<AlleyHunterFeature>
		(*this, Data::Get().get_feature_dict().at("Alley Hunter Dynamic")));
};

AlleyHunter::AlleyHunterStatModifier::AlleyHunterStatModifier(float val, AbstractFeature* feature) : StatModifier(val, feature) {};

AlleyHunter::AlleyHunterFeature::AlleyHunterFeature(Component& _component, FeatureData _data) 
	: StatModifierDecorator<DynamicFeature, AlleyHunterStatModifier>(_component, _data) {};

void AlleyHunter::AlleyHunterFeature::PassTime(float dt) {
	DynamicFeature::PassTime(dt);
	if (*component.player->sim->current_player == *component.player) {
		for (auto& i : stat_modifiers) {
			AlleyHunterStatModifier& sm = *dynamic_cast<AlleyHunterStatModifier*>(i.second.get());
			sm.field_timer += dt;
			if (sm.field_timer >= 4.0f) sm.dmg_pct = std::max(float(0), sm.dmg_pct - 0.04f * dt);
		}; 
	}
	else {
		for (auto& i : stat_modifiers) {
			AlleyHunterStatModifier& sm = *dynamic_cast<AlleyHunterStatModifier*>(i.second.get());
			sm.field_timer = 0;
			sm.dmg_pct = std::min(0.2f, sm.dmg_pct + 0.02f * dt);
		};
	};
};