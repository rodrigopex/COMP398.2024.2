#include <stdint.h>
#include <zephyr/kernel.h>

#include "greetings.h"

// ponteiros
// estruturas
// union?
// array

enum direction {
	DIRECTION_INPUT,
	DIRECTION_OUTPUT,
	DIRECTION_COUNT,
};

struct packet_header {
	uint8_t length: 3;
	uint8_t direction: 1;
	uint8_t crc: 4;
};

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

size_t sizeof_pointer(const char *data)
{
	return sizeof(data);
}

size_t sizeof_array(const char data[])
{
	return sizeof(data);
}

int main(int argc, char *argv[])
{
	struct packet_header pkt = {.length = 32, .direction = DIRECTION_OUTPUT, .crc = 0xFB};

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

#if defined(CONFIG_GREETINGS)
	print_upper("^hello world!$ -> pb");
#endif

	return 0;
}
