/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef ZEPHYR_DRIVERS_DISPLAY_GDEW0154M09_REGS_H_
#define ZEPHYR_DRIVERS_DISPLAY_GDEW0154M09_REGS_H_

/* Driver Output control */
#define GDEW0154M09_CMD_DRF 0x01

/* Gate Driving Voltage Control */
#define GDEW0154M09_CMD_GDV 0x03

/* Source Driving Voltage Control */
#define GDEW0154M09_CMD_SDV 0x04

/* Deep Sleep mode */
#define GDEW0154M09_CMD_DSL 0x10

/* Data Entry Mode Setting */
#define GDEW0154M09_CMD_DATA_ENTRY_MODE 0x11

/* SW Reset */
#define GDEW0154M09_CMD_SW_RESET 0x12

/* HV Ready Detection */
#define GDEW0154M09_CMD_HV_READY 0x14

/* VCI detection */
#define GDEW0154M09_CMD_VCI_DETECT 0x15

/* Temp sensor control */
#define GDEW0154M09_CMD_TSENS 0x18

/* Temp register write */
#define GDEW0154M09_CMD_TWRITE 0x1A

/* Temp register read */
#define GDEW0154M09_CMD_TREAD 0x1B

/* Temp sensor write */
#define GDEW0154M09_CMD_TSENS_WRITE 0x1C

/* Master Activation */
#define GDEW0154M09_CMD_MASTER_ACT 0x20

/* Display Update Control 1 */
#define GDEW0154M09_CMD_DISP_CTRL1 0x21

/* Display Update Control 2 */
#define GDEW0154M09_CMD_DISP_CTRL2 0x22

/* Write RAM (Black/White) */
#define GDEW0154M09_CMD_WRITE_RAM 0x24

/* Write RAM (Red) */
#define GDEW0154M09_CMD_WRITE_RAM_RED 0x26

/* VCOM Sense */
#define GDEW0154M09_CMD_VCOM_SENSE 0x28

/* VCOM Sense Duration */
#define GDEW0154M09_CMD_VCOM_DURATION 0x29

/* Program VCOM OTP */
#define GDEW0154M09_CMD_PROG_VCOM 0x2A

/* Write VCOM Register */
#define GDEW0154M09_CMD_WRITE_VCOM 0x2C

/* OTP Register Read */
#define GDEW0154M09_CMD_OTP_READ 0x2D

/* Status Bit Read */
#define GDEW0154M09_CMD_STATUS_READ 0x2F

/* Dummy Line Period */
#define GDEW0154M09_CMD_DUMMY_LINE 0x3A

/* Gate Line Width */
#define GDEW0154M09_CMD_GATE_WIDTH 0x3B

/* Border Waveform Control */
#define GDEW0154M09_CMD_BORDER_WAVEFORM 0x3C

/* Ram X - address Start / End position */
#define GDEW0154M09_CMD_RAM_X_POS 0x44

/* Ram Y - address Start / End position */
#define GDEW0154M09_CMD_RAM_Y_POS 0x45

/* Ram X - address counter */
#define GDEW0154M09_CMD_RAM_X_CTR 0x4E

/* Ram Y - address counter */
#define GDEW0154M09_CMD_RAM_Y_CTR 0x4F

/* Analog Block Control */
#define GDEW0154M09_CMD_ANALOG_CTRL 0xF0

/* Digital Block Control */
#define GDEW0154M09_CMD_DIGITAL_CTRL 0xF1

#endif /* ZEPHYR_DRIVERS_DISPLAY_GDEW0154M09_REGS_H_ */
