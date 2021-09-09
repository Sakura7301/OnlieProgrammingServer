#include"http_server.h"

int pthread_create_test(evhttp_request *req)
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
	ret = pthread_create(&tid, &attr, pthread_func, req);
	if (ret != 0)
	{
		fprintf(stderr, "pthread_attr_setdetachstate error:%s\n", strerror(ret));
		exit(1);
	}
	return 0;
}

void* pthread_func(void* arg)
{
	evhttp_request *req = (evhttp_request *)arg;
	encapsulation_header(*req);
	int res = dispose_data(req);
	if (res == -1)
	{
		cout << "dispose_data error" << endl;
	}
	return (void*)NULL;
}

//获取代码的下标
int get_code_pos(char* data)
{
	char* datas= data;
	int index = 0;
	for (int i=0;i<(int)strlen(datas)-1;i++)
	{
		if (index == 6) {
			return i;
		}
		if (datas[i] == '*') {
			index++;
			continue;
		}
		index=0;
	}
	return -1;
}

int get_code_end_pos(char* data)
{
	char* datas = data;
	int index = 0;
	for (int i = 0; i < (int)strlen(datas) - 1; i++)
	{
		if (index == 6) {
			return i;
		}
		if (datas[i] == '#') {
			index++;
			continue;
		}
		index = 0;
	}
	return -1;
}