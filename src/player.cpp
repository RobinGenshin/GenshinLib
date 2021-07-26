#include "player.h"
#include "team.h"
#include "weapon_dict.h"

Player::Player(Team& _team) : team(_team), substats({}), character_level(90), weapon_level(0), constellation(6), energy(0), skill_cd(0), burst_cd(0), current_skill_charges(0), maximum_skill_charges(0), _stats(), _checked() {
	std::vector<Stat> subs = { Stat::PCT_ATK, Stat::PCT_DEF, Stat::PCT_HP, Stat::ENERGY_RECHARGE, Stat::CRIT_RATE, Stat::CRIT_DMG, Stat::ELEMENTAL_MASTERY };
	for (auto& i : subs) substats.emplace(std::make_pair(i, std::make_shared<ArtifactSubstatComponent>(i)));
	artifact = std::make_unique<Artifact>(*this);
}

std::vector<Component*> Player::get_components() {
	std::vector<Component*> comps = {};
	if (character != nullptr) comps.emplace_back(character.get());
	if (weapon != nullptr) comps.emplace_back(weapon.get());
	if (artifact != nullptr) comps.emplace_back(artifact.get());
	return comps;
};

Component* Player::get_component(ComponentsInd compType) {
	if (compType == ComponentsInd::CHARACTER) return character.get();
	if (compType == ComponentsInd::WEAPON) return weapon.get();
	if (compType == ComponentsInd::ARTIFACT) return artifact.get();
	else throw std::runtime_error("Incorrect component string\n");
};

std::map<std::string, DynamicFeature*> Player::get_dynamic_features() {
	std::map<std::string, DynamicFeature*> vec = {};
	for (auto& i : get_components()) {
		for (auto& j : i->features) {
			if (j.second.get()->isDynamic) vec.emplace(j.first, dynamic_cast<DynamicFeature*>(j.second.get()));
		};
	}
	return vec;
};

void Player::set_substat_amount(Stat stat, int a) {
	substats.at(stat).get()->set_amount(a);
	ResetComponentChecks();
};

void Player::set_mainstat(ArtifactPiece piece, Stat stat) {
	if (piece == ArtifactPiece::FLOWER) flowerMain = stat;
	if (piece == ArtifactPiece::PLUME) plumeMain = stat;
	if (piece == ArtifactPiece::SANDS) sandsMain = stat;
	if (piece == ArtifactPiece::GOBLET) gobletMain = stat;
	if (piece == ArtifactPiece::CIRCLET) circletMain = stat;
	ResetComponentChecks();
};

float Player::get_stat(Stat statName) {

	float _value = 0;
	if (_checked.find(statName) == _checked.end() || !_checked.at(statName)) {
		_value += CalculateComponentStatValue(statName);
		if (substats.find(statName) != substats.end()) {
			_value += substats.at(statName).get()->get_value();
		};

		_stats[statName] = _value;
		_checked[statName] = true;
	}
	else _value += _stats[statName];

	for (auto& i : team.players) {
		for (auto& j : i.get()->get_components()) {
			for (auto& k : j->features) {
				if (!k.second.get()->isDynamic && !k.second.get()->hasStatModifier) {
					FeatureStatModifierContainer* container = dynamic_cast<FeatureStatModifierContainer*>(k.second.get());

					if ((i.get() == this || k.second.get()->data.share) &&
						((std::find(container->stats.begin(), container->stats.end(), statName) != container->stats.end()))) {
						_value += container->get_stat(statName);
					};
				}
			};
		};
	};

	return _value;
};

void Player::EquipComponent(ComponentsInd compType, std::string compName) {
	if (compType == ComponentsInd::CHARACTER) {
		std::cout << "Equipping component of type: character\n";
		CharacterDict& d = CharacterDict::Get();
		if (character != nullptr) throw std::runtime_error("Trying to equip character without unequipping\n");
		if (d.map.find(compName) != d.map.end()) {
			character = d.map.at(compName)(this);
		}
	};

	if (compType == ComponentsInd::WEAPON) {
		WeaponDict& d = WeaponDict::Get();
		if (weapon != nullptr) throw std::runtime_error("Trying to equip character without unequipping\n");
		if (d.map.find(compName) != d.map.end()) {
			weapon = d.map.at(compName)(this);
		}
		else throw std::runtime_error("");
	};
	ResetComponentChecks();
	std::cout << "Equipped component\n";
}
void Player::UnequipComponent(ComponentsInd compType) {
	if (compType == ComponentsInd::CHARACTER) character = nullptr;
	if (compType == ComponentsInd::WEAPON) weapon = nullptr;
	if (compType == ComponentsInd::ARTIFACT) artifact = nullptr;
	ResetComponentChecks();
};

bool Player::CheckTalentAvailable(Talent talentName, float stamina) {
	if (talentName == Talent::SKILL) {
		//std::cout << "SKILL CD IS: " << skill_cd << std::endl;
		if (skill_cd > 0) return false;
	};
	if (talentName == Talent::BURST) {
		//std::cout << "Burst CD IS: " << burst_cd << std::endl;
		if (burst_cd > 0 || energy < character.get()->talent_data.at(Talent::BURST)->energy_cost) return false;
	};
	return true;
}

std::shared_ptr<TalentEvent> Player::CreateTalentEvent(Talent talentName, int ticks) {
	TalentData& td = *character.get()->talent_data.at(talentName).get();
	return character.get()->talent_event_constructors.at(talentName)(*this, ticks);
};


void Player::Reset() {
	std::cout << "Resetting player..\n";
	skill_cd = 0, burst_cd = 0;
	maximum_skill_charges = 0, current_skill_charges = 0;
	energy = character.get()->talent_data.at(Talent::BURST).get()->energy_cost;
	std::cout << "Reset player..\n";
};

void Player::ResetComponentChecks() {
	for (auto& i : _checked) i.second = false;
};

float Player::CalculateComponentStatValue(Stat statName) {
	float finalValue = 0;
	for (auto& i : get_components()) {
		finalValue += i->get_stat(statName);
	};
	return finalValue;
};

int Player::get_normal_level() {
	return normal_level + get_stat(Stat::NORMAL_LEVEL);
};

int Player::get_skill_level() {
	return skill_level + get_stat(Stat::SKILL_LEVEL);
};

int Player::get_burst_level() {
	return burst_level + get_stat(Stat::BURST_LEVEL);
};