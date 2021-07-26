#pragma once
#include <vector>
#include <memory>
#include <string>
#include "player.h"

class Team
{
public:

	Team();
	std::vector<std::unique_ptr<Player>> players;
	void EquipComponentToPlayer(int index, Player::ComponentsInd compType, std::string compName);
	void UnequipComponentFromPlayer(int index, Player::ComponentsInd compType);
};