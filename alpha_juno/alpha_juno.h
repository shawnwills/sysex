#ifndef __ALPHA_JUNO_H__
#define __ALPHA_JUNO_H__

#include <stdint.h>
/* 0000 0 */
/* 0001 1 */
/* 0010 2 */
/* 0011 3 */
/* 0100 4 */
/* 0101 5 */
/* 0110 6 */
/* 0111 7 */
/* 1000 8 */
/* 1001 9 */
/* 1010 a */
/* 1011 b */
/* 1100 c */
/* 1101 d */
/* 1110 e */
/* 1111 f */

#define ALPHA_JUNO_SOX SYSEX_SOX
#define ALPHA_JUNO_EOX SYSEX_EOX
#define ALPHA_JUNO_MID 0x41 /* Roland ID */
#define ALPHA_JUNO_PID 0x23 /* JU-1, JU-2, HS-10, HS-80, MKS-50 */
#define ALPHA_JUNO_LVL 0x20 /* Level */
#define ALPHA_JUNO_GRP 0x01 /* Group */

enum alpha_juno_opcode {
		ALPHA_JUNO_OPCODE_APR = 0x35, /* All Tone Parameters (APR) */
		ALPHA_JUNO_OPCODE_IPR = 0x36, /* Individual Tone Parameter (IPR) */
		ALPHA_JUNO_OPCODE_BLD = 0x37, /* Bulk Dump (BLD) */
		ALPHA_JUNO_OPCODE_WSF = 0x40, /* Want to send a file (WSF) */
		ALPHA_JUNO_OPCODE_RQF = 0x41, /* Request a file (RQF) */
		ALPHA_JUNO_OPCODE_DAT = 0x42, /* Data (DAT) */
		ALPHA_JUNO_OPCODE_ACK = 0x43, /* Acknowledge (ACK) */
		ALPHA_JUNO_OPCODE_EOF = 0x45, /* End of file (EOF) */
		ALPHA_JUNO_OPCODE_ERR = 0x46, /* Communication error (ERR) */
		ALPHA_JUNO_OPCODE_RJC = 0x4f, /* Rejection (RJC) */
};

struct alpha_juno_msg_header {
		uint8_t header[5];
};

struct alpha_juno_msg_ext_header {
		struct alpha_juno_msg_header header;
		uint8_t ext[2];
};

#define ALPHA_JUNO_EXT_HEADER_INIT { ALPHA_JUNO_LVL, ALPHA_JUNO_GRP }
struct alpha_juno_msg_footer {
		uint8_t footer;
};

struct alpha_juno_apr_tx_msg {
		struct alpha_juno_msg_ext_header ext_header;
		uint8_t value[36];
		uint8_t tone[10];
		struct alpha_juno_msg_footer footer;
};

struct alpha_juno_apr_rx_msg {
		struct alpha_juno_msg_ext_header ext_header;
		uint8_t value[36];
		struct alpha_juno_msg_footer footer;
};

#define ALPHA_JUNO_APR_RX_MSG_INIT { .ext_header = {				\
	.header = { ALPHA_JUNO_SOX,	\
	ALPHA_JUNO_MID, ALPHA_JUNO_OPCODE_APR, 0 /* MIDI channel */,	\
	ALPHA_JUNO_PID },												\
	.ext = ALPHA_JUNO_EXT_HEADER_INIT }								\
	.footer = { ALPHA_JUNO_EOX }}

#define ALPHA_JUNO_PG_MASK 0x3f
#define ALPHA_JUNO_TONE_MASK 0x0f
struct alpha_juno_bld_msg {
		struct alpha_juno_msg_ext_header header;
		uint16_t program;
		uint8_t tone[32];
		struct alpha_juno_msg_footer footer;
};

/* excludes ALPHA_JUNO_OPCODE_DAT */
struct alpha_juno_hs_msg {
		struct alpha_juno_msg_header header;
		struct alpha_juno_msg_footer footer;
};

#define ALPHA_JUNO_HEADER {  }
#define ALPHA_JUNO_WSF_MSG_INIT { .header = { ALPHA_JUNO_SOX,		\
	ALPHA_JUNO_MID, ALPHA_JUNO_OPCODE_WSF, 0 /* MIDI channel */,	\
	ALPHA_JUNO_PID },												\
	.footer = { ALPHA_JUNO_EOX }}
#define ALPHA_JUNO_RQF_MSG_INIT { .header = { ALPHA_JUNO_SOX,		\
	ALPHA_JUNO_MID, ALPHA_JUNO_OPCODE_RQF, 0 /* MIDI channel */,	\
	ALPHA_JUNO_PID },												\
	.footer = { ALPHA_JUNO_EOX }}
#define ALPHA_JUNO_ACK_MSG_INIT { .header = { ALPHA_JUNO_SOX,		\
	ALPHA_JUNO_MID, ALPHA_JUNO_OPCODE_ACK, 0 /* MIDI channel */,	\
	ALPHA_JUNO_PID },												\
	.footer = { ALPHA_JUNO_EOX }}
#define ALPHA_JUNO_EOF_MSG_INIT { .header = { ALPHA_JUNO_SOX,		\
	ALPHA_JUNO_MID, ALPHA_JUNO_OPCODE_EOF, 0 /* MIDI channel */,	\
	ALPHA_JUNO_PID },												\
	.footer = { ALPHA_JUNO_EOX }}
#define ALPHA_JUNO_ERR_MSG_INIT { .header = { ALPHA_JUNO_SOX,		\
	ALPHA_JUNO_MID, ALPHA_JUNO_OPCODE_ERR, 0 /* MIDI channel */,	\
	ALPHA_JUNO_PID },												\
	.footer = { ALPHA_JUNO_EOX }}
#define ALPHA_JUNO_RJC_MSG_INIT { .header = { ALPHA_JUNO_SOX,		\
	ALPHA_JUNO_MID, ALPHA_JUNO_OPCODE_RJC, 0 /* MIDI channel */,	\
	ALPHA_JUNO_PID },												\
	.footer = { ALPHA_JUNO_EOX }}

struct alpha_juno_dat_msg {
		struct alpha_juno_msg_header header;
		uint8_t tone[256];
		uint8_t chksum;
		struct alpha_juno_msg_footer footer;
};
#define ALPHA_JUNO_DAT_MSG_INIT { .header = { ALPHA_JUNO_SOX,		\
	ALPHA_JUNO_MID, ALPHA_JUNO_OPCODE_DAT, 0 /* MIDI channel */,	\
	ALPHA_JUNO_PID },												\
	.footer = { ALPHA_JUNO_EOX }}

enum alpha_juno_parameter {
		ALPHA_JUNO_DCO_ENV_MODE = 0,
		/*
		 * 0 = ENV normal
		 * 1 = ENV inverted
		 * 2 = ENV normal   with dynamics
		 * 3 = ENV inverted with dynamics
		 */
		ALPHA_JUNO_VCF_ENV_MODE = 1,
		/*
		 * 0 = ENV normal
		 * 1 = ENV inverted
		 * 2 = ENV normal   with dynamics
		 * 3 = ENV inverted with dynamics
		 */
		ALPHA_JUNO_VCA_ENV_MODE = 2,
		/*
		 * 0 = ENV
		 * 1 = GATE
		 * 2 = ENV  with dynamics
		 * 3 = GATE with dynamics
		 */
		ALPHA_JUNO_DCO_WAVEFORM_PULSE = 3, /* 0 - 3 */
		ALPHA_JUNO_DCO_WAVEFORM_SAWTOOTH = 4, /* 0 - 5 */
		ALPHA_JUNO_DCO_WAVEFORM_SUB = 5, /* 0 - 5 */
		ALPHA_JUNO_DCO_RANGE = 6,
		/*
		 * 0 =  4'
		 * 1 =  8'
		 * 2 = 16'
		 * 3 = 32'
		 */
		ALPHA_JUNO_DCO_SUB_LEVEL = 7, /* 0 - 3 */
		ALPHA_JUNO_DCO_NOISE_LEVEL = 8, /* 0 - 3 */
		ALPHA_JUNO_HPF_CUTOFF_FREQ = 9, /* 0 - 3 */
		ALPHA_JUNO_CHORUS = 10, /* 0 = OFF, 1 = ON */
		ALPHA_JUNO_DCO_LFO_MOD_DEPTH = 11, /* 0 - 127 */
		ALPHA_JUNO_DCO_ENV_MOD_DEPTH = 12, /* 0 - 127 */
		ALPHA_JUNO_DCO_AFTER_DEPTH = 13, /* 0 - 127 */
		ALPHA_JUNO_DCO_PW_PWM_DEPTH = 14, /* 0 - 127 */
		ALPHA_JUNO_DCO_PWM_RATE = 15,
		/*
		 * 0 = PW manual,
		 * 1 - 127 = PWM LFO RATE
		 */
		ALPHA_JUNO_VCF_CUTOFF_FREQ = 16, /* 0 - 127 */
		ALPHA_JUNO_VCF_RESONANCE = 17, /* 0 - 127 */
		ALPHA_JUNO_VCF_LFO_MOD_DEPTH = 18, /* 0 - 127 */
		ALPHA_JUNO_VCF_ENV_MOD_DEPTH = 19, /* 0 - 127 */
		ALPHA_JUNO_VCF_KEY_FOLLOW = 20, /* 0 - 127 */
		ALPHA_JUNO_VCF_AFTER_DEPTH = 21, /* 0 - 127 */
		ALPHA_JUNO_VCA_LEVEL = 22, /* O - 127 */
		ALPHA_JUNO_VCA_AFTER_DEPTH = 23, /* O - 127 */
		ALPHA_JUNO_LFO_RATE = 24, /* 0 - 127 */
		ALPHA_JUNO_LFO_DELAY_TIME = 25, /* 0 - 127 */
		ALPHA_JUNO_ENV_T1 = 26, /* 0 - 127 (ATTACK TIME } */
		ALPHA_JUNO_ENV_L1 = 27, /* 0 - 127 (ATTACK LEVEL) */
		ALPHA_JUNO_ENV_T2 = 28, /* 0 - 127 (BREAK TIME } */
		ALPHA_JUNO_ENV_L2 = 29, /* 0 - 127 (BREAK LEVEL) */
		ALPHA_JUNO_ENV_T3 = 30, /* 0 - 127 (DECAY TIME ) */
		ALPHA_JUNO_ENV_L3 = 31, /* 0 - 127 (SUSTAIN LEVEL} */
		ALPHA_JUNO_ENV_T4 = 32, /* 0 - 127 (RELEASE TIME ) */
		ALPHA_JUNO_ENV_KEY_FOLLOW = 33, /* 0 - 127 */
		ALPHA_JUNO_CHORUS_RATE = 34, /* 0 - 127 */
		ALPHA_JUNO_BENDER_RANGE = 35, /* 0 - 12 */
		ALPHA_JUNO_TONE_NAME_0 = 36, /* 0 - 63 */
		ALPHA_JUNO_TONE_NAME_1 = 37, /* 0 - 63 */
		ALPHA_JUNO_TONE_NAME_2 = 38, /* 0 - 63 */
		ALPHA_JUNO_TONE_NAME_3 = 39, /* 0 - 63 */
		ALPHA_JUNO_TONE_NAME_4 = 40, /* 0 - 63 */
		ALPHA_JUNO_TONE_NAME_5 = 41, /* 0 - 63 */
		ALPHA_JUNO_TONE_NAME_6 = 42, /* 0 - 63 */
		ALPHA_JUNO_TONE_NAME_7 = 43, /* 0 - 63 */
		ALPHA_JUNO_TONE_NAME_8 = 44, /* 0 - 63 */
		ALPHA_JUNO_TONE_NAME_9 = 45, /* 0 - 63 */
		ALPHA_JUNO_RESERVED_0 = 46,
		ALPHA_JUNO_RESERVED_1 = 47,
		ALPHA_JUNO_TONE_MODIFY = 48,
		/*
		 * (ignored if received)
		 * O = ENV TIME (increment)
		 *  1 = BRILLIANCE (increment)
		 *  2 = MOD DEPTH (increment)
		 *  3 = MOD RATE (increment)
		 * 16 = ENV TIME (decrement)
		 * 17 = BRILLIANCE (decrement)
		 * 18 = MOD DEPTH (decrement)
		 * 19 = MOD RATE (decrement)
		 */
};

static uint8_t alpha_juno_tone_name_table[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
		'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
		'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z', ' ', '-'
};

#endif /* __ALPHA_JUNO_H__ */
