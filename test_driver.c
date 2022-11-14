#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include "ring_buffer.h"

static int biolog_proc_show(struct seq_file *m, void *v) {
  seq_printf(m, "Hello proc!\n");
  return 0;
}

static int biolog_proc_open(struct inode *inode, struct  file *file) {
  return single_open(file, biolog_proc_show, NULL);
}

static const struct proc_ops biolog_proc_fops = {
  .proc_open = biolog_proc_open,
  .proc_read = seq_read,
  .proc_lseek = seq_lseek,
  .proc_release = single_release,
};

static int __init biolog_proc_init(void) {
  proc_create("bio_log", 0, NULL, &biolog_proc_fops);
  return 0;
}

static void __exit biolog_proc_exit(void) {
  remove_proc_entry("bio_log", NULL);
}

MODULE_LICENSE("GPL");
module_init(biolog_proc_init);
module_exit(biolog_proc_exit);
