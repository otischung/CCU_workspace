#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
// #define printf (void)
#define MAXLINE 8192
static inline int min(int a, int b) {
    return a < b ? a : b;
}
void serve_img(FILE *fp_outcome, const char *img_path) {
    char header[8192];
    char header_format[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: %ld\r\n"
        "Content-Type: image/jpeg\r\n"
        "\r\n";
    char buff[8192];
    int imgfd;
    ssize_t size = 0;

    imgfd = open(img_path, O_RDONLY);  // <fcntl.h>
    if (imgfd == -1) {
        perror("open image error");
        exit(1);
    }
    /*---Find the size of image---*/
    off_t filesize = lseek(imgfd, 0, SEEK_END);
    lseek(imgfd, 0, SEEK_SET);
    sprintf(header, header_format, filesize);
    fwrite(header, sizeof(char), strlen(header), fp_outcome);

    /*---Write image---*/
    while ((size = read(imgfd, buff, 8192)) > 0) {
        fwrite(buff, sizeof(char), size, fp_outcome);
    }

    close(imgfd);
}

void serve_result(FILE *fp_outcome, size_t content_length, const char *boundary) {
    FILE *output;
    char filename[8192];
    char *ptr;
    int l = 0;

    for (char buf[8192]; fgets(buf, 8192, fp_outcome);) {
        l += strlen(buf);
        if (!strcmp(buf, "\r\n")) break;
        if (ptr = strstr(buf, "filename=")) {
            ptr += strlen("filename=") + 1;
            strcpy(filename, ptr);
            filename[strlen(filename) - 3] = '\0';
            // printf("----File name = %s----\n", filename);
        }
    }

    output = fopen(filename, "wb+");
    int s;
    for (char buf[8192]; l < content_length;) {
        int read_len = min(8192, content_length - l);

        s = fread(buf, sizeof(char), read_len, fp_outcome);  // must read exactly length, the remain content cannot greater than length.
        fwrite(buf, s, sizeof(char), output);
        // printf("####### %d\n", s);
        l += s;
    }
    fclose(output);
    // serve_img(fp_outcome, "./output.jpg");
}

int main() {
    int listenfd, connectfd, imgfd;
    FILE *fp_outcome;
    struct sockaddr_in servaddr;  // <netinet/in.h>
    int ret;
    pid_t pid;  // <unistd.h>
    off_t filesize;
    ssize_t imgsize, client;
    size_t content_length;
    unsigned val = 1;
    char *ptr;

    signal(SIGCHLD, SIG_IGN);                    // ignore child's task struct  <signal.h>
    listenfd = socket(AF_INET, SOCK_STREAM, 0);  // IPv4, TCP  <sys/socket.h>
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    bzero(&servaddr, sizeof(servaddr));  // <strings.h>
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);  // <arpa/inet.h>
    servaddr.sin_port = htons(8080);
    ret = bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));  // <sys/socket.h>
    if (ret < 0) {
        perror("bind error");
        exit(1);
    }
    ret = listen(listenfd, SOMAXCONN);  // <sys/socket.h>
    if (ret < 0) {
        perror("listen error");
        exit(1);
    }

    while (1) {
        connectfd = accept(listenfd, (struct sockaddr *)NULL, NULL);  // <sys/socket.h>
        if (connectfd > 0) {
            fprintf(stderr, "connection accept\n");
        } else {
            perror("accept error");
            continue;
        }
        pid = fork();
        if (pid < 0) {
            perror("fork error");
            continue;
        }
        if (pid == 0) {  // child
            close(listenfd);
            fp_outcome = fdopen(dup(connectfd), "a+b");
            char line1[8293];
            fgets(line1, 8192, fp_outcome);
            char method[8192], url[8192];
            sscanf(line1, "%s %s", method, url);
            // printf("----URL: %s----\n", url);
            char boundary[8192] = "--";
            for (char buf[8192]; fgets(buf, 8192, fp_outcome);) {
                // printf("%s", buf);
                if (!strcmp(buf, "\r\n")) break;
                if (ptr = strstr(buf, "Content-Length: ")) {
                    ptr += strlen("Content-Length: ");
                    content_length = atol(ptr);
                    // printf("----Content Length = %ld----\n", content_length);
                }
                if (ptr = strstr(buf, "boundary=")) {
                    ptr += strlen("boundary=");
                    strcat(boundary, ptr);
                    boundary[strlen(boundary) - 2] = '\0';
                }
            }
            if (!strcmp(url, "/img")) {
                serve_img(fp_outcome, "./test.jpg");
            } else if (!strcmp(url, "/result")) {
                serve_result(fp_outcome, content_length, boundary);
            } else {
                char header[] =
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "\r\n";
                fwrite(header, sizeof(char), strlen(header), fp_outcome);
                char body[] =
                    "<body>"
                    "<form method='POST' action='/result' enctype='multipart/form-data'>"
                    "<input type=file name='file' />"
                    "<input type=submit value='upload file' />"
                    "</form>"
                    "<br />"  // HTML new line.
                    "<img src='/img' width='70%%' />"
                    "</body>";
                // write(connectfd, body, strlen(body));
                size_t s = fwrite(body, sizeof(char), strlen(body), fp_outcome);
                // printf("#### %d\n", s);
            }

            /*---Close the socket---*/
            fclose(fp_outcome);
            // shutdown(connectfd, SHUT_RDWR);
            close(connectfd);
            exit(0);
        }  // child
        close(connectfd);
    }
    return 0;
}
