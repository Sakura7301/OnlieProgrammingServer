#include"server.h"

//读取包头
bool read_head(struct bufferevent *bev)
{
	char head[HEAD_LEN + 1];
	memset(head, '\0', sizeof(head));
	bufferevent_read(bev, head, HEAD_LEN);//读取包头
	if (strcmp(head, HEAD) == 0)
	{
		return true;
	}

	return false;
}

//读取用户ID
void read_userid(struct bufferevent *bev, char* userid)
{

	bufferevent_read(bev, userid, USER_ID_LEN);//读取用户ID
}

//读取编程语言
int read_language(struct bufferevent *bev)
{
	char language[USER_LANGUAGE_LEN + 1];
	memset(language, '\0', sizeof(language));
	bufferevent_read(bev, language, USER_LANGUAGE_LEN);//读取语言
	if (strlen(language) == 8)
	{
		if (strcmp(language, C) == 0)//C语言
		{
			return 1;
		}

		if (strcmp(language, CPP) == 0)//C++
		{
			return 2;
		}

		if (strcmp(language, PYTHON) == 0)//python
		{
			return 3;
		}
	}
	return -1;
}

