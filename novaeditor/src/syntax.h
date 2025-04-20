#ifndef SYNTAX_H
#define SYNTAX_H

#include <stdlib.h>

// Forward declaration
struct erow;

#define HL_HIGHLIGHT_NUMBERS (1<<0)
#define HL_HIGHLIGHT_STRINGS (1<<1)

enum editorHighlight {
    HL_NORMAL = 0,
    HL_COMMENT,
    HL_MLCOMMENT,
    HL_KEYWORD1,
    HL_KEYWORD2,
    HL_STRING,
    HL_NUMBER,
    HL_MATCH
};

struct editorSyntax {
    char *filetype;
    char **filematch;
    char **keywords;
    char *singleline_comment_start;
    char *multiline_comment_start;
    char *multiline_comment_end;
    int flags;
};

void editorSelectSyntaxHighlight();
int editorSyntaxToColor(int hl);
void editorUpdateSyntax(struct erow *row);

#endif

