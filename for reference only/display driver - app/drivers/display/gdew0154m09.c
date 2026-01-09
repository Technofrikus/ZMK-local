/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT gooddisplay_gdew0154m09

#include <string.h>
#include <zephyr/device.h>
#include <zephyr/init.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>

#include "gdew0154m09_regs.h"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(gdew0154m09, CONFIG_DISPLAY_LOG_LEVEL);

#define EPD_PANEL_WIDTH DT_INST_PROP(0, width)
#define EPD_PANEL_HEIGHT DT_INST_PROP(0, height)
#define GDEW0154M09_PIXELS_PER_BYTE 8U

/* Align to byte boundary */
#define GDEW0154M09_BUFFER_SIZE (EPD_PANEL_WIDTH * EPD_PANEL_HEIGHT / 8)

struct gdew0154m09_config {
	struct spi_dt_spec spi;
	struct gpio_dt_spec dc;
	struct gpio_dt_spec reset;
	struct gpio_dt_spec busy;
	uint16_t height;
	uint16_t width;
};

struct gdew0154m09_data {
	bool blanking_on;
};

static inline int gdew0154m09_write_cmd(const struct device *dev, uint8_t cmd, const uint8_t *data,
					size_t len)
{
	const struct gdew0154m09_config *config = dev->config;
	struct spi_buf buf = {.buf = &cmd, .len = sizeof(cmd)};
	struct spi_buf_set buf_set = {.buffers = &buf, .count = 1};
	int err;

	gpio_pin_set_dt(&config->dc, 0);
	err = spi_write_dt(&config->spi, &buf_set);
	if (err < 0) {
		return err;
	}

	if (data != NULL) {
		buf.buf = (void *)data;
		buf.len = len;
		gpio_pin_set_dt(&config->dc, 1);
		err = spi_write_dt(&config->spi, &buf_set);
		if (err < 0) {
			return err;
		}
	}

	return 0;
}

static inline void gdew0154m09_busy_wait(const struct device *dev)
{
	const struct gdew0154m09_config *config = dev->config;
	int pin_state;

	/* Wait for BUSY to go high (idle) */
	/* Note: Check datasheet for active level. Usually high = idle for these controllers */
	/* Logic analyzer trace shows busy low during update, high when done */
	do {
		pin_state = gpio_pin_get_dt(&config->busy);
		k_sleep(K_MSEC(1));
	} while (pin_state == 0);
}

static int gdew0154m09_reset(const struct device *dev)
{
	const struct gdew0154m09_config *config = dev->config;

	gpio_pin_set_dt(&config->reset, 0);
	k_sleep(K_MSEC(10));
	gpio_pin_set_dt(&config->reset, 1);
	k_sleep(K_MSEC(10));
	gdew0154m09_busy_wait(dev);
	return 0;
}

static int gdew0154m09_blanking_off(const struct device *dev)
{
	struct gdew0154m09_data *data = dev->data;
	data->blanking_on = false;
	/* Power on if needed, but usually handled in update */
	return 0;
}

static int gdew0154m09_blanking_on(const struct device *dev)
{
	struct gdew0154m09_data *data = dev->data;
	data->blanking_on = true;
	/* Deep sleep could be entered here */
	return 0;
}

static int gdew0154m09_update_display(const struct device *dev, const uint8_t *ram, size_t size)
{
	LOG_DBG("Update display");
	gdew0154m09_reset(dev);

	// Initialization sequence for GDEW0154M09 (JD79653)
	gdew0154m09_write_cmd(dev, GDEW0154M09_CMD_DRF, NULL, 0); // Driver Output Control
	uint8_t drf[] = { (EPD_PANEL_HEIGHT - 1) & 0xFF, ((EPD_PANEL_HEIGHT - 1) >> 8) & 0xFF, 0x00 };
	gdew0154m09_write_cmd(dev, GDEW0154M09_CMD_DRF, drf, sizeof(drf));

	gdew0154m09_write_cmd(dev, GDEW0154M09_CMD_DATA_ENTRY_MODE, (uint8_t[]){0x03}, 1); // X increment, Y increment
	
	gdew0154m09_write_cmd(dev, GDEW0154M09_CMD_RAM_X_POS, (uint8_t[]){0x00, (EPD_PANEL_WIDTH/8)-1}, 2);
	gdew0154m09_write_cmd(dev, GDEW0154M09_CMD_RAM_Y_POS, (uint8_t[]){0x00, 0x00, (EPD_PANEL_HEIGHT-1) & 0xFF, ((EPD_PANEL_HEIGHT-1) >> 8) & 0xFF}, 4);
	
	gdew0154m09_write_cmd(dev, GDEW0154M09_CMD_BORDER_WAVEFORM, (uint8_t[]){0x05}, 1);
	
	gdew0154m09_write_cmd(dev, GDEW0154M09_CMD_TSENS, (uint8_t[]){0x80}, 1); // Built-in temp sensor
	
	// Load image data
	gdew0154m09_write_cmd(dev, GDEW0154M09_CMD_RAM_X_CTR, (uint8_t[]){0x00}, 1);
	gdew0154m09_write_cmd(dev, GDEW0154M09_CMD_RAM_Y_CTR, (uint8_t[]){0x00, 0x00}, 2);
	
	gdew0154m09_write_cmd(dev, GDEW0154M09_CMD_WRITE_RAM, ram, size);
	
	// Power on and update
	gdew0154m09_write_cmd(dev, GDEW0154M09_CMD_DISP_CTRL2, (uint8_t[]){0xF7}, 1); // Enable clock, analog, display, disable deep sleep? 
	gdew0154m09_write_cmd(dev, GDEW0154M09_CMD_MASTER_ACT, NULL, 0);
	
	// Wait for update
	gdew0154m09_busy_wait(dev);
	
	// Deep sleep
	gdew0154m09_write_cmd(dev, GDEW0154M09_CMD_DSL, (uint8_t[]){0x01}, 1);
	
	return 0;
}

static int gdew0154m09_write(const struct device *dev, const uint16_t x, const uint16_t y,
			     const struct display_buffer_descriptor *desc, const void *buf)
{
	size_t buf_len = desc->width * desc->height / 8;
	if (desc->pitch != desc->width) {
		LOG_ERR("Unsupported pitch");
		return -ENOTSUP;
	}
	
	// Simple full refresh for now
	return gdew0154m09_update_display(dev, buf, buf_len);
}

static int gdew0154m09_read(const struct device *dev, const uint16_t x, const uint16_t y,
			    const struct display_buffer_descriptor *desc, void *buf)
{
	return -ENOTSUP;
}

static void *gdew0154m09_get_framebuffer(const struct device *dev)
{
	return NULL;
}

static int gdew0154m09_set_brightness(const struct device *dev, const uint8_t brightness)
{
	return -ENOTSUP;
}

static int gdew0154m09_set_contrast(const struct device *dev, const uint8_t contrast)
{
	return -ENOTSUP;
}

static void gdew0154m09_get_capabilities(const struct device *dev,
					 struct display_capabilities *capabilities)
{
	const struct gdew0154m09_config *config = dev->config;

	memset(capabilities, 0, sizeof(struct display_capabilities));
	capabilities->x_resolution = config->width;
	capabilities->y_resolution = config->height;
	capabilities->supported_pixel_formats = PIXEL_FORMAT_MONO10;
	capabilities->current_pixel_format = PIXEL_FORMAT_MONO10;
	capabilities->screen_info = SCREEN_INFO_MONO_VTILED | SCREEN_INFO_EPD;
}

static int gdew0154m09_set_pixel_format(const struct device *dev,
					const enum display_pixel_format pixel_format)
{
	if (pixel_format == PIXEL_FORMAT_MONO10) {
		return 0;
	}
	return -ENOTSUP;
}

static int gdew0154m09_set_orientation(const struct device *dev,
				       const enum display_orientation orientation)
{
	return -ENOTSUP;
}

static int gdew0154m09_init(const struct device *dev)
{
	const struct gdew0154m09_config *config = dev->config;

	if (!spi_is_ready_dt(&config->spi)) {
		LOG_ERR("SPI bus %s not ready", config->spi.bus->name);
		return -ENODEV;
	}

	if (!gpio_is_ready_dt(&config->reset)) {
		LOG_ERR("Reset GPIO not ready");
		return -ENODEV;
	}

	if (!gpio_is_ready_dt(&config->dc)) {
		LOG_ERR("DC GPIO not ready");
		return -ENODEV;
	}

	if (!gpio_is_ready_dt(&config->busy)) {
		LOG_ERR("Busy GPIO not ready");
		return -ENODEV;
	}

	gpio_pin_configure_dt(&config->reset, GPIO_OUTPUT_ACTIVE);
	gpio_pin_configure_dt(&config->dc, GPIO_OUTPUT_INACTIVE);
	gpio_pin_configure_dt(&config->busy, GPIO_INPUT);

	LOG_INF("GDEW0154M09 initialized");
	return 0;
}

static struct gdew0154m09_data gdew0154m09_data;

static const struct gdew0154m09_config gdew0154m09_config = {
	.spi = SPI_DT_SPEC_INST_GET(0, SPI_OP_MODE_MASTER | SPI_WORD_SET(8), 0),
	.dc = GPIO_DT_SPEC_INST_GET(0, dc_gpios),
	.reset = GPIO_DT_SPEC_INST_GET(0, reset_gpios),
	.busy = GPIO_DT_SPEC_INST_GET(0, busy_gpios),
	.width = DT_INST_PROP(0, width),
	.height = DT_INST_PROP(0, height),
};

static struct display_driver_api gdew0154m09_driver_api = {
	.blanking_on = gdew0154m09_blanking_on,
	.blanking_off = gdew0154m09_blanking_off,
	.write = gdew0154m09_write,
	.read = gdew0154m09_read,
	.get_framebuffer = gdew0154m09_get_framebuffer,
	.set_brightness = gdew0154m09_set_brightness,
	.set_contrast = gdew0154m09_set_contrast,
	.get_capabilities = gdew0154m09_get_capabilities,
	.set_pixel_format = gdew0154m09_set_pixel_format,
	.set_orientation = gdew0154m09_set_orientation,
};

DEVICE_DT_INST_DEFINE(0, gdew0154m09_init, NULL, &gdew0154m09_data,
		      &gdew0154m09_config, POST_KERNEL,
		      CONFIG_DISPLAY_INIT_PRIORITY, &gdew0154m09_driver_api);
