/* Copyright (c) 2008-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/mm.h>
#include <linux/fb.h>
#include <linux/init.h>
#include <linux/ioport.h>
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/uaccess.h>
#include <linux/workqueue.h>
#include <linux/string.h>
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <linux/vmalloc.h>
#include <linux/debugfs.h>

#include "msm_fb_panel.h"

int panel_next_on(struct platform_device *pdev)
{
	int ret = 0;
	struct msm_fb_panel_data *pdata;
	struct msm_fb_panel_data *next_pdata;
	struct platform_device *next_pdev;

	pdata = (struct msm_fb_panel_data *)pdev->dev.platform_data;

	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata =
			    (struct msm_fb_panel_data *)next_pdev->dev.
			    platform_data;
			if ((next_pdata) && (next_pdata->on))
				ret = next_pdata->on(next_pdev);
		}
	}

	return ret;
}

int panel_next_off(struct platform_device *pdev)
{
	int ret = 0;
	struct msm_fb_panel_data *pdata;
	struct msm_fb_panel_data *next_pdata;
	struct platform_device *next_pdev;

	pdata = (struct msm_fb_panel_data *)pdev->dev.platform_data;

	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata =
			    (struct msm_fb_panel_data *)next_pdev->dev.
			    platform_data;
			if ((next_pdata) && (next_pdata->on))
				ret = next_pdata->off(next_pdev);
		}
	}

	return ret;
}

int panel_next_fps_level_change(struct platform_device *pdev,
					 u32 fps_level)
{
	int ret = 0;
	struct msm_fb_panel_data *pdata;
	struct msm_fb_panel_data *next_pdata;
	struct platform_device *next_pdev;

	pdata = (struct msm_fb_panel_data *)pdev->dev.platform_data;

	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata =
			    (struct msm_fb_panel_data *)next_pdev->dev.
			    platform_data;
			if ((next_pdata) && (next_pdata->fps_level_change))
				ret = next_pdata->fps_level_change(next_pdev,
							 fps_level);
		}
	}

	return ret;
}

int panel_next_low_power_config(struct platform_device *pdev,
					 int enable)
{
	int ret = 0;
	struct msm_fb_panel_data *pdata;
	struct msm_fb_panel_data *next_pdata;
	struct platform_device *next_pdev;

	pdata = (struct msm_fb_panel_data *)pdev->dev.platform_data;

	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata =
			    (struct msm_fb_panel_data *)next_pdev->dev.
			    platform_data;
			if ((next_pdata) && (next_pdata->fps_level_change))
				ret = next_pdata->fps_level_change(next_pdev,
							 fps_level);
		}
	}

	return ret;
}

int panel_next_low_power_config(struct platform_device *pdev,
					 int enable)
 {
 	int ret = 0;
 	struct msm_fb_panel_data *pdata;
 	struct msm_fb_panel_data *next_pdata;
 	struct platform_device *next_pdev;
 
 	pdata = (struct msm_fb_panel_data *)pdev->dev.platform_data;
 
 	if (pdata) {
 		next_pdev = pdata->next;
 		if (next_pdev) {
 			next_pdata =
 			    (struct msm_fb_panel_data *)next_pdev->dev.
 			    platform_data;
 			if ((next_pdata) && (next_pdata->low_power_config))
 				ret = next_pdata->low_power_config(next_pdev,
 							 enable);
 		}
 	}
 
 	return ret;
 }

int panel_next_late_init(struct platform_device *pdev)
{
	int ret = 0;
	struct msm_fb_panel_data *pdata;
	struct msm_fb_panel_data *next_pdata;
	struct platform_device *next_pdev;

	pdata = (struct msm_fb_panel_data *)pdev->dev.platform_data;

	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata = (struct msm_fb_panel_data *)
					next_pdev->dev.platform_data;
			if ((next_pdata) && (next_pdata->late_init))
				ret = next_pdata->late_init(next_pdev);
		}
	}

	return ret;
}

int panel_next_early_off(struct platform_device *pdev)
{
	int ret = 0;
	struct msm_fb_panel_data *pdata;
	struct msm_fb_panel_data *next_pdata;
	struct platform_device *next_pdev;

	pdata = (struct msm_fb_panel_data *)pdev->dev.platform_data;

	if (pdata) {
		next_pdev = pdata->next;
		if (next_pdev) {
			next_pdata = (struct msm_fb_panel_data *)
					next_pdev->dev.platform_data;
			if ((next_pdata) && (next_pdata->early_off))
				ret = next_pdata->early_off(next_pdev);
		}
	}

	return ret;
}

struct platform_device *msm_fb_device_alloc(struct msm_fb_panel_data *pdata,
						u32 type, u32 id)
{
	struct platform_device *this_dev = NULL;
	char dev_name[16];

	switch (type) {
	case EBI2_PANEL:
		snprintf(dev_name, sizeof(dev_name), "ebi2_lcd");
		break;

	case MDDI_PANEL:
		snprintf(dev_name, sizeof(dev_name), "mddi");
		break;

	case EXT_MDDI_PANEL:
		snprintf(dev_name, sizeof(dev_name), "mddi_ext");
		break;

	case TV_PANEL:
		snprintf(dev_name, sizeof(dev_name), "tvenc");
		break;

	case HDMI_PANEL:
	case LCDC_PANEL:
		snprintf(dev_name, sizeof(dev_name), "lcdc");
		break;

	case LVDS_PANEL:
		snprintf(dev_name, sizeof(dev_name), "lvds");
		break;

	case DTV_PANEL:
		snprintf(dev_name, sizeof(dev_name), "dtv");
		break;

	case MIPI_VIDEO_PANEL:
	case MIPI_CMD_PANEL:
		snprintf(dev_name, sizeof(dev_name), "mipi_dsi");
		break;
	case WRITEBACK_PANEL:
		snprintf(dev_name, sizeof(dev_name), "writeback");
		break;

	default:
		return NULL;
	}

	if (pdata != NULL)
		pdata->next = NULL;
	else
		return NULL;

	this_dev =
	    platform_device_alloc(dev_name, ((u32) type << 16) | (u32) id);

	if (this_dev) {
		if (platform_device_add_data
		    (this_dev, pdata, sizeof(struct msm_fb_panel_data))) {
			printk
			    ("msm_fb_device_alloc: platform_device_add_data failed!\n");
			platform_device_put(this_dev);
			return NULL;
		}
	}

	return this_dev;
}
