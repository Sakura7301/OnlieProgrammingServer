#include"server.h"

//���ص�����
void read_cb(struct bufferevent *bev, void *arg)
{
	char userid[9] = { 0 };
	memset(userid, '\0', sizeof(userid));
	//��ȡ��ͷ
	if (read_head(bev))
	{
		//��ȡid
		read_userid(bev, userid);//��ȡ�û�id
		if (strlen(userid) > 0) {
			//��ȡ�������
			int language = read_language(bev);//��ȡ�������
			if (language == -1) {
				return;//��ȡ��-1��ʾ�û��ı������ѡ�����
			}

			//��ȡ���ݰ�����������ļ���
			int res = makedir_test(bev, userid, language);
			if (res == -1) {
				cout << "makedir_test error" << endl;
				return;
			}
			int res2 = make_test(bev, res);//����
			if (res2 != -1) {
				out_test(bev, res2);//ֻ�б���ɹ��˲Ż�����
			}
		}
	}
	chdir(DIR);//�������Ŀ¼��Դ�������ڵ��ļ���
	string delete_source;
	delete_source = "rm -rf " + (string)userid;
	system(delete_source.c_str());//ɾ���û��ļ�Ŀ¼
}




//�¼��ص�����
void event_cb(struct bufferevent *bev, short events, void *arg)
{

	cout << "event_cb is being executed." << endl;
	if (events & BEV_EVENT_EOF)
	{
		cout << "Connection disconnected." << endl;
	}
	else if (events & BEV_EVENT_ERROR)
	{
		cout << "Network anomalies!" << endl;
	}
	bufferevent_free(bev);
	cout << "The bufferevent has been released." << endl;
}


//�¼��������Ļص�����
void cb_listener(struct evconnlistener *listener,
	evutil_socket_t fd,
	struct sockaddr *addr,
	int len, void *ptr)
{
	cout << "There's a new connection." << endl;

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
	int res = event_base_dispatch(base);
	//int res=event_base_loop(base,EVLOOP_NONBLOCK);
	cout << res << endl;


	evconnlistener_free(listener);
	event_base_free(base);
	return 0;
}