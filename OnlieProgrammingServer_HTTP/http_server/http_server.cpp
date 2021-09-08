#include"http_server.h"

//����uri
char* dispose_uri(struct evhttp_request *req)
{
	char output[2048] = {0};
	char tmp[1024];
	//��ȡ�ͻ��������URI(ʹ��evhttp_request_uri��ֱ��req->uri)
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
	//����URI�Ĳ���(��GET�����Ĳ���)
	struct evkeyvalq params;
	//��URL���ݷ�װ��key-value��ʽ,q=value1, s=value2
	evhttp_parse_query(decoded_uri, &params);
	//�õ�q����Ӧ��value
	sprintf(tmp, "q=%s\n", evhttp_find_header(&params, "q"));
	strcat(output, tmp);
	//�õ�s����Ӧ��value
	sprintf(tmp, "s=%s\n", evhttp_find_header(&params, "s"));
	strcat(output, tmp);
	free(decoded_uri);

	char *res = output;
	return res;
}



//��װheader
void encapsulation_header(struct evhttp_request &req)
{
	evhttp_add_header(req.output_headers, "Server", MYHTTPD_SIGNATURE);
	evhttp_add_header(req.output_headers, "Content-Type", "text/plain; charset = UTF - 8");
	evhttp_add_header(req.output_headers, "Connection", "close"
	);
}


//���ݴ���
int dispose_data(struct evhttp_request *req)
{
	//���������

	//��ȡPOST����������
	char *post_data = (char *)EVBUFFER_DATA(req->input_buffer);
	char userid[9] = { 0 };
	char language[9] = { 0 };
	char head[7] = { 0 };
	//��ȡhead userid language
	sscanf(post_data, "%[^ ] %[^ ] %[^ \r\n]", head,userid,language);
	if (strcmp(head, HEAD) != 0){
		cout << "head error" << endl;
		return -1;
	}
	if (strlen(userid) != 8){
		cout << "id error" << endl;
		return -1;
	}
	if (strlen(language) != 8) {
		cout << "language error" << endl;
		return -1;
	}

	string program = post_data;
	long pos= program.find_last_of('*');
	//��ȡ�������
	program = program.substr(pos+1);
	int res = make_dir(userid, language, program);
	if (res == -1){
		chdir(DIR);//�������Ŀ¼��Դ�������ڵ��ļ���
		rmdir(userid);
		cout << "make_dir error" << endl;
		return -1;
	}

	if (make_test(req, res) == -1){
		chdir(DIR);//�������Ŀ¼��Դ�������ڵ��ļ���
		rmdir(userid);
		cout<<"make_test error\n"<<endl;
		return -1;
	}

	if (out_test(req, res) == -1){
		chdir(DIR);//�������Ŀ¼��Դ�������ڵ��ļ���
		rmdir(userid);
		cout << "out_test error" << endl;
		return -1;
	}
	chdir(DIR);//�������Ŀ¼��Դ�������ڵ��ļ���
	rmdir(userid);
	return 0;
}