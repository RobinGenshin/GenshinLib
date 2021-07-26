#include "combo_list.h"

std::vector< std::vector<std::pair<Talent, int> >> ComboList::create(Player& player) {
	std::vector< std::vector<std::pair<Talent, int > > > combo_dict;

	auto& character = *player.character;

	int nt = character.talent_data.at(Talent::NORMAL).get()->ticks;

	std::vector<Talent> options = {};

	for (auto& i : character.talent_data) {
		if ((i.first != Talent::SKILL) && (i.first != Talent::BURST)) options.push_back(i.first);
	};

	// Normal Attacks
	for (int i = 0; i < nt; i++) {
		combo_dict.push_back({ {Talent::NORMAL, i + 1} });

		if (find(options.begin(), options.end(), Talent::PLUNGED) != options.end()) {
			combo_dict.push_back({ {Talent::NORMAL, i + 1}, {Talent::PLUNGED, 1} });
		};
	};

	// Charged Attacks
	if (character.talent_data.at(Talent::NORMAL).get()->time_to_attack.size() == 0) {
		combo_dict.push_back({ {Talent::CHARGED, 1} });
	}
	else {
		// N + C (+P) Combos
		for (int i = 0; i < nt - 1; i++) {
			combo_dict.push_back({ {Talent::NORMAL, (i + 1)}, {Talent::CHARGED,1} });

			if (find(options.begin(), options.end(), Talent::PLUNGED) != options.end()) {
				combo_dict.push_back({ {Talent::NORMAL, (i + 1)}, {Talent::CHARGED,1}, {Talent::PLUNGED, 1} });
			};
		};
	};

	// Plunge Spam
	if (find(options.begin(), options.end(), Talent::PLUNGED) != options.end()) {
		combo_dict.push_back({ {Talent::PLUNGED, 1} });
	};
	for (auto& i : combo_dict) {

	};

	return combo_dict;
};


Combo::Combo(Player& p, std::vector<std::pair<Talent, int>> combo) {
	for (auto& i : combo) {
		auto& character = *p.character;
		if (i.first == Talent::NORMAL) {
			talents.emplace_back(i.first, p.CreateTalentEvent(i.first, i.second));
		}
		else {
			talents.emplace_back(i.first, p.CreateTalentEvent(i.first));
		};
	};

	std::map<Talent, std::string> name_map = {
		{Talent::NORMAL, "N"},
		{Talent::CHARGED, "C"},
		{Talent::PLUNGED, "P"}
	};

	name = p.character->character_name + " ";
	for (auto& i : combo) {
		name.append(name_map.at(i.first));
		if (i.first == Talent::NORMAL) {
			name.append(std::to_string(i.second));
		};
	};
};
