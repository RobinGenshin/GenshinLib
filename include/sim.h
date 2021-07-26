#pragma once
#include <vector>
#include <memory>
#include "team.h"
#include "combo_list.h"
#include "enemy.h"

class AbstractEvent;

class Sim {
public:
	Sim(Team* t, Enemy* e);

	std::vector<std::unique_ptr<Player>>& players;
	std::vector<std::shared_ptr<AbstractEvent>> events;
	std::vector<std::string> rotation = {};

	Enemy* enemy;

	int talent_count = 0;

	float current_time = 0;
	float run_time = 30;
	float turnEndTime();
	float damage = 0;

	std::shared_ptr<TalentEvent> current_talent = nullptr;
	std::shared_ptr<TalentEvent> last_talent = nullptr;
	std::shared_ptr<Combo> current_combo = nullptr;
	std::map<std::string, std::shared_ptr<TalentEvent>> talent_options = {};
	std::map<std::string, std::shared_ptr<Combo>> combo_options = {};
	Player* current_player = nullptr;
	Player* last_player = nullptr;

	bool stamina_toggle = true;
	float stamina = 250;

	void ResetTeam();
	void TurnOnSim();
	void NewTurn();
	void UpdateTalentList();
	void PickTalent();
	void PassTime(float dt);
	float PickAnimationCancel();
	void ProcessChainedEvents();
	void CheckTimeBeforeUse();
	void CheckFeatures(AbstractEvent& event, std::string timing);
	void AddEvent(std::shared_ptr<AbstractEvent> event);
	void UseTalent();
	std::shared_ptr<AbstractEvent>* CalculateNextEvent();
	void ProcessEvent(AbstractEvent* event);
	void ProcessEvents();
	void SkipToEndOfTurn();
};
