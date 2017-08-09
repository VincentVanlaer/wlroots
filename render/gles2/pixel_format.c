#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include "render/gles2.h"

// Adapted from weston
struct pixel_format formats[] = {
	{
		.wl_format = WL_SHM_FORMAT_ARGB8888,
		.egl_format = EGL_TEXTURE_RGBA,
		.depth = 32,
		.bpp = 32,
		.gl_format = GL_BGRA_EXT,
		.gl_type = GL_UNSIGNED_BYTE,
		.shader = &shaders.rgba
	},
	{
		.wl_format = WL_SHM_FORMAT_XRGB8888,
		.egl_format = EGL_TEXTURE_RGB,
		.depth = 24,
		.bpp = 32,
		.gl_format = GL_BGRA_EXT,
		.gl_type = GL_UNSIGNED_BYTE,
		.shader = &shaders.rgbx
	},
	{
		.wl_format = WL_SHM_FORMAT_XBGR8888,
		.egl_format = EGL_TEXTURE_RGB,
		.gl_format = GL_RGBA,
		.gl_type = GL_UNSIGNED_BYTE,
		.shader = &shaders.rgbx
	},
	{
		.wl_format = WL_SHM_FORMAT_ABGR8888,
		.egl_format = EGL_TEXTURE_RGBA,
		.gl_format = GL_RGBA,
		.gl_type = GL_UNSIGNED_BYTE,
		.shader = &shaders.rgba
	},
};
// TODO: more pixel formats

const struct pixel_format *gl_format_for_wl_format(enum wl_shm_format fmt) {
	for (size_t i = 0; i < sizeof(formats) / sizeof(*formats); ++i) {
		if (formats[i].wl_format == fmt) {
			return &formats[i];
		}
	}
	return NULL;
}

const struct pixel_format *gl_format_for_egl_format(uint32_t fmt) {
	for (size_t i = 0; i < sizeof(formats) / sizeof(*formats); ++i) {
		if (formats[i].egl_format == fmt) {
			return &formats[i];
		}
	}
	return NULL;
}
