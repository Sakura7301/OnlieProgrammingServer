#include"server.h"

//��ȡ��ͷ
bool read_head(struct bufferevent *bev)
{
	char head[HEAD_LEN + 1];
	memset(head, '\0', sizeof(head));
	bufferevent_read(bev, head, HEAD_LEN);//��ȡ��ͷ
	if (strcmp(head, HEAD) == 0)
	{
		return true;
	}
	return false;
}

//��ȡ�û�ID
void read_userid(struct bufferevent *bev, char* userid)
{
	bufferevent_read(bev, userid, USER_ID_LEN);//��ȡ�û�ID
}

//��ȡ�������
int read_language(struct bufferevent *bev)
{
	char language[USER_LANGUAGE_LEN + 1];
	memset(language, '\0', sizeof(language));
	bufferevent_read(bev, language, USER_LANGUAGE_LEN);//��ȡ����
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

//ɾ���û��ļ���
void rm_dir(char* userid)
{
	chdir(DIR);//�������Ŀ¼��Դ�������ڵ��ļ���
	string delete_source;
	delete_source = "rm -rf " + (string)userid;
	system(delete_source.c_str());//ɾ���û��ļ�Ŀ¼
}

//���ݴ�����
int data_processing(struct bufferevent *bev)
{
	char userid[9] = { 0 };
	memset(userid, '\0', sizeof(userid));
	//��ȡ��ͷ
	if (read_head(bev))
	{
		//��ȡid
		read_userid(bev, userid);
		if (strlen(userid) > 0) {
			//��ȡ�������
			int language = read_language(bev);
			if (language == -1) {
				return -1;//��ȡʧ��
			}
			//��ȡ���ݰ�����������ļ���
			int res = makedir_test(bev, userid, language);
			if (res == -1) {
				return -2;//�ļ��д���ʧ��
			}
			//����
			res = make_test(bev, res);
			if (res == -1){
				return -3;//����ʧ��
			}
			//����
			res=out_test(bev, res);
			if(res==-1){
				return -4;//����ʧ��
			}
		}
	}
	rm_dir(userid);//ɾ���û�Ŀ¼
	return 0;
}

//�̵߳Ļص�����
void *pthread_func(void* arg)
{
	struct bufferevent *bev = (bufferevent *)arg;
	data_processing(bev);
	return (void*)NULL;
}

//�̴߳�������
int pthread_create(struct bufferevent *bev)
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
	ret = pthread_create(&tid, &attr, pthread_func, bev);
	if (ret != 0)
	{
		fprintf(stderr, "pthread_attr_setdetachstate error:%s\n", strerror(ret));
		exit(1);
	}
	return 0;
}
