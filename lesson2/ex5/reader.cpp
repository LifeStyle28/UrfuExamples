#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <iostream>
#include <string>

static const std::string fifo = "named_pipe";

int main()
{
    struct stat d;
    if (stat(fifo.c_str(), &d) != 0)
    {
        if (mknod(fifo.c_str(), S_IFIFO | 0666, 0) < 0)
        {
            std::cerr << strerror(errno) << std::endl;
            return EXIT_FAILURE;
        }
    }

    std::cout << "Waiting for a writer..." << std::endl;
    const int fd = open(fifo.c_str(), O_RDONLY);
    if (fd < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Writer was connected..." << std::endl;

    char buf[64];

    if (ssize_t result = read(fd, buf, sizeof(buf)); result > 0)
    {
        const std::string str{buf, buf + result};
        std::cout << "Read: " << str << std::endl;
    }

    unlink(fifo.c_str());

    return EXIT_SUCCESS;
}
