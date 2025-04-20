#ifndef BACKUP_H
#define BACKUP_H
void initBackupSystem();
void editorCreateBackup();
char *findLatestBackup(const char *filename);
void editorRestoreBackup(const char *filename);
#endif
