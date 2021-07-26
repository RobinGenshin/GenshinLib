#pragma once
#include "abstract_event.h"
#include "transformative_reaction.h"

class TransformativeReactionEvent : public AbstractEvent {
public:
	TransformativeReaction transformative_reaction;

	TransformativeReactionEvent(Player& p, TransformativeReaction t_r);

	virtual float get_event_time() override;
	virtual std::vector<std::string> get_triggers() override;

	virtual void ProcessEvent(Sim& sim) override;
};