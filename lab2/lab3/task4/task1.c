#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/string.h>

#define QUEUE_SIZE 10

// Structure to represent a queue node
struct queue_node {
    char *data; // Variable-length string
    struct list_head list;
};

// Head of the queue
static LIST_HEAD(queue_head);

// Initialize the FIFO queue
static int __init fifo_queue_init(void) {
    printk(KERN_INFO "FIFO Queue Module: Initialization\n");

    // Define an array of strings to provide through module parameters
    static const char *input_strings[QUEUE_SIZE] = {
        "String 1",
        "Another string",
        "A longer string with varying length",
        "Yet another string",
        "Short string",
        "A very long string that takes up a lot of space",
        "String 7",
        "String 8",
        "String 9",
        "String 10"
    };

    // Add the strings to the queue
    int i;
    for (i = 0; i < QUEUE_SIZE; ++i) {
        // Allocate memory for the queue node
        struct queue_node *node = kmalloc(sizeof(struct queue_node), GFP_KERNEL);
        if (!node) {
            printk(KERN_ALERT "Failed to allocate memory for queue node\n");
            return -ENOMEM;
        }
        
        // Allocate memory for the string and copy the data
        node->data = kmalloc(strlen(input_strings[i]) + 1, GFP_KERNEL);
        if (!node->data) {
            printk(KERN_ALERT "Failed to allocate memory for string\n");
            kfree(node);
            return -ENOMEM;
        }
        strcpy(node->data, input_strings[i]);

        // Add the node to the tail of the queue
        list_add_tail(&node->list, &queue_head);

        // Print information about the string being added to the queue
        printk(KERN_INFO "Added string to the queue: %s\n", node->data);
    }

    return 0;
}

// Cleanup the FIFO queue
static void __exit fifo_queue_exit(void) {
    printk(KERN_INFO "FIFO Queue Module: Cleanup\n");

    // Remove elements from the queue and free memory
    while (!list_empty(&queue_head)) {
        struct queue_node *node = list_first_entry(&queue_head, struct queue_node, list);
        printk(KERN_INFO "Removed string from the queue: %s\n", node->data);
        list_del(&node->list);
        kfree(node->data); // Free the string
        kfree(node); // Free the node
    }
}


module_init(fifo_queue_init);
module_exit(fifo_queue_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arkadiusz Chrobot <a.chrobot@tu.kielce.pl>");
MODULE_DESCRIPTION("Kernel module to store strings of varying lengths in a FIFO queue");
MODULE_VERSION("1.0");
