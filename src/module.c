// gtklock
// Copyright (c) 2022 Jovan Lanik

// Module support

#include "module.h"

static void (*on_activation)(struct GtkLock *gtklock) = NULL;
static void (*on_output_change)(struct GtkLock *gtklock) = NULL;
static void (*on_focus_change)(struct GtkLock *gtklock, struct Window *win, struct Window *old) = NULL;
static void (*on_window_empty)(struct GtkLock *gtklock, struct Window *ctx) = NULL;
static void (*on_body_empty)(struct GtkLock *gtklock, struct Window *ctx) = NULL;
static void (*on_idle_hide)(struct GtkLock *gtklock) = NULL;
static void (*on_idle_show)(struct GtkLock *gtklock) = NULL;

GModule *module_load(const char *name) {
	if(g_module_supported() == FALSE) return NULL;

	GError *err = NULL;
	GModule *module = g_module_open_full(name, 0, &err);
	if(module == NULL) {
		g_warning("Module loading failed: %s", err->message);
		g_error_free(err);
		return NULL;
	}

	g_module_symbol(module, "on_activation", (gpointer *)&on_activation);
	g_module_symbol(module, "on_output_change", (gpointer *)&on_output_change);
	g_module_symbol(module, "on_focus_change", (gpointer *)&on_focus_change);
	g_module_symbol(module, "on_window_empty", (gpointer *)&on_window_empty);
	g_module_symbol(module, "on_body_empty", (gpointer *)&on_body_empty);
	g_module_symbol(module, "on_idle_hide",  (gpointer *)&on_idle_hide);
	g_module_symbol(module, "on_idle_show",  (gpointer *)&on_idle_show);
	return module;
}

void module_on_activation(struct GtkLock *gtklock) {
	if(on_activation != NULL) on_activation(gtklock);
}

void module_on_output_change(struct GtkLock *gtklock) {
	if(on_output_change != NULL) on_output_change(gtklock);
}

void module_on_focus_change(struct GtkLock *gtklock, struct Window *win, struct Window *old) {
	if(on_focus_change != NULL) on_focus_change(gtklock, win, old);
}

void module_on_window_empty(struct GtkLock *gtklock, struct Window *ctx) {
	if(on_window_empty != NULL) on_window_empty(gtklock, ctx);
}

void module_on_body_empty(struct GtkLock *gtklock, struct Window *ctx) {
	if(on_body_empty != NULL) on_body_empty(gtklock, ctx);
}

void module_on_idle_hide(struct GtkLock *gtklock) {
	if(on_idle_hide != NULL) on_idle_hide(gtklock);
}

void module_on_idle_show(struct GtkLock *gtklock) {
	if(on_idle_show != NULL) on_idle_show(gtklock);
}

