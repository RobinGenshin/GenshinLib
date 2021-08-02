#pragma once

enum class Stat {
	NONE = 0,

	BASE_ATK = 1,
	PCT_ATK,
	FLAT_ATK,

	BASE_DEF,
	PCT_DEF,
	FLAT_DEF,

	BASE_HP,
	PCT_HP,
	FLAT_HP,

	CRIT_RATE,
	NORMAL_CRIT_RATE,
	CHARGED_CRIT_RATE,
	SKILL_CRIT_RATE,
	BURST_CRIT_RATE,
	CONDITIONAL_CRIT_RATE,

	CRIT_DMG,

	ENERGY_RECHARGE,
	ELEMENTAL_MASTERY,

	PHYSICAL_DMG,
	ANEMO_DMG,
	CRYO_DMG,
	ELECTRO_DMG,
	GEO_DMG,
	HYDRO_DMG,
	PYRO_DMG,
	ELEMENTAL_DMG,

	NORMAL_DMG,
	CHARGED_DMG,
	PLUNGE_DMG,
	SKILL_DMG,
	BURST_DMG,
	ALL_DMG,
	CONDITIONAL_ALL_DMG,

	NORMAL_LEVEL,
	SKILL_LEVEL,
	BURST_LEVEL,

	HEALING_BONUS,

	SKILL_CDR,
	BURST_CDR,
	ALL_CDR,

	MAX_SKILL_CHARGES,

	SUPERCONDUCT_DMG,
	OVERLOAD_DMG,
	ELECTROCHARGED_DMG,
	SWIRL_DMG,
	VAPORISE_DMG,
	MELT_DMG,

	NORMAL_ATK_SPEED,

	TRAVEL_TIME_DMG,
};