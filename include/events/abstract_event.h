#pragma once
#include <memory>
#include <vector>
#include <string>
#include <iostream>

class Sim;
class Player;

class AbstractEvent {
public:
	bool operator==(AbstractEvent& other) {
		if (this == &other) return true;
		else return false;
	};

	AbstractEvent() = delete;
	AbstractEvent(Player& p);
	virtual ~AbstractEvent();

	float get_initial_time();
	void set_initial_time(float t);

	virtual float get_event_time() = 0;
	virtual std::vector<std::string> get_triggers() = 0;
	Player& get_player();

	virtual void InitialiseForSim(Sim& sim);
	virtual void ProcessEvent(Sim& sim);
	virtual void PostProcessEvent(Sim& sim);

protected:
	float _initial_time;
	Player& _player;
};