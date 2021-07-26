#pragma once
#include "component.h"
#include <string>
#include <iostream>
#include <map>
#include "element.h"

class Enemy;

class Monster {
public:
	Enemy* enemy;

	Monster();
	Monster(const Monster& toCopy);
	Monster(Enemy* enemy, const Monster& toCopy);
	~Monster() {};

	std::string monster_name;
	std::map<Element, float> res_dict = {};

	bool levelChanged = true;
};

