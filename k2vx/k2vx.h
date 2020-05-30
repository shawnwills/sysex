#ifndef __K2VX_H__
#define __K2VX_H__

#include <stdint.h>

#include "sysex.h"

#define K2VX_SOX SYSEX_SOX /* start of sysex */
#define K2VX_EOX SYSEX_EOX /* end of sysex */
#define K2VX_MID 0x07 /* Kurzweil Manufacturer ID */
#define K2VX_KID K2VX_MID /* Kurzweil Manufacturer ID */
#define K2VX_PID 0x78 /* Product Identifier */

#define K2VX_HEADER_SIZE 4 /* sox, kid, dev_id, pid */
#define K2VX_FOOTER_SIZE 1 /* eox */
#define K2VX_MSG_TYPE_SIZE 1 /* msg_type */
#define K2VX_PARAM_SIZE (K2VX_HEADER_SIZE + K2VX_MSG_TYPE_SIZE + \
    K2VX_FOOTER_SIZE)
/* sox, kid, dev_id, pid, msg_type, eox */

enum k2vx_msg_type {
		K2VX_MSG_DUMP			= 0x00,
		K2VX_MSG_LOAD			= 0x01,
		K2VX_MSG_DACK			= 0x02,
		K2VX_MSG_DNAK			= 0x03,
		K2VX_MSG_DIR			= 0x04,
		K2VX_MSG_INFO			= 0x05,
		K2VX_MSG_NEW			= 0x06,
		K2VX_MSG_DEL			= 0x07,
		K2VX_MSG_CHANGE			= 0x08,
		K2VX_MSG_WRITE			= 0x09,
		K2VX_MSG_READ			= 0x0A,
		K2VX_MSG_READBANK		= 0x0B,
		K2VX_MSG_DIRBANK		= 0x0C,
		K2VX_MSG_ENDOFBANK		= 0x0D,
		K2VX_MSG_DELBANK		= 0x0E,
		K2VX_MSG_MOVEBANK		= 0x0F,
		K2VX_MSG_PANEL			= 0x14,
		K2VX_MSG_ALLTEXT		= 0x15,
		K2VX_MSG_PARAMVALUE		= 0x16,
		K2VX_MSG_PARAMNAME		= 0x17,
		K2VX_MSG_GETGRAPHICS	= 0x18,
		K2VX_MSG_SCREENREPLY	= 0x19
};

struct k2vx_message {
		uint8_t msg_type;
		uint32_t size;
		uint8_t *buf;
};

struct k2vx_sysex_message {
		uint8_t sox;
		uint8_t kid;
		uint8_t dev_id;
		uint8_t pid;
		struct k2vx_message message;
		uint8_t eox;
};

enum k2vx_button_event_type {
		K2VX_BUTTON_EV_UP			= 0x08,
		K2VX_BUTTON_EV_DOWN			= 0x09,
		K2VX_BUTTON_EV_REPEAT		= 0x0A,
		K2VX_BUTTON_EV_ALPHA_WHEEL	= 0x0D
};

struct k2vx_panel_button {
		uint8_t event_type;
		uint8_t number;
		uint8_t count;
};

enum k2vx_button_number {
		/* Alphanumeric pad */
		K2VX_BUTTON_NO_ZERO					= 0x00,
		K2VX_BUTTON_NO_ONE					= 0x01,
		K2VX_BUTTON_NO_TWO					= 0x02,
		K2VX_BUTTON_NO_THREE				= 0x03,
		K2VX_BUTTON_NO_FOUR					= 0x04,
		K2VX_BUTTON_NO_FIVE					= 0x05,
		K2VX_BUTTON_NO_SIX					= 0x06,
		K2VX_BUTTON_NO_SEVEN				= 0x07,
		K2VX_BUTTON_NO_EIGHT				= 0x08,
		K2VX_BUTTON_NO_NINE					= 0x09,
		K2VX_BUTTON_NO_PLUS_MINUS			= 0x0A,
		K2VX_BUTTON_NO_CANCEL				= 0x0B,
		K2VX_BUTTON_NO_CLEAR				= 0x0C,
		K2VX_BUTTON_NO_ENTER				= 0x0D,
		/* Navigation */
		K2VX_BUTTON_NO_PLUS					= 0x16,
		K2VX_BUTTON_NO_MINUS				= 0x17,
		K2VX_BUTTON_NO_PLUS_AND_MINUS		= 0x1E,
		K2VX_BUTTON_NO_CHAN_BANK_INC		= 0x14,
		K2VX_BUTTON_NO_CHAN_BANK_DEC		= 0x15,
		K2VX_BUTTON_NO_CHAN_BANK_INC_DEC	= 0x1C,
		K2VX_BUTTON_NO_CURSOR_LEFT			= 0x12,
		K2VX_BUTTON_NO_CURSOR_RIGHT			= 0x13,
		K2VX_BUTTON_NO_CURSOR_LEFT_RIGHT	= 0x1A,
		K2VX_BUTTON_NO_CURSOR_UP			= 0x10,
		K2VX_BUTTON_NO_CURSOR_DOWN			= 0x11,
		K2VX_BUTTON_NO_CURSOR_UP_DOWN		= 0x18,
		/* Soft-Buttons A-F */
		K2VX_BUTTON_NO_A					= 0x22,  /* leftmost */
		K2VX_BUTTON_NO_B					= 0x23,
		K2VX_BUTTON_NO_C					= 0x24,
		K2VX_BUTTON_NO_D					= 0x25,
		K2VX_BUTTON_NO_E					= 0x26,
		K2VX_BUTTON_NO_F					= 0x27, /* rightmost */
		K2VX_BUTTON_NO_AB					= 0x28,
		K2VX_BUTTON_NO_CD					= 0x29, /* two center */
		K2VX_BUTTON_NO_EF					= 0x2A,
		K2VX_BUTTON_NO_YES					= 0x26,
		K2VX_BUTTON_NO_NO					= 0x27,
		/* Edit/Exit */
		K2VX_BUTTON_NO_EDIT					= 0x20,
		K2VX_BUTTON_NO_EXIT					= 0x21,
		/* Mode Selection */
		K2VX_BUTTON_NO_PROGRAM				= 0x40,
		K2VX_BUTTON_NO_SETUP				= 0x41,
		K2VX_BUTTON_NO_QUICK_ACCESS			= 0x42,
		K2VX_BUTTON_NO_EFFECTS				= 0x47,
		K2VX_BUTTON_NO_MIDI					= 0x44,
		K2VX_BUTTON_NO_MASTER				= 0x43,
		K2VX_BUTTON_NO_SONG					= 0x46,
		K2VX_BUTTON_NO_DISK					= 0x45
};

#endif /* __K2VX_H__ */
