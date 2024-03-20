#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arkadiusz Chrobot <a.chrobot@tu.kielce.pl>");
MODULE_DESCRIPTION("Kernel module to implement a stack using linked list");
MODULE_VERSION("1.0");

// Define a structure for stack node
struct stack_node {
    int data;
    struct list_head list;
};

// Define the head of the stack
static LIST_HEAD(stack_head);

// Module parameters for stack elements
static int stack_elements[] = {1, 2, 3, 4, 5,6};
module_param_array(stack_elements, int, NULL, 0644);
MODULE_PARM_DESC(stack_elements, "Elements of the stack");

static int __init stack_module_init(void) {
    printk(KERN_INFO "Stack Module: Initialization\n");

    // Push elements onto the stack
    int i;
    struct stack_node *node;
    for (i = 0; i < ARRAY_SIZE(stack_elements); ++i) {
        node = kmalloc(sizeof(struct stack_node), GFP_KERNEL);
        if (!node) {
            printk(KERN_ERR "Failed to allocate memory for stack node\n");
            return -ENOMEM;
        }
        node->data = stack_elements[i];
        INIT_LIST_HEAD(&node->list);
        list_add(&node->list, &stack_head);
    }

    // Print the contents of the stack
    struct stack_node *ptr;
    printk(KERN_INFO "Stack contents:");
    list_for_each_entry(ptr, &stack_head, list) {
        printk(KERN_INFO "%d ", ptr->data);
    }
    printk(KERN_INFO "\n");

    return 0;
}

static void __exit stack_module_exit(void) {
    printk(KERN_INFO "Stack Module: Cleanup\n");

    // Pop elements from the stack and free memory
    struct stack_node *ptr, *next;
    list_for_each_entry_safe(ptr, next, &stack_head, list) {
        list_del(&ptr->list);
        kfree(ptr);
    }
}

module_init(stack_module_init);
module_exit(stack_module_exit);
