#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include "export_demo.h"

static int __init use_variable_init(void) {
    printk(KERN_INFO "Use Variable Module: Initialization\n");
    printk(KERN_INFO "Value of my_variable: %d\n", my_variable); // Access my_variable
    return 0;
}

static void __exit use_variable_exit(void) {
    printk(KERN_INFO "Use Variable Module: Cleanup\n");
}

module_init(use_variable_init);
module_exit(use_variable_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arkadiusz Chrobot <a.chrobot@tu.kielce.pl>");
MODULE_DESCRIPTION("Module using the exported variable from export_demo module.");
MODULE_VERSION("1.0");
