#include "calc.h"

#include <zephyr/kernel.h>
int sum(int a, int b, int *result)
{
	if (result == NULL) {
		return -EINVAL;
	}

	*result = a + b;

	return 0;
}

int div(int a, int b, int *result)
{
	if (result == NULL) {
		return -EINVAL;
	}

	if (b == 0) {
		return -EFAULT;
	}

	if (a >= 1024) {
		return -ENODATA;
	}

	*result = a / b;

	return 0;
}

int calc(char op, int a, int b, int *result)
{
	if (result == NULL) {
		return -EINVAL;
	}

	switch (op) {
	case '+':
		return sum(a, b, result);
	case '/':
		return div(a, b, result);
	default:
		return -EFAULT;
	}
}
