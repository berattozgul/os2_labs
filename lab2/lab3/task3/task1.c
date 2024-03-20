#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>

#define QUEUE_SIZE 10

// Structure to represent a queue node
struct queue_node {
    int data;
    struct list_head list;
};

// Head of the queue
static LIST_HEAD(queue_head);

static int __init fifo_queue_init(void) {
    printk(KERN_INFO "FIFO Queue Module: Initialization\n");

    int i;
    for (i = 0; i < QUEUE_SIZE; ++i) {
        // Create a new queue node
        struct queue_node *node = kmalloc(sizeof(struct queue_node), GFP_KERNEL);
        if (!node) {
            printk(KERN_ALERT "Failed to allocate memory for queue node\n");
            return -ENOMEM;
        }
        node->data = i; // Set the data for the node

        // Add the node to the tail of the queue
        list_add_tail(&node->list, &queue_head);
    }

    // Print the elements of the queue
    printk(KERN_INFO "Queue elements: ");
    struct queue_node *current_node;
    list_for_each_entry(current_node, &queue_head, list) {
        printk(KERN_CONT "%d ", current_node->data);
    }
    printk(KERN_CONT "\n");

    return 0;
}

static void __exit fifo_queue_exit(void) {
    printk(KERN_INFO "FIFO Queue Module: Cleanup\n");

    // Free the memory allocated for queue nodes
    // Remove elements from the queue and free memory
    while (!list_empty(&queue_head)) {
        struct queue_node *node = list_first_entry(&queue_head, struct queue_node, list);
        printk(KERN_INFO "Removed element from the queue: %d\n", node->data);
        list_del(&node->list);
        kfree(node);
    }
}

module_init(fifo_queue_init);
module_exit(fifo_queue_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arkadiusz Chrobot <a.chrobot@tu.kielce.pl>");
MODULE_DESCRIPTION("Kernel module to implement a FIFO queue using linked list");
MODULE_VERSION("1.0");
