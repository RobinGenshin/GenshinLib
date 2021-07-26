#include "normal_talent_event.h"
#include "player.h"
#include "sim.h"

NormalTalentEvent::NormalTalentEvent(Player& p) : TalentEvent(p, p.character.get()->get_talent_data(Talent::NORMAL)) {
}

NormalTalentEvent::NormalTalentEvent(Player& p, int ticks) : TalentEvent(p, p.character.get()->get_talent_data(Talent::NORMAL), ticks) {
}

int NormalTalentEvent::get_pos() {
	return (ticks - 1);
};

float NormalTalentEvent::get_use_time() {
	TalentData& td = dynamic_cast<TalentData&>(data);
	int pos = ticks - 1;
	std::vector<float> v = { td.time_to_cancel[pos], td.time_to_swap[pos], td.time_to_burst[pos], td.time_to_skill[pos] };
	return *min_element(std::begin(v), std::end(v));
};

float NormalTalentEvent::CalculateChainTime(Sim& sim) {

	if (dynamic_cast<TalentData&>(sim.last_talent.get()->data).time_to_attack.size() == 0) {
		float f = sim.PickAnimationCancel();
		return sim.last_talent.get()->get_time_to_cancel() - sim.last_talent.get()->get_use_time() + f;
	}

	float dt = sim.last_talent.get()->get_time_to_attack() - sim.last_talent.get()->get_use_time();
	//std::cout << "DT is: " << dt << std::endl;
	if (dt > (31.0f / 60.0f)) {
		float f = sim.PickAnimationCancel();
		return sim.last_talent.get()->get_time_to_cancel() - sim.last_talent.get()->get_use_time() + f;
	}
	else if (dt > (21.0f / 60.0f)) {
		float f = sim.PickAnimationCancel();
		return sim.last_talent.get()->get_time_to_cancel() - sim.last_talent.get()->get_use_time() + f;
	}
	else return dt;
};


float NormalTalentEvent::get_time_to_attack() {
	if (ticks == data.ticks) return dynamic_cast<TalentData&>(data).at;
	else return TalentEvent::get_time_to_attack();
};

void NormalTalentEvent::ProcessEvent(Sim& sim) {
	DamageEvent::ProcessEvent(sim);
	_player.energy += 0.25;
};

void NormalTalentEvent::InitialiseForSim(Sim& sim) {
	TalentEvent::InitialiseForSim(sim);
};

float NormalTalentEvent::get_ratio(DamageScalingStat damageType, int tick) {
	float m = TalentScaling::Get().scaling_map.at(dynamic_cast<TalentData&>(data).scaling).at(_player.get_normal_level());
	return m * DamageEvent::get_ratio(damageType, tick);
}