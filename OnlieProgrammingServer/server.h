#pragma once
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<event2/event.h>
#include<event2/listener.h>
#include<event2/bufferevent.h>
#include<unistd.h>
#include<string.h>
using namespace std;

//�˿ں����ݰ���С
#define PORT 8888
#define BUFFSIZE 4096

#define HEAD "Onlie*"			//�̶���ͷ
#define HEAD_LEN 6				//��ͷ����
#define USER_ID_LEN 8			//ID����
#define USER_LANGUAGE_LEN 8		//��������ֽڳ���

//���Է���
#define C		"c*******"
#define CPP		"cpp*****"
#define PYTHON	"python**"

//�����в���
#define TOUCH "touch "
#define CD	"cd "
#define MKDIR "mkdir "
#define DIR ".."


//����ִ�н������ĺ���
int out_test(struct bufferevent *bev, int language);

//������뺯��
int make_test(struct bufferevent *bev, int language);

//�ļ��з��ຯ��
int makedir_test(struct bufferevent *bev, char* userid, int language);

//��ȡ��ͷ����
bool read_head(struct bufferevent *bev);

//��ȡID����
void read_userid(struct bufferevent *bev, char *userid);

//��ȡ������������
int read_language(struct bufferevent *bev);

