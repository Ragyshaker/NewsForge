#pragma once
#include<string>
#include<iostream>
#include<queue>
#include<set>
#include "news_data.h"
using namespace std;
class user
{

private:
	string name, class_choice, for_choice, commentt, news_number, news_rate;
	string password;
	int for_num, int_news_number, int_news_rate;
	queue <string> prefered_categories;
	void add_user_to_database(const string& username, const string& password);
	void add_rates_to_database(list<rate>& rate_list);
	void add_comments_to_database(list<comment> comments);
	void add_spams_to_database(list<spam> spams);
	void display_categories();
	void display_news_by_date();
	struct news_compare_by_date {
		bool operator()(const news_data& lhs, const news_data& rhs) const {
			return lhs.datetime > rhs.datetime;
		}
	};

public:
	
	bool contains(list<spam> list, string value);
	void display_latest_news();
	void display_news_by_rate();
	string get_user_name();
	void user_register();
	void main_options();
	void filter();
	void display_all();
	void user_action();
	void set_user_name(string name);
	void set_password(string password);
	~user();
};

