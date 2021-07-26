#include "artifact.h"
#include "player.h"

Artifact::Artifact(Player& p) : Component(), flowerMain(&p.flowerMain), plumeMain(&p.plumeMain), sandsMain(&p.sandsMain), gobletMain(&p.gobletMain), circletMain(&p.circletMain) {
};

float Artifact::get_stat(Stat statName) {
	float _value = 0;
	for (auto& i : main_stats) {
		if (statName == *i) _value += mainStatMap.at(statName);
	};
	return _value;
};