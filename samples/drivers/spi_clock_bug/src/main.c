/*
 * Copyright (c) 2021 Marc Reilly, Creative Product Design
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app, LOG_LEVEL_INF);

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/drivers/spi.h>

#define SPIBB_NODE	DT_NODELABEL(spi3)

int main(void)
{
	const struct device *const dev = DEVICE_DT_GET(SPIBB_NODE);
	struct spi_dt_spec bus = SPI_DT_SPEC_GET(DT_NODELABEL(uc8179_waveshare_epaper_gdew075t7),
						 SPI_OP_MODE_MASTER | SPI_WORD_SET(8) | SPI_LOCK_ON,
						 0);

	if (!device_is_ready(dev)) {
		printk("%s: device not ready.\n", dev->name);
		return 0;
	}

	struct spi_buf buf = {.buf = "data", .len = 4};
	struct spi_buf_set buf_set = {.buffers = &buf, .count = 1};

	while (1) {
		spi_write_dt(&bus, &buf_set);
		k_msleep(100);
	}
	return 0;
}
