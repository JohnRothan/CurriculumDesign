#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/string.h>
#include<linux/mm.h>
#include<linux/proc_fs.h>
#include<linux/uaccess.h>
#include<asm/uaccess.h>
#include<linux/slab.h>
#include<linux/sched.h>
#include<linux/seq_file.h>

extern unsigned long volatile pfcount;
   
static int my_proc_show(struct seq_file *m,void *v){
seq_printf(m,"The pfcount is %ld !\n",pfcount);
return 0;
}

static int my_proc_open(struct inode *inode,struct file *file){
return single_open(file,my_proc_show,NULL);
}

struct file_operations fops={
.owner=THIS_MODULE,
.open=my_proc_open,
.release=single_release,
.read=seq_read,
.llseek=seq_lseek,
};

static int pf_init(void){
struct proc_dir_entry *file;
struct proc_dir_entry *parent = proc_mkdir("pf",NULL);
file=proc_create("pfcount",0644,parent,&fops);
if(file==NULL)
printk("create_proc_entry failed.\n");
return 0;
}

static void pf_exit(void){
remove_proc_entry("pf",NULL);
}

module_init(pf_init);
module_exit(pf_exit);
MODULE_LICENSE("GPL");
