#include <stdint.h>
#include <zephyr/kernel.h>

// ponteiros
// estruturas
// union?
// array
struct time { // bitfield
	uint64_t seconds: 6;
	uint64_t minutes: 6;
	uint64_t hours: 5;
	uint64_t days: 9;
	uint64_t years: 37;
	uint64_t daylightsavings: 1;
};

struct acc {
	int32_t x;
	int16_t y;
	uint8_t z;
	union {
		uint64_t n;
		struct time time;
		uint8_t bytes[8];
	} timestamp;
};

static bool acc_is_valid(const struct acc *acc)
{
	return acc->x > 0;
}

static void acc_print(const struct acc *acc)
{
	printk("Acc timestamp: %02u:%02u:%2u\n", acc->timestamp.time.hours,
	       acc->timestamp.time.minutes, acc->timestamp.time.seconds);
}

int main(int argc, char *argv[])
{
	struct acc a = {
		.x = 1,
		.y = 10,
		.z = 100,
		.timestamp.time.hours = 1,
		.timestamp.time.minutes = 2,
		.timestamp.time.seconds = 30,
	};
	printk("Is valid: %s\nSizeof acc %d\n", acc_is_valid(&a) ? "true" : "false",
	       sizeof(struct acc));
	acc_print(&a);

	return 0;
}
