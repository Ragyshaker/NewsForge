#pragma once
#include<iostream>
using namespace std;
class spam
{
private:
	friend class user;
	string username;
	int news_number;
	string objection;
public:
	spam();
	spam(string username, string objection, int news_number);
	void set_username(string username);
	void set_news_number(int news_number);
	void set_objection(string objection);
	string get_username();
	int get_news_number();
	string get_objection();
};

