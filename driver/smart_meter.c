#include "../include/smartmeter_ioctl.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/atomic.h>

#define DEVICE_NAME "smartmeter"

static atomic64_t pulse_count = ATOMIC64_INIT(0);

/* Read current pulse count */
static ssize_t smartmeter_read(struct file *file,
                               char __user *buffer,
                               size_t len,
                               loff_t *offset)
{
    char data[64];
    int size;

    size = snprintf(data, sizeof(data),
                    "%lld\n",
                    atomic64_read(&pulse_count));

    return simple_read_from_buffer(buffer, len, offset,
                                   data, size);
}

/* Add pulses to simulate meter pulses */
static ssize_t smartmeter_write(struct file *file,
                                const char __user *buffer,
                                size_t len,
                                loff_t *offset)
{
    char data[32];
    long pulses;

    if (len >= sizeof(data))
        return -EINVAL;

    if (copy_from_user(data, buffer, len))
        return -EFAULT;

    data[len] = '\0';

    if (kstrtol(data, 10, &pulses) != 0)
        return -EINVAL;

    if (pulses < 0)
        return -EINVAL;

    atomic64_add(pulses, &pulse_count);

    pr_info("smartmeter: %ld pulse(s) added, total = %lld\n",
            pulses,
            atomic64_read(&pulse_count));

    return len;
}

/* Reset pulse counter */
static long smartmeter_ioctl(struct file *file,
                             unsigned int cmd,
                             unsigned long arg)
{
    if (cmd == SMARTMETER_RESET) {
        atomic64_set(&pulse_count, 0);
    } else {
        return -EINVAL;
    }

    return 0;
}

/* File operations */
static const struct file_operations smartmeter_fops = {
    .owner = THIS_MODULE,
    .read = smartmeter_read,
    .write = smartmeter_write,
    .unlocked_ioctl = smartmeter_ioctl,
};

/* Device definition */
static struct miscdevice smartmeter_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &smartmeter_fops,
    .mode = 0666,
};

/* Driver initialization */
static int __init smartmeter_init(void)
{
    int ret;

    atomic64_set(&pulse_count, 0);

    ret = misc_register(&smartmeter_device);

    if (ret) {
        pr_err("smartmeter: device registration failed\n");
        return ret;
    }

    pr_info("smartmeter: driver loaded successfully\n");
    pr_info("smartmeter: /dev/%s created\n", DEVICE_NAME);

    return 0;
}

/* Driver cleanup */
static void __exit smartmeter_exit(void)
{
    misc_deregister(&smartmeter_device);

    pr_info("smartmeter: driver unloaded\n");
}

module_init(smartmeter_init);
module_exit(smartmeter_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Smart Meter Project");
MODULE_DESCRIPTION("Virtual Smart Meter Pulse Counter Driver");
MODULE_VERSION("1.0");
