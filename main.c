#include <linux/unistd.h>
#include <stdio.h>
#include "syscall_header.h"
#include <string.h>

#define __NR_my_syscall 359

int main()
{
	struct process processes[PROCESS_NUM];
	int ret =0;
	int i=0;
	ret = syscall(__NR_my_syscall,processes, 1);
	int ts,tm,th;
	printf("%5s %-8s %8s %s\n","PID", "TTY" , "TIME", "CMD");
	for(i=0;i<200 && processes[i].pid != -1; i++){
		ts = processes[i].time_sec;
		tm=ts/60;
		ts=ts%60;
		th=tm/60;
		tm=tm%60;
		
		printf("%5d %-8s %02d:%02d:%02d %s\n", processes[i].pid, processes[i].tty, th,tm, ts, processes[i].processes);	
	}
	return 0;
}
