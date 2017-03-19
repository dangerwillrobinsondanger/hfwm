/*
 * Copyright 2014-2017 Katherine Flavel
 *
 * See LICENCE for the full copyright terms.
 */

#ifndef GEOM_H
#define GEOM_H

struct geom {
	unsigned x;
	unsigned y;
	unsigned w;
	unsigned h;
};

struct ratio {
	double x;
	double y;
	double w;
	double h;
};

int
geom_inset(struct geom *in, const struct geom *g,
	unsigned int bw, int spacing);

void
geom_ratio(struct ratio *r, const struct geom *old, const struct geom *new);

void
geom_scale(struct geom *g, const struct ratio *r);

int
geom_move(struct geom *g, enum axis axis, int n);

#endif

