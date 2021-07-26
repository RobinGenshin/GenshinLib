#include "charged_talent_event.h"
#include "player.h"
#include "sim.h"
#include "talent_scaling.h"


ChargedTalentEvent::ChargedTalentEvent(Player& p) : TalentEvent(p, p.character.get()->get_talent_data(Talent::CHARGED)) {
}


ChargedTalentEvent::ChargedTalentEvent(Player& p, int ticks) : TalentEvent(p, p.character.get()->get_talent_data(Talent::CHARGED), ticks) {
}

int ChargedTalentEvent::get_pos() {
	if (_player.character.get()->weapon_type == WeaponType::CLAYMORE) return ticks - 1;
	return 0;
};

float ChargedTalentEvent::get_use_time() {
	TalentData& td = dynamic_cast<TalentData&>(data);
	int pos = 0;
	std::vector<float> v = { td.time_to_cancel[pos], td.time_to_swap[pos], td.time_to_burst[pos], td.time_to_skill[pos] };
	return *min_element(std::begin(v), std::end(v));
};

float ChargedTalentEvent::CalculateChainTime(Sim& sim) {
	WeaponType weapon = _player.character.get()->weapon_type;
	if (weapon == WeaponType::BOW) return sim.last_talent.get()->get_time_to_cancel();

	if (weapon == WeaponType::SWORD || weapon == WeaponType::POLEARM) return sim.last_talent.get()->get_time_to_attack();

	if (weapon == WeaponType::CATALYST || weapon == WeaponType::CLAYMORE) {
		float dt = sim.last_talent.get()->get_time_to_attack() - sim.last_talent.get()->get_use_time();
		if (dt < (31.0f / 60.0f)) {
			float f = sim.PickAnimationCancel();
			return sim.last_talent.get()->get_time_to_cancel() - sim.last_talent.get()->get_use_time() + f;
		}
		else if (dt < (21.0f / 60.0f)) {
			float f = sim.PickAnimationCancel();
			return sim.last_talent.get()->get_time_to_cancel() - sim.last_talent.get()->get_use_time() + f;
		}
		else return dt;
	}
};


void ChargedTalentEvent::ProcessEvent(Sim& sim) {
	DamageEvent::ProcessEvent(sim);
};


void ChargedTalentEvent::InitialiseForSim(Sim& sim) {
	TalentEvent::InitialiseForSim(sim);
};


float ChargedTalentEvent::get_ratio(DamageScalingStat damageType, int tick) {
	float m = TalentScaling::Get().scaling_map.at(dynamic_cast<TalentData&>(data).scaling).at(_player.get_normal_level());
	return m * DamageEvent::get_ratio(damageType, tick);
}