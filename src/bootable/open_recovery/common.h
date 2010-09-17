/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef RECOVERY_COMMON_H
#define RECOVERY_COMMON_H

#include <stdio.h>

#define LOGE(...) ui_print("E:" __VA_ARGS__)
#define LOGW(...) fprintf(stderr, "W:" __VA_ARGS__)
#define LOGI(...) fprintf(stderr, "I:" __VA_ARGS__)

#if 0
#define LOGV(...) fprintf(stderr, "V:" __VA_ARGS__)
#define LOGD(...) fprintf(stderr, "D:" __VA_ARGS__)
#else
#define LOGV(...) do {} while (0)
#define LOGD(...) do {} while (0)
#endif

#define STRINGIFY(x) #x
#define EXPAND(x) STRINGIFY(x)

//Open Recovery Version
#define OPEN_RECOVERY_VERSION_BASE "1.42"

//phone versions
#if OPEN_RCVR_SHOLS

#define OPEN_RECOVERY_PHONE "MILESTONE"
#define OPEN_RECOVERY_PHONE_SWITCH "SHOLS"
#define OPEN_RECOVERY_NAVIG "Use d-pad to highlight; center to select."
#define PHONE_SHELL "/sbin/bash"
#define OPEN_RECOVERY_HAVE_CONSOLE 1
#define HAVE_CUST 1

#elif OPEN_RCVR_STCU

#define OPEN_RECOVERY_PHONE "SHOLES TABLET"
#define OPEN_RECOVERY_PHONE_SWITCH "STCU"
#define OPEN_RECOVERY_NAVIG "VolUp/VolDn to move focus;"
#define OPEN_RECOVERY_NAVIG2 "Camera to select."
#define PHONE_SHELL "/sbin/bash"
#define OPEN_RECOVERY_HAVE_CONSOLE 0
#define HAVE_CUST 0

#elif OPEN_RCVR_TITA

#define OPEN_RECOVERY_PHONE "TITANIUM"
#define OPEN_RECOVERY_PHONE_SWITCH "TITA"
#define OPEN_RECOVERY_NAVIG "Use volume key to highlight; top-left key to select."
#define PHONE_SHELL "/sbin/bash"
#define HAVE_CUST 1
#define OPEN_RECOVERY_HAVE_CONSOLE 0

#else

#error "No phone defined."

#endif

#if OPEN_RCVR_VERSION_LITE
#define OPEN_RECOVERY_VERSION OPEN_RECOVERY_VERSION_BASE" Lite"
#else
#define OPEN_RECOVERY_VERSION OPEN_RECOVERY_VERSION_BASE
#endif

#define MAX_LINE_LENGTH	4096
#define MAX_ARGS 100
#define ARGC_NUM	20



// Initialize the graphics system.
void ui_init();

// Use KEY_* codes from <linux/input.h> or KEY_DREAM_* from "minui/minui.h".
int ui_get_key();							// returns keycode if a key event is pending
int ui_wait_key();            // waits for a key/button press, returns the code
int ui_key_pressed(int key);  // returns >0 if the code is currently pressed
int ui_text_visible();        // returns >0 if text log is currently visible
void ui_clear_key_queue();

// Write a message to the on-screen log shown with Alt-L (also to stderr).
// The screen is small, and users may need to report these messages to support,
// so keep the output short and not too cryptic.
void ui_print(const char *fmt, ...);
void ui_print_raw(const char *buf);

// Display some header text followed by a menu of items, which appears
// at the top of the screen (in place of any scrolling ui_print()
// output, if necessary).
void ui_start_menu(char** headers, char** items, int title_length, int start_sel);
// Set the menu highlight to the given index, and return it (capped to
// the range [0..numitems).
int ui_menu_select(int sel);
// End menu mode, resetting the text overlay so that ui_print()
// statements will be displayed.
void ui_end_menu();
//Resets the menu
void ui_reset_menu();

//file with properties for ui
#define PROPERTY_FILE "/res/ui.prop"

// Set the icon (normally the only thing visible besides the progress bar).
enum {
  BACKGROUND_ICON_NONE,
  BACKGROUND_ICON_INSTALLING,
  BACKGROUND_ICON_ERROR,
  BACKGROUND_ICON_FIRMWARE_INSTALLING,
  BACKGROUND_ICON_FIRMWARE_ERROR,
  NUM_BACKGROUND_ICONS
};
void ui_set_background(int icon);

// Get a malloc'd copy of the screen image showing (only) the specified icon.
// Also returns the width, height, and bits per pixel of the returned image.
// TODO: Use some sort of "struct Bitmap" here instead of all these variables?
char *ui_copy_image(int icon, int *width, int *height, int *bpp);

// Show a progress bar and define the scope of the next operation:
//   portion - fraction of the progress bar the next operation will use
//   seconds - expected time interval (progress bar moves at this minimum rate)
void ui_show_progress(float portion, int seconds);
void ui_set_progress(float fraction);  // 0.0 - 1.0 within the defined scope

// Default allocation of progress bar segments to operations
static const int VERIFICATION_PROGRESS_TIME = 60;
static const float VERIFICATION_PROGRESS_FRACTION = 0.25;
static const float DEFAULT_FILES_PROGRESS_FRACTION = 0.4;
static const float DEFAULT_IMAGE_PROGRESS_FRACTION = 0.1;

// Show a rotating "barberpole" for ongoing operations.  Updates automatically.
void ui_show_indeterminate_progress();

// Hide and reset the progress bar.
void ui_reset_progress();

//returns the number of columns for menu / script
int ui_get_num_columns();

//LED functions
void ui_led_toggle(int state);
void ui_led_blink(int once);

//Shows interactive menu
int show_interactive_menu(char** headers, char** items);

/****************************************************************************************
 * Console functions
 ***************************************************************************************/

#ifdef OPEN_RECOVERY_HAVE_CONSOLE

//shows the console
void ui_console_begin();

//ends the console
void ui_console_end();

//prevents the console from redrawing until the end update is called
void ui_console_begin_update();

//ends the update and refreshes the screen
void ui_console_end_update();

//returns the number of rows on the console
int ui_console_get_num_rows();

//returns the number of columns on the console
int ui_console_get_num_columns();

//returns console width in pixels
int ui_console_get_width();

//returns console height in pixels
int ui_console_get_height();

//scrolls up in the console
void ui_console_scroll_up(int num_rows);

//scrolls down in the console
void ui_console_scroll_down(int num_rows);

enum {
  CONSOLE_HEADER_COLOR,
  CONSOLE_DEFAULT_BACKGROUND_COLOR,
  CONSOLE_DEFAULT_FRONT_COLOR  
};

//get system console color
void ui_console_get_system_front_color(int which, unsigned char* r, unsigned char* g, unsigned char* b);

//set system console color
void ui_console_set_system_front_color(int which);

//gets the current console color
void ui_console_get_front_color(unsigned char* r, unsigned char* g, unsigned char* b);

//sets the current console color
void ui_console_set_front_color(unsigned char r, unsigned char g, unsigned char b);

//prints to console
void ui_console_print(const char *text);

#endif // OPEN_RECOVERY_HAVE_CONSOLE

#endif  // RECOVERY_COMMON_H
