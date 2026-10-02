#ifndef SMARTMETER_IOCTL_H
#define SMARTMETER_IOCTL_H

#include <linux/ioctl.h>

#define SMARTMETER_MAGIC 'S'

#define SMARTMETER_RESET _IO(SMARTMETER_MAGIC, 0)

#endif
