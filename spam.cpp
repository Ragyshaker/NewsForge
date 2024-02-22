#include "spam.h"

spam::spam()
{

}

spam::spam(string username, string objection, int news_number)
{
	this->username = username;
	this->objection = objection;
	this->news_number = news_number;
}

void spam::set_username(string username)
{
	this->username = username;
}

void spam::set_news_number(int news_number)
{
	this->news_number = news_number;
}

void spam::set_objection(string objection)
{
	this->objection = objection;
}

string spam::get_username()
{
	return username;
}

int spam::get_news_number()
{
	return news_number;
}

string spam::get_objection()
{
	return objection;
}
