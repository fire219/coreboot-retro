/* SPDX-License-Identifier: GPL-2.0-or-later */

#include <baseboard/gpio.h>
#include <baseboard/variants.h>
#include <console/console.h>
#include <fw_config.h>


static const struct pad_config lte_disable_pads[] = {
	/* A8  : WWAN_RF_DISABLE_ODL */
	PAD_NC(GPP_A8, NONE),
	/* B5  : I2C_P_SENSOR_SDA */
	PAD_NC(GPP_B5, NONE),
	/* B6  : I2C_P_SENSOR_SCL */
	PAD_NC(GPP_B6, NONE),
	/* D6  : WWAN_EN */
	PAD_NC(GPP_D6, NONE),
	/* F12 : WWAN_RST_L */
	PAD_NC(GPP_F12, NONE),
	/* H19  : P_SENSOR_INT_L */
	PAD_NC(GPP_H19, NONE),
	/* H23 : WWAN_SAR_DETECT_ODL */
	PAD_NC(GPP_H23, NONE),
};

static const struct pad_config emmc_disable_pads[] = {
	/* I7  : EMMC_CMD */
	PAD_NC(GPP_I7, NONE),
	/* I8  : EMMC_D0 */
	PAD_NC(GPP_I8, NONE),
	/* I9  : EMMC_D1 */
	PAD_NC(GPP_I9, NONE),
	/* I10 : EMMC_D2 */
	PAD_NC(GPP_I10, NONE),
	/* I11 : EMMC_D3 */
	PAD_NC(GPP_I11, NONE),
	/* I12 : EMMC_D4 */
	PAD_NC(GPP_I12, NONE),
	/* I13 : EMMC_D5 */
	PAD_NC(GPP_I13, NONE),
	/* I14 : EMMC_D6 */
	PAD_NC(GPP_I14, NONE),
	/* I15 : EMMC_D7 */
	PAD_NC(GPP_I15, NONE),
	/* I16 : EMMC_RCLK */
	PAD_NC(GPP_I16, NONE),
	/* I17 : EMMC_CLK */
	PAD_NC(GPP_I17, NONE),
	/* I18 : EMMC_RST_L */
	PAD_NC(GPP_I18, NONE),
};

static const struct pad_config stylus_disable_pads[] = {
	/* F13 : SOC_PEN_DETECT_R_ODL */
	PAD_NC_LOCK(GPP_F13, NONE, LOCK_CONFIG),
	/* F15 : SOC_PEN_DETECT_ODL */
	PAD_NC_LOCK(GPP_F15, NONE, LOCK_CONFIG),
};

static const struct pad_config disable_wifi_pch_susclk[] = {
	/* GPD8 ==> NC */
	PAD_NC(GPD8, NONE),
};

void fw_config_gpio_padbased_override(struct pad_config *padbased_table)
{
	if (!fw_config_probe(FW_CONFIG(DB_USB, DB_1C_LTE))) {
		printk(BIOS_INFO, "Disable LTE-related GPIO pins.\n");
		gpio_padbased_override(padbased_table, lte_disable_pads,
				       ARRAY_SIZE(lte_disable_pads));
	}
	if (fw_config_is_provisioned() && !fw_config_probe(FW_CONFIG(STORAGE, STORAGE_EMMC))) {
		printk(BIOS_INFO, "Disable eMMC GPIO pins.\n");
		gpio_padbased_override(padbased_table, emmc_disable_pads,
				       ARRAY_SIZE(emmc_disable_pads));
	}
	if (fw_config_probe(FW_CONFIG(STYLUS, STYLUS_ABSENT))) {
		printk(BIOS_INFO, "Disable Stylus GPIO pins.\n");
		gpio_padbased_override(padbased_table, stylus_disable_pads,
				       ARRAY_SIZE(stylus_disable_pads));
	}
	if (fw_config_probe(FW_CONFIG(WIFI_SAR_ID, SAR_ID_3))) {
		printk(BIOS_INFO, "Disable PCH SUSCLK.\n");
		gpio_padbased_override(padbased_table, disable_wifi_pch_susclk,
					ARRAY_SIZE(disable_wifi_pch_susclk));
	}
}
