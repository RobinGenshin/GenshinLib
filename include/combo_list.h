#pragma once
#include <vector>
#include <string>
#include <map>
#include "player.h"

class ComboList {
public:
	ComboList() = delete;
	static std::vector< std::vector<std::pair<Talent, int> >> create(Player& player);
};


class Combo {
public:
	Combo(Player& p, std::vector<std::pair<Talent, int>> combo);

	std::string name;
	std::vector<std::pair<Talent, std::shared_ptr<TalentEvent>>> talents;
	int index = 0;
};
