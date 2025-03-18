#include "calc.h"
#include <zephyr/kernel.h>

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
