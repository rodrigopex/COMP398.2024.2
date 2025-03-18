/*
 * Copyright (c) 2025 Rodrigo Peixoto <rodrigopex@gmail.com>
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/irq_offload.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/ztest.h>

#include "calc.h"

extern int div(int a, int b, int *result);
extern int sum(int a, int b, int *result);

#define EXEC_TEST_CALC(_op, _a, _b, _expected_err, _expected_ret)                                  \
	do {                                                                                       \
		int ret = 0, err;                                                                  \
		err = calc(_op, _a, _b, &ret);                                                     \
		zassert_equal(err, _expected_err);                                                 \
		zassert_equal(ret, _expected_ret);                                                 \
	} while (0)

ZTEST(basic, test_sum)
{
	/* Specification-based tests
	 * Partitions:
	 *  MIN
	 *  (N) negative
	 *  (Z) zero
	 *  (P) positive
	 *  MAX
	 */
	/* N + N */
	/* N + Z */
	/* N + P */
	/* Z + Z */
	/* Z + P */
	/* P + P */
	EXEC_TEST_CALC('+', -5, -5, 0, -10);
	EXEC_TEST_CALC('+', -5, 0, 0, -5);
	EXEC_TEST_CALC('+', -5, 5, 0, 0);
	EXEC_TEST_CALC('+', 0, 0, 0, 0);
	EXEC_TEST_CALC('+', 0, 5, 0, 5);
	EXEC_TEST_CALC('+', 5, 5, 0, 10);
	/* Structural tests */
	EXEC_TEST_CALC('#', 5, 5, -EFAULT, 0);
	zassert_equal(calc('+', 5, 10, NULL), -EINVAL);
	zassert_equal(sum(1, 2, NULL), -EINVAL);
}

ZTEST(basic, test_div)
{
	/* Specification-based tests
	 * Partitions:
	 *  MIN
	 *  (N) negative
	 *  (Z) zero
	 *  (P) positive
	 *  MAX
	 */
	/* N + N */
	/* N + Z */
	/* N + P */
	/* Z + Z */
	/* Z + P */
	/* P + P */
	int ret;
	int err = calc('/', 5, 5, &ret);
	zassert_equal(err, 0);
	zassert_equal(ret, 1);

	EXEC_TEST_CALC('/', -5, -5, 0, 1);
	EXEC_TEST_CALC('/', -5, 0, -EFAULT, 0);
	EXEC_TEST_CALC('/', -5, 5, 0, -1);
	EXEC_TEST_CALC('/', 0, 0, -EFAULT, 0);
	EXEC_TEST_CALC('/', 0, 5, 0, 0);
	EXEC_TEST_CALC('/', 5, 5, 0, 1);
	EXEC_TEST_CALC('/', 1025, 5, -ENODATA, 0);
	EXEC_TEST_CALC('/', 1025, 0, -EFAULT, 0);
	/* Structural tests */
	zassert_equal(div(1, 2, NULL), -EINVAL);

	// EXEC_TEST_CALC('/', 5, 5, 0, 1);
}

ZTEST_SUITE(basic, NULL, NULL, NULL, NULL, NULL);
