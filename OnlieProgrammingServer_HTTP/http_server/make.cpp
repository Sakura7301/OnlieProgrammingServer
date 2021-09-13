#include"http_server.h"
int language_test(const char* language)
{
	if (strlen(language) == USER_LANGUAGE_LEN)
	{
		if (strcmp(language, C) == 0){
			return 1;
		}
		if (strcmp(language, CPP) == 0) {
			return 2;
		}
		if (strcmp(language, PYTHON) == 0) {
			return 3;
		}
	}
	return -1;
}
int make_dir(const char* userid, const char* language,string data)
{
	rmdir(userid);
	int type = language_test(language);
	string makedir = MKDIR + (string)userid;
	system(makedir.c_str());//����ID�����ļ���
	chdir(userid);//�������Ŀ¼���û����ļ���
	if (type != -1)
	{
		ofstream ofs;
		if (type == 1){
			ofs.open("test.c", ios::trunc | ios::out);//����ļ��Ѿ�����,��ɾ���ٴ�����
			ofs << data;
			ofs.close();
			return 1;
		}
		if (type == 2){
			ofs.open("test.cpp", ios::trunc | ios::out);
			ofs << data;
			ofs.close();
			return 2;
		}
		if (type == 3){
			ofs.open("test.py", ios::trunc | ios::out);
			ofs << data;
			ofs.close();
			return 3;
		}
	}
	return -1;
}

//���뺯��
int make_test(evhttp_request *req,int language)
{
	char buf[BUFSIZ] = {0};
	memset(buf, '\0', sizeof(buf));
	system("touch make.txt");
	struct evbuffer *buf_make = evbuffer_new();
	if (language == 1)
	{
		system("timeout 1 gcc test.c  > make.txt 2>&1");//�ض����ļ�make��
		ifstream ifs;
		ifs.open("make.txt", ios::in);
		if (!ifs.is_open()) {
			cout << "openfile make.txt error" << endl;
			ifs.close();
			return -1;
		}
		ifs.get(buf, sizeof(buf), '\0');//���ļ��ж�ȡ�ַ����ַ���buf���������ַ�'\0'���ȡ��sizeof(buf)���ַ�ʱ��ֹ��
		ifs.close();
		if (strlen(buf) > 0)//make��������˵�����뱨����
		{
			cout<<buf<<endl;
			evbuffer_add_printf(buf_make, buf);
			evhttp_send_reply(req, HTTP_OK, "OK", buf_make);//��������
			evbuffer_free(buf_make);
			return -1;
		}
	}

	if (language == 2)
	{
		system("timeout 1 g++ test.cpp  > make.txt 2>&1");//�ض����ļ�make��
		ifstream ifs;
		ifs.open("make.txt", ios::in);
		if (!ifs.is_open()) {
			cout << "openfile make.txt error" << endl;
			ifs.close();
			return -1;
		}
		ifs.get(buf, sizeof(buf), '\0');
		ifs.close();
		if (strlen(buf) > 0)//make��������˵�����뱨����
		{
			evbuffer_add_printf(buf_make, buf);
			evhttp_send_reply(req, HTTP_OK, "OK", buf_make);//��������
			evbuffer_free(buf_make);
			cout << buf << endl;
			return -1;
		}
	}
	return 0;
}

//���к���
int out_test(evhttp_request *req,int language)
{
	char data[BUFSIZ] = {0};
	struct evbuffer *buf_make = evbuffer_new();
	memset(data, '\0', sizeof(data));
	string name("touch out");
	system(name.c_str());//�������ڴ洢�������н�����ļ�out
	if (language == 1 || language == 2)
	{
		//ʹ��timeout���Ƴ���ִ��ʱ��Ϊ1��(��ֹ��ѭ���ĳ���)
		system("timeout 1 ./a.out > out 2>&1");//�ض����ļ�out��
		ifstream ifs;
		ifs.open("out", ios::in);
		if (!ifs.is_open()) {
			cout << "openfile out error" << endl;
			ifs.close();
			return -1;
		}
		ifs.get(data, sizeof(data), '\0');//���ļ��ж�ȡ�ַ����ַ���data���������ַ�'\0'���ȡ��sizeof(buf)���ַ�ʱ��ֹ��
		ifs.close();
		if (strlen(data) > 0) {
			evbuffer_add_printf(buf_make, data);
			evhttp_send_reply(req, HTTP_OK, "OK", buf_make);//��������
			evbuffer_free(buf_make);
		}
		return 0;
	}

	if (language == 3)
	{
		//ʹ��timeout���Ƴ���ִ��ʱ��Ϊ1��
		system("timeout 1 python3 test.py > out 2>&1");//�ض���
		system("cat out");
		ifstream ifs;
		ifs.open("out", ios::in);
		if (!ifs.is_open()) {
			cout << "openfile out error" << endl;
			ifs.close();
			return -1;
		}
		ifs.get(data, sizeof(data), '\0');
		ifs.close();
		if (strlen(data) > 0){
			evbuffer_add_printf(buf_make, data);
			evhttp_send_reply(req, HTTP_OK, "OK", buf_make);//��������
			evbuffer_free(buf_make);
		}
		return 0;
	}
	return -1;
}

//ɾ���û�Ŀ¼
void rmdir(char *userid)
{
	string delete_source;
	delete_source = "rm -rf " + (string)userid;
	system(delete_source.c_str());//ɾ���û��ļ�Ŀ¼
}