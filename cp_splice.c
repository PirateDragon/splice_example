#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void usage() {
    printf("./cp_splice infile, outfile");
}

int main(int argc, char** argv) {
    if (argc != 3) {
        usage();
        return -1;
    }
    const char* infile = argv[1];
    const char*  outfile = argv[2];
    int fds[2];
    int ret = pipe(fds);
    if (ret == -1) {
        return -1;
    }
    loff_t off_in;
    loff_t off_out;
    struct stat statbuf;

    if (-1 == stat(infile, &statbuf)) {
        return -1;
    }
    off_t size = statbuf.st_size;
    int fdin = open(infile, O_RDONLY);
    int fdout = open(outfile, O_CREAT|O_WRONLY, 0644);
    size_t len = 0;
    const size_t batch = 0x1000 * 16;
    while (size > 0) {
        len = batch < size? batch:size;
        size -= len;
        splice(fdin, NULL, fds[1], NULL, len, SPLICE_F_MORE | SPLICE_F_MOVE|SPLICE_F_NONBLOCK);
        splice(fds[0], NULL, fdout, NULL, len, SPLICE_F_MORE | SPLICE_F_MOVE|SPLICE_F_NONBLOCK);
    }
    close(fdin);
    close(fdout);
    close(fds[1]);
    close(fds[0]);
}