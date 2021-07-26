#include "enemy.h"
#include "monster.h"
#include "read_data.h"
#include "element.h"

Enemy::Enemy() : monster(nullptr) {}

void Enemy::EquipMonster(std::string compName) {
	if (monster != nullptr) UnequipMonster();
	monster = std::make_unique<Monster>(this, Data::Get().get_monster_dict().at(compName));
}

void Enemy::UnequipMonster() {
	monster = nullptr;
};

float Enemy::get_RES_multi(Element element) {
	//std::cout << monster.get()->res_dict.size();
	//std::cout << element << std::endl;
	return monster.get()->res_dict.at(element);
};

float Enemy::get_DEF() {
	return 0;
};