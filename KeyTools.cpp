#include "KeyTools.h"

using namespace KeyTools;

BYTE KeyTools::getKeyRow ( BYTE keyIndex ) {
    switch ( keyIndex ) {
    case KEY_ESC:
    case KEY_F1: case KEY_F2: case KEY_F3: case KEY_F4:
    case KEY_F5: case KEY_F6: case KEY_F7: case KEY_F8:
    case KEY_F9: case KEY_F10: case KEY_F11: case KEY_F12:
    case KEY_PRINT_SCREEN: case KEY_SCROLL_LOCK: case KEY_PAUSE_BREAK:
        return 0;

    case KEY_TILDE: case KEY_1: case KEY_2: case KEY_3: case KEY_4:
    case KEY_5: case KEY_6: case KEY_7: case KEY_8: case KEY_9:
    case KEY_0: case KEY_MIN: case KEY_ADD: case KEY_BACKSPACE:
    case KEY_INS: case KEY_HOME: case KEY_PGUP: case KEY_NUMLK: case KEY_N_SLASH:
    case KEY_N_MUL: case KEY_N_MIN:
        return 1;

    case KEY_TAB: case KEY_Q: case KEY_W: case KEY_E: case KEY_R:
    case KEY_T: case KEY_Y: case KEY_U: case KEY_I: case KEY_O:
    case KEY_P: case KEY_L_BRACKET: case KEY_R_BRACKET: case KEY_BACKSLASH:
    case KEY_DEL: case KEY_END: case KEY_PGDN: case KEY_N_7: case KEY_N_8:
    case KEY_N_9: case KEY_N_PLUS:
        return 2;

    case KEY_CAPS: case KEY_A: case KEY_S: case KEY_D: case KEY_F: case KEY_G:
    case KEY_H: case KEY_J: case KEY_K: case KEY_L: case KEY_SEMICOLON: case KEY_QUOT:
    case KEY_ENTER: case KEY_N_4: case KEY_N_5: case KEY_N_6:
        return 3;

    case KEY_SHIFT: case KEY_Z: case KEY_X: case KEY_C: case KEY_V: case KEY_B:
    case KEY_N: case KEY_M: case KEY_COMMA: case KEY_POINT: case KEY_SLASH:
    case KEY_R_SHIFT: case KEY_U_ARROW: case KEY_N_1: case KEY_N_2: case KEY_N_3: case KEY_N_ENTER:
        return 4;

    default:
        return 5;

    }
}

BYTE KeyTools::getKeyCol ( BYTE keyIndex ) {
    switch ( keyIndex ) {
    case KEY_ESC:
    case KEY_TILDE:
    case KEY_TAB:
    case KEY_CAPS:
    case KEY_SHIFT:
    case KEY_CTRL:
        return 0;
    case KEY_1:
    case KEY_Q:
    case KEY_A:
    case KEY_Z:
    case KEY_L_WIN:
        return 1;
    case KEY_F1:
    case KEY_2:
    case KEY_W:
    case KEY_S:
    case KEY_X:
    case KEY_L_ALT:
        return 2;
    case KEY_F2:
    case KEY_3:
    case KEY_E:
    case KEY_D:
    case KEY_C:
        return 3;
    case KEY_F3:
    case KEY_4:
    case KEY_R:
    case KEY_F:
    case KEY_V:
        return 4;
    case KEY_F4:
    case KEY_5:
    case KEY_T:
    case KEY_G:
    case KEY_B:
    case KEY_SPACE:
        return 5;
    case KEY_F5:
    case KEY_6:
    case KEY_Y:
    case KEY_H:
    case KEY_N:
        return 6;
    case KEY_F6:
    case KEY_7:
    case KEY_U:
    case KEY_J:
    case KEY_M:
        return 7;
    case KEY_F7:
    case KEY_8:
    case KEY_I:
    case KEY_K:
    case KEY_COMMA:
    case KEY_R_ALT:
        return 8;
    case KEY_F8:
    case KEY_9:
    case KEY_O:
    case KEY_L:
    case KEY_POINT:
        return 9;
    case KEY_F9:
    case KEY_0:
    case KEY_P:
    case KEY_SEMICOLON:
    case KEY_SLASH:
    case KEY_FN:
        return 10;
    case KEY_F10:
    case KEY_MIN:
    case KEY_L_BRACKET:
    case KEY_QUOT:
        return 11;
    case KEY_F11:
    case KEY_ADD:
    case KEY_R_BRACKET:
    case KEY_OPTIONS:
        return 12;
    case KEY_F12:
    case KEY_BACKSPACE:
    case KEY_BACKSLASH:
    case KEY_ENTER:
    case KEY_R_SHIFT:
    case KEY_R_CTRL:
        return 13;
    case KEY_PRINT_SCREEN:
    case KEY_INS:
    case KEY_DEL:
    case KEY_L_ARROW:
        return 14;
    case KEY_SCROLL_LOCK:
    case KEY_HOME:
    case KEY_END:
    case KEY_U_ARROW:
    case KEY_D_ARROW:
        return 15;
    case KEY_PAUSE_BREAK:
    case KEY_PGUP:
    case KEY_PGDN:
    case KEY_R_ARROW:
        return 16;
    case KEY_NUMLK:
    case KEY_N_7:
    case KEY_N_4:
    case KEY_N_1:
    case KEY_N_0:
        return 17;
    case KEY_N_SLASH:
    case KEY_N_8:
    case KEY_N_5:
    case KEY_N_2:
        return 18;
    case KEY_N_MUL:
    case KEY_N_9:
    case KEY_N_6:
    case KEY_N_3:
    case KEY_N_DOT:
        return 19;
    case KEY_N_MIN:
    case KEY_N_PLUS:
    case KEY_N_ENTER:
        return 20;
    default:
        return -1;
    }
}

using namespace std;
unordered_map<BYTE, vector<BYTE>> genRow2K ( ) {
    unordered_map<BYTE, vector<BYTE>> map;
    for ( auto k : AllKeys ) {
        BYTE row = getKeyRow ( k );

		auto it = map.find ( row );
        if ( it == map.end ( ) )
            map[ row ] = vector<BYTE> ( );

        map[ row ].push_back( k );
    }

    return map;
}

unordered_map<BYTE, vector<BYTE>> genCol2K ( ) {
    unordered_map<BYTE, vector<BYTE>> map;
    for ( auto k : AllKeys ) {
        BYTE col = getKeyCol ( k );

        auto it = map.find ( col );
        if ( it == map.end ( ) )
            map[ col ] = vector<BYTE> ( );

        map[ col ].push_back ( k );
    }

    return map;
}

unordered_map<BYTE, vector<BYTE>> KeyTools::Row2Keys = genRow2K ( );
unordered_map<BYTE, vector<BYTE>> KeyTools::Col2Keys = genCol2K ( );

unordered_map<int, KeyTools::KEY_INDEX> KeyTools::RawKeyToEnum = {
    {0x29, KeyTools::KEY_ESC},
    {0x35, KeyTools::KEY_TILDE},
    {0x2B, KeyTools::KEY_TAB},
    {0x39, KeyTools::KEY_CAPS},
    {0xE1, KeyTools::KEY_SHIFT},
    {0xE0, KeyTools::KEY_CTRL},

    {0x1E, KeyTools::KEY_1},
    {0x14, KeyTools::KEY_Q},
    {0x04, KeyTools::KEY_A},
    {0x1D, KeyTools::KEY_Z},
    {0xE3, KeyTools::KEY_L_WIN},

    {0x3A, KeyTools::KEY_F1},
    {0x1F, KeyTools::KEY_2},
    {0x1A, KeyTools::KEY_W},
    {0x16, KeyTools::KEY_S},
    {0x1B, KeyTools::KEY_X},
    {0xE2, KeyTools::KEY_L_ALT},

    {0x3B, KEY_F2},
    {0x20, KEY_3},
    {0x08, KEY_E},
    {0x07, KEY_D},
    {0x06, KEY_C},

    {0x3C, KEY_F3},
    {0x21, KEY_4},
    {0x15, KEY_R},
    {0x09, KEY_F},
    {0x19, KEY_V},

    {0x3D, KEY_F4},
    {0x22, KEY_5},
    {0x17, KEY_T},
    {0x0A, KEY_G},
    {0x05, KEY_B},
    {0x2C, KEY_SPACE},

    {0x3E, KEY_F5},
    {0x23, KEY_6},
    {0x1C, KEY_Y},
    {0x0B, KEY_H},
    {0x11, KEY_N},
    
    {0x3F, KEY_F6},
    {0x24, KEY_7},
    {0x18, KEY_U},
    {0x0D, KEY_J},
    {0x10, KEY_M},
    
    {0x40, KEY_F7},
    {0x25, KEY_8},
    {0x0C, KEY_I},
    {0x0E, KEY_K},
    {0x36, KEY_COMMA},
    {0xE6, KEY_R_ALT},
    
    {0x41, KEY_F8},
    {0x26, KEY_9},
    {0x12, KEY_O},
    {0x0F, KEY_L},
    {0x37, KEY_POINT},
    
    {0x42, KEY_F9},
    {0x27, KEY_0},
    {0x13, KEY_P},
    {0x33, KEY_SEMICOLON},
    {0x38, KEY_SLASH},
    {0xA4, KEY_FN},
    
    {0x43, KEY_F10},
    {0x2D, KEY_MIN},
    {0x2F, KEY_L_BRACKET},
    {0x34, KEY_QUOT},
    
    {0x44, KEY_F11},
    {0x2E, KEY_ADD},
    {0x30, KEY_R_BRACKET},
    {0x65, KEY_OPTIONS},
          
    {0x45, KEY_F12},
    {0x2A, KEY_BACKSPACE},
    {0x31, KEY_BACKSLASH},
    {0x28, KEY_ENTER},
    {0xE5, KEY_R_SHIFT},
    {0xE4, KEY_R_CTRL},
          
    {0x46, KEY_PRINT_SCREEN},
    {0x49, KEY_INS},
    {0x4C, KEY_DEL},
    {0x50, KEY_L_ARROW},
          
    {0x47, KEY_SCROLL_LOCK},
    {0x4A, KEY_HOME},
    {0x4D, KEY_END},
    {0x52, KEY_U_ARROW},
    {0x51, KEY_D_ARROW},
          
    {0x48, KEY_PAUSE_BREAK},
    {0x4B, KEY_PGUP},
    {0x4E, KEY_PGDN},
    {0x4F, KEY_R_ARROW},
          
    {0x53, KEY_NUMLK},
    {0x5F, KEY_N_7},
    {0x5C, KEY_N_4},
    {0x59, KEY_N_1},
    {0x62, KEY_N_0},
          
    {0x54, KEY_N_SLASH},
    {0x60, KEY_N_8},
    {0x5D, KEY_N_5},
    {0x5A, KEY_N_2},
    
    {0x55, KEY_N_MUL},
    {0x61, KEY_N_9},
    {0x5E, KEY_N_6},
    {0x5B, KEY_N_3},
    {0x63, KEY_N_DOT},
    
    {0x56, KEY_N_MIN},
    {0x57, KEY_N_PLUS},
    {0x58, KEY_N_ENTER},
};