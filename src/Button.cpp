#include "Button.h"
#include <inttypes.h>
#include <Arduino.h>

Button::Button() {}

Button::Button(TriggerMode _triggerMode, void (*_trigger)()) {
	triggerMode = _triggerMode;
	trigger = _trigger;

	pressedTime = millis();
	lastState = false;
}

Button::Button(TriggerMode _triggerMode, void (*_trigger)(), void (*_triggerLong)(), bool _blockLongEnable) {
	triggerMode = _triggerMode;
	trigger = _trigger;
	triggerLong = _triggerLong;
	blockLongEnable = _blockLongEnable;
	longPulse = true;

	pressedTime = millis();
	lastState = false;
}

Button::Button(uint8_t _pin, uint8_t _mode, TriggerMode _triggerMode, void (*_trigger)()) {
	pin = _pin;
	mode = _mode;
	triggerMode = _triggerMode;
	trigger = _trigger;

	pinMode(pin, mode);

	pressedTime = millis();
	lastState = digitalRead(pin);
}

Button::Button(uint8_t _pin, uint8_t _mode, TriggerMode _triggerMode, void (*_trigger)(), void (*_triggerLong)(), bool _blockLongEnable) {
	pin = _pin;
	mode = _mode;
	triggerMode = _triggerMode;
	trigger = _trigger;
	triggerLong = _triggerLong;
	blockLongEnable = _blockLongEnable;
	longPulse = true;

	pinMode(pin, mode);

	pressedTime = millis();
	lastState = digitalRead(pin);
}

void Button::setDebounce(long _debounce) {
	debounce = _debounce;
}

void Button::setLongTime(long _interval) {
	interval = _interval;
}

void Button::update() {
	update(digitalRead(pin));
}

void Button::update(bool _input) {
	switch (triggerMode) {
		case TriggerMode::B2_LOW:
			if(!_input) trigger();
			break;
		case TriggerMode::B2_HIGH:
			if(_input) trigger();
			break;
		case TriggerMode::B2_RISING:
			if (longPulse) {
				if(_input) {
					prevPressed = true;
					if (millis() - pressedTime >= debounce && !firstTriggered && !blockLongEnable) {
						firstTriggered = true;
						trigger();
					}
					if (millis() - pressedTime >= interval && !(block && blockLongEnable)) {
						block = true;
						triggerLong();
					}
				} else {
					if (millis() - pressedTime >= debounce && !block && prevPressed && blockLongEnable) {
						block = true;
						trigger();
					}

					prevPressed = false;
					pressedTime = millis();
					block = false;
					firstTriggered = false;
				}
			} else {
				if(_input) {
					if (millis() - pressedTime >= debounce && !block) {
						block = true;
						trigger();
					}
				} else {
					pressedTime = millis();
					block = false;
				}
			}
			break;
		case TriggerMode::B2_FALLING:
			if (longPulse) {
				if(!_input) {
					prevPressed = true;
					if (millis() - pressedTime >= debounce && !firstTriggered && !blockLongEnable) {
						firstTriggered = true;
						trigger();
					}
					if (millis() - pressedTime >= interval && !(block && blockLongEnable)) {
						block = true;
						triggerLong();
					}
				} else {
					if (millis() - pressedTime >= debounce && !block && prevPressed && blockLongEnable) {
						block = true;
						trigger();
					}

					prevPressed = false;
					pressedTime = millis();
					block = false;
					firstTriggered = false;
				}
			} else {
				if(!_input) {
					if (millis() - pressedTime >= debounce && !block) {
						block = true;
						trigger();
					}
				} else {
					pressedTime = millis();
					block = false;
				}
			}
			break;
		case TriggerMode::B2_CHANGE:
			if(_input != lastState) {
				if (millis() - pressedTime >= debounce && !block) {
					block = true;
					trigger();
					lastState = _input;
				}
			} else {
				pressedTime = millis();
				block = false;
			}
			break;
	}
}
