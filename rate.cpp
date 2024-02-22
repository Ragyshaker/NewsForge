#include "rate.h"

rate::rate(string username, int news_number, float news_rate)
{
	this->username = username;
	this->news_number = news_number;
	this->news_rate = news_rate;
}

rate::rate()
{
	news_rate = 0.0;
}

void rate::set_username(string username)
{
	this->username = username;
}

void rate::set_news_number(int news_number)
{
	this->news_number = news_number;
}

void rate::set_rate(float news_rate)
{
	if (news_rate > 5)
		news_rate = 5;
	else if (news_rate < 0)
		news_rate = 0;
	else
		this->news_rate = news_rate;
}

string rate::get_username()
{
	return username;
}

int rate::get_news_number()
{
	return news_number;
}

float rate::get_rate()
{
	return news_rate;
}
