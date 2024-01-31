#include "news_data.h"
news_data::news_data()
{
    rate_counter = 0;
    spam_counter = 0;
    comment_counter = 0;
    average_rate = 0;
}
news_data::news_data(string category, string titel, string describtion, string admin_name)
{
    this->category = category;
    this->describtion = describtion;
    this->title = title;
    this->admin_name = admin_name;
    rate_counter = 0;
    average_rate = 0;
}

void news_data::show_data()const
{
    if (average_rate < 2 && average_rate > 0)
        return;
    cout << "number ::" << number << endl;
    cout << "category ::" << category << endl;
    cout << "title ::" << title << endl;
    cout << "describtion ::" << describtion << endl;
    cout << "rate ::" << average_rate << endl;
    cout << "number of rates ::" << rate_counter << endl;
    cout << "publishing date and time ::" <<datetime<< endl;
    display_comment();
    cout << endl;
}

void news_data::set_number(int number)
{
    this->number = number;
}

void news_data::set_category(string category)
{
    this->category = category;
}

void news_data::set_title(string title)
{
    this->title = title;
}

void news_data::set_describtion(string describtion)
{
    this->describtion = describtion;
}

void news_data::set_admin_name(string admin_name)
{
    this->admin_name = admin_name;
}

string news_data::get_category()
{
    return category;
}

string news_data::get_title()
{
    return title;
}

string news_data::get_describtion()
{
    return describtion;
}

string news_data::get_datetime()
{
    return datetime;
}

string news_data::get_admin_name()
{
    return admin_name;
}

int news_data::get_number()
{
    return number;
}

float news_data::get_average_rate()
{
    return average_rate;
}

void news_data::display_rates()const
{
    if (rate_list.empty()) {
        cout << "No rates yet" << endl;
        return;
    }
    cout << "rates..." << endl;
    for (auto i : rate_list) {
        cout<<i.get_username()<<"->>" << i.get_rate() << endl;
    }
}


void news_data::display_comment()const
{
    cout << "comments..." << endl;
    if (comment_list.empty()) {
        cout << "No comments yet" << endl;
        return;
    }
    for (auto comment : comment_list) {
        cout << comment.get_username() << " : " << comment.get_comment() << endl;
    }
}
void news_data::display_spams() const
{
    if (spam_list.empty()) {
        cout << "No spams" << endl;
        return;
    }
    cout << "spams..." << endl;
    for (auto i : spam_list) {
        cout << i.get_username() << "->>" << i.get_objection() << endl;
    }
}
void news_data::show_data_for_admins()
{
    cout << "number ::" << number << endl;
    cout << "category ::" << category << endl;
    cout << "title ::" << title << endl;
    cout << "describtion ::" << describtion << endl;
    cout << "rate ::" << average_rate << endl;
    cout << "number of rates ::" << rate_counter << endl;
    cout << "publishing date and time ::" << datetime << endl;
    cout << "published by ::" << admin_name << endl;
    cout << "number of spams :: " << spam_list.size() << endl;
    display_comment();
    display_rates();
    display_spams();
    cout << endl;
}

void news_data::compute_avg_rate(float ratee)
{
    average_rate =average_rate * rate_counter;
    rate_counter++;
    average_rate = (average_rate + ratee) / rate_counter;
}

bool news_data::operator<(const news_data& other) const
{
    return average_rate < other.average_rate;
}




