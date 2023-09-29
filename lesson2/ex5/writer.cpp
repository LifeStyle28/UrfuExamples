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

    std::cout << "Waiting for a reader..." << std::endl;
    const int fd = open(fifo.c_str(), O_WRONLY);
    if (fd < 0)
    {
        std::cerr << strerror(errno) << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Reader was connected..." << std::endl;

    const std::string str = "Hello, world!";

    write(fd, str.c_str(), str.size());

    std::cout << "Write: " << str << std::endl;

    unlink(fifo.c_str());

    return EXIT_SUCCESS;
}
