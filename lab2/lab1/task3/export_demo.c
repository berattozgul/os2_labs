#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

int my_variable = 42;

static int __init export_demo_init(void) {
    printk(KERN_INFO "Export Demo Module: Initialization\n");
    return 0;
}

static void __exit export_demo_exit(void) {
    printk(KERN_INFO "Export Demo Module: Cleanup\n");
}

EXPORT_SYMBOL(my_variable);

module_init(export_demo_init);
module_exit(export_demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arkadiusz Chrobot <a.chrobot@tu.kielce.pl>");
MODULE_DESCRIPTION("Module demonstrating the use of EXPORT_SYMBOL() macro.");
MODULE_VERSION("1.0");
