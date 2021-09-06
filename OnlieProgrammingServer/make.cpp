#include"server.h"
//文件夹分类函数
int makedir_test(struct bufferevent *bev, char* userid, int language)
{
	char data[BUFFSIZE] = { 0 };//读缓冲区
	memset(data, '\0', sizeof(data));
	bufferevent_read(bev, data, sizeof(data));
	if (strlen(data) > 0)
	{

		string makedir = MKDIR + (string)userid;
		system(makedir.c_str());//根据ID创建文件夹

		chdir(userid);//变更工作目录到用户的文件夹

		if (language == 1)
		{
			ofstream ofs;
			ofs.open("test.c", ios::trunc | ios::out);//如果文件已经存在,则删除再创建打开
			ofs << data;
			ofs.close();
			return 1;
		}

		if (language == 2)
		{
			ofstream ofs;
			ofs.open("test.cpp", ios::trunc | ios::out);//如果文件已经存在,则删除再创建打开
			ofs << data;
			ofs.close();
			return 2;
		}

		if (language == 3)
		{
			ofstream ofs;
			ofs.open("test.py", ios::trunc | ios::out);//如果文件已经存在,则删除再创建打开
			ofs << data;
			ofs.close();
			return 3;
		}
	}
	return -1;
}

//编译函数
int make_test(struct bufferevent *bev, int language)
{
	if (language == 1)
	{
		system("rm make");//先删除再创建
		system("touch make");
		system("rm a.out");//清除上一次编译生成的可执行文件
		system("gcc test.c  > make 2>&1");//重定向到文件make中
		char buf[BUFFSIZE];
		memset(buf, '\0', sizeof(buf));
		ifstream ifs;
		ifs.open("make", ios::in);
		if (!ifs.is_open()) {
			cout << "openfile make error" << endl;
		}
		ifs.get(buf, sizeof(buf), '\0');
		//从文件中读取字符到字符串buf，当遇到字符'\0'或读取了sizeof(buf)个字符时终止。
		ifs.close();
		if (strlen(buf) > 0)//make中有数据说明编译报错了
		{
			bufferevent_write(bev, buf, strlen(buf));//发送错误提示
			return -1;
		}
		return 1;
	}

	if (language == 2)
	{
		system("rm make");//先删除再创建
		system("touch make");
		system("rm a.out");//清除上一次编译生成的可执行文件
		system("g++ test.cpp  > make 2>&1");//重定向到文件make中
		char buf[BUFFSIZE];
		memset(buf, '\0', sizeof(buf));
		ifstream ifs;
		ifs.open("make", ios::in);
		if (!ifs.is_open()) {
			cout << "openfile make error" << endl;
		}
		ifs.get(buf, sizeof(buf), '\0');
		//从文件中读取字符到字符串buf，当遇到字符'\0'或读取了sizeof(buf)个字符时终止。
		ifs.close();
		if (strlen(buf) > 0)//make中有数据说明编译报错了
		{
			bufferevent_write(bev, buf, strlen(buf));//发送错误提示
			return -1;
		}
		return 2;
	}

	if (language == 3)
	{
		char data[50] = "The results of the program are as follows:\n";
		bufferevent_write(bev, data, strlen(data));//python无需编译,直接让out输出即可
		return 3;
	}

	return -1;
}

//运行程序的函数
int out_test(struct bufferevent *bev, int language)
{
	if (language == 1)
	{
		string name("touch ");
		name = name + "out";
		system(name.c_str());
		system("./a.out > out 2>&1");//重定向到文件out中
		char buf[BUFFSIZE];
		memset(buf, '\0', sizeof(buf));
		ifstream ifs;
		ifs.open("out", ios::in);
		if (!ifs.is_open()) {
			cout << "openfile out error" << endl;
		}
		ifs.get(buf, sizeof(buf), '\0');
		//从文件中读取字符到字符串buf，当遇到字符'\0'或读取了sizeof(buf)个字符时终止。
		ifs.close();
		if (strlen(buf) > 0)//读取到数据,说明程序有输出
		{
			bufferevent_write(bev, buf, strlen(buf));//回传程序输出
			return 0;
		}
		return -1;
	}

	if (language == 2)
	{
		string name("touch ");
		name = name + "out";
		system(name.c_str());
		system("./a.out > out 2>&1");//重定向到文件out中
		char buf[BUFFSIZE];
		memset(buf, '\0', sizeof(buf));
		ifstream ifs;
		ifs.open("out", ios::in);
		if (!ifs.is_open()) {
			cout << "openfile out error" << endl;
		}
		ifs.get(buf, sizeof(buf), '\0');
		//从文件中读取字符到字符串buf，当遇到字符'\0'或读取了sizeof(buf)个字符时终止。
		ifs.close();
		if (strlen(buf) > 0)//读取到数据,说明程序有输出
		{
			bufferevent_write(bev, buf, strlen(buf));//回传程序输出
			return 0;
		}
		return -1;
	}

	if (language == 3)
	{
		string name("touch ");
		name = name + "out";
		system(name.c_str());
		system("python3 test.py > out 2>&1");
		system("cat out");
		char buf[BUFFSIZE];
		memset(buf, '\0', sizeof(buf));
		ifstream ifs;
		ifs.open("out", ios::in);
		if (!ifs.is_open()) {
			cout << "openfile out error" << endl;
		}
		ifs.get(buf, sizeof(buf), '\0');
		//从文件中读取字符到字符串buf，当遇到字符'\0'或读取了sizeof(buf)个字符时终止。
		ifs.close();
		if (strlen(buf) > 0)//读取到数据,说明程序有输出
		{
			cout << strlen(buf) << endl;
			bufferevent_write(bev, buf, strlen(buf));//回传程序输出
			return 0;
		}
		return -1;
	}
	return -1;
}