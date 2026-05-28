
 /**
  bs_window.h
  Window and system functions
  */

#ifndef BS_WINDOW_H
#define BS_WINDOW_H

#include <bs_types.h>

#define BS_SET_BIT(array, index)     ((array)[(index) / 8] |=  (1 << ((index) % 8)))
#define BS_CLEAR_BIT(array, index)   ((array)[(index) / 8] &= ~(1 << ((index) % 8)))
#define BS_GET_BIT(array, index)     (((array)[(index) / 8] >> ((index) % 8)) & 1)
#define BS_WRITE_BIT(array, index, value) \
    do { if (value) BS_SET_BIT(array, index); else BS_CLEAR_BIT(array, index); } while (0)

	BSAPI bs_Window* bs_wnd();
	BSAPI bs_IO* bs_io();



  /*==============================================================================
   * System
   *============================================================================*/

   /**
    @returns Time zone bias, ex: 2 if UTC+2
    */
	BSAPI int 
	bs_timeZoneBias();

   /**
    @returns Current date and time
    */
	BSAPI bs_DateTime
	bs_dateTime();

   /**
    @param date_time
	@returns Total number of seconds between the given date time and 1970-01-01
    */
	BSAPI bs_I64
	bs_totalSeconds(
		const bs_DateTime* date_time);

   /**
    @param a
	@param b
	@returns true if a > b, otherwise false
    */
	BSAPI bool
	bs_isLaterThan(
		const bs_DateTime* a,
		const bs_DateTime* b);

   /**
    @returns Cursor position in pixels
    */
	BSAPI bs_vec2 
	bs_cursorPosition();

	BSAPI bs_ivec2 
	bs_getWindowPosition();
	BSAPI bs_vec2 bs_screenCursorPosition();

	BSAPI void bs_setCursorPosition(int x, int y);

	BSAPI void bs_lockCursorPosition(bool value);
	BSAPI void bs_disableUserInputs(bool value);

   /**
    @returns true if the middle mouse button is currently being held down, otherwise false
    */
	BSAPI bool bs_middleClick();

   /**
	@returns true if the middle mouse button was clicked once, otherwise false
	*/
	BSAPI bool bs_middleClickOnce();

		/**
		 @returns true if the middle mouse button was released once, otherwise false
		 */
	BSAPI bool bs_middleClickUpOnce();

		/**
		 @returns true if the left mouse button is currently being held down, otherwise false
		 */
	BSAPI bool bs_leftClick();

		/**
		 @returns true if the right mouse button is currently being held down, otherwise false
		 */
	BSAPI bool bs_rightClick();

		/**
		 @returns true if the right mouse button was clicked once, otherwise false
		 */
	BSAPI bool bs_rightClickOnce();

		/**
		 @returns true if the left mouse button was clicked once, otherwise false
		 */
	BSAPI bool bs_leftClickOnce();

		/**
		 @returns true if the right mouse button was released once, otherwise false
		 */
	BSAPI bool bs_rightClickUpOnce();

		/**
		 @returns true if the left mouse button was released once, otherwise false
		 */
	BSAPI bool bs_leftClickUpOnce();

   /**
    @param code - Key code, prefixed with BS_KEY_...
	@returns true if the key is currently being held down, otherwise false
    */
	BSAPI bool 
	bs_keyDown(
		bs_U32 code);

	BSAPI bool bs_keyHeld(bs_U32 code);

   /**
    @param code - Key code, prefixed with BS_KEY_...
	@returns true if the key was pressed this frame but not the last frame, otherwise false
    */
	BSAPI bool 
	bs_keyDownOnce(
		bs_U32 code);

   /**
    @param code - Key code, prefixed with BS_KEY_...
    @returns true if the key was not pressed this frame but was pressed the last frame, otherwise false
    */
	BSAPI bool 
	bs_keyUpOnce(
		bs_U32 code);


	// todo docs
	BSAPI bool 
	bs_charDown(
		unsigned char c);

	BSAPI bool 
	bs_charDownOnce(
		unsigned char c);

	BSAPI bool 
	bs_charUpOnce(
		unsigned char c);

	BSAPI int bs_scroll();


  /*==============================================================================
   * Window
   *============================================================================*/

   /**
    Resize the window
	@param width
	@param height
    */
	BSAPI void
	bs_resize(
		bs_U32 width, 
		bs_U32 height);

	BSAPI bs_ivec2
	bs_screenDimensions();

	BSAPI void 
	bs_moveWindow(
		int x, int y);

   /**
    Create a window
    @param width
    @param height
	@param title
	@param ... - List of window icon paths, ended with NULL
	*/
	BSAPI void
	bs_window(
		bs_U32 width,
		bs_U32 height,
		const char* title,
		...);

   /**
    Start the rendering loop
	@param tick - Pointer to a parameterless void function that will be called every frame, or NULL
	@param fixed_tick - Pointer to a parameterless void function that will be called at a fixed timestep, or NULL
    */
	BSAPI void
	bs_tick(
		bs_Callback tick, 
		bs_Callback fixed_tick);

   /**
    Close the window and end the rendering loop after the current frame is done
    */
	BSAPI void 
	bs_exit();

	BSAPI void 
	bs_setCursor(
		bs_CursorIcon type);

	BSAPI void 
	bs_maximize();

	BSAPI void 
	bs_minimize();

   /**
    @returns Difference in time (seconds) between current and last frame, returns a fixed timestemp if it is called in fixed_tick
    */
	BSAPI double 
	bs_deltaTime();

   /**
    Pauses or resumes the fixed loop
    */
	BSAPI void 
	bs_pause();

   /**
    Advances a frame
	@throws BSX_GENERAL - Application is not paused
    */
	BSAPI void
	bs_advance();

   /**
    @returns Total elapsed time in seconds
    */
	BSAPI double 
	bs_elapsedTime();

   /**
    @returns Window resolution in pixels
    */
	BSAPI bs_ivec2 
	bs_resolution();
	BSAPI bs_ivec2 bs_queryResolution(); // todo docs

   /**
    Set the window title
	@param title - Title format
	@param ... - Optional format values
    */
	BSAPI void 
	bs_title(
		const char* title, ...);

	BSAPI bool bs_inFixedTick();

	BSAPI bs_Timer bs_timer();

	BSAPI void bs_checkTimer(bs_Timer* timer);



  /*==============================================================================
   * Macros
   *============================================================================*/

#define BS_LEFT_MOUSE_BUTTON 0x01
#define BS_RIGHT_MOUSE_BUTTON 0x02
#define BS_CTRL_BRK_PRCS 0x03
#define BS_MID_MOUSE_BUTTON 0x04
#define BS_THUMB_FORWARD 0x05
#define BS_THUMB_BACK 0x06
#define BS_KEY_BACKSPACE 0x08
#define BS_KEY_TAB 0x09
#define BS_CLEAR 0x0C
#define BS_KEY_ENTER 0x0D
#define BS_KEY_LEFT_SHIFT 0x10
#define BS_KEY_LEFT_CONTROL 0x11
#define BS_KEY_ALT 0x12
#define BS_PAUSE 0x13
#define BS_CAPSLOCK 0x14
#define BS_KANA 0x15
#define BS_HANGEUL 0x15
#define BS_HANGUL 0x15
#define BS_JUNJU 0x17
#define BS_FINAL 0x18
#define BS_HANJA 0x19
#define BS_KANJI 0x19
#define BS_KEY_ESCAPE 0x1B
#define BS_CONVERT 0x1C
#define BS_NONCONVERT 0x1D
#define BS_ACCEPT 0x1E
#define BS_MODECHANGE 0x1F
#define BS_KEY_SPACE 0x20
#define BS_KEY_PAGEUP 0x21
#define BS_KEY_PAGEDOWN 0x22
#define BS_KEY_END 0x23
#define BS_KEY_HOME 0x24
#define BS_KEY_LEFT 0x25
#define BS_KEY_UP 0x26
#define BS_KEY_RIGHT 0x27
#define BS_KEY_DOWN 0x28
#define BS_KEY_SELECT 0x29
#define BS_KEY_PRINT 0x2A
#define BS_KEY_EXECUTE 0x2B
#define BS_KEY_PRINT_SCREEN 0x2C
#define BS_KEY_INSERT 0x2D
#define BS_KEY_DELETE 0x2E
#define BS_HELP 0x2F
#define BS_KEY_0 0x30
#define BS_KEY_1 0x31
#define BS_KEY_2 0x32
#define BS_KEY_3 0x33
#define BS_KEY_4 0x34
#define BS_KEY_5 0x35
#define BS_KEY_6 0x36
#define BS_KEY_7 0x37
#define BS_KEY_8 0x38
#define BS_KEY_9 0x39
#define BS_KEY_A 0x41
#define BS_KEY_B 0x42
#define BS_KEY_C 0x43
#define BS_KEY_D 0x44
#define BS_KEY_E 0x45
#define BS_KEY_F 0x46
#define BS_KEY_G 0x47
#define BS_KEY_H 0x48
#define BS_KEY_I 0x49
#define BS_KEY_J 0x4A
#define BS_KEY_K 0x4B
#define BS_KEY_L 0x4C
#define BS_KEY_M 0x4D
#define BS_KEY_N 0x4E
#define BS_KEY_O 0x4F
#define BS_KEY_P 0x50
#define BS_KEY_Q 0x51
#define BS_KEY_R 0x52
#define BS_KEY_S 0x53
#define BS_KEY_T 0x54
#define BS_KEY_U 0x55
#define BS_KEY_V 0x56
#define BS_KEY_W 0x57
#define BS_KEY_X 0x58
#define BS_KEY_Y 0x59
#define BS_KEY_Z 0x5A
#define BS_LEFT_WIN 0x5B
#define BS_RIGHT_WIN 0x5C
#define BS_APPS 0x5D
#define BS_SLEEP 0x5F
#define BS_NUMPAD0 0x60
#define BS_NUMPAD1 0x61
#define BS_NUMPAD2 0x62
#define BS_NUMPAD3 0x63
#define BS_NUMPAD4 0x64
#define BS_NUMPAD5 0x65
#define BS_NUMPAD6 0x66
#define BS_NUMPAD7 0x67
#define BS_NUMPAD8 0x68
#define BS_NUMPAD9 0x69
#define BS_MULTIPLY 0x6A
#define BS_ADD 0x6B
#define BS_SEPARATOR 0x6C
#define BS_SUBTRACT 0x6D
#define BS_DECIMAL 0x6E
#define BS_DIVIDE 0x6F
#define BS_KEY_F1 0x70
#define BS_KEY_F2 0x71
#define BS_KEY_F3 0x72
#define BS_KEY_F4 0x73
#define BS_KEY_F5 0x74
#define BS_KEY_F6 0x75
#define BS_KEY_F7 0x76
#define BS_KEY_F8 0x77
#define BS_KEY_F9 0x78
#define BS_KEY_F10 0x79
#define BS_KEY_F11 0x7A
#define BS_KEY_F12 0x7B
#define BS_KEY_F13 0x7C
#define BS_KEY_F14 0x7D
#define BS_KEY_F15 0x7E
#define BS_KEY_F16 0x7F
#define BS_KEY_F17 0x80
#define BS_KEY_F18 0x81
#define BS_KEY_F19 0x82
#define BS_KEY_F20 0x83
#define BS_KEY_F21 0x84
#define BS_KEY_F22 0x85
#define BS_KEY_F23 0x86
#define BS_KEY_F24 0x87
#define BS_NAVIGATION_VIEW 0x88
#define BS_NAVIGATION_MENU 0x89
#define BS_NAVIGATION_UP 0x8A
#define BS_NAVIGATION_DOWN 0x8B
#define BS_NAVIGATION_LEFT 0x8C
#define BS_NAVIGATION_RIGHT 0x8D
#define BS_NAVIGATION_ACCEPT 0x8E
#define BS_NAVIGATION_CANCEL 0x8F
#define BS_NUMLOCK 0x90
#define BS_SCROLLLOCK 0x91
#define BS_NUMPAD_EQUAL 0x92
#define BS_FJ_JISHO 0x92
#define BS_FJ_MASSHOU 0x93
#define BS_FJ_TOUROKU 0x94
#define BS_FJ_LOYA 0x95
#define BS_FJ_ROYA 0x96
#define BS_KEY_RIGHT_SHIFT 0xA1
#define BS_KEY_LEFT_CTRL 0xA2
#define BS_KEY_RIGHT_CTRL 0xA3
#define BS_KEY_LEFT_MENU 0xA4
#define BS_KEY_RIGHT_MENU 0xA5
#define BS_BROWSER_BACK 0xA6
#define BS_BROWSER_FORWARD 0xA7
#define BS_BROWSER_REFRESH 0xA8
#define BS_BROWSER_STOP 0xA9
#define BS_BROWSER_SEARCH 0xAA
#define BS_BROWSER_FAVORITES 0xAB
#define BS_BROWSER_HOME 0xAC
#define BS_VOLUME_MUTE 0xAD
#define BS_VOLUME_DOWN 0xAE
#define BS_VOLUME_UP 0xAF
#define BS_NEXT_TRACK 0xB0
#define BS_PREV_TRACK 0xB1
#define BS_STOP 0xB2
#define BS_PLAY_PAUSE 0xB3
#define BS_MAIL 0xB4
#define BS_MEDIA_SELECT 0xB5
#define BS_APP1 0xB6

#endif