#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

void my_function(void) {
    printk(KERN_INFO "Exported function called!\n");
}

static int __init export_gpl_demo_init(void) {
    printk(KERN_INFO "Export GPL Demo Module: Initialization\n");
    return 0;
}

static void __exit export_gpl_demo_exit(void) {
    printk(KERN_INFO "Export GPL Demo Module: Cleanup\n");
}

EXPORT_SYMBOL_GPL(my_function);

module_init(export_gpl_demo_init);
module_exit(export_gpl_demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arkadiusz Chrobot <a.chrobot@tu.kielce.pl>");
MODULE_DESCRIPTION("Module demonstrating the use of EXPORT_SYMBOL_GPL() macro.");
MODULE_VERSION("1.0");
