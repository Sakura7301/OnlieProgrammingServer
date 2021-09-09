#pragma once
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<unistd.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include <event2/util.h>
#include <signal.h>
#include <sys/stat.h>
#include<pthread.h>
//for struct evkeyvalq
#include <sys/queue.h>
#include <event.h>
//for http
//#include <evhttp.h>
#include <event2/http.h>
#include <event2/http_struct.h>
#include <event2/http_compat.h>


using namespace std;

#define MYHTTPD_SIGNATURE "myhttpd v 0.0.1"
//端口和数据包大小
#define PORT 8888
#define IP "0.0.0.0"
#define HTTP_TIMEOUT 120
#define BUFFSIZE 4096

#define HEAD "Onlie*"			//固定包头
#define HEAD_LEN 6				//包头长度
#define USER_ID_LEN 8			//ID长度
#define USER_LANGUAGE_LEN 8	   //编程语言字节长度

//语言分类
//这样设计是为了更好的分割字符串
//只有识别到6个连续*才会匹配成功
#define C		"CI******"
#define CPP		"CP******"
#define PYTHON	"PY******"

//命令行操作
#define TOUCH "touch "
#define CD	"cd "
#define MKDIR "mkdir "
#define DIR ".."

//文件不存在
#define NOFILE "File does not exist"

//处理uri
char* dispose_uri(struct evhttp_request *req);

//封装header
void encapsulation_header(struct evhttp_request &req);

//处理数据
int dispose_data(struct evhttp_request *req);

//创建文件夹
int make_dir(const char* userid, const char* language,string data);

//判断语言类别的函数
int language_test(const char* language);

//编译函数
int make_test(evhttp_request *req,int language);

//运行函数
int out_test(evhttp_request *req,int language);

//删除用户目录
void rmdir(char *userid);

//线程创建函数
int pthread_create_test(evhttp_request *req);

//线程回调函数
void* pthread_func(void* arg);

int get_code_pos(char* data);

int get_code_end_pos(char* data);