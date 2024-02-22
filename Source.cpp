#include<iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <set>
#include <list>
#include "news_data.h"
#include "news_management.h"
#include <unordered_map>
using namespace std;

int main() {
	
	bool check;
	news_management news;
	do {
		news.welcome();
		check = news.start_app();
		cout << news_management::news_next_number << endl;
		if (check == true)
		{
			do
			{
				news.admin_options();
				check = news.user_admin_outro();
			} while (check == true);
			//admin
		}
		else
		{
			do
			{
				//user
				news.main_options_and_actions();
				check = news.user_admin_outro();
			} while (check == true);
		}
		check = news.final_outro();
	} while (check == true);
	news.bye_bye();
	
	
	return 0;
}

