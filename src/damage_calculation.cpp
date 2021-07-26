#include "damage_calculation.h"
#include <memory>
#include <string>
#include <functional>
#include "component.h"
#include "sim.h"
#include "damage_event.h"
#include <algorithm>
#include "enemy.h"
#include "enum_maps.h"


float DamageCalculation::StandardCalculate(DamageEvent& dE, Sim& sim) {
	float dmg = 0;
	for (auto& i : dE.data.damage) dmg += StandardHelper(dE, sim, dE.get_tick(), i.first);
	return dmg;
};

float DamageCalculation::StandardHelper(DamageEvent& dE, Sim& sim, int tick, DamageScalingStat stat) {
	Player& player = dE.get_player();

	float totCoreStat;
	float critRate;
	float critDMG;
	float dmgBonus;

	float ratio = dE.get_ratio(stat, tick);
	float RES = sim.enemy->get_RES_multi(dE.data.element);
	float DEFENCE = (100 + player.character_level) / (100 + player.character_level + sim.enemy->get_DEF());
	if (!dE.snapshot) {
		if (stat == DamageScalingStat::ATK) totCoreStat = player.get_stat(Stat::BASE_ATK) * player.get_stat(Stat::PCT_ATK) + player.get_stat(Stat::FLAT_ATK);
		else if (stat == DamageScalingStat::DEF) totCoreStat = player.get_stat(Stat::BASE_DEF) * player.get_stat(Stat::PCT_DEF) + player.get_stat(Stat::FLAT_DEF);
		else if (stat == DamageScalingStat::HP) totCoreStat = player.get_stat(Stat::BASE_HP) * player.get_stat(Stat::PCT_HP) + player.get_stat(Stat::FLAT_HP);
		else throw std::runtime_error("Incorrect stat assignent");
		critRate = std::min(1.0f, player.get_stat(Stat::CRIT_RATE) + player.get_stat(Stat::CONDITIONAL_CRIT_RATE) + player.get_stat(EnumMap::get_stat_index("cond_" + EnumMap::get_string_talent(dE.data.talent_type) + "_crit_rate")));
		critDMG = player.get_stat(Stat::CRIT_DMG);
		dmgBonus = 
			player.get_stat(Stat::ALL_DMG) +
			player.get_stat(Stat::CONDITIONAL_ALL_DMG) + 
			player.get_stat(EnumMap::get_stat_index(EnumMap::get_string_element(dE.data.element) + "_dmg"));

		if (dE.data.talent_type != Talent::null) dmgBonus += player.get_stat(EnumMap::get_stat_index(EnumMap::get_string_talent(dE.data.talent_type) + "_dmg"));
	}
	else {
		if (stat == DamageScalingStat::ATK) totCoreStat = dE.snapshots.get()->ATK;
		else if (stat == DamageScalingStat::DEF) totCoreStat = dE.snapshots.get()->DEF;
		else if (stat == DamageScalingStat::HP) totCoreStat = dE.snapshots.get()->HP;
		else throw std::runtime_error("Incorrect stat assignent");
		critRate = dE.snapshots.get()->CR + player.get_stat(Stat::CONDITIONAL_CRIT_RATE);
		critDMG = dE.snapshots.get()->CD;
		dmgBonus = dE.snapshots.get()->DMG + player.get_stat(Stat::CONDITIONAL_ALL_DMG);
	};
	//if (stat == DamageScalingStat::ATK) cout << "\n" << totCoreStat << " * ( 1 + " << critRate << " * " << critDMG << " ) * " << dmgBonus << " * " << ratio << " * ( 1 - " << RES << " ) * " << DEF << endl;
	//if (stat == DamageScalingStat::DEF) cout << "\n" << totCoreStat << " * ( 1 + " << critRate << " * " << critDMG << " ) * " << dmgBonus << " * " << ratio << " * ( 1 - " << RES << " ) * " << DEF << endl;
	//if (stat == DamageScalingStat::HP) cout << "\n" << totCoreStat << " * ( 1 + " << critRate << " * " << critDMG << " ) * " << dmgBonus << " * " << ratio << " * ( 1 - " << RES << " ) * " << DEF << endl;

	//std::cout << totCoreStat << " * ( 1 + " << critRate << " * " << critDMG << " ) " << " * " << dmgBonus << " * " << ratio << " * " << "( 1 - " << RES << " ) * " << DEFENCE << std::endl;
	return totCoreStat * (1 + critRate * critDMG) * ( 1 + dmgBonus ) * ratio * (1 - RES) * DEFENCE;

};


float DamageCalculation::TransformativeCalculate(TransformativeReactionEvent& t_r_event, Sim& sim) {
	Player& player = t_r_event.get_player();

	switch (t_r_event.transformative_reaction)
	{
	case TransformativeReaction::SUPERCONDUCT:
		return 0.5f * (1 + get_em_multiplier(player) + player.get_stat(Stat::SUPERCONDUCT_DMG)) * get_level_scaling(player.character_level) * (1 - sim.enemy->get_RES_multi(Element::CRYO));
	case TransformativeReaction::SWIRL_CRYO:
		return 0.6f * (1 + get_em_multiplier(player) + player.get_stat(Stat::SWIRL_DMG)) * get_level_scaling(player.character_level) * (1 - sim.enemy->get_RES_multi(Element::CRYO));
	case TransformativeReaction::SWIRL_ELECTRO:
		return 0.6f * (1 + get_em_multiplier(player) + player.get_stat(Stat::SWIRL_DMG)) * get_level_scaling(player.character_level) * (1 - sim.enemy->get_RES_multi(Element::ELECTRO));
	case TransformativeReaction::SWIRL_HYDRO:
		return 0.6f * (1 + get_em_multiplier(player) + player.get_stat(Stat::SWIRL_DMG)) * get_level_scaling(player.character_level) * (1 - sim.enemy->get_RES_multi(Element::HYDRO));
	case TransformativeReaction::SWIRL_PYRO:
		return 0.6f * (1 + get_em_multiplier(player) + player.get_stat(Stat::SWIRL_DMG)) * get_level_scaling(player.character_level) * (1 - sim.enemy->get_RES_multi(Element::PYRO));
	case TransformativeReaction::OVERLOAD:
		return 2.0f * (1 + get_em_multiplier(player) + player.get_stat(Stat::OVERLOAD_DMG)) * get_level_scaling(player.character_level) * (1 - sim.enemy->get_RES_multi(Element::PYRO));
	case TransformativeReaction::SHATTERED:
		return 1.5f * (1 + get_em_multiplier(player)) * get_level_scaling(player.character_level) * (1 - sim.enemy->get_RES_multi(Element::PHYSICAL));
	case TransformativeReaction::ELECTROCHARGED:
		return 1.2f * (1 + get_em_multiplier(player) + player.get_stat(Stat::ELECTROCHARGED_DMG)) * get_level_scaling(player.character_level) * (1 - sim.enemy->get_RES_multi(Element::ELECTRO));
	};
}

float DamageCalculation::get_level_scaling(int character_level) {
	return Data::Get().get_reaction_scaling_dict().at(character_level);
}

float DamageCalculation::get_em_multiplier(Player& p) {
	float em = p.get_stat(Stat::ELEMENTAL_MASTERY);
	float em_mult = 16 * (em / (em + 2000));
	return em_mult;
};