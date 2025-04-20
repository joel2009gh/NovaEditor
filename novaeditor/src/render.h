#ifndef RENDER_H
#define RENDER_H

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define CTRL_KEY(k) ((k) & 0x1f)

struct abuf {
    char *b;
    int len;
};

#define ABUF_INIT {NULL, 0}

void abAppend(struct abuf *ab, const char *s, int len);
void abFree(struct abuf *ab);

void editorScroll();
void editorDrawRows(struct abuf *ab);
void editorDrawStatusBar(struct abuf *ab);
void editorDrawMessageBar(struct abuf *ab);
void editorRefreshScreen();

#endif

