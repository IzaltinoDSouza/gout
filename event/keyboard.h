#pragma once

#include <functional>

class keyboard
{
public:
    enum class modifiers
    {
        none        = 0x0000,
        left_shift  = 0x0001,
        right_shift = 0x0002,
        left_ctrl   = 0x0040,
        right_ctrl  = 0x0080,
        left_alt    = 0x0100,
        right_alt   = 0x0200,
        left_gui    = 0x0400,
        right_gui   = 0x0800,
        num_lock    = 0x1000,
        caps_lock   = 0x2000,
        altgr       = 0x4000,
        ctrl        = (left_ctrl  |  right_ctrl),
        shift       = (left_shift |  right_shift),
        alt         = (left_alt   |  right_alt),
        gui         = (left_gui   |  right_gui),
        reserved    = 0x8000
    };
    
    enum class keys
    {
        unknown = 0,
        
        a = 4,
        b = 5,
        c = 6,
        d = 7,
        e = 8,
        f = 9,
        g = 10,
        h = 11,
        i = 12,
        j = 13,
        k = 14,
        l = 15,
        m = 16,
        n = 17,
        o = 18,
        p = 19,
        q = 20,
        r = 21,
        s = 22,
        t = 23,
        u = 24,
        v = 25,
        w = 26,
        x = 27,
        y = 28,
        z = 29,
        
        num_1 = 30,
        num_2 = 31,
        num_3 = 32,
        num_4 = 33,
        num_5 = 34,
        num_6 = 35,
        num_7 = 36,
        num_8 = 37,
        num_9 = 38,
        num_0 = 39,
        
        enter = 40,
        escape = 41,
        esc = escape,
        backspace = 42,
        tab = 43,
        space = 44,
        
        minus = 45,
        equals = 46,
        left_bracket = 47,
        right_bracket = 48,
        backslash = 49, 
        nonushash = 50, 
        semicolon = 51,
        apostrophe = 52,
        grave = 53, 
        comma = 54,
        period = 55,
        slash = 56,
        
        caps_lock = 57,
        
        f1 = 58,
        f2 = 59,
        f3 = 60,
        f4 = 61,
        f5 = 62,
        f6 = 63,
        f7 = 64,
        f8 = 65,
        f9 = 66,
        f10 = 67,
        f11 = 68,
        f12 = 69,
        
        print_screen = 70,
        scroll_lock = 71,
        pause = 72,
        insert = 73, 
        home = 74,
        page_up = 75,
        delete_ = 76,
        end = 77,
        page_down = 78,
        right = 79,
        left = 80,
        down = 81,
        up = 82,
        
        num_lock = 83, 
        keypad_divide = 84,
        keypad_multiply = 85,
        keypad_minus = 86,
        keypad_plus = 87,
        keypad_enter = 88,
        keypad_1 = 89,
        keypad_2 = 90,
        keypad_3 = 91,
        keypad_4 = 92,
        keypad_5 = 93,
        keypad_6 = 94,
        keypad_7 = 95,
        keypad_8 = 96,
        keypad_9 = 97,
        keypad_0 = 98,
        keypad_period = 99,
        
        nonusbackslash = 100, 
        application = 101, 
        power = 102, 
        keypad_equals = 103,
        f13 = 104,
        f14 = 105,
        f15 = 106,
        f16 = 107,
        f17 = 108,
        f18 = 109,
        f19 = 110,
        f20 = 111,
        f21 = 112,
        f22 = 113,
        f23 = 114,
        f24 = 115,
        execute = 116,
        help = 117,
        menu = 118,
        select = 119,
        stop = 120,
        again = 121,   
        undo = 122,
        cut = 123,
        copy = 124,
        paste = 125,
        find = 126,
        mute = 127,
        volume_up = 128,
        volume_down = 129,
        
        keypad_comma = 133,
        
        
        alt_erase = 153, 
        sys_req = 154,
        cancel = 155,
        clear = 156,
        prior = 157,
        return2 = 158,
        separator = 159,
        out = 160,
        oper = 161,
        clear_again = 162,
        
        keypad_00 = 176,
        keypad_000 = 177,
        thousands_separator = 178,
        decimal_separator = 179,
        currency_unit = 180,
        currency_sub_unit = 181,
        keypad_left_paren = 182,
        keypad_right_paren = 183,
        keypad_left_brace = 184,
        keypad_right_brace = 185,
        keypad_tab = 186,
        keypad_backspace = 187,
        keypad_a = 188,
        keypad_b = 189,
        keypad_c = 190,
        keypad_d = 191,
        keypad_e = 192,
        keypad_f = 193,
        keypad_xor = 194,
        keypad_power = 195,
        keypad_percent = 196,
        keypad_less = 197,
        keypad_greater = 198,
        keypad_ampersand = 199,
        keypad_dblampersand = 200,
        keypad_verticalbar = 201,
        keypad_dblverticalbar = 202,
        keypad_colon = 203,
        keypad_hash = 204,
        keypad_space = 205,
        keypad_at = 206,
        keypad_exclam = 207,
        keypad_mem_store = 208,
        keypad_mem_recall = 209,
        keypad_mem_clear = 210,
        keypad_mem_add = 211,
        keypad_mem_subtract = 212,
        keypad_mem_multiply = 213,
        keypad_mem_divide = 214,
        keypad_plus_minus = 215,
        keypad_clear = 216,
        keypad_clear_entry = 217,
        keypad_binary = 218,
        keypad_octal = 219,
        keypad_decimal = 220,
        keypad_hexadecimal = 221,
        
        left_ctrl = 224,
        left_shift = 225,
        left_alt = 226, 
        left_gui = 227, 
        
        right_ctrl = 228,
        right_shift = 229,
        right_alt = 230, 
        right_gui = 231, 
        
        altgr = 257,    
        
        audio_next = 258,
        audio_prev = 259,
        audio_stop = 260,
        audio_play = 261,
        audio_mute = 262,
        
        media_select = 263,
        www = 264,
        mail = 265,
        calculator = 266,
        computer = 267, 
        
        ac_search = 268,
        ac_home = 269,
        ac_back = 270,
        ac_forward = 271,
        ac_stop = 272,
        ac_refresh = 273,
        ac_bookmarks = 274,
        
        brightness_down = 275,
        brightness_up = 276,
        display_switch = 277, 
        
        eject = 281,
        sleep = 282,
            
        audio_rewind = 285,
        audio_fast_forward = 286
    };
    keyboard(bool event = false)
     : m_has_event{event},
       m_key{keys::unknown},
       m_mod{modifiers::none}{}
    
    keyboard(keys key,modifiers mod,bool reapeat,bool pressed)
     :  m_has_event{true},
        m_key{key},
        m_mod{mod},
        m_reapeat{reapeat},
        m_pressed{pressed}{}
  
    using keyboard_callback = std::function<void(keys,modifiers,bool)>;
    void on_pressed(keyboard_callback callback)
    {
        if(m_has_event && m_pressed)
        {
            callback(m_key,m_mod,m_reapeat);
        }
    }   
    void on_released(keyboard_callback callback)
    {
        if(m_has_event && !m_pressed)
        {
            callback(m_key,m_mod,m_reapeat);
        }
    }
private:
    bool      m_has_event;
    keys      m_key;
    modifiers m_mod;
    bool      m_reapeat;
    bool      m_pressed;
};
