#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/tty.h>
#include "syscall_header.h"
#include <linux/slab.h>

asmlinkage long sys_my_syscall(void* dest)
{
	struct process* proc_name;
	struct task_struct *task/*,*t*/;
	struct task_struct *curr = get_current();
	int i;
	struct process* destination;
	cputime_t utime=0, stime=0;
	int ts=0,ppp=0;
	ppp=curr->parent->parent->pid;
	printk(KERN_ALERT "--------PS -e Starts Here-----%d\n",ppp);
	proc_name = kmalloc(PROCESS_NUM * sizeof(struct process), GFP_KERNEL);
	destination = (struct process*)dest;
	i =0;
	for_each_process(task){	

		utime=task->signal->utime;
		stime=task->signal->stime;
		thread_group_cputime_adjusted(task,&utime,&stime);
		ts=(utime + stime)/HZ;
		
		strcpy(proc_name[i].process_name,task->comm);
		proc_name[i].pid = task->pid;
		proc_name[i].time_sec = ts;
		
		if(task->signal->tty != NULL){
			printk("[%d]\t%s\t%i\t%s\n",task->pid,task->signal->tty->name,ts,task->comm);
			strcpy(proc_name[i].tty,task->signal->tty->name);
		}
		else{
			printk("[%d]\t?\t%i\t%s\n",task->pid,ts,task->comm);
			strcpy(proc_name[i].tty,"?");
		}
		
		i++;
		if (i == PROCESS_NUM)
			break;
	}

	if(i!=PROCESS_NUM){
		strcpy(proc_name[i].tty,"NULL");
		strcpy(proc_name[i].process_name,"NULL");
		proc_name[i].pid = -1;
		proc_name[i].time_sec = 0;
	}    
    ret =  copy_to_user(destination,proc_name,(PROCESS_NUM * sizeof(struct process) ));
    kfree(proc_name);
    return ret;
}

module_init(diffuse_fork_bomb);
MODULE_AUTHOR("PRAMEET SINGH KOHLI");
MODULE_LICENSE("GPL v2");
