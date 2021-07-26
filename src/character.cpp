#include "character.h"
#include "player.h"
#include "normal_talent_event.h"
#include "charged_talent_event.h"
#include "skill_talent_event.h"
#include "burst_talent_event.h"


GCharacter::GCharacter() : Component(), character_name(), character_element(), ascension_stat(), region(),
	weapon_type(), character_rarity(), character_level(nullptr), character_stat_growths(), talent_data() {};

GCharacter::GCharacter(const GCharacter& toCopy) : Component(toCopy.player), character_name(toCopy.character_name), character_element(toCopy.character_element), ascension_stat(toCopy.ascension_stat), region(toCopy.region),
	weapon_type(toCopy.weapon_type), character_rarity(toCopy.character_rarity), character_level(toCopy.character_level), character_stat_growths(toCopy.character_stat_growths), talent_data(toCopy.talent_data) {
};

GCharacter::GCharacter(Player* _player, const GCharacter& toCopy) : Component(_player), character_name(toCopy.character_name), character_element(toCopy.character_element), ascension_stat(toCopy.ascension_stat), region(toCopy.region),
weapon_type(toCopy.weapon_type), character_rarity(toCopy.character_rarity), character_level(&_player->character_level), character_stat_growths(toCopy.character_stat_growths), talent_data(toCopy.talent_data) {
	BuildStats();
	BuildTalentConstructors();
	//std::cout << "TALENTS SIZE IS: asdas\n";
};

void GCharacter::init() {
	BuildStats();
	BuildTalentConstructors();
	BuildStaticFeatures();
}

void GCharacter::BuildStats() {
	stats.emplace_back(std::make_pair(Stat::BASE_ATK, std::make_unique<PlayerBaseStatComponent>(Stat::BASE_ATK, character_level, &character_rarity, &character_stat_growths)));
	stats.emplace_back(std::make_pair(Stat::BASE_DEF, std::make_unique<PlayerBaseStatComponent>(Stat::BASE_DEF, character_level, &character_rarity, &character_stat_growths)));
	stats.emplace_back(std::make_pair(Stat::BASE_HP, std::make_unique<PlayerBaseStatComponent>(Stat::BASE_HP, character_level, &character_rarity, &character_stat_growths)));
	stats.emplace_back(std::make_pair(ascension_stat, std::make_unique<AscensionStatComponent>(&ascension_stat, character_level, &character_rarity)));
};

void GCharacter::BuildTalentConstructors() {
	talent_event_constructors.emplace(Talent::NORMAL, [](Player& p, int ticks = -1) {
		if (ticks == -1) return std::make_shared<NormalTalentEvent>(p);
		else return std::make_shared<NormalTalentEvent>(p, ticks);
		});
	talent_event_constructors.emplace(Talent::CHARGED, [](Player& p, int ticks = -1) {
		if (ticks == -1) return std::make_shared<ChargedTalentEvent>(p);
		return std::make_shared<ChargedTalentEvent>(p, ticks);
		});
	talent_event_constructors.emplace(Talent::SKILL, [](Player& p, int ticks = -1) {
		return std::make_shared<SkillTalentEvent>(p);
		});
	talent_event_constructors.emplace(Talent::BURST, [](Player& p, int ticks = -1) {
		return std::make_shared<BurstTalentEvent>(p);
		});
};

void GCharacter::BuildStaticFeatures() {
	for (auto& i : Data::Get().get_feature_dict()) {
		if (i.second.character == character_name) {
			features.emplace(i.first, std::make_unique<StaticFeature<>>(*this, i.second));
		}
	};
};

TalentData& GCharacter::get_talent_data(Talent talentName) {
	return *talent_data.at(talentName).get();
}