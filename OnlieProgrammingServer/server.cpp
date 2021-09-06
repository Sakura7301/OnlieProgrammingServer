#include"server.h"

//读回调函数
void read_cb(struct bufferevent *bev, void *arg)
{
	char userid[9] = { 0 };
	memset(userid, '\0', sizeof(userid));
	//读取包头
	if (read_head(bev))
	{
		//读取id
		read_userid(bev, userid);//获取用户id
		if (strlen(userid) > 0) {
			//读取编程语言
			int language = read_language(bev);//读取编程语言
			if (language == -1) {
				return;//读取到-1表示用户的编程语言选择错误
			}

			//读取数据包并创建相关文件夹
			int res = makedir_test(bev, userid, language);
			if (res == -1) {
				cout << "makedir_test error" << endl;
				return;
			}
			int res2 = make_test(bev, res);//编译
			if (res2 != -1) {
				out_test(bev, res2);//只有编译成功了才会运行
			}
		}
	}
	chdir(DIR);//变更工作目录到源程序所在的文件夹
	string delete_source;
	delete_source = "rm -rf " + (string)userid;
	system(delete_source.c_str());//删除用户文件目录
}




//事件回调函数
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


//事件监听器的回调函数
void cb_listener(struct evconnlistener *listener,
	evutil_socket_t fd,
	struct sockaddr *addr,
	int len, void *ptr)
{
	cout << "There's a new connection." << endl;

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
	int res = event_base_dispatch(base);
	//int res=event_base_loop(base,EVLOOP_NONBLOCK);
	cout << res << endl;


	evconnlistener_free(listener);
	event_base_free(base);
	return 0;
}