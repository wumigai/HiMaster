/*************************************************************************
    > File Name: master.c
    > Author: HHH
    > Mail: 305837300@qq.com 
    > Created Time: 2018年04月01日 星期日 16时47分36秒
 ************************************************************************/
#include "module.h"
#define  STATUSTXT "/home/pi/master/status.txt"
#define MODE 00777
//int Status;
//主动唤醒。
void wake(){
	if (ACLOCK){
		//主动唤醒播放歌曲。
		system("play /home/pi/Desktop/xsycq.mp3");
		printf("timeout to ACLOCK");
	}
}
//被动唤醒
void bewake(){
	
}
int getstatus(){
	//
	int rfd,rlen,wfd;
	char buf[7];
	//if(access(MYPIPE,F_OK)<0)
	//	mkfifo(MYPIPE,O_CREAT | O_RDWR | 00777);
	
	if((rfd=open(STATUSTXT,O_RDONLY | O_CREAT,MODE))<0){
		printf("open status error!\n");
	}
	memset(buf,0,sizeof(buf));
	rlen=read(rfd,buf,7);
	if(rlen != 0 && buf[0] == 'p') {
		printf("read the status P %s\n",buf);
		wfd=open(STATUSTXT,O_WRONLY | O_TRUNC,00777);
		write(wfd,"actived",7);
		close(wfd);
		close(rfd);
		return 1;
		
	}
	else {
		close(rfd);
		return 0;
	}
	
	
}



int main(){
	system("bash /home/pi/master/shell/init.sh");
	system("python /home/pi/master/snowboy/examples/Python/demo.py /home/pi/master/snowboy/examples/Python/HiMaster.pmdl &");
	rebspeak("你好啊，主人!\n");
	int wfd;
	wfd=open(STATUSTXT,O_WRONLY |O_CREAT| O_TRUNC,00777);
	write(wfd,"actived",7);
	close(wfd);
	
	while(1)
	{	
		int Status;
		Status=getstatus();
		if(Status){   //1被动唤醒
			sleep(5);
			system("bash /home/pi/master/shell/iat.sh");//录制要识别的语句
		
			Py_Initialize();
			PyCall("mix","iaten","()");
			Py_Finalize();
			//每调用一次Python程序要打开关闭python接口
		
			moduleinit();//功能模块集成初始化。
			if(Jump==1) continue;
			Py_Initialize();
			PyCall("mix","tuling","()");
			Py_Finalize();
			system("python /home/pi/master/snowboy/examples/Python/demo.py /home/pi/master/snowboy/examples/Python/HiMaster.pmdl &");
		}
		else {
			
			//主动唤醒
			//wake();
		}
		usleep(20000);//20ms
	}
	return 0;
}
