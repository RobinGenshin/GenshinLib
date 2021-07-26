#include "monster.h"
#include "read_data.h"
#include "enemy.h"
#include <string>
#include "stat_component.h"
#include "component.h"

using namespace std;

Monster::Monster() : enemy(nullptr), monster_name(), res_dict() {};

Monster::Monster(const Monster& toCopy) : enemy(toCopy.enemy), monster_name(toCopy.monster_name), res_dict(toCopy.res_dict) {};

Monster::Monster(Enemy* _enemy, const Monster& toCopy) : enemy(_enemy), monster_name(toCopy.monster_name), res_dict(toCopy.res_dict) {}