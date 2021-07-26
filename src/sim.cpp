#include "sim.h"
#include <random>
#include "enum_maps.h"
#include "elemental_gauges.h"

Sim::Sim(Team* t, Enemy* e) : players(t->players), enemy(e), events(), current_time(0) {
		t->players.erase(std::remove_if(t->players.begin(), t->players.end(),
			[](std::unique_ptr<Player>& v) {
				return (v.get()->character == nullptr);
			}), t->players.end());
	};

float Sim::turnEndTime() {
	float t = current_talent.get()->get_initial_time() + current_talent.get()->get_use_time();
	if (t < current_time) throw std::runtime_error("Error: turnEndTime() < current_time?\n");
	return t;
}

void Sim::ResetTeam() {
	for (auto& i : players) i.get()->Reset();
};

void Sim::TurnOnSim() {
	std::cout << "Resetting team of size: " << players.size() << std::endl;
	ResetTeam();
	std::cout << "Reset team.\n";
	while (run_time > current_time) {
		NewTurn();
		UpdateTalentList();
		PickTalent();
		CheckTimeBeforeUse();
		UseTalent();
		ProcessEvents();
		SkipToEndOfTurn();
	};

	std::cout << "ENDING SIM; RUN TIME = " << run_time << ", CURRENT_TIME = " << current_time << std::endl;
};

void Sim::NewTurn() {
	talent_count++;
	if (talent_count > 1) {
		last_player = current_player;
		last_talent = current_talent;
	};

	//for (auto& i : players) {
	//	for (auto& j : i.get()->get_dynamic_features()) {
	//		std::cout << j.second->get()->enabled() << ", ";
	//	};
	//};
};

void Sim::UpdateTalentList() {
	//std::cout << "Updating action list\n";
	std::vector<Talent> abilties = { Talent::SKILL, Talent::BURST };
	for (auto& i : players) {
		for (auto j : abilties) {
			if (i.get()->CheckTalentAvailable(j, stamina)) {
				std::shared_ptr<TalentEvent> t = i.get()->CreateTalentEvent(j);
				t.get()->name = i.get()->character.get()->character_name + " " + EnumMap::get_string_talent(t.get()->data.talent_type);
				talent_options.emplace(t.get()->name, move(t));
				//std::cout << "Added 1 option\n";
			};
			std::vector<std::vector<std::pair<Talent, int>>> combolist = ComboList::create(*i);
			for (auto& j : combolist) {
				std::shared_ptr<Combo> combo = std::make_unique<Combo>(*i, j);
				if (i.get()->CheckTalentAvailable(combo.get()->talents.begin()->first, stamina)) combo_options.emplace(combo.get()->name, move(combo));
			};
		};
	};
	//std::cout << "Updated action list\n";
}

void Sim::PickTalent() {
	if (current_combo != nullptr) {
		int len = std::distance(current_combo.get()->talents.begin(), current_combo.get()->talents.end());
		int ind = ++current_combo.get()->index;
		if (ind < len) {
			current_talent = current_combo.get()->talents.at(ind).second;
			return;
		}
		else current_combo = nullptr;
	};

	//for (auto& i : talent_options) std::cout << i.first << std::endl;
	//for (auto& i : combo_options) std::cout << i.first << std::endl;

	//std::cout << "Please pick an action..\n";

	std::string act;
	bool picked = false;
	//while (!picked) {
	//	std::getline(std::cin, act);
	//	if (talent_options.count(act) > 0) {
	//		current_player = &talent_options.at(act).get()->player;
	//		current_talent = move(talent_options.at(act));
	//		rotation.push_back(act);
	//		picked = true;
	//	}
	//	else if (combo_options.count(act) > 0) {
	//		current_player = &combo_options.at(act).get()->talents[0].second.get()->player;
	//		current_combo = move(combo_options.at(act));
	//		current_talent = current_combo.get()->talents[0].second;
	//		std::cout << "Current action is: " << current_talent.get()->name << std::endl;
	//		rotation.push_back(act);
	//		picked = true;
	//	}
	//};

	while (!picked) {
		std::vector<std::string> options = {};
		for (auto& pair : talent_options) options.push_back(pair.first);
		for (auto& pair : combo_options) options.push_back(pair.first);
		std::vector<std::string> out;
		std::sample(options.begin(), options.end(), std::back_inserter(out), 1, std::mt19937{ std::random_device{}() });
		//std::cout << out.size();
		act = out.front();
		if (talent_options.count(act) > 0) {
			current_player = &talent_options.at(act).get()->get_player();
			current_talent = move(talent_options.at(act));
			rotation.push_back(act);
			picked = true;
		}
		else if (combo_options.count(act) > 0) {
			current_player = &combo_options.at(act).get()->talents[0].second.get()->get_player();
			current_combo = move(combo_options.at(act));
			current_talent = current_combo.get()->talents[0].second;
			//std::cout << "Current action is: " << current_talent.get()->name << std::endl;
			rotation.push_back(act);
			picked = true;
		}
	};

	talent_options = {}; combo_options = {};
};

void Sim::PassTime(float dt) {
	//std::cout << dt;
	if (dt < 0) throw std::runtime_error("Error: Invalid time.\n");
	//std::cout << "Passing " << dt << " seconds..\n";
	current_time += dt;
	for (auto& i : players) {
		for (auto& j : i.get()->get_dynamic_features()) {
			if (j.second->data.temporary && j.second->cd > 0) {
				j.second->cd = std::max(float(0), j.second->cd-dt);
			};
		};
		i.get()->skill_cd = std::max(float(0), i.get()->skill_cd - dt);
		i.get()->burst_cd = std::max(float(0), i.get()->burst_cd - dt);

		for (auto& j : i.get()->character.get()->attenuations) {
			j.second.timer = std::max(float(0), j.second.timer - dt);
		};
	};

	for (auto& i : enemy->gauges.get_gauges()) {
		i.second.get()->PassTime(dt);
	};
	enemy->gauges.Update();
};

float Sim::PickAnimationCancel() {
	//std::cout << "Current stamina is: " << stamina << std::endl;
	//std::cout << "Please pick an animation cancel from: { ";
	//std::vector<std::string> options = { "jump" };
	//if (stamina >= 20) options.emplace_back("dash");
	//for (auto& i : options) std::cout << i << " ";
	//std::cout << "}\n";
	std::string act;
	bool picked = false;
	//while (!picked) {
	//	std::getline(std::cin, act);
	//	if (count(options.begin(), options.end(), act) > 0) picked = true;
	//};
	//if (act == "dash") {
	//	PassTime(0.33f);
	//	return 0.33f;
	//}
	act = "jump";
	if (act == "jump") {
		PassTime(35 / 60);
		return (0.35f / 0.6f);
	};
};

void Sim::ProcessChainedEvents() {
	//std::cout << "Processing chained events..\n";
	TalentEvent& current = *current_talent.get();
	TalentEvent& last = *last_talent.get();
	TalentData& current_data = dynamic_cast<TalentData&>(current_talent.get()->data);
	TalentData& last_data = dynamic_cast<TalentData&>(last_talent.get()->data);
	Player& current_player = current.get_player();
	Player& last_player = last.get_player();

	//int pos;
	//if (last.data.talent_type != Talent::NORMAL) pos = 0;
	//else pos = last.ticks - 1;

	//std::cout << "Last pos is: " << pos << std::endl;

	if (!(current_player == last_player)) {
		PassTime(last.get_time_to_swap() - last.get_use_time());
	}
	else {
		current.CalculateChainTime(*this);
	};
};

void Sim::CheckTimeBeforeUse() {
	//std::cout << "Checking time before use\n";
	if (talent_count == 1) return;
	ProcessChainedEvents();
	//std::cout << "Checked time before use\n";
};

void Sim::CheckFeatures(AbstractEvent& event, std::string timing) {
	for (auto& i : players) {
		for (auto& j : i.get()->get_components()) {
			for (auto& k : j->features) {
				if (k.second.get()->isDynamic) dynamic_cast<DynamicFeature*>(k.second.get())->CheckEvent(*this, event, timing);
			};
		};
	};
};


void Sim::AddEvent(std::shared_ptr<AbstractEvent> event) {
	event.get()->InitialiseForSim(*this);
	events.emplace_back(std::move(event));
};

void Sim::UseTalent() {
	TalentEvent& t = *current_talent.get();
	CheckFeatures(t, "precast");
	AddEvent(current_talent);
	CheckFeatures(t, "postcast");
};

std::shared_ptr<AbstractEvent>* Sim::CalculateNextEvent() {
	std::vector<std::shared_ptr<AbstractEvent>>::iterator next = min_element(events.begin(), events.end(),
		[](std::shared_ptr<AbstractEvent>& a, std::shared_ptr<AbstractEvent>& b)->bool {
			return a.get()->get_event_time() < b.get()->get_event_time();
		}
	);
	if (next == events.end()) return nullptr;
	else if (next->get()->get_event_time() > turnEndTime()) return nullptr;
	else return &*next;
};

void Sim::ProcessEvent(AbstractEvent* event) {
	event->ProcessEvent(*this);
	event->PostProcessEvent(*this);
};

void Sim::ProcessEvents() {
	//std::cout << "Beginning queue\n";
	//std::cout << "Number of events: " << events.size() << std::endl;
	//std::cout << "Current time is: " << current_time << ", while turn ends at: " << turnEndTime();
	while (current_time < turnEndTime()) {
		//for (auto& i : events) std::cout << i.get()->get_event_time() << std::endl;
		std::shared_ptr<AbstractEvent>* next = CalculateNextEvent();
		//std::cout << "Got next event\n";
		if (next == nullptr) break;
		ProcessEvent(next->get());
		//std::cout << "Finished processing event\n";
	};
	//std::cout << "Finished queue\n";
};

void Sim::SkipToEndOfTurn() {
	float dt = turnEndTime() - current_time;
	PassTime(dt);
};
