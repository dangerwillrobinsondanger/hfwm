/*
 * Copyright 2014-2017 Katherine Flavel
 *
 * See LICENCE for the full copyright terms.
 */

#ifndef FRAME_H
#define FRAME_H

struct client;
struct geom;

#define FRAME_MARGIN  13
#define FRAME_BORDER  7
#define FRAME_SPACING 5

#define FRAME_MIN_WIDTH  30
#define FRAME_MIN_HEIGHT 30

/* for XClassHint */
#define FRAME_NAME  "hfwm"
#define FRAME_CLASS "Frame"

enum rel {
	REL_SIBLING,
	REL_LINEAGE
};

enum frame_type {
	FRAME_BRANCH,
	FRAME_LEAF
};

struct frame {
	struct frame *parent; /* pointer up */
	struct frame *prev;   /* list of sibling frames */
	struct frame *next;   /* list of sibling frames */

	enum layout layout;   /* layout for .u.children or .u.window list */
	struct geom geom;

	Window win;

	/* only for FRAME_LEAF */
	struct client *current_client;

	enum frame_type type;
	union {
		struct frame *children; /* list of zero or more children by .prev/.next */
		struct client *clients; /* list of managed client windows in this frame */
	} u;
};

enum rel
rel_lookup(const char *s);

struct frame *
frame_top(void);

struct frame *
frame_create_leaf(const struct geom *geom, struct client *clients);

struct frame *
frame_branch(struct frame *p, enum layout layout, enum order order);

void
frame_cat(struct frame **head, struct frame **tail);

struct frame *
frame_merge(struct frame *old, enum layout layout, enum order order);

struct frame *
frame_focus(struct frame *curr, enum rel rel, enum order order);

int
frame_redistribute(struct frame *p, enum layout layout, enum order order, unsigned n);

struct frame *
frame_find_win(const struct frame *top, Window win);

struct frame *
frame_find_client(const struct frame *top, Window win);

const char *
frame_type(const struct frame *p);

#endif

