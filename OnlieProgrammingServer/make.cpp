#include"server.h"
//�ļ��з��ຯ��
int makedir_test(struct bufferevent *bev, char* userid, int language)
{
	char data[BUFFSIZE] = { 0 };//��������
	memset(data, '\0', sizeof(data));
	bufferevent_read(bev, data, sizeof(data));
	if (strlen(data) > 0)//�����ݲ�д��
	{
		string makedir = MKDIR + (string)userid;
		system(makedir.c_str());//����ID�����ļ���

		chdir(userid);//�������Ŀ¼���û����ļ���
		ofstream ofs;
		if (language == 1)
		{
			ofs.open("test.c", ios::trunc | ios::out);//����ļ��Ѿ�����,��ɾ���ٴ�����
			ofs << data;
			return 1;
		}
		if (language == 2)
		{
			ofs.open("test.cpp", ios::trunc | ios::out);
			ofs << data;
			return 2;
		}
		if (language == 3)
		{
			ofs.open("test.py", ios::trunc | ios::out);
			ofs << data;
			return 3;
		}
		ofs.close();
	}
	return -1;
}

//���뺯��
int make_test(struct bufferevent *bev, int language)
{
	system("touch make");
	if (language == 1)
	{
		system("timeout 1 gcc test.c  > make 2>&1");//�ض����ļ�make��
		char buf[BUFFSIZE];
		memset(buf, '\0', sizeof(buf));
		ifstream ifs;
		ifs.open("make", ios::in);
		if (!ifs.is_open()) {
			cout << "openfile make error" << endl;
		}
		ifs.get(buf, sizeof(buf), '\0');//���ļ��ж�ȡ�ַ����ַ���buf���������ַ�'\0'���ȡ��sizeof(buf)���ַ�ʱ��ֹ��
		ifs.close();
		if (strlen(buf) > 0)//make��������˵�����뱨����
		{
			bufferevent_write(bev, buf, strlen(buf));//���ʹ�����ʾ
			return -1;
		}
		return 1;
	}

	if (language == 2)
	{
		system("timeout 1 g++ test.cpp  > make 2>&1");//�ض����ļ�make��
		char buf[BUFFSIZE];
		memset(buf, '\0', sizeof(buf));
		ifstream ifs;
		ifs.open("make", ios::in);
		if (!ifs.is_open()) {
			cout << "openfile make error" << endl;
		}
		ifs.get(buf, sizeof(buf), '\0');
		ifs.close();
		if (strlen(buf) > 0)//make��������˵�����뱨����
		{
			bufferevent_write(bev, buf, strlen(buf));//���ʹ�����ʾ
			return -1;
		}
		return 2;
	}

	if (language == 3)
	{
		char data[50] = "The results of the program are as follows:\n";
		bufferevent_write(bev, data, strlen(data));//python�������,ֱ����out�������
		return 3;
	}
	return -1;
}

//���г���ĺ���
int out_test(struct bufferevent *bev, int language)
{
	string name("touch out");
	system(name.c_str());//�������ڴ洢�������н�����ļ�out
	if (language == 1|| language==2)
	{
		//ʹ��timeout���Ƴ���ִ��ʱ��Ϊ0.01��(��ֹ��ѭ���ĳ���)
		system("timeout 1 ./a.out > out 2>&1");//�ض����ļ�out��
		char buf[BUFFSIZE];
		memset(buf, '\0', sizeof(buf));
		ifstream ifs;
		ifs.open("out", ios::in);
		if (!ifs.is_open()) {
			cout << "openfile out error" << endl;
		}
		ifs.get(buf, sizeof(buf), '\0');//���ļ��ж�ȡ�ַ����ַ���buf���������ַ�'\0'���ȡ��sizeof(buf)���ַ�ʱ��ֹ��
		ifs.close();
		if (strlen(buf) > 0)//��ȡ������,˵�����������
		{
			bufferevent_write(bev, buf, strlen(buf));//�ش��������
			return 0;
		}
		return -1;
	}

	if (language == 3)
	{
		//ʹ��timeout���Ƴ���ִ��ʱ��Ϊ0.01��
		system("timeout 1 python3 test.py > out 2>&1");//�ض���
		char buf[BUFFSIZE];
		memset(buf, '\0', sizeof(buf));
		ifstream ifs;
		ifs.open("out", ios::in);
		if (!ifs.is_open()) {
			cout << "openfile out error" << endl;
		}
		ifs.get(buf, sizeof(buf), '\0');
		ifs.close();
		if (strlen(buf) > 0)//��ȡ������,˵�����������
		{
			bufferevent_write(bev, buf, strlen(buf));//�ش��������
			return 0;
		}
		return -1;
	}
	return -1;
}