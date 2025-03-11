#include "calc.h"
#include <zephyr/kernel.h>

int main(int argc, char *argv[])
{
	printk("Sum(10,20)=%d\n", sum(10, 20));
	return 0;
}
