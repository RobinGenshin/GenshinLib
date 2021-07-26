#pragma once
#include "component.h"
#include "character_stat_growths.h"
#include "character_base_stat_component.h"
#include "character_ascension_stat_component.h"
#include "artifact_substat_stat_component.h"
#include "talent_event.h"
#include <functional>
#include "talent.h"
#include "stat.h"
#include "element.h"
#include "region.h"
#include "weapon_type.h"
#include "attenuation.h"

class GCharacter : public Component {
public:

	GCharacter();
	GCharacter(const GCharacter& toCopy);
	GCharacter(Player* player, const GCharacter& toCopy);


	std::string character_name;
	Element character_element;
	Stat ascension_stat;
	Region region;
	WeaponType weapon_type;
	int character_rarity;
	int* character_level;

	CharacterStatGrowths character_stat_growths;
	std::map<Talent, std::shared_ptr<TalentData>> talent_data;
	virtual TalentData& get_talent_data(Talent talentName);

	std::map<Talent, std::function<std::shared_ptr<TalentEvent>(Player& p, int ticks)>> talent_event_constructors;
	std::map<AttenuationTag, Attenuation> attenuations;

	void init();
	void BuildStats();
	void BuildTalentConstructors();
	void BuildStaticFeatures();
};