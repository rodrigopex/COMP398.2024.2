#include <zephyr/kernel.h>

void print_upper(const char *str)
{
	for (const char *iter = str; *iter != '\0'; ++iter) {
		char cursor = *iter;
		char dec = 0;
		if ('a' <= cursor && cursor <= 'z') {
			dec = CONFIG_UPPER_TRANSFORM_VALUE;
		}

		if (IS_ENABLED(CONFIG_FILTER_P) && cursor == 'p') {
			dec = 0;
		}

		if (IS_ENABLED(CONFIG_FILTER_B) && cursor == 'b') {
			dec = 0;
		}

		printk("%c", cursor - dec);
	}
}
