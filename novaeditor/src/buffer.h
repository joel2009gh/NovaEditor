#ifndef BUFFER_H
#define BUFFER_H

#include "editor.h"

int editorRowCxToRx(erow *row, int cx);
int editorRowRxToCx(erow *row, int rx);
void editorUpdateRow(erow *row);
void editorInsertRow(int at, char *s, size_t len);
void editorFreeRow(erow *row);
void editorDelRow(int at);
void editorRowInsertChar(erow *row, int at, int c);
void editorRowAppendString(erow *row, char *s, size_t len);
void editorRowDelChar(erow *row, int at);
void editorInsertChar(int c);
void editorInsertNewline();
void editorDelChar();
char *editorRowsToString(int *buflen);
void editorOpen(char *filename);
void editorSave();
void editorFind();

#endif

