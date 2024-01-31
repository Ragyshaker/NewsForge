#pragma once
#include<iostream>
using namespace std;
class comment
{
private:
	friend class user;
	string username, news_comment;
	int news_number;
public:
	
	comment();
	comment(string username, string news_comment, int news_number);
	void set_username(string username);
	void set_comment(string news_comment);
	void set_news_number(int news_number);
	string get_username();
	int get_news_number();
	string get_comment();
};

