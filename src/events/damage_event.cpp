#include "damage_event.h"
#include "player.h"
#include "sim.h"
#include "damage_calculation.h"
#include "enum_maps.h"
#include "attenuation.h"

Snapshots::Snapshots(Player& p, DamageEvent& d) {
	ATK = p.get_stat(Stat::BASE_ATK) * (p.get_stat(Stat::PCT_ATK) + 1) + p.get_stat(Stat::FLAT_ATK);
	DEF = p.get_stat(Stat::BASE_DEF) * (p.get_stat(Stat::PCT_DEF) + 1) + p.get_stat(Stat::FLAT_DEF);
	HP = p.get_stat(Stat::BASE_HP) * (p.get_stat(Stat::PCT_HP) + 1) + p.get_stat(Stat::FLAT_HP);
	CR = p.get_stat(Stat::CRIT_RATE);
	CD = p.get_stat(Stat::CRIT_DMG);
	DMG = p.get_stat(Stat::ALL_DMG) + p.get_stat(EnumMap::get_stat_index(EnumMap::get_string_element(d.data.element) + "_dmg"));

	if (d.data.talent_type != Talent::null) {
		DMG += p.get_stat(EnumMap::get_stat_index(EnumMap::get_string_talent(d.data.talent_type) + "_dmg"));
		CR += p.get_stat(EnumMap::get_stat_index("cond_" + EnumMap::get_string_talent(d.data.talent_type) + "_crit_rate"));
	};
};


DamageEvent::DamageEvent(Player& e, DamageData& dd) : AbstractEvent(e), data(dd), ticks(dd.ticks), ticks_used(std::vector<bool>(ticks, false)) {};
DamageEvent::DamageEvent(Player& e, DamageData& dd, int t) : AbstractEvent(e), data(dd), ticks(t), ticks_used(std::vector<bool>(ticks, false)) {};


//Returns index of current tick, i.e. if no ticks have been used, returns 0 as index.
int DamageEvent::get_tick() {
	auto itr = std::find(ticks_used.begin(), ticks_used.end(), false);
	return std::distance(ticks_used.begin(), itr);
};

void DamageEvent::IncrementTick() { ticks_used.at(get_tick()) = true; };

DamageEvent::~DamageEvent() {};

float DamageEvent::get_ratio(DamageScalingStat damageType, int tick) {
	return data.damage.at(damageType)[tick]; 
}

float DamageEvent::get_event_time() { 
	return data.times.at(get_tick()) + _initial_time; 
};

std::vector<std::string> DamageEvent::get_triggers() {
	std::vector<std::string> triggers = std::vector<std::string>{ "damage", EnumMap::get_string_element(data.element) };
	if (data.talent_type != Talent::null) triggers.push_back(EnumMap::get_string_talent(data.talent_type));
	return triggers;
};

void DamageEvent::InitialiseForSim(Sim& sim) {
	AbstractEvent::InitialiseForSim(sim);
	if (snapshot) snapshots = std::make_unique<Snapshots>(_player, *this);
};


void DamageEvent::CheckAttenuation(Sim& sim) {
	if (data.a_tag != AttenuationTag::NONE) {
		std::map<AttenuationTag, Attenuation>& a_map = get_player().character.get()->attenuations;
		if (a_map.find(data.a_tag) == a_map.end()) {
			a_map.emplace(data.a_tag, Attenuation(data.a_tag, data.a_group));
		}
		a_map.at(data.a_tag).ProcessAttenuation(sim, *this);
	};
}

void DamageEvent::ProcessEvent(Sim& sim) {
	CheckAttenuation(sim);
	sim.CheckFeatures(*this, "pre_hit");
	sim.damage += DamageCalculation::StandardCalculate(*this, sim);
	sim.CheckFeatures(*this, "on_hit");
};

void DamageEvent::PostProcessEvent(Sim& sim) {
	IncrementTick();

	if (get_tick() == ticks) {
		AbstractEvent::PostProcessEvent(sim);
	};
}