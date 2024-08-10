#pragma once
#include "HXChroma.h"

namespace KeyTools {
	enum KEY_INDEX {
		KEY_ESC,
		KEY_TILDE,
		KEY_TAB,
		KEY_CAPS,
		KEY_SHIFT,
		KEY_CTRL,
		//unused

		KEY_1 = KEY_CTRL + 2,
		KEY_Q,
		KEY_A,
		KEY_Z,
		KEY_L_WIN,

		KEY_F1,
		KEY_2,
		KEY_W,
		KEY_S,
		KEY_X,
		KEY_L_ALT,

		KEY_F2,
		KEY_3,
		KEY_E,
		KEY_D,
		KEY_C,
		//unused

		KEY_F3 = KEY_C + 2,
		KEY_4,
		KEY_R,
		KEY_F,
		KEY_V,
		//unused

		KEY_F4 = KEY_V + 2,
		KEY_5,
		KEY_T,
		KEY_G,
		KEY_B,
		KEY_SPACE,

		KEY_F5,
		KEY_6,
		KEY_Y,
		KEY_H,
		KEY_N,
		//unused

		KEY_F6 = KEY_N + 2,
		KEY_7,
		KEY_U,
		KEY_J,
		KEY_M,
		//unused

		KEY_F7 = KEY_M + 2,
		KEY_8,
		KEY_I,
		KEY_K,
		KEY_COMMA,
		KEY_R_ALT,

		KEY_F8,
		KEY_9,
		KEY_O,
		KEY_L,
		KEY_POINT,
		//unused

		KEY_F9 = KEY_POINT + 2,
		KEY_0,
		KEY_P,
		KEY_SEMICOLON,
		KEY_SLASH,
		KEY_FN,

		KEY_F10,
		KEY_MIN,
		KEY_L_BRACKET,
		KEY_QUOT,
		//unused
		//unused

		KEY_F11 = KEY_QUOT + 3,
		KEY_ADD,
		KEY_R_BRACKET,
		//unused
		//unused
		KEY_OPTIONS = KEY_R_BRACKET + 3,

		KEY_F12,
		KEY_BACKSPACE,
		KEY_BACKSLASH,
		KEY_ENTER,
		KEY_R_SHIFT,
		KEY_R_CTRL,

		KEY_PRINT_SCREEN,
		KEY_INS,
		KEY_DEL,
		//unused
		//unused
		KEY_L_ARROW = KEY_DEL + 3,

		KEY_SCROLL_LOCK,
		KEY_HOME,
		KEY_END,
		//unused
		KEY_U_ARROW = KEY_END + 2,
		KEY_D_ARROW,

		KEY_PAUSE_BREAK,
		KEY_PGUP,
		KEY_PGDN,
		//unused
		//unused
		KEY_R_ARROW = KEY_PGDN + 3,
		//unused

		KEY_NUMLK = KEY_R_ARROW + 2,
		KEY_N_7,
		KEY_N_4,
		KEY_N_1,
		KEY_N_0,
		//unused

		KEY_N_SLASH = KEY_N_0 + 2,
		KEY_N_8,
		KEY_N_5,
		KEY_N_2,
		//unused
		//unused

		KEY_N_MUL = KEY_N_2 + 3,
		KEY_N_9,
		KEY_N_6,
		KEY_N_3,
		KEY_N_DOT,
		//unused

		KEY_N_MIN = KEY_N_DOT + 2,
		KEY_N_PLUS,
		//unused
		//unused
		KEY_N_ENTER = KEY_N_PLUS + 3,
	};

	static const KEY_INDEX AllKeys[ ] = {
		KEY_ESC, KEY_TILDE, KEY_TAB, KEY_CAPS, KEY_SHIFT, KEY_CTRL,
		KEY_1, KEY_Q, KEY_A, KEY_Z, KEY_L_WIN, KEY_F1, KEY_2,
		KEY_W, KEY_S, KEY_X, KEY_L_ALT, KEY_F2, KEY_3,
		KEY_E, KEY_D, KEY_C, KEY_F3, KEY_4, KEY_R, KEY_F,
		KEY_V, KEY_F4, KEY_5, KEY_T, KEY_G, KEY_B, KEY_SPACE,
		KEY_F5, KEY_6, KEY_Y, KEY_H, KEY_N, KEY_F6, KEY_7,
		KEY_U, KEY_J, KEY_M, KEY_F7, KEY_8, KEY_I, KEY_K,
		KEY_COMMA, KEY_R_ALT, KEY_F8, KEY_9, KEY_O, KEY_L,
		KEY_POINT, KEY_F9, KEY_0, KEY_P, KEY_SEMICOLON, KEY_SLASH,
		KEY_FN, KEY_F10, KEY_MIN, KEY_L_BRACKET, KEY_QUOT, KEY_F11,
		KEY_ADD, KEY_R_BRACKET, KEY_OPTIONS, KEY_F12, KEY_BACKSPACE,
		KEY_BACKSLASH, KEY_ENTER, KEY_R_SHIFT, KEY_R_CTRL, KEY_PRINT_SCREEN,
		KEY_INS, KEY_DEL, KEY_L_ARROW, KEY_SCROLL_LOCK, KEY_HOME, KEY_END,
		KEY_U_ARROW, KEY_D_ARROW, KEY_PAUSE_BREAK, KEY_PGUP, KEY_PGDN,
		KEY_R_ARROW, KEY_NUMLK, KEY_N_7, KEY_N_4, KEY_N_1, KEY_N_0,
		KEY_N_SLASH, KEY_N_8, KEY_N_5, KEY_N_2, KEY_N_MUL, KEY_N_9,
		KEY_N_6, KEY_N_3, KEY_N_DOT, KEY_N_MIN, KEY_N_PLUS, KEY_N_ENTER,
	};

	extern BYTE getKeyRow ( BYTE keyIndex );
	extern BYTE getKeyCol ( BYTE keyIndex );

	extern std::unordered_map<BYTE, std::vector<BYTE>> Row2Keys;
	extern std::unordered_map<BYTE, std::vector<BYTE>> Col2Keys;
	extern std::unordered_map<int, KEY_INDEX> VirtualKeyToEnum;
}