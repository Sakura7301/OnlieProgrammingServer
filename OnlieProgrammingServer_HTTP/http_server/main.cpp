#include"http_server.h"
//请求处理模块
void httpd_handler(struct evhttp_request *req, void *arg) 
{
	encapsulation_header(*req);
	char *post_data = (char *)EVBUFFER_DATA(req->input_buffer);
	if (post_data == NULL || req->input_buffer == NULL) {
		char ERROR_DATA[BUFFSIZE * 3] = { 0 };
		ifstream ifs;
		ifs.open(HTML_PATH, ios::in);
		ifs.get(ERROR_DATA, sizeof(ERROR_DATA), '\0');//从文件中读取字符到字符串buf，当遇到字符'\0'或读取了sizeof(buf)个字符时终止。
		ifs.close();
		struct evbuffer *buf_html = evbuffer_new();
		evbuffer_add_printf(buf_html, ERROR_DATA);
		evhttp_send_reply(req, HTTP_OK, "OK", buf_html);//发送数据
		evbuffer_free(buf_html);
		return;
	}
	pthread_create_test(req);
	return;

}

void show_help() {
	char help[BUFSIZ] = " http://localhost:8080\n -l <ip_addr> interface to listen on, default is 0.0.0.0\n -p <num> port number to listen on, default is 1984\n -d run as a deamon\n -t <second> timeout for a http request, default is 120seconds\n -h print this help and exit\n\n";
	fprintf(stderr, "%s", help);
}

//当向进程发出SIGTERM/SIGHUP/SIGINT/SIGQUIT的时候，终止event的事件侦听
void signal_handler(int sig) {
	switch (sig) {
	case SIGTERM:
	case SIGHUP:
	case SIGQUIT:
	case SIGINT:
		event_loopbreak(); //终止侦听event_dispatch()的事件侦听循环，执行之后的代码
		break;
	}
}

int main(int argc, char *argv[]) {//注册信号
	signal(SIGHUP, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);

	char *httpd_option_listen = IP;
	int httpd_option_port = htons(PORT);
	int httpd_option_daemon = 0;
	int httpd_option_timeout = HTTP_TIMEOUT;


	//获取参数
	int c;
	while ((c = getopt(argc, argv, "l:p:dt:h")) != -1) {
		switch (c) {
		case 'l':
			httpd_option_listen = optarg;
			break;
		case 'p':
			httpd_option_port = atoi(optarg);
			break;
		case 'd':
			httpd_option_daemon = 1;
			break;
		case 't':
			httpd_option_timeout = atoi(optarg);
			break;
		case 'h':
		default:
			show_help();
			exit(EXIT_SUCCESS);
		}
	}
	//判断是否设置了-d，以daemon运行
	if (httpd_option_daemon) {
		pid_t pid;
		pid = fork();
		if (pid < 0) {
			perror("fork failed");
			exit(EXIT_FAILURE);
		}
		if (pid > 0) {
			//生成子进程成功，退出父进程
			cout << "daemon succesful" << endl;
			exit(EXIT_SUCCESS);
		}
	}
	/* 使用libevent创建HTTP Server */

	//初始化event API
	event_init();
	//创建一个http server
	struct evhttp *httpd;
	httpd = evhttp_start(IP, PORT);
	evhttp_set_timeout(httpd, HTTP_TIMEOUT);
	//指定generic callback
	evhttp_set_gencb(httpd, httpd_handler, NULL);
	//也可以为特定的URI指定callback
	//evhttp_set_cb(httpd, "/", specific_handler, NULL);
	//循环处理events


	event_dispatch();



	evhttp_free(httpd);
	return 0;
}