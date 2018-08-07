#include <err.h>
#include <fcntl.h>
#include <linux/tty.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static void __attribute__((__noreturn__)) handler(int s)
{
    (void) s;
    exit(EXIT_SUCCESS);
}

static void __attribute__((__noreturn__)) usage()
{
    printf("ldattach <ldisc> <device>\n"
           "\n"
           "This is a dumb version of ldattach. Please be kind\n"
           "and pass it a number and a tty path.\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
        usage();

    int ldisc = (int) strtol(argv[1], NULL, 0);
    const char *tty_path = argv[2];

    if (ldisc < 0 || ldisc >= NR_LDISCS)
        errx(EXIT_FAILURE, "%d isn't a valid line discipline", ldisc);

    signal(SIGKILL, handler);
    signal(SIGINT, handler);

    int tty_fd = open(tty_path, O_RDWR | O_NOCTTY);
    if (tty_fd < 0)
        err(EXIT_FAILURE, "can't open %s", tty_path);

    if (!isatty(tty_fd))
        errx(EXIT_FAILURE, "not a serial line");

    if (ioctl(tty_fd, TIOCSETD, &ldisc) < 0)
        err(EXIT_FAILURE, "cannot set line discipline");

    if (daemon(0, 0) < 0)
        err(EXIT_FAILURE, "cannot daemonize");

    pause();

    exit(EXIT_SUCCESS);
}
