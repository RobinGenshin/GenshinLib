#pragma once
#include <string>
#include "element.h"
#include "stat.h"
#include "talent.h"
#include "region.h"
#include "weapon_type.h"
#include "attentuation_group.h"
#include "attenuation_tag.h"
#include "transformative_reaction.h"

class EnumMap {
public:

	static Element get_element_index(std::string s);

	static std::string get_string_element(Element s);

	static Region get_region_index(std::string s);

	static Talent get_talent_index(std::string s);

	static std::string get_string_talent(Talent s);

	static Stat get_stat_index(std::string s);

	static WeaponType get_weapon_index(std::string s);

	static AttenuationGroup get_agroup_index(std::string s);
	static AttenuationTag get_atag_index(std::string s);

	static std::string get_string_transformative(TransformativeReaction);
};