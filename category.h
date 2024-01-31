#pragma once
#include<iostream>
#include"news_data.h"
#include<unordered_map>
using namespace std;
class category
{
private:
	string name;

public:
	unordered_map<int, news_data> newslist;//hashtable of news
	category();
	category(string name);
	void set_name(string name);
	string get_name();
	void display_news();
	void display_news_for_admins();
};

