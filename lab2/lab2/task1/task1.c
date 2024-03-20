#include <linux/module.h>
#include <linux/slab.h>
#include <linux/string.h>

static struct example_struct{
    unsigned int id;
    char example_string[10];
} *example_struct_pointer[5]; // Array to hold 5 pointers
static struct kmem_cache *example_cachep;

static void example_constructor(void *argument) {
    static unsigned int id = 0; // Initialize static id here
    static char test_string[] = "Test";

    struct example_struct *example = (struct example_struct *)argument;
    example->id = id++;  // Assign and increment id
    strcpy(example->example_string, test_string);
}

// Function to print a single example struct
void print_example_struct(struct example_struct *example) {
    pr_notice("Example struct id: %u\n", example->id);
    pr_notice("Example string field content: %s\n", example->example_string);
}

static int __init slabmod_init(void) {
    example_cachep = kmem_cache_create("example cache", sizeof(struct example_struct), 0,
                                        SLAB_HWCACHE_ALIGN | SLAB_POISON | SLAB_RED_ZONE,
                                        example_constructor);
    if (IS_ERR(example_cachep)) {
        pr_alert("Error creating cache: %ld\n", PTR_ERR(example_cachep));
        return -ENOMEM;
    }

    // Allocate and print 5 structures
    for (int i = 0; i < 5; i++) {
        example_struct_pointer[i] = (struct example_struct *)kmem_cache_alloc(example_cachep, GFP_KERNEL);
        if (IS_ERR(example_struct_pointer[i])) {
            pr_alert("Error allocating from cache: %ld\n", PTR_ERR(example_struct_pointer[i]));
            kmem_cache_destroy(example_cachep);
            return -ENOMEM;
        }
        print_example_struct(example_struct_pointer[i]); // Print contents immediately
    }

    return 0;
}

static void __exit slabmod_exit(void) {
    if (example_cachep) {
        // Free all allocated structures
        for (int i = 0; i < 5; i++) {
            if (example_struct_pointer[i]) {
                kmem_cache_free(example_cachep, example_struct_pointer[i]);
            }
        }
        kmem_cache_destroy(example_cachep);
    }
	pr_notice("Module slabmod unloaded!\n");
}

module_init(slabmod_init);
module_exit(slabmod_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Arkadiusz Chrobot <a.chrobot@tu.kielce.pl>");
MODULE_DESCRIPTION("A module demonstrating the use of the slab allocator.");
MODULE_VERSION("1.0");
