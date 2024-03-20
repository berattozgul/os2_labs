#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init datatypes_module_init(void) {
    printk(KERN_INFO "Data Types Module: Initialization\n");
    printk(KERN_INFO "Size of s8: %lu bytes\n", sizeof(s8));
    printk(KERN_INFO "Size of u8: %lu bytes\n", sizeof(u8));
    printk(KERN_INFO "Size of s16: %lu bytes\n", sizeof(s16));
    printk(KERN_INFO "Size of u16: %lu bytes\n", sizeof(u16));
    printk(KERN_INFO "Size of s32: %lu bytes\n", sizeof(s32));
    printk(KERN_INFO "Size of u32: %lu bytes\n", sizeof(u32));
    printk(KERN_INFO "Size of s64: %lu bytes\n", sizeof(s64));
    printk(KERN_INFO "Size of u64: %lu bytes\n", sizeof(u64));
    return 0;
}

static void __exit datatypes_module_exit(void) {
    printk(KERN_INFO "Data Types Module: Cleanup\n");
}

module_init(datatypes_module_init);
module_exit(datatypes_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arkadiusz Chrobot <a.chrobot@tu.kielce.pl>");
MODULE_DESCRIPTION("\"Hello world\" module in two parts.");
MODULE_VERSION("1.0");
