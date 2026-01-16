/*
*
* Copyright (c) 2021 Darryl deHaan, 2021 weteor
* SPDX-License-Identifier: MIT
*
*/

#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/battery.h>
#include <zmk/display.h>
#include "battery_status.h"
#include <zmk/usb.h>
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/event_manager.h>
#include <zmk/events/battery_state_changed.h>

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

LV_IMAGE_DECLARE(bat_100);
LV_IMAGE_DECLARE(bat_100_c);
LV_IMAGE_DECLARE(bat_80);
LV_IMAGE_DECLARE(bat_80_c);
LV_IMAGE_DECLARE(bat_60);
LV_IMAGE_DECLARE(bat_60_c);
LV_IMAGE_DECLARE(bat_40);
LV_IMAGE_DECLARE(bat_40_c);
LV_IMAGE_DECLARE(bat_20);
LV_IMAGE_DECLARE(bat_20_c);
LV_IMAGE_DECLARE(bat_00);
LV_IMAGE_DECLARE(bat_00_c);

struct battery_status_state {
    uint8_t level;
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
    bool usb_present;
#endif
};

static void set_battery_symbol(lv_obj_t *icon, struct battery_status_state state) {

    uint8_t level = state.level;

#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
    if (level > 80) {
        if (state.usb_present) {
             lv_image_set_src(icon, &bat_100_c);
        }else{
            lv_image_set_src(icon, &bat_100);
        }
    } else if (level > 60) {
        if (state.usb_present) {
             lv_image_set_src(icon, &bat_80_c);
        }else{
            lv_image_set_src(icon, &bat_80);
        }
    } else if (level > 40) {
        if (state.usb_present) {
             lv_image_set_src(icon, &bat_60_c);
        }else{
            lv_image_set_src(icon, &bat_60);
        }
    } else if (level > 20) {
        if (state.usb_present) {
             lv_image_set_src(icon, &bat_40_c);
        }else{
            lv_image_set_src(icon, &bat_40);
        }
    } else if (level > 5) {
        if (state.usb_present) {
             lv_image_set_src(icon, &bat_20_c);
        }else{
            lv_image_set_src(icon, &bat_20);
        }
    } else {
        if (state.usb_present) {
             lv_image_set_src(icon, &bat_00_c);
        }else{
            lv_image_set_src(icon, &bat_00);
        }
    }
#endif /* IS_ENABLED(CONFIG_USB_DEVICE_STACK) */

}

void battery_status_update_cb(struct battery_status_state state) {
    struct zmk_widget_battery_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_battery_symbol(widget->obj, state); }
}

static struct battery_status_state battery_status_get_state(const zmk_event_t *eh) {
    const struct zmk_battery_state_changed *ev = as_zmk_battery_state_changed(eh);

    return (struct battery_status_state){
        .level = (ev != NULL) ? ev->state_of_charge : zmk_battery_state_of_charge(),
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
        .usb_present = zmk_usb_is_powered(),
#endif /* IS_ENABLED(CONFIG_USB_DEVICE_STACK) */
    };
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_battery_status, struct battery_status_state,
                            battery_status_update_cb, battery_status_get_state)

ZMK_SUBSCRIPTION(widget_battery_status, zmk_battery_state_changed);
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
ZMK_SUBSCRIPTION(widget_battery_status, zmk_usb_conn_state_changed);
#endif /* IS_ENABLED(CONFIG_USB_DEVICE_STACK) */

int zmk_widget_battery_status_init(struct zmk_widget_battery_status *widget, lv_obj_t *parent) {
    widget->obj = lv_image_create(parent);

    sys_slist_append(&widgets, &widget->node);

    widget_battery_status_init();
    return 0;
}

lv_obj_t *zmk_widget_battery_status_obj(struct zmk_widget_battery_status *widget) {
    return widget->obj;
}
