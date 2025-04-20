#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>
#include <dirent.h>
#include "editor.h"
void initBackupSystem() {
    char *home = getenv("HOME");
    if (home == NULL) {
        editorSetStatusMessage("Error: Could not get HOME directory");
        return;
    }
    int len = strlen(home) + 20;
    E.backup_path = malloc(len);
    snprintf(E.backup_path, len, "%s/.novaeditor_backups", home);
    struct stat st = {0};
    if (stat(E.backup_path, &st) == -1) {
        if (mkdir(E.backup_path, 0700) == -1) {
            editorSetStatusMessage("Error: Could not create backup directory");
            free(E.backup_path);
            E.backup_path = NULL;
            return;
        }
    }
}
void editorCreateBackup() {
    if (E.filename == NULL || E.backup_path == NULL) return;
    char *basename = strrchr(E.filename, '/');
    basename = basename ? basename + 1 : E.filename;
    time_t now = time(NULL);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y%m%d%H%M%S", localtime(&now));
    char *backup_file = malloc(strlen(E.backup_path) + strlen(basename) + strlen(timestamp) + 3);
    sprintf(backup_file, "%s/%s.%s", E.backup_path, basename, timestamp);
    FILE *fp = fopen(backup_file, "w");
    if (fp == NULL) {
        editorSetStatusMessage("Error: Could not create backup file");
        free(backup_file);
        return;
    }
    for (int i = 0; i < E.numrows; i++) {
        fwrite(E.row[i].chars, 1, E.row[i].size, fp);
        fwrite("\n", 1, 1, fp);
    }
    fclose(fp);
    free(backup_file);
    editorSetStatusMessage("Backup created");
}
char *findLatestBackup(const char *filename) {
    if (E.backup_path == NULL) return NULL;
    char *basename = strrchr(filename, '/');
    basename = basename ? basename + 1 : filename;
    DIR *dir = opendir(E.backup_path);
    if (dir == NULL) return NULL;
    struct dirent *entry;
    char *latest_backup = NULL;
    time_t latest_time = 0;
    int prefix_len = strlen(basename);
    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(entry->d_name, basename, prefix_len) == 0 && 
            entry->d_name[prefix_len] == '.') {
            char *timestamp_str = entry->d_name + prefix_len + 1;
            struct tm tm = {0};
            if (strptime(timestamp_str, "%Y%m%d%H%M%S", &tm) != NULL) {
                time_t backup_time = mktime(&tm);
                if (backup_time > latest_time) {
                    latest_time = backup_time;
                    free(latest_backup);
                    latest_backup = malloc(strlen(E.backup_path) + strlen(entry->d_name) + 2);
                    sprintf(latest_backup, "%s/%s", E.backup_path, entry->d_name);
                }
            }
        }
    }
    closedir(dir);
    return latest_backup;
}
void editorRestoreBackup(const char *filename) {
    char *backup_file = findLatestBackup(filename);
    if (backup_file == NULL) {
        editorSetStatusMessage("No backup found for %s", filename);
        return;
    }
    FILE *fp = fopen(backup_file, "r");
    if (fp == NULL) {
        editorSetStatusMessage("Error: Could not open backup file");
        free(backup_file);
        return;
    }
    while (E.numrows > 0) editorDelRow(E.numrows - 1);
    char *line = NULL;
    size_t linecap = 0;
    ssize_t linelen;
    while ((linelen = getline(&line, &linecap, fp)) > 0) {
        if (linelen > 0 && (line[linelen - 1] == '\n' || line[linelen - 1] == '\r'))
            linelen--;
        editorInsertRow(E.numrows, line, linelen);
    }
    free(line);
    fclose(fp);
    free(backup_file);
    E.dirty = 1;
    editorSetStatusMessage("Backup restored");
}
