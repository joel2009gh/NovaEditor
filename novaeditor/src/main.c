#include "editor.h"
#include "terminal.h"
#include "input.h"
#include "render.h"
#include "buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include "backup.h"
int main(int argc, char *argv[]) {
    enableRawMode();
    initEditor();
    if (argc >= 2) {
        if (argc >= 3 && strcmp(argv[2], "--restore") == 0) {
            editorOpen(argv[1]);
            editorRestoreBackup(argv[1]);
        } else {
            editorOpen(argv[1]);
        }
    }
    editorSetStatusMessage("HELP: Ctrl-S = save | Ctrl-Q = quit | Ctrl-F = find");
    while (1) {
        editorRefreshScreen();
        editorProcessKeypress();
    }
    return 0;
}


