#include"http_server.h"

int pthread_create_test(evhttp_request *req)
{
	pthread_t tid;
	pthread_attr_t attr;//�����߳�����
	int ret;
	ret = pthread_attr_init(&attr);//��ʼ���߳�����
	if (ret != 0)
	{
		fprintf(stderr, "pthread_attr_init error:%s\n", strerror(ret));
		exit(1);
	}
	//�����߳�����Ϊ����̬
	ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (ret != 0)
	{
		fprintf(stderr, "pthread_attr_setdetachstate error:%s\n", strerror(ret));
		exit(1);
	}
	//�������Դ����߳�
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