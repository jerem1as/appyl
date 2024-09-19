#ifndef KEYMAP_H
#define KEYMAP_H

#include <map>

const std::map<uint8_t, String> keyMap = {
    {0x2C, "SPACE BAR"},
    {0x80, "KEY_LEFT_CTRL"},
    {0x81, "KEY_LEFT_SHIFT"},
    {0x82, "KEY_LEFT_ALT"},
    {0x83, "KEY_LEFT_GUI"}, 
    {0x84, "KEY_RIGHT_CTRL"},
    {0x85, "KEY_RIGHT_SHIFT"},
    {0x86, "KEY_RIGHT_ALT"},
    {0x87, "KEY_RIGHT_GUI"},
    {0xDA, "KEY_UP_ARROW"},
    {0xD9, "KEY_DOWN_ARROW"},
    {0xD8, "KEY_LEFT_ARROW"},
    {0xD7, "KEY_RIGHT_ARROW"},
    {0xB2, "KEY_BACKSPACE"},
    {0xB3, "KEY_TAB"},
    {0xB0, "KEY_RETURN"},
    {0xB1, "KEY_ESC"},
    {0xD1, "KEY_INSERT"},
    {0xCE, "KEY_PRTSC"},
    {0xD4, "KEY_DELETE"},
    {0xD3, "KEY_PAGE_UP"},
    {0xD6, "KEY_PAGE_DOWN"},
    {0xD2, "KEY_HOME"},
    {0xD5, "KEY_END"}
};

#endif
