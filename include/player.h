#pragma once
#include "character_dict.h"
#include "weapon.h"
#include "artifact.h"
#include "static_feature.h"
#include "dynamic_feature.h"

class Team;
class Sim;

class Player {
public:

	enum class ComponentsInd {
		CHARACTER,
		WEAPON,
		ARTIFACT,
	};

	enum class ArtifactPiece {
		FLOWER,
		PLUME,
		SANDS,
		GOBLET,
		CIRCLET
	};

	bool operator==(Player& other) {
		if (this == &other) return true;
		else return false;
	}

	Player() = delete;
	Player(Team& _team);

	Team& team;
	Sim* sim;

	std::shared_ptr<GCharacter> character = nullptr;
	std::shared_ptr<GWeapon> weapon = nullptr;
	std::shared_ptr<Artifact> artifact = nullptr;


	std::vector<Component*> get_components();
	Component* get_component(ComponentsInd compType);

	std::map<Stat, std::shared_ptr<ArtifactSubstatComponent>> substats;

	void set_substat_amount(Stat stat, int a);
	void set_mainstat(ArtifactPiece piece, Stat stat);

	virtual float get_stat(Stat statName);
	virtual std::map<std::string, DynamicFeature*> get_dynamic_features();
	void EquipComponent(ComponentsInd compType, std::string compName);
	void UnequipComponent(ComponentsInd compType);

	int normal_level = 10;
	int get_normal_level();
	int skill_level = 10;
	int get_skill_level();
	int burst_level = 10;
	int get_burst_level();
	int character_level = 90;
	int weapon_level = 90;
	int constellation = 6;
	int refinement = 5;
	Stat flowerMain = Stat::NONE;
	Stat plumeMain = Stat::NONE;
	Stat sandsMain = Stat::NONE;
	Stat gobletMain = Stat::NONE;
	Stat circletMain = Stat::NONE;
	float energy;
	float skill_cd;
	float burst_cd;
	int current_skill_charges;
	int maximum_skill_charges;

	bool isShielded;

	bool CheckTalentAvailable(Talent talentName, float stamina);

	std::shared_ptr<TalentEvent> CreateTalentEvent(Talent talentName, int ticks = -1);


	void Reset();

private:

	float CalculateComponentStatValue(Stat stat);
};
