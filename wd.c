#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MYPIPE "/tmp/mypipe"



int main() {
	int wd;
	while(1){
	wd=open(MYPIPE,O_WRONLY | O_NONBLOCK);
	if(wd<0) printf("open error!    ");
	if(write(wd,"HHH",3)<0) printf("wd error!\n");
	close(wd);
	sleep(3);
	}
	return 0;
}