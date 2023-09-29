#include <errno.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <spawn.h>
#include <string.h>

#include <iostream>
#include <vector>

static pid_t run_program(const std::string& path, const std::vector<std::string>& args)
{
    // подготавливаем аргументы для запуска
    std::vector<const char *> argv;
    argv.push_back(path.c_str());
    for (const std::string& arg : args)
    {
        argv.push_back(arg.c_str());
    }
    argv.push_back(NULL);

    posix_spawn_file_actions_t fileActions;

    int result = posix_spawn_file_actions_init(&fileActions);
    if (result != 0)
    {
        std::cerr << "posix_spawn_file_actions_init failed" << std::endl;
        return -1;
    }

    result = posix_spawn_file_actions_addclose(&fileActions, STDOUT_FILENO);
    if (result != 0)
    {
        std::cerr << "posix_spawn_file_actions_addclose failed" << std::endl;
        return -1;
    }

    posix_spawn_file_actions_t* pFileActions = &fileActions;

    posix_spawnattr_t attr;

    result = posix_spawnattr_init(&attr);
    if (result != 0)
    {
        std::cerr << "posix_spawnattr_init failed" << std::endl;
        return -1;
    }

    result = posix_spawnattr_setflags(&attr, POSIX_SPAWN_SETSIGMASK);
    if (result != 0)
    {
        std::cerr << "posix_spawnattr_setflags failed" << std::endl;
        return -1;
    }

    sigset_t mask;
    sigfillset(&mask);
    result = posix_spawnattr_setsigmask(&attr, &mask);
    if (result != 0)
    {
        std::cerr << "posix_spawnattr_setsigmask failed" << std::endl;
        return -1;
    }
    posix_spawnattr_t* pAttr = &attr;

    pid_t childPid;
    result = posix_spawnp(&childPid, path.c_str(), pFileActions, pAttr, const_cast<char**>(&argv[0]),
        nullptr);
    if (result != 0)
    {
        std::cerr << "posix_spawn failed" << std::endl;
        return -1;
    }

    if (pAttr != NULL)
    {
        result = posix_spawnattr_destroy(pAttr);
        if (result != 0)
        {
            std::cerr << "posix_spawnattr_destroy failed" << std::endl;
            return -1;
        }
    }

    if (pFileActions != NULL) {
        result = posix_spawn_file_actions_destroy(pFileActions);
        if (result != 0)
        {
            std::cerr << "posix_spawn_file_actions_destroy failed" << std::endl;
            return -1;
        }
    }

    int status;
    result = waitpid(childPid, &status, WNOHANG);
    if (result == -1)
    {
        std::cerr << "waitpid failed" << std::endl;
        return -1;
    }
    return childPid;
}

int main()
{
    std::vector<std::string> dummy;
    const pid_t childPid = run_program(
        "/home/severgin/Documents/reps/UrfuExamples/lesson2/ex6/build/consumer", dummy);

    if (childPid < 0)
    {
        std::cerr << "error on spawn child process" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Consumer started at pid = " << childPid << std::endl;
    std::cout << "Send SIGUSR1 to " << childPid << std::endl;

    if (kill(childPid, SIGUSR1) < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "kill signal sending successful" << std::endl;

    return EXIT_SUCCESS;
}
