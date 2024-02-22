#pragma once
#include "user.h"
#include <unordered_map>
#include<list>
#include<vector>
#include "news_data.h"
#include "admin.h"
#include "category.h"
using namespace std;
class news_management
{
private:
	
	string choose;
	user us;
	string name, password;
	struct category_hash
	{
		size_t operator()(const string& key) const {
			return hash<string>()(key);
		}
	};
	void get_users_data();// A function to return users data and store it in userslist(hashtable)
	void get_admins_data();// A function to return users data and store it in adminlist(hashtable)
public:
	static int news_next_number;
	static unordered_map<string, string> userslist;
	static unordered_map<string, string> adminlist;
	static unordered_map<string, category, category_hash> categorylist;
	void welcome();
	bool login();
	bool start_app();
	void main_options_and_actions();
	void admin_options();
	bool user_admin_outro();
	bool final_outro();
	void bye_bye();
	void get_categories_data();
	list<rate> get_rates_data(int news_number, float& avgrate, int& ratecount);
	unordered_map<int, news_data> get_news_data(string categoryy,int & newscuurentnumber);
	list<comment> get_comments_data(int news_number, int& commentcount);
	list<spam> get_spam_data(int news_number, int& spamcount);

};
