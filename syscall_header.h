#include <sys/types.h>

#define PROCESS_NUM 200

struct process{
	char tty[64];
	pid_t pid;
	int time_sec;
	char process_name[200];
};
