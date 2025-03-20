/**
 * @file
 * @brief Led API
 */

#include <zephyr/kernel.h>
#include <zephyr/zbus/zbus.h>

struct led_config {
	bool flashing;
	int32_t sleep_time_ms;
};

ZBUS_CHAN_DECLARE(chan_led_config);

// /**
//  * @brief Led flashing get function
//  *
//  * @param[out] bool true if is flashing and false otherwise.
//  * @return int 0 on success negative otherwise
//  */
// int led_get_flashing(bool *is_flashing);
//
// /**
//  * @brief Led flashing set function.
//  *
//  * @param should_flash bool indicates the desired state
//  * @retval 0 success
//  * @return int 0 on success negative otherwise
//  */
// int led_set_flashing(bool should_flash);
