/**
 * 2026
 * Avery Allison
 * headers for custom dwm functionality
 */

#pragma once

#define DWM_AUTOSTART               "$HOME/.dwm/dwm_autostart.sh"
#define DWM_AUTOSTART_BACKGROUND    "$HOME/.dwm/dwm_autostart_background.sh"

/*
 * make sure your chosen interpreter supports:
 *  - running a command string with the `-c` option
 *  - backgrounding a process with the `&` symbol
 */
#define DWM_AUTOSTART_INTERPRETER   "/usr/bin/sh"

/*
 * attempts to call autostart scripts from the following paths:
 *  - `DWM_AUTOSTART` (for tasks that must finish before dwm starts).
 *  - `DWM_AUTOSTART_BACKGROUND` (for tasks intended to run with dwm).
 * set the path to your preferred interpreter with `DWM_AUTOSTART_INTERPRETER`
 */
void autostart(void);
