#include"server.h"

//读取包头
bool read_head(struct bufferevent *bev)
{
	char head[HEAD_LEN + 1];
	memset(head, '\0', sizeof(head));
	bufferevent_read(bev, head, HEAD_LEN);//读取包头
	if (strcmp(head, HEAD) == 0)
	{
		return true;
	}
	return false;
}

//读取用户ID
void read_userid(struct bufferevent *bev, char* userid)
{
	bufferevent_read(bev, userid, USER_ID_LEN);//读取用户ID
}

//读取编程语言
int read_language(struct bufferevent *bev)
{
	char language[USER_LANGUAGE_LEN + 1];
	memset(language, '\0', sizeof(language));
	bufferevent_read(bev, language, USER_LANGUAGE_LEN);//读取语言
	if (strlen(language) == 8)
	{
		if (strcmp(language, C) == 0)
			return 1;

		if (strcmp(language, CPP) == 0)
			return 2;

		if (strcmp(language, PYTHON) == 0)
			return 3;
	}
	return -1;
}

//删除用户文件夹
void rm_dir(char* userid)
{
	chdir(DIR);//变更工作目录到源程序所在的文件夹
	string delete_source;
	delete_source = "rm -rf " + (string)userid;
	system(delete_source.c_str());//删除用户文件目录
}

//数据处理函数
int data_processing(struct bufferevent *bev)
{
	char userid[9] = { 0 };
	memset(userid, '\0', sizeof(userid));
	//读取包头
	if (read_head(bev))
	{
		//读取id
		read_userid(bev, userid);
		if (strlen(userid) > 0) {
			//读取编程语言
			int language = read_language(bev);
			if (language == -1) {
				return -1;//读取失败
			}
			//读取数据包并创建相关文件夹
			int res = makedir_test(bev, userid, language);
			if (res == -1) {
				return -2;//文件夹创建失败
			}
			//编译
			res = make_test(bev, res);
			if (res == -1){
				return -3;//编译失败
			}
			//运行
			res=out_test(bev, res);
			if(res==-1){
				return -4;//运行失败
			}
		}
	}
	rm_dir(userid);//删除用户目录
	return 0;
}

//线程的回调函数
void *pthread_func(void* arg)
{
	struct bufferevent *bev = (bufferevent *)arg;
	data_processing(bev);
	return (void*)NULL;
}

//线程创建函数
int pthread_create(struct bufferevent *bev)
{
	pthread_t tid;
	pthread_attr_t attr;//创建线程属性
	int ret;
	ret = pthread_attr_init(&attr);//初始化线程属性
	if (ret != 0)
	{
		fprintf(stderr, "pthread_attr_init error:%s\n", strerror(ret));
		exit(1);
	}
	//设置线程属性为分离态
	ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (ret != 0)
	{
		fprintf(stderr, "pthread_attr_setdetachstate error:%s\n", strerror(ret));
		exit(1);
	}
	//基于属性创建线程
	ret = pthread_create(&tid, &attr, pthread_func, bev);
	if (ret != 0)
	{
		fprintf(stderr, "pthread_attr_setdetachstate error:%s\n", strerror(ret));
		exit(1);
	}
	return 0;
}
