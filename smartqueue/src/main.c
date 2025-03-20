#include "button.h"
#include "calc.h"
#include "led.h"
#include <zephyr/kernel.h>

void change_led_config(const struct zbus_channel *chan)
{
	struct button_evt *evt = (struct button_evt *)zbus_chan_const_msg(chan);

	struct led_config led_cfg;
	zbus_chan_read(&chan_led_config, &led_cfg, K_NO_WAIT);

	led_cfg.flashing = evt->on;
	zbus_chan_pub(&chan_led_config, &led_cfg, K_NO_WAIT);
}

ZBUS_LISTENER_DEFINE(lis_button_evt_connect_led_config, change_led_config);

ZBUS_CHAN_ADD_OBS(chan_button_evt, lis_button_evt_connect_led_config, 3);

int main(int argc, char *argv[])
{

	int ret = 0, err;

	if (ret) {
		printk("Could no init button!\n");
	}

	err = calc('+', 10, 20, &ret);
	if (err) {
		printk("Operation not permited\n");
	}

	printk("Sum(10,20)=%d\n", ret);

	return 0;
}
