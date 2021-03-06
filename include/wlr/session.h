#ifndef WLR_SESSION_H
#define WLR_SESSION_H

#include <stdbool.h>
#include <wayland-server.h>
#include <sys/types.h>

struct session_impl;

struct wlr_session {
	const struct session_impl *impl;
	/*
	 * Signal for when the session becomes active/inactive.
	 * It's called when we swap virtual terminal.
	 */
	struct wl_signal session_signal;
	bool active;

	int drm_fd;
	unsigned vtnr;
	char seat[8];
};

/*
 * Opens a session, taking control of the current virtual terminal.
 * This should not be called if another program is already in control
 * of the terminal (Xorg, another Wayland compositor, etc.).
 *
 * If logind support is not enabled, you must have CAP_SYS_ADMIN or be root.
 * It is safe to drop priviledges after this is called.
 *
 * Returns NULL on error.
 */
struct wlr_session *wlr_session_start(struct wl_display *disp);

/*
 * Closes a previously opened session and restores the virtual terminal.
 * You should call wlr_session_close_file on each files you opened
 * with wlr_session_open_file before you call this.
 */
void wlr_session_finish(struct wlr_session *session);

/*
 * Opens the file at path.
 * This can only be used to open DRM or evdev (input) devices.
 *
 * When the session becomes inactive:
 * - DRM files lose their DRM master status
 * - evdev files become invalid and should be closed
 *
 * Returns -errno on error.
 */
int wlr_session_open_file(struct wlr_session *session, const char *path);

/*
 * Closes a file previously opened with wlr_session_open_file.
 */
void wlr_session_close_file(struct wlr_session *session, int fd);

/*
 * Changes the virtual terminal.
 */
bool wlr_session_change_vt(struct wlr_session *session, unsigned vt);

#endif
