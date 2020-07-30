#include	<stdio.h>
#include 	<stdlib.h>
#include	<unistd.h>
#include	<sys/wait.h> 
#include	<time.h>


int main(int argc, char* argv[]) {
	void 	child_process();
	int		exit_process();
	pid_t 	pids[3];	
	
	for (int i = 0; i < 3; i++) {
		if ((pids[i] = fork()) == -1) {
			perror("fork");
			abort();
		} else if(pids[i] == 0) {
			child_process(i, argv);
			wait(NULL);
		} 
	}	
	
	for (int i = 0; i < 3; i++) {
		int status = 0;
		pids[i] = wait(&status);
	}
	
	printf("\nParent done.\n");
	return 0;
}

int exit_process(int childpid) {
	int child_status;
	waitpid(childpid, &child_status, 0);
	if ( WIFEXITED(child_status)) {
		int exit_rv = WEXITSTATUS(child_status);     
		return exit_rv;
	}
	return -1;
}

void child_process(int child, char* argv[]) {
	printf("\nChild %d here. ", getpid());
	int exit_rv = exit_process(child);
	switch (child) {
		case 0:
			printf("Will calculate average mark.\nPlease enter 10 marks: \n");
			fflush(stdout);
			int i = 0, num = 0;
			float ans = 0;
			for (i; i < 10; i++) {
				printf("(%d): ", i + 1);
				scanf("%d", &num);
				ans += num;
			}
			printf("Average: %0.2f", (ans/i));
			printf("\nChild %d done, the exit status is %d.\n", getpid(), exit_rv);
			break;
		case 1:
			printf("Will execute command wc.\nHere is the output from wc:\n");
			fflush(stdout);
			char* 	args[4];
					args[0] = "wc";
					args[1] = "-w";
					args[2] = argv[1];
					args[3] = NULL;
			printf("\nChild %d done, the exit status is %d.\n", getpid(), exit_rv);
			execvp(args[0], args);
			break;
		case 2:
			printf("Will update file.\n");
			fflush(stdout);
			printf("%s has been updated.\n", argv[2]);
			printf("\nChild %d done, the exit status is %d.\n", getpid(), exit_rv);
			execvp("./cw", argv);
			break;
	}
	exit(0);
}
								