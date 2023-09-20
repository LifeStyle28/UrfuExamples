#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main([[maybe_unused]] int argc, [[maybe_unused]] const char* argv[])
{
    static int value = 3;

    const pid_t pid = fork();

    if (pid == -1)
    {
        std::cerr << "error when forked, errno: " << errno << std::endl;
        return EXIT_FAILURE;
    }

    if (pid == 0)
    {
        ++value;
        std::cout << "I'm a child process, value addr = " << &value
            << ", value = " << value << std::endl;
    }
    else if (waitpid(pid, nullptr, 0))
    {
        std::cout << "I'm a parent process, value addr = " << &value
            << ", value = " << value << std::endl;
    }
    return EXIT_SUCCESS;
}
