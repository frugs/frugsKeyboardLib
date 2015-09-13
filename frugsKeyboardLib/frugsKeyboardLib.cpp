// frugsKeyboardLib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

LRESULT CALLBACK remapFrugsKeys(
	_In_  int nCode,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
) {
	const BYTE RSHIFT_SCANCODE = 0x36;
	const BYTE RALT_SCANCODE = 0x38;

	DWORD* vkCode = &(((KBDLLHOOKSTRUCT*)lParam)->vkCode);
	DWORD KBDLLHOOKSTRUCT_keyState = ((KBDLLHOOKSTRUCT*)lParam)->flags & LLKHF_UP;
	DWORD keybd_event_keyState = KBDLLHOOKSTRUCT_keyState >> 6;
	
	LRESULT result = 1;
	if (*vkCode == VK_APPS) {
		keybd_event(VK_RSHIFT, RSHIFT_SCANCODE, keybd_event_keyState, NULL);
	} else if (*vkCode == VK_RWIN) {
		keybd_event(VK_RMENU, RALT_SCANCODE, keybd_event_keyState, NULL);
	} else {
		result = CallNextHookEx(NULL, nCode, wParam, lParam);
	}

	return result;
}
