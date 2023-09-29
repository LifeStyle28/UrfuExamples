#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#include <iostream>
#include <string>

int main()
{
    int fd[2];

    if (pipe(fd) < 0)
    {
        std::cerr << "Failed to create pipe" << std::endl;
        return EXIT_FAILURE;
    }

    const pid_t pid = fork();

    if (pid == -1)
    {
        std::cerr << "error when forked, errno: " << errno << std::endl;
        return EXIT_FAILURE;
    }

    if (pid == 0)
    {
        const std::string str = "Hello, world!";
        std::cout << "I'm a child process" << std::endl;
        write(fd[1], str.c_str(), str.size());
        std::cout << "Write, str = " << str << std::endl;
    }
    else if (waitpid(pid, nullptr, 0))
    {
        char buf[64];
        std::cout << "I'm a parent process" << std::endl;
        if (read(fd[0], buf, sizeof(buf)) > 0)
        {
            std::cout << "Read, buf = " << buf << std::endl;
        }
    }

    close(fd[0]);
    close(fd[1]);

    return EXIT_SUCCESS;
}
