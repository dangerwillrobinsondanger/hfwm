#ifndef FRAME_H
#define FRAME_H

struct window;
struct geom;

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

	enum frame_type type;
	union {
		struct frame *children; /* list of zero or more children by .prev/.next */
		struct window *windows; /* list of windows in this frame */
	} u;
};

extern struct frame *current_frame;

struct frame *
frame_split(struct frame *old, enum layout layout, enum order order);

struct frame *
frame_create_leaf(struct frame *parent, const struct geom *g,
	struct window *windows);

struct frame *
frame_branch_leaf(struct frame *old, enum layout layout, enum order order,
	struct window *windows);

struct frame *
frame_focus(struct frame *curr, enum rel rel, int delta);

#endif

