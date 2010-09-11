#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "keyboard.h"
#include "conf.h"

typedef struct {
    short grp;
    short hackkey;
    long canonkey;
} KeyMap;


static long kbd_new_state[3];
static long kbd_prev_state[3];
static long kbd_mod_state[3];
static KeyMap keymap[];
static long last_kbd_key = 0;
static int usb_power=0;
static int remote_key, remote_count;
static int shoot_counter=0;
#define DELAY_TIMEOUT 10000

//#define KEYS_MASK0 (0x00002319)
#define KEYS_MASK0 (0x0000090F)
#define KEYS_MASK1 (0x000000F0)
//#define KEYS_MASK2 (0x0FFF)
#define KEYS_MASK2 (0x00000000)
static long alt_mode_key_mask = 0x00000008;    // ToDo: KEY_LEFT, we have no print key...

#define SD_READONLY_FLAG (0x20000)

#define USB_MASK (0x40000)

volatile int jogdial_stopped=0;

void kbd_fetch_data(long*);

long __attribute__((naked)) wrap_kbd_p1_f();


static void __attribute__((noinline)) mykbd_task_proceed() {
    while (physw_run) {
        _SleepTask(10);

        if (wrap_kbd_p1_f() == 1) { // autorepeat ?
            _kbd_p2_f();
        }
    }
}


// no stack manipulation needed here, since we create the task directly
void __attribute__((naked,noinline)) mykbd_task() {
    mykbd_task_proceed();
    _ExitTask();
}


// ROM:FF83484C, like SX110
long __attribute__((naked,noinline)) wrap_kbd_p1_f() {
    asm volatile(
                "STMFD   SP!, {R1-R5,LR}\n"
                "MOV     R4, #0\n"
                "BL      _kbd_read_keys\n"       // original function
                "BL      my_kbd_read_keys\n"     // +
                "B       _kbd_p1_f_cont\n"       // continue at ROM:FF834858
    );
    return 0; // shut up the compiler
}


// like SX110
void my_kbd_read_keys() {
    kbd_prev_state[0] = kbd_new_state[0];
    kbd_prev_state[1] = kbd_new_state[1];
    kbd_prev_state[2] = kbd_new_state[2];

    // The following three lines replace the call to kbd_fetch_data()
    kbd_new_state[0] = physw_status[0];
    kbd_new_state[1] = physw_status[1];
    kbd_new_state[2] = physw_status[2];

    if (kbd_process() == 0){
        // we read keyboard state with _kbd_read_keys()

        // override the alt mode key
        physw_status[0] |= alt_mode_key_mask;
            jogdial_stopped=0;
    } else {
        // override keys
        physw_status[0] = (kbd_new_state[0] | KEYS_MASK0) & (~KEYS_MASK0 | kbd_mod_state[0]);
        physw_status[1] = (kbd_new_state[1] | KEYS_MASK1) & (~KEYS_MASK1 | kbd_mod_state[1]);
        physw_status[2] = (kbd_new_state[2] | KEYS_MASK2) & (~KEYS_MASK2 | kbd_mod_state[2]);

        if ((jogdial_stopped==0) && !state_kbd_script_run){ jogdial_stopped=1; get_jogdial_direction(); }
        else if (jogdial_stopped && state_kbd_script_run) jogdial_stopped=0;
    }

    // SD-Card override READONLY flag for diskboot
    physw_status[2] = physw_status[2] & ~SD_READONLY_FLAG;
}

int get_usb_power(int edge) {
    int x;

    if (edge) return remote_key;
    x = usb_power;
    usb_power = 0;
    return x;
}


void kbd_key_press(long key) {
    int i;
    for (i=0;keymap[i].hackkey;i++){
        if (keymap[i].hackkey == key){
            kbd_mod_state[keymap[i].grp] &= ~keymap[i].canonkey;
            return;
        }
    }
}

void kbd_key_release(long key) {
    int i;
    for (i=0;keymap[i].hackkey;i++) {
        if (keymap[i].hackkey == key){
            kbd_mod_state[keymap[i].grp] |= keymap[i].canonkey;
            return;
        }
    }
}

void kbd_key_release_all() {
    kbd_mod_state[0] |= KEYS_MASK0;
    kbd_mod_state[1] |= KEYS_MASK1;
    kbd_mod_state[2] |= KEYS_MASK2;
}

long kbd_is_key_pressed(long key) {
    int i;
    for (i=0;keymap[i].hackkey;i++) {
        if (keymap[i].hackkey == key) {
            return ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0) ? 1:0;
        }
    }
    return 0;
}

long kbd_is_key_clicked(long key) {
    int i;
    for (i=0;keymap[i].hackkey;i++) {
        if (keymap[i].hackkey == key){
            return ((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) &&
                ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0);
        }
    }
    return 0;
}

long kbd_get_pressed_key() {
    int i;
    for (i=0;keymap[i].hackkey;i++) {
        if ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0) {
            return keymap[i].hackkey;
        }
    }
    return 0;
}

long kbd_get_clicked_key() {
    int i;
    for (i=0;keymap[i].hackkey;i++) {
        if (((kbd_prev_state[keymap[i].grp] & keymap[i].canonkey) != 0) && ((kbd_new_state[keymap[i].grp] & keymap[i].canonkey) == 0)) {
            return keymap[i].hackkey;
        }
    }
    return 0;
}

void kbd_reset_autoclicked_key() {
    last_kbd_key = 0;
}

long kbd_get_autoclicked_key() {
    static long last_kbd_time = 0, press_count = 0;
    register long key, t;

    key=kbd_get_clicked_key();
    if (key) {
        last_kbd_key = key;
        press_count = 0;
        last_kbd_time = get_tick_count();
        return key;
    } else {
        if (last_kbd_key && kbd_is_key_pressed(last_kbd_key)) {
            t = get_tick_count();
            if (t-last_kbd_time>((press_count)?175:500)) {
                ++press_count;
                last_kbd_time = t;
                return last_kbd_key;
            } else {
                return 0;
            }
        } else {
            last_kbd_key = 0;
            return 0;
        }
    }
}

#ifdef CAM_USE_ZOOM_FOR_MF
    long kbd_use_zoom_as_mf() {
        static long v;
        static long zoom_key_pressed = 0;

        if (kbd_is_key_pressed(KEY_ZOOM_IN) && (mode_get()&MODE_MASK) == MODE_REC) {
            get_property_case(PROPCASE_FOCUS_MODE, &v, 4);
            if (v) {
                kbd_key_release_all();
                kbd_key_press(KEY_RIGHT);
                zoom_key_pressed = KEY_ZOOM_IN;
                return 1;
            }
        } else {
            if (zoom_key_pressed==KEY_ZOOM_IN) {
                kbd_key_release(KEY_RIGHT);
                zoom_key_pressed = 0;
                return 1;
            }
        }
        if (kbd_is_key_pressed(KEY_ZOOM_OUT) && (mode_get()&MODE_MASK) == MODE_REC) {
            get_property_case(PROPCASE_FOCUS_MODE, &v, 4);
            if (v) {
                kbd_key_release_all();
                kbd_key_press(KEY_LEFT);
                zoom_key_pressed = KEY_ZOOM_OUT;
                return 1;
            }
        } else {
            if (zoom_key_pressed==KEY_ZOOM_OUT) {
                kbd_key_release(KEY_LEFT);
                zoom_key_pressed = 0;
                return 1;
            }
        }
        return 0;
    }
#endif

// Base values in Play Mode
// physw_status[0] = 0x800C91F      // 1
// physw_status[1] = 0xFFE          // 2 (Mode Switch: Auto)
// physw_status[2] = 0x400000       // 3
// Mode Switch:
// physw_status[1] 0x1 Auto
// physw_status[1] 0x0 Photo
// physw_status[1] 0x2 Video
static KeyMap keymap[] = {
    // tiny bug: key order matters. see kbd_get_pressed_key() for example
    { 0, KEY_UP         , 0x00000004 },
    { 0, KEY_DOWN       , 0x00000001 },
    { 0, KEY_LEFT       , 0x00000008 },
    { 0, KEY_RIGHT      , 0x00000002 },
    { 1, KEY_SET        , 0x00000040 },
    { 0, KEY_SHOOT_FULL , 0x00000800 },    // 0x800C01F ?!?
    { 0, KEY_SHOOT_HALF , 0x00000100 },    // 0x800C81F
    { 1, KEY_ZOOM_IN    , 0x00000010 },
    { 1, KEY_ZOOM_OUT   , 0x00000020 },
    { 1, KEY_MENU       , 0x00000080 },
    { 0, KEY_PRINT      , 0x00000008 },    // ToDo: workaround, camera has not print key, for now we use KEY_LEFT, otherwise conf.alt_mode_button must be defined in CHDK config
    //{ 1, KEY_PLAY        , 0x80000000 },  // SD990 play button
    { 0, 0, 0 }
};

// ToDo: find some way to use Key combination (for Example LEFT+SET) to enter ALT mode
void kbd_set_alt_mode_key_mask(long key) {
    int i;
    for (i=0; keymap[i].hackkey; ++i) {
        if (keymap[i].hackkey == key) {
            alt_mode_key_mask = keymap[i].canonkey;
            return;
        }
    }
}
