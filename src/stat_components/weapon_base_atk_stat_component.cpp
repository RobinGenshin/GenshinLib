#include "weapon_base_atk_stat_component.h"

WeaponBaseAtkStatComponent::WeaponBaseAtkStatComponent(int* lvl, int* rarity, std::string* wclass) : StatComponent(), weapon_level(lvl), weapon_rarity(rarity), weapon_class(wclass) {};
float WeaponBaseAtkStatComponent::get_value() {
	//std::cout << "Calculating scalabale stat component\n";
	if (levelChanged) {
		_value = growthCalc() + ascensionCalc();
		levelChanged = false;
	};
	return _value;
};

float WeaponBaseAtkStatComponent::growthCalc() {
	if (*weapon_class == "41") return ((-0.0000440854f * *weapon_level * *weapon_level) + (0.0741905f * *weapon_level) + 0.943986f) * 41.07f;
	if (*weapon_class == "42") return ((0.000000034854f * *weapon_level * *weapon_level) + (0.0825656f * *weapon_level) + 0.917492f) * 42.40f;
	if (*weapon_class == "44") return ((0.0000413707f * *weapon_level * *weapon_level) + (0.0904399f * *weapon_level) + 0.892447f) * 43.73f;
	if (*weapon_class == "45") return ((0.0000803392f * *weapon_level * *weapon_level) + (0.0978381f * *weapon_level) + 0.869066f) * 45.07f;
	if (*weapon_class == "44b") return ((0.0000247343f * *weapon_level * *weapon_level) + (0.0761433f * *weapon_level) + 0.944037f) * 44.34f;
	if (*weapon_class == "46") return ((0.0000711123f * *weapon_level * *weapon_level) + (0.0853616f * *weapon_level) + 0.91452f) * 45.94f;
	if (*weapon_class == "48") return ((0.000114414f * *weapon_level * *weapon_level) + (0.093953f * *weapon_level) + 0.887141f) * 47.54f;
	if (*weapon_class == "49") return ((0.000154958f * *weapon_level * *weapon_level) + (0.101979f * *weapon_level) + 0.861598f) * 49.13f;
	else throw std::runtime_error("Incorrect base stat assignment" + *weapon_class);
};
float WeaponBaseAtkStatComponent::ascensionCalc() {
	if (*weapon_rarity == 5) {
		if (*weapon_level > 80) return 186.7f;
		else if (*weapon_level > 70) return 155.6f;
		else if (*weapon_level > 60) return 124.5f;
		else if (*weapon_level > 50) return 93.4f;
		else if (*weapon_level > 40) return 62.2f;
		else if (*weapon_level > 20) return 31.1f;
		else return 0;
	}

	if (*weapon_rarity == 4) {
		if (*weapon_level > 80) return 155.6f;
		else if (*weapon_level > 70) return 129.7f;
		else if (*weapon_level > 60) return 103.7f;
		else if (*weapon_level > 50) return 77.8f;
		else if (*weapon_level > 40) return 51.9f;
		else if (*weapon_level > 20) return 25.9f;
		else return 0;
	}
	else throw std::runtime_error("Incorrect weapon rarity assignment\n");
}
