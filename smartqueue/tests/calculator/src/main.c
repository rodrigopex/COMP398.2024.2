/*
 * Copyright (c) 2025 Rodrigo Peixoto <rodrigopex@gmail.com>
 * SPDX-License-Identifier: Apache-2.0
 */
#include <zephyr/irq_offload.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/ztest.h>

#include "calc.h"

ZTEST(basic, test_sum)
{
	/* Partitions:
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
	int err = calc('+', 5, 5, &ret);
	zassert_equal(err, 0);
	zassert_equal(ret, 10);
}

ZTEST(basic, test_div)
{
	/* Partitions:
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
}
ZTEST_SUITE(basic, NULL, NULL, NULL, NULL, NULL);
