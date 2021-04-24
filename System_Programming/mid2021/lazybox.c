#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <libgen.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/limits.h>

char lazyBox_path[PATH_MAX];
int lazyshell_main();
int ln_main(int argc, char **argv);
int stat_main(int argc, char **argv);
int chown_main(int argc, char **argv);


//////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    int exit;
    char command[PATH_MAX];
    char *name = basename(argv[0]);
    char lazyBox_path[PATH_MAX];
    if (!strcmp(name, "lazyshell")) {
        exit = lazyshell_main(argc, argv);
        if (exit == 1) {
            return 1;
        }
    } else if (!strcmp(name, "ln")) {
        ln_main(argc, argv);
    } else if (!strcmp(name, "stat")) {
        stat_main(argc, argv);
    } else if (!strcmp(name, "chown")) {
        chown_main(argc, argv);
    } else {
        exit = lazyshell_main(argc, argv);
        if (exit == 1) {
            return 1;
        }
    }
    return 0;
}
//////////////////////////////////////////////////////////////////////


int lazyshell_main() {
    char lazyBox_path[PATH_MAX];
    char command[PATH_MAX];
    char *comptr;
    char buf[PATH_MAX];
    while (true) {
        getcwd(lazyBox_path, PATH_MAX);
        printf("lazybox:");
        printf("%s$ ", lazyBox_path);

        fgets(command, PATH_MAX, stdin);
        if (command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] =  '\0';
        }
        sscanf(command, "%s", buf);

        if (!strcmp(buf, "exit")) {
            exit(1);
        } else if (!strcmp(buf, "cd")){
            comptr = command + 3;
            sscanf(comptr, "%s", buf);
            chdir(buf);
        } else {
            system(command);
        }
    }
}

int ln_main(int argc, char **argv) {
    char lazyBox_path[PATH_MAX];
    char old[PATH_MAX], new[PATH_MAX];
    getcwd(lazyBox_path, PATH_MAX);
    if (!strcmp(argv[1], "-s") && argc == 4) {
        strcpy(old, lazyBox_path);
        strcpy(new, lazyBox_path);
        strncat(old, "/", PATH_MAX - 1);
        strncat(old, argv[2], PATH_MAX - 1);
        strncat(new, "/", PATH_MAX - 1);
        strncat(new, argv[3], PATH_MAX - 1);
        symlink(old, new);
    } else if (argc == 3) {
        strcpy(old, lazyBox_path);
        strcpy(new, lazyBox_path);
        strncat(old, "/", PATH_MAX - 1);
        strncat(old, argv[1], PATH_MAX - 1);
        strncat(new, "/", PATH_MAX - 1);
        strncat(new, argv[2], PATH_MAX - 1);
        symlink(old, new);
        link(old, new);
    } else {
        fprintf(stderr, "ln: missing file operand\n");
        return 1;
    }
    return 0;
}

int stat_main(int argc, char **argv) {
    int success;
    struct stat filestat;

    char lazyBox_path[PATH_MAX];
    getcwd(lazyBox_path, PATH_MAX);
    char filename[PATH_MAX];

    if (argc != 2) {
        fprintf(stderr, "stat: missing operand\n");
        return 1;
    }

    if (argv[1][0] == '/') {  // absolute path.
        strcpy(filename, argv[1]);
    } else {  // relative path.
        strcpy(filename, lazyBox_path);
        strncat(filename, "/", PATH_MAX - 1);
        strncat(filename, argv[1], PATH_MAX - 1);
    }
    
    uid_t fileowner;
    char *hfileowner;
    time_t at, mt, ct;
    char *hat, *hmt, *hct;

    success = stat(filename, &filestat);
    if (success != 0) {
        perror("stat error");
        return 1;
    }
    fileowner = filestat.st_uid;
    at = filestat.st_atime;
    mt = filestat.st_mtime;
    ct = filestat.st_ctime;
    hat = ctime(&at);
    hmt = ctime(&mt);
    hct = ctime(&ct);
    hfileowner = getpwuid(fileowner)->pw_name;
    printf("The stat of %s:\n", filename);
    printf("Fileowner; %s\n", hfileowner);
    printf("atime = %s", hat);
    printf("mtime = %s", hmt);
    printf("ctime = %s", hct);
    return 0;
}

int chown_main(int argc, char **argv) {
    char lazyBox_path[PATH_MAX];
    getcwd(lazyBox_path, PATH_MAX);
    char filename[PATH_MAX];
    if (argv[2][0] == '/') {
        strcpy(filename, argv[2]);
    } else {
        strcpy(filename, lazyBox_path);
        strncat(filename, "/", PATH_MAX - 1);
        strncat(filename, argv[2], PATH_MAX - 1);
    }

    int statsuccess;
    uid_t ruid, euid, suid;
    getresuid(&ruid, &euid, &suid);
    // printf("%d %d %d\n", ruid, euid, suid);
    setreuid(euid, ruid);
    getresuid(&ruid, &euid, &suid);
    // printf("%d %d %d\n", ruid, euid, suid);
    struct timespec file_t, current_t;
    struct stat curstat, sudostat;
    char yn[256];
    char command[PATH_MAX];
    char *name = basename(argv[0]);

    statsuccess = stat(filename, &curstat);
    if (statsuccess != 0) {
        perror("stat error");
        return 1;
    }
    if (access("./.sudo_success", F_OK) == 0) {
        statsuccess = stat("./.sudo_success", &sudostat);
        if (statsuccess != 0) {
            perror("stat error");
            return 1;
        }
    } else {
        system("touch .sudo_success");
        statsuccess = stat("./.sudo_success", &sudostat);
        if (statsuccess != 0) {
            perror("stat error");
            return 1;
        }
        sudostat.st_atime = 0;
        sudostat.st_mtime = 0;
    }

    file_t = curstat.st_ctim;
    clock_gettime(CLOCK_REALTIME, &current_t);
    if (current_t.tv_sec - sudostat.st_mtime > 30 || current_t.tv_sec - file_t.tv_sec > 30) {
        printf("你要執行的是特權指令,確定的話,請輸入『yes』,否則按下『enter』終止操作：");
        fgets(yn, 256, stdin);
        // putchar('\n');
        if (strcmp(yn, "yes\n")) {
            return 0;
        }
    }
    strcpy(command, name);
    strncat(command, " ", PATH_MAX - 1);
    strncat(command, argv[1], PATH_MAX - 1);
    strncat(command, " ", PATH_MAX - 1);
    strncat(command, filename, PATH_MAX - 1);
    printf("%s\n", command);
    system(command);
    system("touch .sudo_success");
    return 0;
}
