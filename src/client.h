#ifndef CLIENT_H
#define CLIENT_H

struct client {
	Window win;
	struct client *next;
};

void
client_cat(struct client **head, struct client **tail);

struct client *
client_find(const struct client *head, Window win);

struct client *
client_add(struct client **head, Window win);

void
client_remove(struct client **head, Window win);

#endif
