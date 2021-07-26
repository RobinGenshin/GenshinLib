#include "team.h"

Team::Team() : players() {
	std::cout << "IN TEAM CONSTRUCTOR " << &*this << std::endl;
	players.emplace_back(std::make_unique<Player>(*this));
	players.emplace_back(std::make_unique<Player>(*this));
	players.emplace_back(std::make_unique<Player>(*this));
	players.emplace_back(std::make_unique<Player>(*this));
};

void Team::EquipComponentToPlayer(int index, Player::ComponentsInd compType, std::string compName) {
	Player& p = *players.at(index).get();
	if (p.get_component(compType) != nullptr) UnequipComponentFromPlayer(index, compType);
	p.EquipComponent(compType, compName);
};

void Team::UnequipComponentFromPlayer(int index, Player::ComponentsInd compType) {
	players.at(index).get()->UnequipComponent(compType);
};