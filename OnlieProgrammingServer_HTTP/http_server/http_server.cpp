#include"http_server.h"

//处理uri
char* dispose_uri(struct evhttp_request *req)
{
	char output[2048] = {0};
	char tmp[1024];
	//获取客户端请求的URI(使用evhttp_request_uri或直接req->uri)
	const char *uri;
	uri = evhttp_request_uri(req);
	sprintf(tmp, "uri=%s\n", uri);
	strcat(output, tmp);
	sprintf(tmp, "uri=%s\n", req->uri);
	strcat(output, tmp);
	//decoded uri
	char *decoded_uri;
	decoded_uri = evhttp_decode_uri(uri);
	sprintf(tmp, "decoded_uri=%s\n", decoded_uri);
	strcat(output, tmp);
	//解析URI的参数(即GET方法的参数)
	struct evkeyvalq params;
	//将URL数据封装成key-value格式,q=value1, s=value2
	evhttp_parse_query(decoded_uri, &params);
	//得到q所对应的value
	sprintf(tmp, "q=%s\n", evhttp_find_header(&params, "q"));
	strcat(output, tmp);
	//得到s所对应的value
	sprintf(tmp, "s=%s\n", evhttp_find_header(&params, "s"));
	strcat(output, tmp);
	free(decoded_uri);

	char *res = output;
	return res;
}



//封装header
void encapsulation_header(struct evhttp_request &req)
{
	evhttp_add_header(req.output_headers, "Server", MYHTTPD_SIGNATURE);
	evhttp_add_header(req.output_headers, "Content-Type", "text/plain; charset = UTF - 8");
	evhttp_add_header(req.output_headers, "Connection", "close"
	);
}


//数据处理
int dispose_data(struct evhttp_request *req)
{
	//获取POST方法的数据
	char *post_data = (char *)EVBUFFER_DATA(req->input_buffer);
	char userid[BUFSIZ] = { 0 };
	char language[BUFSIZ] = { 0 };
	char head[BUFSIZ] = { 0 };
	//获取head userid language
	sscanf(post_data, "%[^ ] %[^ ] %[^ \r\n]", head,userid,language);
	if (strcmp(head, HEAD) != 0){
		cout << "head error" << endl;
		return -1;
	}
	if (strlen(userid) != USER_ID_LEN){
		cout << "id error" << endl;
		return -1;
	}
	if (strlen(language) != USER_LANGUAGE_LEN) {
		cout << "language error" << endl;
		return -1;
	}

	string program = post_data;
	int end=get_code_end_pos(post_data);//代码结束位置下标
	//cout << "end:"<<end ;
	int pos= get_code_pos(post_data);//获取代码所在位置的下标
	//cout<<"  pos:"<<pos<<endl;
	int len = end - pos;
	if (pos == -1){
		cout << "Not fund code" << endl;
		return -1;
	}
	if (end == -1) {
		cout << "Not fund code end" << endl;
		return -1;
	}
	program = program.substr(pos,len);
	//cout << "--------------------" << endl;
	//cout << program << endl;
	//cout << "--------------------" << endl;

	int res = make_dir(userid, language, program);
	if (res == -1){
		chdir(DIR);//变更工作目录到源程序所在的文件夹
		rmdir(userid);
		cout << "make_dir error" << endl;
		return -1;
	}

	if (make_test(req, res) == -1){
		chdir(DIR);//变更工作目录到源程序所在的文件夹
		rmdir(userid);
		cout<<"make_test error\n"<<endl;
		return -1;
	}

	if (out_test(req, res) == -1){
		chdir(DIR);//变更工作目录到源程序所在的文件夹
		rmdir(userid);
		cout << "out_test error" << endl;
		return -1;
	}
	chdir(DIR);//变更工作目录到源程序所在的文件夹
	rmdir(userid);
	return 0;
}