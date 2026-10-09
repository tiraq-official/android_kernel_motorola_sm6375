/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * KCAL color control for SDE (PCC + HSIC)
 *
 * Adapted for the Motorola sm6375 ("blair", Moto G34 5G / fogos) techpack
 * display driver on msm-5.4.
 *
 * The DSPP PCC block is used for the per-channel RGB gain and the DSPP HSIC
 * block for hue / saturation / value / contrast.  Values are exposed to
 * userspace through sysfs at /sys/devices/platform/kcal_ctrl.0/.
 */

#ifndef _SDE_HW_KCAL_CTRL_H
#define _SDE_HW_KCAL_CTRL_H

#include <drm/msm_drm_pp.h>

#define SDE_HW_KCAL_ENABLED		(1)

#define SDE_HW_KCAL_MIN_VALUE		(20)
#define SDE_HW_KCAL_INIT_RED		(256)
#define SDE_HW_KCAL_INIT_GREEN		(256)
#define SDE_HW_KCAL_INIT_BLUE		(256)

#define SDE_HW_KCAL_INIT_HUE		(0)
#define SDE_HW_KCAL_INIT_ADJ		(255)

struct sde_hw_kcal_pcc {
	u32 red;
	u32 green;
	u32 blue;
};

struct sde_hw_kcal_hsic {
	u32 hue;
	u32 saturation;
	u32 value;
	u32 contrast;
};

struct sde_hw_kcal {
	struct sde_hw_kcal_pcc pcc;
	struct sde_hw_kcal_hsic hsic;

	u32 enabled:1;
	u32 min_value;
};

/**
 * sde_hw_kcal_get() - get a handle to the internal kcal calibration plan.
 *
 * Pointer is used here for performance reasons. Races are expected in the
 * color processing code.
 */
struct sde_hw_kcal *sde_hw_kcal_get(void);

/**
 * sde_hw_kcal_hsic_struct() - get an HSIC configuration structure with the
 * adjustments applied from kcal.
 */
struct drm_msm_pa_hsic sde_hw_kcal_hsic_struct(void);

/**
 * sde_hw_kcal_pcc_adjust() - change RGB colors according to kcal setup.
 * @data: data array of PCC coefficients.
 * @plane: index of the PCC color plane.
 */
void sde_hw_kcal_pcc_adjust(u32 *data, int plane);

#endif /* _SDE_HW_KCAL_CTRL_H */
