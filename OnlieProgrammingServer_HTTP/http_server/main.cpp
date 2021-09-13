#include"http_server.h"
//������ģ��
void httpd_handler(struct evhttp_request *req, void *arg) 
{
	pthread_create_test(req);

}

void show_help() {
	char help[BUFSIZ] = " http://localhost:8080\n -l <ip_addr> interface to listen on, default is 0.0.0.0\n -p <num> port number to listen on, default is 1984\n -d run as a deamon\n -t <second> timeout for a http request, default is 120seconds\n -h print this help and exit\n\n";
	fprintf(stderr, "%s", help);
}

//������̷���SIGTERM/SIGHUP/SIGINT/SIGQUIT��ʱ����ֹevent���¼�����
void signal_handler(int sig) {
	switch (sig) {
	case SIGTERM:
	case SIGHUP:
	case SIGQUIT:
	case SIGINT:
		event_loopbreak(); //��ֹ����event_dispatch()���¼�����ѭ����ִ��֮��Ĵ���
		break;
	}
}

int main() {
	//int argc, char *argv[]
	//�Զ����źŴ�����
	
	//string packet_error = "Your packet is wrong.";
	//struct evbuffer *buf_error = evbuffer_new();
	signal(SIGHUP, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);

	//��ȡ����
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
	//�ж��Ƿ�������-d����daemon����
	//if (httpd_option_daemon) {
	//	pid_t pid;
	//	pid = fork();
	//	if (pid < 0) {
	//		perror("fork failed");
	//		exit(EXIT_FAILURE);
	//	}
	//	if (pid > 0) {
	//		//�����ӽ��̳ɹ����˳�������
	//		exit(EXIT_SUCCESS);
	//	}
	//}
	/* ʹ��libevent����HTTP Server */

	//��ʼ��event API
	event_init();
	//����һ��http server
	struct evhttp *httpd;
	httpd = evhttp_start(IP, PORT);
	evhttp_set_timeout(httpd, HTTP_TIMEOUT);
	//ָ��generic callback
	evhttp_set_gencb(httpd, httpd_handler, NULL);
	//Ҳ����Ϊ�ض���URIָ��callback
	//evhttp_set_cb(httpd, "/", specific_handler, NULL);
	//ѭ������events
	event_dispatch();
	evhttp_free(httpd);
	return 0;
}