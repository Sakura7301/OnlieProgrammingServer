#include"http_server.h"
//请求处理模块
void httpd_handler(struct evhttp_request *req, void *arg) 
{
	pthread_create_test(req);

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

int main() {
	//int argc, char *argv[]
	//自定义信号处理函数
	
	//string packet_error = "Your packet is wrong.";
	//struct evbuffer *buf_error = evbuffer_new();
	signal(SIGHUP, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);

	//获取参数
	//int c;
	/*while ((c = getopt(argc, argv, "l:p:dt:h")) != -1) {
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
	}*/
	//判断是否设置了-d，以daemon运行
	//if (httpd_option_daemon) {
	//	pid_t pid;
	//	pid = fork();
	//	if (pid < 0) {
	//		perror("fork failed");
	//		exit(EXIT_FAILURE);
	//	}
	//	if (pid > 0) {
	//		//生成子进程成功，退出父进程
	//		exit(EXIT_SUCCESS);
	//	}
	//}
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