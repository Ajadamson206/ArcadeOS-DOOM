#include "doomkeys.h"
#include "m_argv.h"
#include "doomgeneric.h"

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <keyboard.h>
#include <graphics.h>

#define KEYQUEUE_SIZE 16

// Linear Frame Buffer
static volatile u8 *fb;
static screen_info frame_buffer_info;
static volatile uint32_t d_ticks;

static void addKeyToQueue(u16 keycode);

// Initialize the program, (Create Window, Framebuffer, etc)
void DG_Init() {
    d_ticks = 0;
    frame_buffer_info = get_screen_info();

    // Add Keyboard Hook
    kb_hook_add(addKeyToQueue);

    // Copy the framebuffer
    fb = (volatile u8 *)get_lfb();
}

// Frame is ready in DG_ScreenBuffer. Copy it to the screen
void DG_DrawFrame() {
    // Copy Line by Line
    for(u32 y = 0; y < DOOMGENERIC_RESY; y++) {
        // Get Row
        volatile u32* row = (volatile u32*)(fb + y * frame_buffer_info.framebuffer_pitch);        

        // RESX Matches OS Resolution
        memcopy((void *)row, (void *)DG_ScreenBuffer, DOOMGENERIC_RESX);
    }
}

// Sleep in milliseconds
void DG_SleepMs(uint32_t ms) {
    usleep(ms);
}

// Get the ticks passed since launch in milliseconds
uint32_t DG_GetTicksMs() {

    // (Seconds * 1000) + (usec / 1000)
    return d_ticks;
}

static u16 s_KeyQueue[KEYQUEUE_SIZE];
static unsigned int s_KeyQueueWriteIndex = 0;
static unsigned int s_KeyQueueReadIndex = 0;

static unsigned char convertToDoomKey(u16 key){
    unsigned char r_key = 0;
    switch (key) {
        case KEY_ENTER_PRESSED:
            r_key = KEY_ENTER;
            break;
        case KEY_ESC_PRESSED:
            r_key = KEY_ESCAPE;
            break;
        case KEY_ARROW_LEFT_PRESSED:
            r_key = KEY_LEFTARROW;
            break;
        case KEY_ARROW_RIGHT_PRESSED:
            r_key = KEY_RIGHTARROW;
            break;
        case KEY_ARROW_UP_PRESSED:
            r_key = KEY_UPARROW;
            break;
        case KEY_ARROW_DOWN_PRESSED:
            r_key = KEY_DOWNARROW;
            break;
        case KEY_L_CTRL_PRESSED:
        case KEY_R_CTRL_PRESSED:
            r_key = KEY_FIRE;
            break;
        case KEY_SPACE_PRESSED:
            r_key = KEY_USE;
            break;
        case KEY_L_SHIFT_PRESSED:
        case KEY_R_SHIFT_PRESSED:
            r_key = KEY_RSHIFT;
            break;
        case KEY_L_ALT_PRESSED:
        //case KEY_R_ALT:
            r_key = KEY_LALT;
            break;
        case KEY_F2_PRESSED:
            r_key = KEY_F2;
            break;
        case KEY_F3_PRESSED:
            r_key = KEY_F3;
            break;
        case KEY_F4_PRESSED:
            r_key = KEY_F4;
            break;
        case KEY_F5_PRESSED:
            r_key = KEY_F5;
            break;
        case KEY_F6_PRESSED:
            r_key = KEY_F6;
            break;
        case KEY_F7_PRESSED:
            r_key = KEY_F7;
            break;
        case KEY_F8_PRESSED:
            r_key = KEY_F8;
            break;
        case KEY_F9_PRESSED:
            r_key = KEY_F9;
            break;
        case KEY_F10_PRESSED:
            r_key = KEY_F10;
            break;
        case KEY_F11_PRESSED:
            r_key = KEY_F11;
            break;
        case KEY_EQUALS_PRESSED:
            r_key = KEY_EQUALS;
            break;
        case KEY_MINUS_PRESSED:
            r_key = KEY_MINUS;
            break;
        default:
            r_key = kb_to_ascii(key);
            break;
    }

    return r_key;
}

static void addKeyToQueue(u16 keycode) {
    unsigned char key = convertToDoomKey(keycode);
    if(key == 0x00 || key == 0xFF)
        return;

    u16 keyData = 0;
    if(key == KEY_RSHIFT)
        keyData = 1<<8 | key;
    else
        keyData = key;

	s_KeyQueue[s_KeyQueueWriteIndex] = keyData;
	s_KeyQueueWriteIndex++;
	s_KeyQueueWriteIndex %= KEYQUEUE_SIZE;
}

// Provide Keyboard Events
int DG_GetKey(int* pressed, unsigned char* doomKey) {
    if(s_KeyQueueReadIndex == s_KeyQueueWriteIndex) {
        return 0;
    }

    unsigned short keyData = s_KeyQueue[s_KeyQueueReadIndex];
    s_KeyQueueReadIndex++;
    s_KeyQueueReadIndex %= KEYQUEUE_SIZE;

    *pressed = keyData >> 8;
    *doomKey = keyData & 0xFF;

    return 1;
}

// Main Function to be called by 'kernel'
void doom_main(int argc, char **argv) {
    doomgeneric_Create(argc, argv);

    for (int i = 0; ; i++)
    {
        d_ticks++;
        doomgeneric_Tick();
    }
    

    kb_hook_remove();
    return 0;
}