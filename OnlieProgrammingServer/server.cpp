#include"server.h"

//���ص�����
void read_cb(struct bufferevent *bev, void *arg)
{
	data_processing(bev);//�������ݴ�����
}


//�¼��ص�����
void event_cb(struct bufferevent *bev, short events, void *arg)
{
	//cout << "event_cb is being executed." << endl;
	if (events & BEV_EVENT_EOF)
	{
		//cout << "Connection disconnected." << endl;
	}

	if (events & BEV_EVENT_ERROR)
	{
		//cout << "Network anomalies!" << endl;
	}
	bufferevent_free(bev);
	//cout << "The bufferevent has been released." << endl;
}


//�¼��������Ļص�����
void cb_listener(struct evconnlistener *listener,
	evutil_socket_t fd,
	struct sockaddr *addr,
	int len, void *ptr)
{
	//���մ����base
	struct event_base* base = (struct event_base*)ptr;

	//��ͻ���ͨ��
	struct bufferevent *bev = NULL;
	//����bufferevent.(��Ϊ����bufferevent��Ҫ�õ�base,������ǽ�base�÷���ָ�봫��ص�����ʹ��)
	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

	//��bufferevent���������ûص�����
	bufferevent_setcb(bev, read_cb, NULL, event_cb, NULL);

	//����ʹ��
	bufferevent_enable(bev, EV_READ);//���ö�������ʹ��
}
int main()
{
	//��ʼ���������ĵ�ַ�ṹ
	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(PORT);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	//����base
	event_base * base = event_base_new();

	//���ü�����
	evconnlistener *listener;
	listener = evconnlistener_new_bind(base, cb_listener, base,
		LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
		-1, (struct sockaddr*)&serv, sizeof(serv));

	//��ʼѭ��
	cout << "Server started, listening." << endl;
	event_base_dispatch(base);

	evconnlistener_free(listener);
	event_base_free(base);
	return 0;
}