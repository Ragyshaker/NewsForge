#pragma once
#include<iostream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include "news_data.h"
#include <sqlext.h>
using namespace std;
#pragma once
class admin
{
private:
	string name, password, news_category, the_new, no_of_new, choose, news_title, news_describtion;
	int int_num;
	string choice;
	void add_news_to_database(const string& category,const  string& titel,const  string& description,const  string& admin_name);
	void update_news_in_database(const string& news_number,const  string& title,const  string& describtion, const string& category);
	void delete_news_from_database(const string& news_number);
	void add_category_to_database(string& category_name);
public:
	void admin_main_options();
	void post_new();
	void remove_new();
	void update_new();
	void add_newcategory();
	void display_news_for_admin();
	void set_admin_name(string name);
	void set_admin_password(string password);
};
