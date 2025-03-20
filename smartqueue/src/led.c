#include "led.h"

#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

ZBUS_CHAN_DEFINE(chan_led_confg, struct led_config, NULL, NULL, ZBUS_OBSERVERS_EMPTY,
		 ZBUS_MSG_INIT(.flashing = true, .sleep_time_ms = 1000));

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

static struct {
	bool flashing;
	int32_t sleep_time_ms;
} self = {.flashing = true, .sleep_time_ms = SLEEP_TIME_MS};
//
// int led_get_flashing(bool *is_flashing)
// {
// 	int err = k_sem_take(&self.sem, K_NO_WAIT);
// 	if (err) {
// 		return err;
// 	}
//
// 	*is_flashing = self.flashing;
// 	k_sem_give(&self.sem);
//
// 	return 0;
// }
//
// int led_set_flashing(bool is_flashing)
// {
// 	int err = k_sem_take(&self.sem, K_NO_WAIT);
// 	if (err) {
// 		return err;
// 	}
//
// 	self.flashing = is_flashing;
// 	k_sem_give(&self.sem);
//
// 	return 0;
// }
//
static int thread(void *ptr1, void *ptr2, void *ptr3)
{
	ARG_UNUSED(ptr1);
	ARG_UNUSED(ptr2);
	ARG_UNUSED(ptr3);

	int ret;
	bool led_state = true;

	if (!gpio_is_ready_dt(&led)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	// k_sem_init(&self.sem, 0, 1);

	int err;
	struct led_config cfg;

	while (1) {
		zbus_chan_read(&chan_led_confg, &cfg, K_FOREVER);

		if (cfg.flashing) {
			ret = gpio_pin_toggle_dt(&led);
			if (ret < 0) {
				return 0;
			}
			printf("LED state: %s\n", led_state ? "ON" : "OFF");

		} else {
			gpio_pin_set_dt(&led, 0);
		}
		led_state = !led_state;

		k_msleep(cfg.sleep_time_ms);
	}
	return 0;
}

K_THREAD_DEFINE(led_thread_id, 1024, thread, NULL, NULL, NULL, 3, 0, 0);
