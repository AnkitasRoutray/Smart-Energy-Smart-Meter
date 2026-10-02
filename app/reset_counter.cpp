#include "../include/smartmeter_ioctl.h"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main()
{
    int fd = open("/dev/smartmeter", O_RDWR);

    if (fd < 0)
    {
        perror("Failed to open device");
        return 1;
    }

    if (ioctl(fd, SMARTMETER_RESET) == 0)
        std::cout << "Smart meter counter reset successfully.\n";
    else
        perror("Reset failed");

    close(fd);

    return 0;
}
