#include <errno.h>
#include <sys/types.h>
#include <signal.h>

#include <iostream>
#include <fstream>

static volatile sig_atomic_t on_signal = 0;

static void alarmhandler(int signo)
{
    if (signo == SIGUSR1)
    {
        on_signal = 1;
    }
}

int main()
{
    unlink("file");
    std::ofstream out{"file", std::ios_base::app};
    if (!out.is_open())
    {
        return EXIT_FAILURE;
    }

    out << "Producer started at pid = " << getpid() << std::endl;

    signal(SIGUSR1, alarmhandler);

    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    sigemptyset(&mask);

    while (true)
    {
        sigsuspend(&mask); // wait for signal here

        if (on_signal)
        {
            out << "Catch signal here" << std::endl;
            break;
        }
    }

    return EXIT_SUCCESS;
}
