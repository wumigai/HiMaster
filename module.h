#include <stdio.h>
#include "usepython.h"
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define  OPATH "/home/pi/master/rebs.txt"
#define FLAGS O_WRONLY|O_CREAT|O_TRUNC
#define MODE 00777
int Jump=0;

//清空机器人说
void clean_rebs(){
	system("> /home/pi/master/rebs.txt");
}
//机器人说
void rebspeak(char* sentence){
	int fd;
	printf("%s",sentence);
	if((fd=open(OPATH,FLAGS,MODE))<0){
		printf("open rebs error!\n");
	}
	else{
		if(write(fd,sentence,strlen(sentence))<0) printf("write rebs.txt error\n") ;
		close(fd);
		
	}
	Py_Initialize();
	PyCall("mix","mixen","()");
	Py_Finalize();
	//system("play /home/pi/master/out.mp3");
}
//我要听歌
void singsong(){
	if(SONG){
		int key;
		Py_Initialize();
		key=PyCall("mix","singsong","()");
		Py_Finalize();
		if(key){
			rebspeak("好的主人，现在为您播放"); 
			system("play /home/pi/Desktop/xsycq.mp3");
			rebspeak("您的品味真高");
			Jump = 1;//跳出循环。不执行图灵回复。
		}
	}
}

//module 功能模块
void moduleinit(){
	Jump=0;   //为零时没有使用tuling回复。
	singsong();
}