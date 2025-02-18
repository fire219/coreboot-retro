/* SPDX-License-Identifier: GPL-2.0-or-later */

#ifndef SOUTHBRIDGE_INTEL_I82371EB_CHIP_H
#define SOUTHBRIDGE_INTEL_I82371EB_CHIP_H

#include <device/device.h>
#include <types.h>

struct southbridge_intel_i82371eb_config {
	bool ide0_enable;
	bool ide0_drive0_udma33_enable;
	bool ide0_drive1_udma33_enable;
	bool ide1_enable;
	bool ide1_drive0_udma33_enable;
	bool ide1_drive1_udma33_enable;
	bool ide_legacy_enable;
	bool usb_enable;
	bool gpi7_enable;  /* Select GPI7 (1) or SERIRQ (0) */
	bool gpo22_enable; /* GPO22/GPO23 (1) vs. XDIR#/XOE# (0) */
	bool gpo24_enable; /* GPO24 (1) vs. RTCCS# (0) */
	bool gpo25_enable; /* GPO25 (1) vs. RTCALE (0) */
	bool gpo26_enable; /* GPO26 (1) vs. KBCCS# (0) */
	bool reqa_gnta_enable;  /* PCI REQA and GNTA (1) vs GPI1, GPO9 (0) */
	int gpo22:1;
	int gpo23:1;
	/* acpi */
	u32 gpo; /* gpio output default */
	u8 lid_polarity;
	u8 thrm_polarity;
};

#endif /* SOUTHBRIDGE_INTEL_I82371EB_CHIP_H */
