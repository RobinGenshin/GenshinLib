#include "enum_maps.h"
#include <map>
#include <stdexcept>

Element EnumMap::get_element_index(std::string s) {
	static std::map<std::string, Element> string_to_element = {
		{"anemo", Element::ANEMO},
		{"cryo", Element::CRYO},
		{"electro", Element::ELECTRO},
		{"geo", Element::GEO},
		{"hydro", Element::HYDRO},
		{"pyro", Element::PYRO},
		{"physical", Element::PHYSICAL}
	};

	auto x = string_to_element.find(s);
	if (x != std::end(string_to_element)) {
		return x->second;
	}
	throw std::invalid_argument("s");
};

std::string EnumMap::get_string_element(Element s) {
	static std::map<Element, std::string> element_to_string = {
		{Element::ANEMO, "anemo"},
		{Element::CRYO, "cryo"},
		{Element::ELECTRO, "electro"},
		{Element::GEO, "geo"},
		{Element::HYDRO, "hydro"},
		{Element::PYRO, "pyro"},
		{Element::PHYSICAL, "physical"}
	};

	auto x = element_to_string.find(s);
	if (x != std::end(element_to_string)) {
		return x->second;
	}
	throw std::invalid_argument("s");
};

Region EnumMap::get_region_index(std::string s) {
	static std::map<std::string, Region> string_to_region = {
		{"Mondstadt", Region::MONDSTADT},
		{"Inazuma", Region::INAZUMA},
	};

	auto x = string_to_region.find(s);
	if (x != std::end(string_to_region)) {
		return x->second;
	}
	throw std::invalid_argument("s");
};

Talent EnumMap::get_talent_index(std::string s) {
	static std::map<std::string, Talent> string_to_talent = {
		{"normal", Talent::NORMAL},
		{"charged", Talent::CHARGED},
		{"plunged", Talent::PLUNGED},
		{"skill", Talent::SKILL},
		{"burst", Talent::BURST},
	};

	auto x = string_to_talent.find(s);
	if (x != std::end(string_to_talent)) {
		return x->second;
	}
	throw std::invalid_argument("s");
};

std::string EnumMap::get_string_talent(Talent s) {
	static std::map<Talent, std::string> talent_to_string = {
		{Talent::NORMAL, "normal"},
		{Talent::CHARGED, "charged"},
		{Talent::PLUNGED, "plunged"},
		{Talent::SKILL, "skill"},
		{Talent::BURST, "burst"}
	};

	auto x = talent_to_string.find(s);
	if (x != std::end(talent_to_string)) {
		return x->second;
	}
	throw std::invalid_argument("s");
};

Stat EnumMap::get_stat_index(std::string s) {
	static std::map<std::string, Stat> string_to_stat = {
		{"base_atk", Stat::BASE_ATK },
		{"pct_atk", Stat::PCT_ATK},
		{"flat_atk", Stat::FLAT_ATK},

		{"base_def", Stat::BASE_DEF},
		{"pct_def", Stat::PCT_DEF},
		{"flat_def", Stat::FLAT_DEF},

		{"base_hp", Stat::BASE_HP},
		{"pct_hp", Stat::PCT_HP},
		{"flat_hp", Stat::FLAT_HP},

		{"crit_rate", Stat::CRIT_RATE},
		{"normal_crit_rate", Stat::NORMAL_CRIT_RATE},
		{"charged_crit_rate", Stat::CHARGED_CRIT_RATE},
		{"skill_crit_rate", Stat::SKILL_CRIT_RATE},
		{"burst_crit_rate", Stat::BURST_CRIT_RATE},
		{"cond_crit_rate", Stat::CONDITIONAL_CRIT_RATE},

		{"crit_dmg", Stat::CRIT_DMG},

		{"recharge", Stat::ENERGY_RECHARGE},
		{"ele_m", Stat::ELEMENTAL_MASTERY},

		{"physical_dmg", Stat::PHYSICAL_DMG},
		{"anemo_dmg", Stat::ANEMO_DMG},
		{"cryo_dmg", Stat::CRYO_DMG},
		{"electro_dmg", Stat::ELECTRO_DMG},
		{"geo_dmg", Stat::GEO_DMG},
		{"hydro_dmg", Stat::HYDRO_DMG},
		{"pyro_dmg", Stat::PYRO_DMG},

		{"normal_dmg", Stat::NORMAL_DMG},
		{"charged_dmg", Stat::CHARGED_DMG},
		{"skill_dmg", Stat::SKILL_DMG},
		{"burst_dmg", Stat::BURST_DMG},
		{"plunge_dmg", Stat::PLUNGE_DMG},
		{"ele_dmg", Stat::ELEMENTAL_DMG},
		{"all_dmg", Stat::ALL_DMG},
		{"cond_all_dmg", Stat::CONDITIONAL_ALL_DMG},

		{"cond_normal_crit_rate", Stat::CONDITIONAL_CRIT_RATE},
		{"cond_skill_crit_rate", Stat::CONDITIONAL_CRIT_RATE},
		{"cond_charged_crit_rate", Stat::CONDITIONAL_CRIT_RATE},
		{"cond_plunged_crit_rate", Stat::CONDITIONAL_CRIT_RATE},
		{"cond_burst_crit_rate", Stat::CONDITIONAL_CRIT_RATE},

		{"normal_level", Stat::NORMAL_LEVEL},
		{"skill_level", Stat::SKILL_LEVEL},
		{"burst_level", Stat::BURST_LEVEL},

		{"heal_bonus", Stat::HEALING_BONUS},

		{"skill_cdr", Stat::SKILL_CDR},
		{"burst_cdr", Stat::BURST_CDR},
		{"all_cdr", Stat::ALL_CDR},

		{"max_skill_charges", Stat::MAX_SKILL_CHARGES},

		{"normal_atk_speed", Stat::NORMAL_ATK_SPEED}
	};

	auto x = string_to_stat.find(s);
	if (x != std::end(string_to_stat)) {
		return x->second;
	}
	throw std::invalid_argument(s);
};

WeaponType EnumMap::get_weapon_index(std::string s) {
	static std::map<std::string, WeaponType> string_to_weapon = {
		{"claymore", WeaponType::CLAYMORE},
		{"sword", WeaponType::SWORD},
		{"polearm", WeaponType::POLEARM},
		{"bow", WeaponType::BOW},
		{"catalyst", WeaponType::CATALYST}
	};

	auto x = string_to_weapon.find(s);
	if (x != std::end(string_to_weapon)) {
		return x->second;
	}
	throw std::invalid_argument(s);
};

AttenuationGroup EnumMap::get_agroup_index(std::string s) {
	static std::map<std::string, AttenuationGroup> string_to_group = {
		{"Default", AttenuationGroup::DEFAULT},
		{"Polearm Charged Attack", AttenuationGroup::POLEARM_CHARGED_ATTACK},
		{"Amber", AttenuationGroup::AMBER},
		{"Venti", AttenuationGroup::VENTI},
		{"Xiao", AttenuationGroup::XIAO},
		{"Fischl", AttenuationGroup::FISCHL},
		{"Diluc", AttenuationGroup::DILUC}
	};

	auto x = string_to_group.find(s);
	if (x != std::end(string_to_group)) {
		return x->second;
	}
	throw std::invalid_argument(s);
};

AttenuationTag EnumMap::get_atag_index(std::string s) {
	static std::map<std::string, AttenuationTag> string_to_tag = {
		{"", AttenuationTag::NONE},
		{"Normal Attack", AttenuationTag::NORMAL_ATTACK},
		{"Elemental Burst Extra", AttenuationTag::ELEMENTAL_BURST_EXTRA},

		{"Hydro Damage", AttenuationTag::HYDRO_DAMAGE},
		{"Pyro Damage", AttenuationTag::PYRO_DAMAGE},
		{"Electro Damage", AttenuationTag::ELECTRO_DAMAGE},

		{"foul_legacy", AttenuationTag::FOUL_LEGACY},
		{"riptide", AttenuationTag::RIPTIDE},
		{"Charged Attack", AttenuationTag::CHARGED_ATTACK},

		{"elemental_skill", AttenuationTag::ELEMENTAL_SKILL},
		{"elemental_skill_anemo", AttenuationTag::ELEMENTAL_SKILL_ANEMO},
		{"elemental_skill_cryo", AttenuationTag::ELEMENTAL_SKILL_CRYO},
		{"elemental_skill_electro", AttenuationTag::ELEMENTAL_SKILL_ELECTRO},
		{"elemental_skill_hydro", AttenuationTag::ELEMENTAL_SKILL_HYDRO},
		{"elemental_skill_pyro", AttenuationTag::ELEMENTAL_SKILL_PYRO},

		{"elemental_burst", AttenuationTag::ELEMENTAL_BURST},
		{"elemental_burst_cryo", AttenuationTag::ELEMENTAL_BURST_CRYO},
		{"elemental_burst_electro", AttenuationTag::ELEMENTAL_BURST_ELECTRO},
		{"elemental_burst_hydro", AttenuationTag::ELEMENTAL_BURST_HYDRO},
		{"elemental_burst_pyro", AttenuationTag::ELEMENTAL_BURST_PYRO},

		{"wake_of_earth", AttenuationTag::WAKE_OF_EARTH},
		{"illusory_torrent", AttenuationTag::ILLUSORY_TORRENT}
	};

	auto x = string_to_tag.find(s);
	if (x != std::end(string_to_tag)) {
		return x->second;
	}
	throw std::invalid_argument(s);
};

std::string EnumMap::get_string_transformative(TransformativeReaction t_r) {
	static std::map<TransformativeReaction, std::string> tr_to_string = {
		{TransformativeReaction::ELECTROCHARGED, "electrocharged"},
		{TransformativeReaction::OVERLOAD, "overload"},
		{TransformativeReaction::SHATTERED, "shattered"},
		{TransformativeReaction::SUPERCONDUCT, "superconduct"},
		{TransformativeReaction::SWIRL_CRYO, "swirl_cryo"},
		{TransformativeReaction::SWIRL_ELECTRO, "swirl_electro"},
		{TransformativeReaction::SWIRL_HYDRO, "swirl_hydro"},
		{TransformativeReaction::SWIRL_PYRO, "swirl_pyro"}
	};

	auto x = tr_to_string.find(t_r);
	if (x != std::end(tr_to_string)) {
		return x->second;
	}
	throw std::invalid_argument("t_r");

};