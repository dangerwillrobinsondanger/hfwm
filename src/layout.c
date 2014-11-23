#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "layout.h"

enum layout
layout_lookup(const char *s)
{
	size_t i;

	struct {
		const char *name;
		enum layout layout;
	} a[] = {
		{ "horiz", LAYOUT_HORIZ },
		{ "vert",  LAYOUT_VERT  },
		{ "max",   LAYOUT_MAX   }
	};

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		if (0 == strcmp(a[i].name, s)) {
			return a[i].layout;
		}
	}

	return -1;
}

void
layout_split(enum layout layout, enum order order, struct geom *new, struct geom *old)
{
	unsigned int orig;

	assert(new != NULL);
	assert(old != NULL);

	switch (layout) {
	case LAYOUT_HORIZ:
		new->w = (orig = old->w, orig - (old->w /= 2));
		new->h = old->h;
		new->x = old->x;
		new->y = old->y;

		switch (order) {
		case ORDER_NEXT: new->x += new->w; break;
		case ORDER_PREV: old->x += new->w; break;
		}
		break;

	case LAYOUT_VERT:
		new->w = old->w;
		new->h = (orig = old->h, orig - (old->h /= 2));
		new->x = old->x;
		new->y = old->y;

		switch (order) {
		case ORDER_NEXT: new->y += new->h; break;
		case ORDER_PREV: old->y += new->h; break;
		}
		break;

	case LAYOUT_MAX:
		*new = *old;
		break;
	}
}

