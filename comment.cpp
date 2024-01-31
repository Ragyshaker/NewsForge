#include "comment.h"

comment::comment()
{

}

comment::comment(string username, string news_comment, int news_number)
{
	this->username = username;
	this->news_comment = news_comment;
	this->news_number = news_number;
}

void comment::set_username(string username)
{
	this->username = username;
}

void comment::set_comment(string news_comment)
{
	this->news_comment = news_comment;
}

void comment::set_news_number(int news_number)
{
	this->news_number = news_number;
}

string comment::get_username()
{
	return username;
}

int comment::get_news_number()
{
	return news_number;
}

string comment::get_comment()
{
	return news_comment;
}


