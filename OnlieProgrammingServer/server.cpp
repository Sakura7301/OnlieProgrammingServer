#include"server.h"

//读回调函数
void read_cb(struct bufferevent *bev, void *arg)
{
	data_processing(bev);//调用数据处理函数
}


//事件回调函数
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


//事件监听器的回调函数
void cb_listener(struct evconnlistener *listener,
	evutil_socket_t fd,
	struct sockaddr *addr,
	int len, void *ptr)
{
	//接收传入的base
	struct event_base* base = (struct event_base*)ptr;

	//与客户端通信
	struct bufferevent *bev = NULL;
	//创建bufferevent.(因为创建bufferevent需要用到base,因此我们将base用泛型指针传入回调函数使用)
	bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

	//给bufferevent缓冲区设置回调函数
	bufferevent_setcb(bev, read_cb, NULL, event_cb, NULL);

	//设置使能
	bufferevent_enable(bev, EV_READ);//设置读缓冲区使能
}
int main()
{
	//初始化服务器的地址结构
	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(PORT);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);

	//创建base
	event_base * base = event_base_new();

	//设置监听器
	evconnlistener *listener;
	listener = evconnlistener_new_bind(base, cb_listener, base,
		LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
		-1, (struct sockaddr*)&serv, sizeof(serv));

	//开始循环
	cout << "Server started, listening." << endl;
	event_base_dispatch(base);

	evconnlistener_free(listener);
	event_base_free(base);
	return 0;
}