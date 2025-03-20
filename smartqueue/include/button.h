#include <zephyr/kernel.h>
#include <zephyr/zbus/zbus.h>

struct button_evt {
	bool on;
};

ZBUS_CHAN_DECLARE(chan_button_evt);
