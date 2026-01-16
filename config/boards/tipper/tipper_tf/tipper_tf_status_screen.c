/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zmk/display/widgets/output_status.h>
#include "battery_status.h"
#include <zmk/display/status_screen.h>
#include <zmk/battery.h>
#include <zmk/endpoints.h>
#include <zmk/ble.h>
#include <zmk/usb.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/events/endpoint_changed.h>
#include <zmk/events/ble_active_profile_changed.h>
#include <zmk/display.h>
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

LV_IMAGE_DECLARE(tipperlogo);

// Declare TBAT battery graphics (with text, pre-rotated)
LV_IMAGE_DECLARE(TBAT00);
LV_IMAGE_DECLARE(TBAT00c);
LV_IMAGE_DECLARE(TBAT20);
LV_IMAGE_DECLARE(TBAT20c);
LV_IMAGE_DECLARE(TBAT40);
LV_IMAGE_DECLARE(TBAT40c);
LV_IMAGE_DECLARE(TBAT60);
LV_IMAGE_DECLARE(TBAT60c);
LV_IMAGE_DECLARE(TBAT80);
LV_IMAGE_DECLARE(TBAT80c);
LV_IMAGE_DECLARE(TBAT100);
LV_IMAGE_DECLARE(TBAT100c);


// Declare custom font
extern const lv_font_t Ramsey;

#if IS_ENABLED(CONFIG_ZMK_WIDGET_OUTPUT_STATUS)
static struct zmk_widget_output_status output_status_widget;
#endif

// BT label object (simpler than canvas to avoid draw pipeline issues)
static lv_obj_t *bt_label;
static lv_obj_t *bat_image; // Battery image object
static lv_obj_t *screen_parent;

static void request_full_screen_refresh() {
    if (screen_parent == NULL) {
        return;
    }
    // Invalidate the whole screen to force a full redraw and avoid ghosting
    lv_obj_invalidate(screen_parent);
}

// Initialize BT label
static void init_bt_label() {
    if (screen_parent == NULL || bt_label != NULL) return;

    bt_label = lv_label_create(screen_parent);
    if (bt_label != NULL) {
        lv_label_set_text(bt_label, "");
        lv_obj_set_style_text_font(bt_label, &Ramsey, 0);
        // Use white text to remain visible on a dark logo background
        lv_obj_set_style_text_color(bt_label, lv_color_white(), 0);
        lv_obj_set_style_bg_opa(bt_label, LV_OPA_TRANSP, 0);
        lv_obj_align(bt_label, LV_ALIGN_BOTTOM_RIGHT, -50, -5);
        lv_obj_move_foreground(bt_label);
    }
}

// Update battery image based on level and charging status
static void update_battery_image(uint8_t level, bool usb_present) {
    if (bat_image == NULL) return;

    const lv_image_dsc_t *img_src = NULL;

    // Select image based on battery level and charging status
    if (usb_present) {
        // Charging variants (with 'c' suffix)
        if (level >= 100) {
            img_src = &TBAT100c;
        } else if (level >= 80) {
            img_src = &TBAT80c;
        } else if (level >= 60) {
            img_src = &TBAT60c;
        } else if (level >= 40) {
            img_src = &TBAT40c;
        } else if (level >= 20) {
            img_src = &TBAT20c;
        } else {
            img_src = &TBAT00c;
        }
    } else {
        // Non-charging variants
        if (level >= 100) {
            img_src = &TBAT100;
        } else if (level >= 80) {
            img_src = &TBAT80;
        } else if (level >= 60) {
            img_src = &TBAT60;
        } else if (level >= 40) {
            img_src = &TBAT40;
        } else if (level >= 20) {
            img_src = &TBAT20;
        } else {
            img_src = &TBAT00;
        }
    }

    if (img_src != NULL) {
        lv_image_set_src(bat_image, img_src);
    }

    request_full_screen_refresh();
}

// Update BT text on canvas
static void update_bt_text(struct zmk_endpoint_instance endpoint, bool connected) {
    if (bt_label == NULL) return;

    if (endpoint.transport == ZMK_TRANSPORT_BLE && connected) {
        char bt_text[5] = "BT?";
        uint8_t profile = endpoint.ble.profile_index + 1;
        if (profile > 9) {
            profile = 9;
        }
        bt_text[2] = (char)('0' + profile);
        bt_text[3] = '\0';
        lv_label_set_text(bt_label, bt_text);
    } else if (endpoint.transport == ZMK_TRANSPORT_USB && connected) {
        lv_label_set_text(bt_label, "USB");
    } else {
        lv_label_set_text(bt_label, "");
    }

    request_full_screen_refresh();
}

// Battery update handler
static int battery_update_handler(const zmk_event_t *eh) {
    uint8_t level = zmk_battery_state_of_charge();
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
    bool usb_present = zmk_usb_is_powered();
#else
    bool usb_present = false;
#endif
    update_battery_image(level, usb_present);
    return 0;
}

ZMK_LISTENER(battery_image_update, battery_update_handler);
ZMK_SUBSCRIPTION(battery_image_update, zmk_battery_state_changed);
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
ZMK_SUBSCRIPTION(battery_image_update, zmk_usb_conn_state_changed);
#endif

// BT/Endpoint update handler
static int endpoint_update_handler(const zmk_event_t *eh) {
    struct zmk_endpoint_instance endpoint = zmk_endpoints_selected();
    bool connected = false;
    
    if (endpoint.transport == ZMK_TRANSPORT_BLE) {
        connected = zmk_ble_active_profile_is_connected();
    } else if (endpoint.transport == ZMK_TRANSPORT_USB) {
        connected = true;
    }
    
    update_bt_text(endpoint, connected);
    return 0;
}

ZMK_LISTENER(endpoint_text, endpoint_update_handler);
ZMK_SUBSCRIPTION(endpoint_text, zmk_endpoint_changed);
#if IS_ENABLED(CONFIG_ZMK_BLE)
ZMK_SUBSCRIPTION(endpoint_text, zmk_ble_active_profile_changed);
#endif

// Delayed initial update
static void delayed_initial_update_work(struct k_work *work) {
    uint8_t level = zmk_battery_state_of_charge();
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
    bool usb_present = zmk_usb_is_powered();
#else
    bool usb_present = false;
#endif
    update_battery_image(level, usb_present);
    
    struct zmk_endpoint_instance endpoint = zmk_endpoints_selected();
    bool connected = false;
    if (endpoint.transport == ZMK_TRANSPORT_BLE) {
        connected = zmk_ble_active_profile_is_connected();
    } else if (endpoint.transport == ZMK_TRANSPORT_USB) {
        connected = true;
    }
    update_bt_text(endpoint, connected);
}

static K_WORK_DELAYABLE_DEFINE(initial_update_work, delayed_initial_update_work);

lv_obj_t *zmk_display_status_screen() {
    lv_obj_t *screen;
    screen = lv_obj_create(NULL);
    
    screen_parent = screen;

    // Use an explicit screen background to avoid transparent blending issues
    lv_obj_set_style_bg_color(screen, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);

    // Logo image in center - create FIRST as background
    lv_obj_t *tipperlogo_icon = lv_image_create(screen);
    if (tipperlogo_icon == NULL) {
        LOG_ERR("Failed to create logo image object");
    } else {
        lv_image_set_src(tipperlogo_icon, &tipperlogo);
        lv_obj_align(tipperlogo_icon, LV_ALIGN_CENTER, 0, 0);
        lv_obj_set_style_img_recolor_opa(tipperlogo_icon, LV_OPA_TRANSP, 0);
        lv_obj_move_to_index(tipperlogo_icon, 0);
        LOG_INF("Created logo image on screen");
    }

    // Battery image enabled
    bat_image = lv_image_create(screen);
    lv_obj_align(bat_image, LV_ALIGN_TOP_LEFT, 0, 0);

    // BT label (created last, so it appears on top of everything)
    init_bt_label();

    // Prime initial values immediately so something is visible even if events are delayed
    {
        // Prime battery + BT immediately
        uint8_t level = zmk_battery_state_of_charge();
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
        bool usb_present = zmk_usb_is_powered();
#else
        bool usb_present = false;
#endif
        update_battery_image(level, usb_present);

        struct zmk_endpoint_instance endpoint = zmk_endpoints_selected();
        bool connected = false;
        if (endpoint.transport == ZMK_TRANSPORT_BLE) {
            connected = zmk_ble_active_profile_is_connected();
        } else if (endpoint.transport == ZMK_TRANSPORT_USB) {
            connected = true;
        }
        update_bt_text(endpoint, connected);
    }

#if IS_ENABLED(CONFIG_ZMK_WIDGET_OUTPUT_STATUS)
    zmk_widget_output_status_init(&output_status_widget, screen);
    lv_obj_align(zmk_widget_output_status_obj(&output_status_widget), LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_add_flag(zmk_widget_output_status_obj(&output_status_widget), LV_OBJ_FLAG_HIDDEN);
#endif

    // Schedule initial update
    k_work_schedule_for_queue(zmk_display_work_q(), &initial_update_work, K_MSEC(500));
    
    return screen;
}
