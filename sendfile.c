#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
 #include <sys/sendfile.h>

void usage() {
    printf("./sendfile infile, outfile");
}

int main(int argc, char** argv) {
    if (argc != 3) {
        usage();
        return -1;
    }
    const char* infile = argv[1];
    const char*  outfile = argv[2];
    loff_t off_in;
    loff_t off_out;
    struct stat statbuf;

    if (-1 == stat(infile, &statbuf)) {
        return -1;
    }
    off_t size = statbuf.st_size;
    int fdin = open(infile, O_RDONLY);
    int fdout = open(outfile, O_CREAT|O_WRONLY, 0644);
    ssize_t len = size;
    while (len > 0) {
        ssize_t hc = sendfile(fdout, fdin, NULL, len);
        if (hc == -1) {
            break;
        }
        len -= hc;
    }
    close(fdin);
    close(fdout);
}