/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <device/device.h>
#include <device/pnp.h>
#include <superio/conf_mode.h>
#include <pc80/keyboard.h>

#include "w83977ef.h"

static void w83977ef_init(struct device *dev)
{

	if (!dev->enabled)
		return;

	switch (dev->path.pnp.device) {
	case W83977EF_KBC:
		pc_keyboard_init(NO_AUX_DEVICE);
		break;
	}
}

static struct device_operations ops = {
	.read_resources   = pnp_read_resources,
	.set_resources    = pnp_set_resources,
	.enable_resources = pnp_enable_resources,
	.enable           = pnp_enable,
	.init             = w83977ef_init,
	.ops_pnp_mode     = &pnp_conf_mode_8787_aa,
};

static struct pnp_info pnp_dev_info[] = {
	{ NULL, W83977EF_FDC,  PNP_IO0 | PNP_IRQ0 | PNP_DRQ0, 0x07f8, },
	{ NULL, W83977EF_PP,   PNP_IO0 | PNP_IRQ0 | PNP_DRQ0, 0x07f8, },
	{ NULL, W83977EF_SP1,  PNP_IO0 | PNP_IRQ0, 0x07f8, },
	{ NULL, W83977EF_SP2,  PNP_IO0 | PNP_IRQ0, 0x07f8, },
	{ NULL, W83977EF_KBC,  PNP_IO0 | PNP_IO1 | PNP_IRQ0 | PNP_IRQ1,
		0x07ff, 0x07ff, },
#if CONFIG(W83977EF_HAVE_SEPARATE_IR_DEVICE)
	{ NULL, W83977EF_CIR,  PNP_IO0 | PNP_IRQ0, 0x07f8, },
#endif
	{ NULL, W83977EF_GAME_MIDI_GPIO1, PNP_IO0 | PNP_IO1 | PNP_IRQ0,
		0x07ff, 0x07fe, },
	{ NULL, W83977EF_ACPI, PNP_IRQ0, },
};

static void enable_dev(struct device *dev)
{
	pnp_enable_devices(dev, &ops, ARRAY_SIZE(pnp_dev_info), pnp_dev_info);
}

struct chip_operations superio_winbond_w83977ef_ops = {
	CHIP_NAME("Winbond W83977EF Super I/O")
	.enable_dev = enable_dev,
};
