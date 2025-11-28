#ifndef Button_h
#define Button_h

#include <inttypes.h>

class Button
{
	public:
		enum TriggerMode
		{
			B2_LOW,
			B2_HIGH,
			B2_RISING,
			B2_FALLING,
			B2_CHANGE
		};
		Button();
		Button(TriggerMode _triggerMode, void (*_trigger)());
		Button(TriggerMode _triggerMode, void (*_trigger)(), void (*_triggerLong)(), bool _blockLongEnable);
		Button(uint8_t _pin, uint8_t _mode, TriggerMode _triggerMode, void (*_trigger)());
		Button(uint8_t _pin, uint8_t _mode, TriggerMode _triggerMode, void (*_trigger)(), void (*_triggerLong)(), bool _blockLongEnable);
		void setDebounce(long _debounce);
		void setLongTime(long _interval);
		void update();
		void update(bool _input);
		
	private:
		uint8_t pin;
		uint8_t mode;
		TriggerMode triggerMode;
		void (*trigger)();
		void (*triggerLong)();

		bool blockLongEnable = true;
		bool firstTriggered = false;
		bool longPulse = false;
		long debounce = 50;
		long interval = 1000;

		bool block = false;
		bool prevPressed = false;
		unsigned long pressedTime = 0;
		bool lastState;

};

#endif
