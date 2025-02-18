/* SPDX-License-Identifier: GPL-2.0-only */

#include <console/console.h>
#include <device/pci_ops.h>
#include <device/smbus_host.h>
#include <spd.h>
#include "raminit.h"

void dump_spd_registers(void)
{
	int i;
	printk(BIOS_DEBUG, "\n");
	for (i = 0; i < DIMM_SOCKETS; i++) {
		unsigned int device;
		/* Logic to handle 3DIMM boards where DIMM0 starts at 0x52 */
#if CONFIG(SDRAM_3DIMM_REVERSE_OFFSET)
        device = DIMM0 - i;
#else
		/* All other (normal) boards 3DIMM or 4DIMM */
        device = DIMM0 + i;
#endif
		if (device) {
			int j;
			printk(BIOS_DEBUG, "DIMM %d: %02x", i, device);
			for (j = 0; j < 256; j++) {
				int status;
				unsigned char byte;
				if ((j & 0xf) == 0) {
					printk(BIOS_DEBUG, "\n%02x: ", j);
				}
				status = smbus_read_byte(device, j);
				if (status < 0) {
					printk(BIOS_DEBUG, "bad device\n");
					break;
				}
				byte = status & 0xff;
				printk(BIOS_DEBUG, "%02x ", byte);
			}
			printk(BIOS_DEBUG, "\n");
		}
	}
}

void dump_pci_device(unsigned int dev)
{
	int i;
	printk(BIOS_DEBUG, "PCI: %02x:%02x.%02x", (dev >> 20) & 0xff, (dev >> 15) & 0x1f,
		(dev >> 12) & 7);

	for (i = 0; i <= 255; i++) {
		if ((i & 0x0f) == 0)
			printk(BIOS_DEBUG, "\n%02x:", i);
		printk(BIOS_DEBUG, " %02x", pci_read_config8(dev, i));
	}
	printk(BIOS_DEBUG, "\n");
}
