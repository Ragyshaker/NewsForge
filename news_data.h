#pragma once
#include<iostream>
#include<list>
#include"comment.h"
#include"spam.h"
#include"rate.h"
#include <string>
using namespace std;
class news_data
{
private:
   

public:
    list<comment>comment_list;
    list<spam>spam_list;
    list<rate>rate_list;
    int number;
    int rate_counter, spam_counter, comment_counter;
    float average_rate;
    string category, title, describtion, datetime, admin_name;
    news_data();
    news_data(string category, string titel, string describtion, string admin_name);
    void show_data()const;
    void set_number(int number);
    void set_category(string category);
    void set_title(string title);
    void set_describtion(string describtion);
    void set_admin_name(string admin_name);
    string get_category();
    string get_title();
    string get_describtion();
    string get_datetime();
    string get_admin_name();
    int get_number();
    float get_average_rate();
    void display_rates()const;
    void display_comment()const;
    void display_spams()const;
    void show_data_for_admins();
    void compute_avg_rate(float ratee);
    bool operator<(const news_data& other) const;
};



