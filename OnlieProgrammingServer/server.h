#pragma once
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<unistd.h>
#include<pthread.h>
#include<event2/event.h>
#include<event2/listener.h>
#include<event2/bufferevent.h>
#include<unistd.h>
#include<string.h>
using namespace std;

//端口和数据包大小
#define PORT 8888
#define BUFFSIZE 4096

#define HEAD "Onlie*"			//固定包头
#define HEAD_LEN 6				//包头长度
#define USER_ID_LEN 8			//ID长度
#define USER_LANGUAGE_LEN 8		//编程语言字节长度

//语言分类
#define C		"c*******"
#define CPP		"cpp*****"
#define PYTHON	"python**"

//命令行操作
#define TOUCH "touch "
#define CD	"cd "
#define MKDIR "mkdir "
#define DIR ".."


//程序执行结果输出的函数
int out_test(struct bufferevent *bev, int language);

//程序编译函数
int make_test(struct bufferevent *bev, int language);

//文件夹分类函数
int makedir_test(struct bufferevent *bev, char* userid, int language);

//读取包头函数
bool read_head(struct bufferevent *bev);

//读取ID函数
void read_userid(struct bufferevent *bev, char *userid);

//读取编程语言类别函数
int read_language(struct bufferevent *bev);

//删除用户文件夹的函数
void rm_dir(char* userid);

//数据处理函数
int data_processing(struct bufferevent *bev);

//线程的回调函数
void *pthread_func(void* arg);

//线程创建函数
int pthread_create(struct bufferevent *bev);