#include "stat_component.h"


StatComponent::StatComponent() {};
StatComponent::~StatComponent() {};
StatComponent::StatComponent(float value) : _value(value) {};
float StatComponent::get_value() { return _value; };

