#include "category.h"

category::category()
{
}

category::category(string name)
{
	this->name = name;
}

void category::set_name(string name)
{
	this->name = name;
}

string category::get_name()
{
	return name;
}

void category::display_news()
{
	cout << name << " category... " << endl;
	for (auto news : newslist) {
		newslist[news.first].show_data();
		cout << "\n";
	}
}

void category::display_news_for_admins()
{
	cout << name << " category... " << endl;
	for (auto news : newslist) {
		newslist[news.first].show_data_for_admins();
		cout << "\n";
	}
	cout << "\n***********************************************************************************************************************************************";
}
