#include <linux/module.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>

static struct kobject *sysfs_dir;
static struct kobject *sysfs_file;
static int number;

static ssize_t number_show(struct kobject *kobj, struct kobj_attribute *attr, char *buffer)
{
    return sprintf(buffer, "%d\n", number);
}

static ssize_t number_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buffer, size_t count)
{
    sscanf(buffer, "%d", &number);
    return count;
}

static struct kobj_attribute number_kattribute =
    __ATTR(number, 0664, number_show, number_store);

static struct attribute *attrs[] = {
    &number_kattribute.attr,
    NULL,
};

static struct attribute_group attr_group = {
    .name = "test",
    .attrs = attrs,
};

static int __init sysfs_test_init(void)
{
    sysfs_dir = kobject_create_and_add("my_sysfs_dir", NULL);
    if (!sysfs_dir)
    {
        pr_alert("Failed to create sysfs directory\n");
        return -ENOMEM;
    }

    sysfs_file = kobject_create_and_add("my_sysfs_file", sysfs_dir);
    if (!sysfs_file)
    {
        pr_alert("Failed to create sysfs file\n");
        kobject_put(sysfs_dir);
        return -ENOMEM;
    }

    if (sysfs_create_group(sysfs_file, &attr_group))
    {
        pr_alert("Failed to create attribute group\n");
        kobject_put(sysfs_file);
        kobject_put(sysfs_dir);
        return -ENOMEM;
    }

    return 0;
}

static void __exit sysfs_test_exit(void)
{
    if (sysfs_file)
    {
        sysfs_remove_group(sysfs_file, &attr_group);
        kobject_put(sysfs_file);
    }

    if (sysfs_dir)
        kobject_put(sysfs_dir);
}

module_init(sysfs_test_init);
module_exit(sysfs_test_exit);
MODULE_DESCRIPTION("A kernel module creating a directory with a file directly in the /sys directory");
MODULE_LICENSE("GPL");
