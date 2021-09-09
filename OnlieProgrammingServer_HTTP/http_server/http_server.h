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
//�˿ں����ݰ���С
#define PORT 8888
#define IP "0.0.0.0"
#define HTTP_TIMEOUT 120
#define BUFFSIZE 4096

#define HEAD "Onlie*"			//�̶���ͷ
#define HEAD_LEN 6				//��ͷ����
#define USER_ID_LEN 8			//ID����
#define USER_LANGUAGE_LEN 8	   //��������ֽڳ���

//���Է���
//���������Ϊ�˸��õķָ��ַ���
//ֻ��ʶ��6������*�Ż�ƥ��ɹ�
#define C		"CI******"
#define CPP		"CP******"
#define PYTHON	"PY******"

//�����в���
#define TOUCH "touch "
#define CD	"cd "
#define MKDIR "mkdir "
#define DIR ".."

//�ļ�������
#define NOFILE "File does not exist"

//����uri
char* dispose_uri(struct evhttp_request *req);

//��װheader
void encapsulation_header(struct evhttp_request &req);

//��������
int dispose_data(struct evhttp_request *req);

//�����ļ���
int make_dir(const char* userid, const char* language,string data);

//�ж��������ĺ���
int language_test(const char* language);

//���뺯��
int make_test(evhttp_request *req,int language);

//���к���
int out_test(evhttp_request *req,int language);

//ɾ���û�Ŀ¼
void rmdir(char *userid);

//�̴߳�������
int pthread_create_test(evhttp_request *req);

//�̻߳ص�����
void* pthread_func(void* arg);

int get_code_pos(char* data);

int get_code_end_pos(char* data);