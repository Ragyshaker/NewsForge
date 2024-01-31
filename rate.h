#pragma once
#include<iostream>
using namespace std;
class rate
{
private:
	string username;
	int news_number;
	float news_rate;
	friend class user;
public:

	rate(string username, int news_number, float rate);
	rate();
	void set_username(string username);
	void set_news_number(int news_number);
	void set_rate(float news_rate);
	string get_username();
	int get_news_number();
	float get_rate();
};

