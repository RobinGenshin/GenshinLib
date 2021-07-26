#include "gauge_vector.h"
#include "transformative_reaction.h"
#include "element.h"
#include "sim.h"
#include "damage_event.h"
#include "transformative_reaction_event.h"
#include "frozen_gauge.h"
#include "elemental_gauges.h"

std::pair<float, TransformativeReaction> ReactionMap(Element e1, Element e2) {
	switch (e2)
	{
	case Element::ELECTRO:
		switch (e1)
		{
		case Element::PYRO:
			return std::make_pair(1.0f, TransformativeReaction::OVERLOAD);
		case Element::CRYO:
			return std::make_pair(1.0f, TransformativeReaction::SUPERCONDUCT);
		}
		break;
	case Element::PYRO:
		switch (e1) 
		{
		case Element::ELECTRO:
			return std::make_pair(1.0f, TransformativeReaction::OVERLOAD);
		case Element::CRYO:
			return std::make_pair(1.0f, TransformativeReaction::SUPERCONDUCT);
		}
		break;
	case Element::ANEMO:
		switch (e1)
		{
		case Element::ELECTRO:
			return std::make_pair(0.5f, TransformativeReaction::SWIRL_ELECTRO);
		case Element::PYRO:
			return std::make_pair(0.5f, TransformativeReaction::SWIRL_PYRO);
		case Element::CRYO:
			return std::make_pair(0.5f, TransformativeReaction::SWIRL_CRYO);
		case Element::FROZEN:
			return std::make_pair(0.5f, TransformativeReaction::SWIRL_CRYO);
		case Element::HYDRO:
			return std::make_pair(0.5f, TransformativeReaction::SWIRL_HYDRO);
		}
		break;
	case Element::CRYO:
		switch (e1)
		{
		case Element::ELECTRO:
			return std::make_pair(1.0f, TransformativeReaction::SUPERCONDUCT);
		}
		break;
	case Element::GEO:
		switch (e1)
		{
		case Element::ELECTRO:
			return std::make_pair(0.5f, TransformativeReaction::CRYSTALLISE_ELECTRO);
		case Element::PYRO:
			return std::make_pair(0.5f, TransformativeReaction::CRYSTALLISE_PYRO);
		case Element::CRYO:
			return std::make_pair(0.5f, TransformativeReaction::CRYSTALLISE_CRYO);
		case Element::FROZEN:
			return std::make_pair(0.5f, TransformativeReaction::CRYSTALLISE_CRYO);
		case Element::HYDRO:
			return std::make_pair(0.5f, TransformativeReaction::CRYSTALLISE_HYDRO);
		}
		break;
	case Element::PHYSICAL:
		switch (e1)
		{
		case Element::FROZEN:
			return std::make_pair(8.0f, TransformativeReaction::SHATTERED);
		}
		break;
	default:
		break;
	}
};

void ElementalGaugesVector::ApplyElement(Sim& sim, DamageEvent& event, bool aura) {
	Element& element = event.data.element;
	int& units = event.data.units;
	float init_u = float(units);

	auto continue_reaction = [&init_u](ElementalGauge& u) {
		return ((u.get_gauge() == float(0)) && (init_u > float(0)));
	};

	auto react = [&init_u, &units, &sim, &event](ElementalGauge& e_g, Element e2) {
		std::pair<float, TransformativeReaction> pair = ReactionMap(e_g.element, e2);
		init_u = std::max(float(0), init_u - e_g.get_gauge());
		e_g.set_gauge(std::max(float(0), e_g.get_gauge() - units * pair.first));
		sim.AddEvent(std::make_shared<TransformativeReactionEvent>(event.get_player(), pair.second));
	};

	switch (element)
	{

	case Element::ANEMO:
	{
		std::map<float, ElementalGauge&> dict = {};

		auto swirl = [&sim, &event, &aura, &units, &element, &init_u, react, &dict](ElementalGauge& e_g) {
			float gauge_reduced = std::min(0.5f * units, e_g.get_gauge());
			float gauge_gained = (gauge_reduced - 0.04f) * 1.25f + 1;

			react(e_g, element);
			dict.emplace(gauge_gained, e_g);
		};

		if ((gauges.find(Element::FROZEN) != gauges.end()) && (gauges.find(Element::HYDRO) != gauges.end())) {
			swirl(*gauges.at(Element::HYDRO).get());
			if (!continue_reaction(*gauges.at(Element::HYDRO).get())) goto break_out;
			else swirl(*gauges.at(Element::FROZEN).get());
			goto break_out;
		};

		for (auto& i : gauges) {
			swirl(*i.second.get());
			if (!continue_reaction(*i.second.get())) goto break_out;
		};

		break_out:

		for (auto& i : dict) {
			i.second.AddToGauge(i.first);
		};

		break;
	}

	case Element::CRYO:
	{
		if (gauges.size() == 0 || (gauges.size() == 1 && (gauges.find(Element::FROZEN) != gauges.end())))
			gauges.emplace(std::make_pair(Element::CRYO, std::make_shared<ElementalGauge>(element, units, aura)));

		else for (auto& i : gauges) {
			if (init_u == float(0)) break;
			switch (i.first) {
			case Element::ELECTRO:
				react(*i.second.get(), element);
				break;
			case Element::PYRO:
				react(*i.second.get(), element);
				break;
			case Element::HYDRO:
				if (gauges.find(Element::FROZEN) != gauges.end()) gauges.at(Element::FROZEN).get()->AddToGauge(std::min(i.second.get()->get_gauge(), init_u));
				else gauges.emplace(Element::FROZEN, std::make_shared<FrozenGauge>(std::min(i.second.get()->get_gauge(), init_u)));
				i.second.get()->set_gauge(0);
				break;
			case Element::CRYO:
				i.second.get()->AddToGauge(float(units));
				break;
			};
			if (!continue_reaction(*i.second.get())) goto end;
		};
		break;
	}

	case Element::ELECTRO:
	{
		if (gauges.size() == 0 || (gauges.size() == 1 && (gauges.find(Element::HYDRO) != gauges.end())))
			gauges.emplace(Element::ELECTRO, std::make_shared<ElementalGauge>(element, units, aura));

		else for (auto& i : gauges) {
			if (init_u == float(0)) break;
			switch (i.first) {
			case Element::ELECTRO:
				i.second.get()->AddToGauge(float(units));
				break;
			case Element::PYRO:
				react(*i.second.get(), element);
				break;
			case Element::CRYO:
				react(*i.second.get(), element);
				break;
			case Element::FROZEN:
				react(*i.second.get(), element);
				break;
			};
			if (!continue_reaction(*i.second.get())) goto end;
		};
		break;
	}
	case Element::GEO:
	{
		if (gauges.size() > 0) {
			for (auto& i : gauges) {
				react(*i.second.get(), element);
				goto end;
			};
		};
		break;
	}
	case Element::HYDRO:
	{
		if (gauges.size() == 0 || (gauges.size() == 1 && ((gauges.find(Element::FROZEN) != gauges.end()) || (gauges.find(Element::ELECTRO) != gauges.end()))))
			gauges.emplace(Element::HYDRO, std::make_shared<ElementalGauge>(element, units, aura));

		else for (auto& i : gauges) {
			if (init_u == float(0)) break;
			switch (i.first) {

			case Element::PYRO:
				react(*i.second.get(), element);
				break;

			case Element::CRYO:
				if (gauges.find(Element::FROZEN) != gauges.end()) gauges.at(Element::FROZEN).get()->AddToGauge(std::min(i.second.get()->get_gauge(), init_u));
				else gauges.emplace(Element::FROZEN, std::make_shared<FrozenGauge>(std::min<float>(i.second.get()->get_gauge(), init_u)));
				i.second.get()->set_gauge(0);
				break;

			case Element::HYDRO:
				i.second.get()->AddToGauge(float(units));
				break;
			};
			if (!continue_reaction(*i.second.get())) goto end;
		};
		break;
	}

	case Element::PYRO:
	{
		if (gauges.size() == 0) gauges.emplace(Element::PYRO, std::make_shared<ElementalGauge>(element, units, aura));
		else for (auto& i : gauges) {
			if (init_u == float(0)) break;
			switch (i.first) {

			case Element::ELECTRO:
				react(*i.second.get(), element);
				break;

			case Element::PYRO:
				i.second.get()->AddToGauge(float(units));
				break;

			case Element::CRYO:
				i.second.get()->SubtractFromGauge(2.0f * units);
				break;

			case Element::FROZEN:
				i.second.get()->SubtractFromGauge(2.0f * units);
				break;

			case Element::HYDRO:
				i.second.get()->SubtractFromGauge(0.5f * units);
				break;

			};
			if (!continue_reaction(*i.second.get())) goto end;
		};
		break;
	};

	case Element::PHYSICAL:
	{
		for (auto& i : gauges) {
			switch (i.first) {
			case Element::FROZEN:
				react(*i.second.get(), element);
				goto end;
			};
		};
		break;
	};
	};
end:
	;
};

void ElementalGaugesVector::Update() {
	for (auto it = gauges.begin(), ite = gauges.end(); it != ite;)
	{
		if (it->second.get()->time_remaining <= float(0))
			it = gauges.erase(it);
		else
			++it;
	}
};