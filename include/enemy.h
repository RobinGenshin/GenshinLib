#pragma once
#include <iostream>
#include "monster.h"
#include <memory>
#include "gauge_vector.h"

class Enemy {
public:

	bool operator==(Enemy& other) {
		if (this == &other) return true;
		else return false;
	}

	Enemy();
	std::unique_ptr<Monster> monster;

	ElementalGaugesVector gauges;

	virtual void EquipMonster(std::string);
	virtual void UnequipMonster();

	bool is_shocked = false;

	float get_RES_multi(Element element);
	float get_DEF();
};