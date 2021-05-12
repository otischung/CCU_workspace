#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <shadow.h>
#include <crypt.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>

char *ltrim(char *s);
char *rtrim(char *s);
char *trim(char *s);
int CheckPassword(const char* user, const char* password);


///////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    char username[1024];
    char buf[1024];
    char *namePtr;
    char password[1024];
    struct passwd passwd_ent;
    struct passwd *result;
    struct group *gr;
    // long ngroups_max;
    int nGroup = sysconf(_SC_NGROUPS_MAX);
    uid_t ruid, euid, suid;
    pid_t pid;
    int wstatus;
    gid_t gid;
    gid_t groups[nGroup];
    int ret;
    char *const bashargv[] = {"/usr/bin/bash", NULL};

    while (true) {
        // getresuid(&ruid, &euid, &suid);
        // setreuid(euid, ruid);  // swap the ruid and the euid.

        printf("user: ");
        namePtr = fgets(username, 1024, stdin);
        if (username[strlen(username) - 1] == '\n') {
            username[strlen(username) - 1] =  '\0';
        }
        // printf("gets %s\n", namePtr);

        namePtr = trim(namePtr);  // clear redundant white space.

        /*************************************************************************
         * int getpwnam_r(const char *name, struct passwd *pwd,
                          char *buf, size_t buflen, struct passwd **result);
         * The  getpwnam()  function returns a pointer to a structure containing
           the broken-out fields of the record in the password  database  (e.g.,
           the  local password file /etc/passwd, NIS, and LDAP) that matches the
           username name.
         * The getpwnam_r() and getpwuid_r() functions obtain the same  informa‐
           tion  as  getpwnam()  and  getpwuid(), but store the retrieved passwd
           structure in the space pointed to by pwd.  The string fields  pointed
           to  by  the  members of the passwd structure are stored in the buffer
           buf of size buflen.  A pointer to the result (in case of success)  or
           NULL  (in  case no entry was found or an error occurred) is stored in
         * result.
         * The getpwnam() and getpwuid() functions return a pointer to a  passwd
           structure, or NULL if the matching entry is not found or an error oc‐
           curs.  If an error occurs, errno is set appropriately.  If one  wants
           to  check  errno  after the call, it should be set to zero before the
           call.
         * On success, getpwnam_r() and getpwuid_r() return zero, and  set  *re‐
           sult  to  pwd.  If no matching password record was found, these func‐
           tions return 0 and store NULL in *result.  In case of error, an error
           number is returned, and NULL is stored in *result.
        *************************************************************************/
        ret = getpwnam_r(namePtr, &passwd_ent, buf, 1024, &result);
        if (ret != 0) {
            perror("getpwnam failed");
            continue;
        }
        if (result == NULL) {
            printf("User '%s' doesn't exist\n", namePtr);
            continue;
        }

        printf("password: ");
        fgets(password, 1024, stdin);
        if (password[strlen(password) - 1] == '\n') {
            password[strlen(password) - 1] =  '\0';
        }
        if (CheckPassword(namePtr, password)) {
            printf("Incorrect, please try again.\n");
            continue;
        }

        pid = fork();
        if (pid < 0) {
            perror("fork error");
            exit(1);
        }
        if (pid > 0) {          // parent
            wait(&wstatus);
            printf("The return value of bash is %d\n", wstatus);

            if (WIFEXITED(wstatus))         printf("bash terminated normally.\n");
            else if (WIFSIGNALED(wstatus))  printf("bash terminated by a signal.\n");
            else if (WCOREDUMP(wstatus))    printf("bash produced a core dump.\n");
            
            continue;
        } else {                // child
        /************************************************************************
         * int getgrouplist(const char *user, gid_t group,
                            gid_t *groups, int *ngroups);
         * The  getgrouplist()  function scans the group database (see group(5))
           to obtain the list of groups that user belongs to.  Up to *ngroups of
           these groups are returned in the array groups.

         * If  it  was  not among the groups defined for user in the group data‐
           base, then group is included in the list of groups returned  by  get‐
           grouplist();  typically  this  argument  is specified as the group ID
           from the password record for user.

         * The ngroups argument is a value-result argument: on return it  always
           contains  the  number of groups found for user, including group; this
           value may be greater than the number of groups stored in groups.

         * If the number of groups of which user is a member  is  less  than  or
           equal to *ngroups, then the value *ngroups is returned.

         * If  the  user is a member of more than *ngroups groups, then getgrou‐
           plist() returns -1.  In this case, the value returned in *ngroups can
           be used to resize the buffer passed to a further call getgrouplist().
        *************************************************************************/
            ret = getgrouplist(namePtr, passwd_ent.pw_gid, groups, &nGroup);

            printf("getgrouplist = %d\n", ret);
            printf("User ID: %d\n", passwd_ent.pw_uid);
            printf("User name: %s\n", passwd_ent.pw_name);
            printf("Group ID: %d\n", passwd_ent.pw_gid);
            printf("Home directory: %s\n", passwd_ent.pw_dir);
            printf("Other informations: %s\n", buf);
            printf("The amount of this account belongs to groups is %d\n", nGroup);

            for (int i = 0; i < nGroup; ++i) {
                gr = getgrgid(groups[i]);
                printf("%s, ", gr->gr_name);
            }
            putchar('\n');

            assert(setgid(passwd_ent.pw_gid) == 0);
            assert(chdir(passwd_ent.pw_dir) == 0);
        /************************************************************************
         * int setenv(const char *name, const char *value, int overwrite);
         * The  setenv() function adds the variable name to the environment with
           the value value, if name does not already exist.  If name does  exist
           in  the  environment, then its value is changed to value if overwrite
           is nonzero; if overwrite is zero, then  the  value  of  name  is  not
           changed (and setenv() returns a success status).  This function makes
           copies of the strings pointed to by name and value (by contrast  with
           putenv(3)).
         * The  setenv()  function returns zero on success, or -1 on error, with
           errno set to indicate the cause of the error.
        *************************************************************************/
            setenv("HOME", passwd_ent.pw_dir, 1);
        /************************************************************************
         * int setgroups(size_t size, const gid_t *list);
         * setgroups() sets the supplementary group IDs for the calling process.
           Appropriate privileges are required (see the description of the EPERM
           error, below).  The size argument specifies the number of  supplemen‐
           tary  group IDs in the buffer pointed to by list.  A process can drop
           all of its supplementary groups with the call:
                    setgroups(0, NULL);
         * On success, setgroups() returns 0.  On error, -1 is returned, and er‐
           rno is set appropriately.
        *************************************************************************/
            setgroups(0, NULL);
            setgroups(nGroup, groups);

            assert(setuid(passwd_ent.pw_uid) == 0);

            ret = execvp(bashargv[0], bashargv);
            // printf("The return value of bash is %d\n", ret);
            // continue;
        }
    }

    

    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////


char *ltrim(char *s) {
    while (isspace(*s)) ++s;
    return s;
}

char *rtrim(char *s) {
    char *back = s + strlen(s);
    while (isspace(*--back));
    *(back + 1) = '\0';
    return s;
}

char *trim(char *s) {
    return rtrim(ltrim(s));
}

int CheckPassword( const char* user, const char* password) {
    struct passwd *passwdEntry = getpwnam(user);
    if (!passwdEntry) {
        return 1;
    }

    if (0 != strcmp(passwdEntry->pw_passwd, "x")) {
        return strcmp(passwdEntry->pw_passwd, crypt(password, passwdEntry->pw_passwd));
    } else {
        // password is in shadow file
        struct spwd *shadowEntry = getspnam(user);
        if (!shadowEntry) {
            printf( "Failed to read shadow entry for user '%s'\n", user);
            return 1;
        }

        return strcmp(shadowEntry->sp_pwdp, crypt(password, shadowEntry->sp_pwdp));
    }
    // https://stackoverflow.com/questions/17499163/how-to-check-password-in-linux-by-using-c-or-shell
}
