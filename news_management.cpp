#include "news_management.h"
#include "user.h"
#include<iostream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <string>
#include <unordered_map>
#include <cstring>
#include<cstdio>
using namespace std;
int news_management::news_next_number;
unordered_map<string, string> news_management::userslist;//hashtable
unordered_map<string, string> news_management::adminlist;//hashtable
unordered_map<string, category, news_management::category_hash>news_management::categorylist;//hashtable
void news_management::get_users_data()
{
	SQLHANDLE env_handle;
	SQLHANDLE dbc_handle;
	SQLHANDLE stmt_handle;
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env_handle);
	SQLSetEnvAttr(env_handle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, env_handle, &dbc_handle);
	SQLCHAR retConString[1024];
	SQLRETURN rc = SQLDriverConnect(dbc_handle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=newsManagementSystem; UID=myID; PWD=myPW;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT);

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {

		cout << "Error connecting to SQL server" << endl;
		return;
	}
	SQLAllocHandle(SQL_HANDLE_STMT, dbc_handle, &stmt_handle);
	SQLCHAR* query = (SQLCHAR*)"SELECT * FROM Users";
	SQLLEN query_length = SQL_NTS;
	SQLRETURN prepare_rc = SQLPrepare(stmt_handle, query, query_length);

	if (prepare_rc != SQL_SUCCESS && prepare_rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error preparing SQL query" << endl;
		return;
	}
	SQLRETURN execute_rc = SQLExecute(stmt_handle);

	if (execute_rc != SQL_SUCCESS && execute_rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error executing SQL query" << endl;
		return;
	}
	char name[256];
	char password[256];
	while (SQLFetch(stmt_handle) != SQL_NO_DATA) {
		SQLGetData(stmt_handle, 1, SQL_C_CHAR, &name, sizeof(name), NULL);
		SQLGetData(stmt_handle, 2, SQL_C_CHAR, &password, sizeof(password), NULL);
		userslist[name] = password;
	}
	SQLFreeHandle(SQL_HANDLE_STMT, stmt_handle);
	SQLDisconnect(dbc_handle);
	SQLFreeHandle(SQL_HANDLE_ENV, env_handle);
}

void news_management::get_admins_data()
{
	SQLHANDLE env_handle;
	SQLHANDLE dbc_handle;
	SQLHANDLE stmt_handle;
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env_handle);
	SQLSetEnvAttr(env_handle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, env_handle, &dbc_handle);
	SQLCHAR retConString[1024];
	SQLRETURN rc = SQLDriverConnect(dbc_handle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=newsManagementSystem; UID=myID; PWD=myPW;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT);

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {

		cout << "Error connecting to SQL server" << endl;
		return;
	}
	SQLAllocHandle(SQL_HANDLE_STMT, dbc_handle, &stmt_handle);
	SQLCHAR* query = (SQLCHAR*)"SELECT * FROM Admin";
	SQLLEN query_length = SQL_NTS;
	SQLRETURN prepare_rc = SQLPrepare(stmt_handle, query, query_length);

	if (prepare_rc != SQL_SUCCESS && prepare_rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error preparing SQL query" << endl;
		return;
	}
	SQLRETURN execute_rc = SQLExecute(stmt_handle);

	if (execute_rc != SQL_SUCCESS && execute_rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error executing SQL query" << endl;
		return;
	}
	char name[256];
	char password[256];
	while (SQLFetch(stmt_handle) != SQL_NO_DATA) {
		SQLGetData(stmt_handle, 1, SQL_C_CHAR, &name, sizeof(name), NULL);
		SQLGetData(stmt_handle, 2, SQL_C_CHAR, &password, sizeof(password), NULL);
		adminlist[name] = password;
	}
	SQLFreeHandle(SQL_HANDLE_STMT, stmt_handle);
	SQLDisconnect(dbc_handle);
	SQLFreeHandle(SQL_HANDLE_ENV, env_handle);
}

void news_management::welcome()
{
	cout << "\t\t\t\t\t        WELCOME TO OUR NEWS MANAGEMENT SYSTEM " << endl;//6 spaces
	cout << "\t\t\t\t\t        -------------------------------------------" << endl;
}
bool news_management::login()
{

	while (true) {
		cout << "\t\t\t\t LOGIN PAGE " << endl;
		cout << "enter your username :: ";
		getline(cin, name);
		cout << "enter your password :: ";
		getline(cin, password);
		if (news_management::adminlist.count(name) > 0 && news_management::adminlist[name] == password) //check if the user is admin
		{

			return true;//true for admin
		}
		else if (news_management::userslist.count(name) > 0 && news_management::userslist[name] == password)
		{
			us.set_user_name(name);
			us.set_password(password);
			return false;
		}
		else
		{
			cout << "incorrect username or password try again" << endl;
		}
	}
}
bool news_management::start_app()
{
	news_next_number = 0;
	get_users_data();
	get_admins_data();
	get_categories_data();
	string choice;
	while (true)
	{
		cout << "\nPress 1 to register\nPress 2 to login\n";
		getline(cin, choice);
		if (choice != "1" && choice != "2")
		{
			cout << "\nInvalid input. Please try again.\n\n";
			continue;
		}
		break;
	}
	if (choice == "1")
	{
		us.user_register();
		if (login() == true) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (choice == "2")
	{
		if (login() == true) {
			return true;
		}
		else {
			return false;
		}
	}

}

void news_management::main_options_and_actions()
{
	us.main_options();
	us.user_action();
}

void news_management::admin_options()
{
	admin admino;
	admino.set_admin_name(name);
	admino.set_admin_password(password);
	admino.admin_main_options();
}
bool news_management::user_admin_outro()
{
	while (true)
	{
		cout << "press 1 if you want to do another operation" << endl;
		cout << "press 2 to out :: " << endl;
		getline(cin, choose);
		if (choose == "1" || choose == "2")
		{
			break;
		}
		else
		{
			cout << "\t\tERROR\nPlease check the number you entered\n\n";

		}
	}

	if (choose == "1")
	{
		return true;
	}
	else {
		return false;
	}
}
bool news_management::final_outro()
{
	cout << "press 1 if you want to enter with another account or create new one" << endl;
	cout << "press anywhere to out :: " << endl;
	getline(cin, choose);
	if (choose == "1")
	{
		return true;
	}
	else {
		return false;
	}
}
void news_management::bye_bye()
{
	cout << "\t\t\t NEWS MAMAGEMENT SYSTEM SAYS TO YOU BYE BYE" << endl;
}

void news_management::get_categories_data()
{
	SQLHANDLE env_handle;
	SQLHANDLE dbc_handle;
	SQLHANDLE stmt_handle;
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env_handle);
	SQLSetEnvAttr(env_handle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, env_handle, &dbc_handle);
	SQLCHAR retConString[1024];
	SQLRETURN rc = SQLDriverConnect(dbc_handle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=newsManagementSystem; UID=myID; PWD=myPW;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT);

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error connecting to SQL server" << endl;
		return;
	}
	SQLAllocHandle(SQL_HANDLE_STMT, dbc_handle, &stmt_handle);
	SQLCHAR* query = (SQLCHAR*)"SELECT * from category";
	SQLLEN query_length = SQL_NTS;
	SQLRETURN prepare_rc = SQLPrepare(stmt_handle, query, query_length);

	if (prepare_rc != SQL_SUCCESS && prepare_rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error preparing SQL query" << endl;
		return;
	}
	SQLRETURN execute_rc = SQLExecute(stmt_handle);

	if (execute_rc != SQL_SUCCESS && execute_rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error executing SQL query" << endl;
		return;
	}
	char category_name[256];
	while (SQLFetch(stmt_handle) != SQL_NO_DATA)
	{
		category new_category;
		SQLGetData(stmt_handle, 1, SQL_C_CHAR, &category_name, sizeof(category_name), NULL);
		new_category.set_name(category_name);
		new_category.newslist = get_news_data(category_name,news_next_number);
		categorylist[category_name] = new_category;
	}
	SQLFreeHandle(SQL_HANDLE_STMT, stmt_handle);
	SQLDisconnect(dbc_handle);
	SQLFreeHandle(SQL_HANDLE_DBC, dbc_handle);
	SQLFreeHandle(SQL_HANDLE_ENV, env_handle);
	
}

list<rate> news_management::get_rates_data(int news_number, float &avgrate, int &ratecount)
{
	list<rate>ratelist;
	SQLHANDLE env_handle;
	SQLHANDLE dbc_handle;
	SQLHANDLE stmt_handle;
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env_handle);
	SQLSetEnvAttr(env_handle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, env_handle, &dbc_handle);
	SQLCHAR retConString[1024];
	SQLRETURN rc = SQLDriverConnect(dbc_handle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=newsManagementSystem; UID=myID; PWD=myPW;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT);

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error connecting to SQL server" << endl;
		return ratelist;
	}
	SQLAllocHandle(SQL_HANDLE_STMT, dbc_handle, &stmt_handle);
	SQLCHAR* query = (SQLCHAR*)"SELECT * FROM rateTo WHERE newsNumber = ?";
	SQLLEN query_length = SQL_NTS;
	SQLRETURN prepare_rc = SQLPrepare(stmt_handle, query, query_length);

	if (prepare_rc != SQL_SUCCESS && prepare_rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error preparing SQL query" << endl;
		return ratelist;
	}
	SQLBindParameter(stmt_handle, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0,&news_number, 0, NULL);

	SQLRETURN execute_rc = SQLExecute(stmt_handle);

	if (execute_rc != SQL_SUCCESS && execute_rc != SQL_SUCCESS_WITH_INFO) {
		SQLCHAR sql_state[6], message[SQL_MAX_MESSAGE_LENGTH];
		SQLINTEGER native_error;
		SQLSMALLINT message_length;
		SQLRETURN diag_rc = SQLGetDiagRec(SQL_HANDLE_STMT, stmt_handle, 1, sql_state, &native_error, message, sizeof(message), &message_length);
		if (diag_rc == SQL_SUCCESS || diag_rc == SQL_SUCCESS_WITH_INFO) {
			cout << "SQL error: " << sql_state << " - " << message << endl;
		}
		else {
			cout << "Error executing SQL query" << endl;
		}
		SQLFreeHandle(SQL_HANDLE_STMT, stmt_handle);
		return ratelist;
	}
	char username[256];
	int news_id;
	float the_rate;
	float sum = 0;
	ratecount = 0;
	while (SQLFetch(stmt_handle) != SQL_NO_DATA)
	{
		rate rates;
		SQLGetData(stmt_handle, 1, SQL_C_CHAR, &username, sizeof(username), NULL);
		SQLGetData(stmt_handle, 2, SQL_INTEGER, &news_id, sizeof(news_id), NULL);
		SQLGetData(stmt_handle, 3, SQL_C_FLOAT, &the_rate, sizeof(the_rate), NULL);
		rates.set_username(username);
		rates.set_news_number(news_id);
		rates.set_rate(the_rate);
		ratecount++;
		sum += the_rate;
		ratelist.push_back(rates);
	}
	if (sum > 0) {
		avgrate = sum / ratecount;
	}
	SQLFreeHandle(SQL_HANDLE_STMT, stmt_handle);
	SQLDisconnect(dbc_handle);
	SQLFreeHandle(SQL_HANDLE_DBC, dbc_handle);
	SQLFreeHandle(SQL_HANDLE_ENV, env_handle);
	return ratelist;
}

unordered_map<int, news_data> news_management::get_news_data(string categoryy, int& newscuurentnumber)
{
	unordered_map<int, news_data> news_hashtable;
	SQLHANDLE env_handle;
	SQLHANDLE dbc_handle;
	SQLHANDLE stmt_handle;
	SQL_TIMESTAMP_STRUCT newsdatetime;
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env_handle);
	SQLSetEnvAttr(env_handle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, env_handle, &dbc_handle);
	SQLCHAR retConString[1024];
	SQLRETURN rc = SQLDriverConnect(dbc_handle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=newsManagementSystem; UID=myID; PWD=myPW;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT);

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error connecting to SQL server" << endl;
		return news_hashtable;
	}
	SQLAllocHandle(SQL_HANDLE_STMT, dbc_handle, &stmt_handle);
	SQLCHAR* query = (SQLCHAR*)"SELECT * FROM News WHERE category = ?";
	SQLLEN query_length = SQL_NTS;
	SQLRETURN prepare_rc = SQLPrepare(stmt_handle, query, query_length);

	if (prepare_rc != SQL_SUCCESS && prepare_rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error preparing SQL query" << endl;
		return news_hashtable;
	}
	SQLBindParameter(stmt_handle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 50, 0, (SQLPOINTER)categoryy.c_str(), 0, NULL);

	SQLRETURN execute_rc = SQLExecute(stmt_handle);

	if (execute_rc != SQL_SUCCESS && execute_rc != SQL_SUCCESS_WITH_INFO) {
		SQLCHAR sql_state[6], message[SQL_MAX_MESSAGE_LENGTH];
		SQLINTEGER native_error;
		SQLSMALLINT message_length;
		SQLRETURN diag_rc = SQLGetDiagRec(SQL_HANDLE_STMT, stmt_handle, 1, sql_state, &native_error, message, sizeof(message), &message_length);
		if (diag_rc == SQL_SUCCESS || diag_rc == SQL_SUCCESS_WITH_INFO) {
			cout << "SQL error: " << sql_state << " - " << message << endl;
		}
		else {
			cout << "Error executing SQL query" << endl;
		}
		SQLFreeHandle(SQL_HANDLE_STMT, stmt_handle);
		return news_hashtable;
	}
	char news_category[256];
	char news_title[256];
	char news_describtion[256];
	char news_adminname[256];
	char datetime_str[256];
	int newsnumber=0, newsratecounter=0;
	float averegeRate=0;
	bool flag = 0;
	while (SQLFetch(stmt_handle) != SQL_NO_DATA)
	{
		news_data news;
		SQLGetData(stmt_handle, 1, SQL_C_CHAR, &news_category, sizeof(news_category), NULL);
		SQLGetData(stmt_handle, 2, SQL_C_CHAR, &news_title, sizeof(news_title), NULL);
		SQLGetData(stmt_handle, 3, SQL_C_CHAR, &news_describtion, sizeof(news_describtion), NULL);
		SQLGetData(stmt_handle, 4, SQL_C_TIMESTAMP, &newsdatetime, sizeof(newsdatetime), NULL);
		SQLGetData(stmt_handle, 5, SQL_C_CHAR, &news_adminname, sizeof(news_adminname), NULL);
		SQLGetData(stmt_handle, 6, SQL_C_FLOAT, &averegeRate, sizeof(averegeRate), NULL);
		SQLGetData(stmt_handle, 7, SQL_INTEGER, &newsratecounter, sizeof(newsratecounter), NULL);
		SQLGetData(stmt_handle, 8, SQL_INTEGER, &newsnumber, sizeof(newsnumber), NULL);
		sprintf_s(datetime_str, "%04d-%02d-%02d %02d:%02d:%02d", newsdatetime.year, newsdatetime.month, newsdatetime.day,
			newsdatetime.hour, newsdatetime.minute, newsdatetime.second);
		news.number = newsnumber;
		news.category = news_category;
		news.title = news_title;
		news.describtion = news_describtion;
		news.admin_name = news_adminname;
		news.average_rate = 0.0;//averegeRate;
		news.rate_counter = 0; //newsratecounter;
		news.datetime = datetime_str;
		news.rate_list = get_rates_data(newsnumber, news.average_rate, news.rate_counter);
		news.comment_list = get_comments_data(newsnumber, news.comment_counter);
		news.spam_list = get_spam_data(newsnumber, news.spam_counter);
		news_hashtable[newsnumber] = news;
		flag = 1;
	}
	if (flag) 
	{
		if (newsnumber > newscuurentnumber)
			newscuurentnumber = newsnumber;
	}
	SQLFreeHandle(SQL_HANDLE_STMT, stmt_handle);
	SQLDisconnect(dbc_handle);
	SQLFreeHandle(SQL_HANDLE_DBC, dbc_handle);
	SQLFreeHandle(SQL_HANDLE_ENV, env_handle);
	return news_hashtable;
}

list<comment> news_management::get_comments_data(int news_number, int& commentcount)
{
	list<comment>commentlist;
	SQLHANDLE env_handle;
	SQLHANDLE dbc_handle;
	SQLHANDLE stmt_handle;
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env_handle);
	SQLSetEnvAttr(env_handle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, env_handle, &dbc_handle);
	SQLCHAR retConString[1024];
	SQLRETURN rc = SQLDriverConnect(dbc_handle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=newsManagementSystem; UID=myID; PWD=myPW;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT);

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error connecting to SQL server" << endl;
		return commentlist;
	}
	SQLAllocHandle(SQL_HANDLE_STMT, dbc_handle, &stmt_handle);
	SQLCHAR* query = (SQLCHAR*)"SELECT * FROM writeComment WHERE newsNumber = ?";
	SQLLEN query_length = SQL_NTS;
	SQLRETURN prepare_rc = SQLPrepare(stmt_handle, query, query_length);

	if (prepare_rc != SQL_SUCCESS && prepare_rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error preparing SQL query" << endl;
		return commentlist;
	}
	SQLBindParameter(stmt_handle, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &news_number, 0, NULL);

	SQLRETURN execute_rc = SQLExecute(stmt_handle);

	if (execute_rc != SQL_SUCCESS && execute_rc != SQL_SUCCESS_WITH_INFO) {
		SQLCHAR sql_state[6], message[SQL_MAX_MESSAGE_LENGTH];
		SQLINTEGER native_error;
		SQLSMALLINT message_length;
		SQLRETURN diag_rc = SQLGetDiagRec(SQL_HANDLE_STMT, stmt_handle, 1, sql_state, &native_error, message, sizeof(message), &message_length);
		if (diag_rc == SQL_SUCCESS || diag_rc == SQL_SUCCESS_WITH_INFO) {
			cout << "SQL error: " << sql_state << " - " << message << endl;
		}
		else {
			cout << "Error executing SQL query" << endl;
		}
		SQLFreeHandle(SQL_HANDLE_STMT, stmt_handle);
		return commentlist;
	}
	char username[256];
	char the_comment[256];
	int news_id;
	while (SQLFetch(stmt_handle) != SQL_NO_DATA)
	{
		comment comments;
		SQLGetData(stmt_handle, 1, SQL_C_CHAR, &username, sizeof(username), NULL);
		SQLGetData(stmt_handle, 2, SQL_INTEGER, &news_id, sizeof(news_id), NULL);
		SQLGetData(stmt_handle, 3, SQL_C_CHAR, &the_comment, sizeof(the_comment), NULL);
		comments.set_comment(the_comment);
		comments.set_username(username);
		comments.set_news_number(news_id);
		commentcount++;
		commentlist.push_back(comments);
	}
	
	SQLFreeHandle(SQL_HANDLE_STMT, stmt_handle);
	SQLDisconnect(dbc_handle);
	SQLFreeHandle(SQL_HANDLE_DBC, dbc_handle);
	SQLFreeHandle(SQL_HANDLE_ENV, env_handle);
	return commentlist;
}

list<spam> news_management::get_spam_data(int news_number, int& spamcount)
{
	list<spam>spamlist;
	SQLHANDLE env_handle;
	SQLHANDLE dbc_handle;
	SQLHANDLE stmt_handle;
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env_handle);
	SQLSetEnvAttr(env_handle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, env_handle, &dbc_handle);
	SQLCHAR retConString[1024];
	SQLRETURN rc = SQLDriverConnect(dbc_handle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=newsManagementSystem; UID=myID; PWD=myPW;", SQL_NTS, retConString, 1024, NULL, SQL_DRIVER_NOPROMPT);

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error connecting to SQL server" << endl;
		return spamlist;
	}
	SQLAllocHandle(SQL_HANDLE_STMT, dbc_handle, &stmt_handle);
	SQLCHAR* query = (SQLCHAR*)"SELECT * FROM reportSpam WHERE newsNumber = ?";
	SQLLEN query_length = SQL_NTS;
	SQLRETURN prepare_rc = SQLPrepare(stmt_handle, query, query_length);

	if (prepare_rc != SQL_SUCCESS && prepare_rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error preparing SQL query" << endl;
		return spamlist;
	}
	SQLBindParameter(stmt_handle, 1, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &news_number, 0, NULL);

	SQLRETURN execute_rc = SQLExecute(stmt_handle);

	if (execute_rc != SQL_SUCCESS && execute_rc != SQL_SUCCESS_WITH_INFO) {
		SQLCHAR sql_state[6], message[SQL_MAX_MESSAGE_LENGTH];
		SQLINTEGER native_error;
		SQLSMALLINT message_length;
		SQLRETURN diag_rc = SQLGetDiagRec(SQL_HANDLE_STMT, stmt_handle, 1, sql_state, &native_error, message, sizeof(message), &message_length);
		if (diag_rc == SQL_SUCCESS || diag_rc == SQL_SUCCESS_WITH_INFO) {
			cout << "SQL error: " << sql_state << " - " << message << endl;
		}
		else {
			cout << "Error executing SQL query" << endl;
		}
		SQLFreeHandle(SQL_HANDLE_STMT, stmt_handle);
		return spamlist;
	}
	char username[256];
	char the_objection[256];
	int news_id;
	while (SQLFetch(stmt_handle) != SQL_NO_DATA)
	{
		spam spams;
		SQLGetData(stmt_handle, 1, SQL_C_CHAR, &username, sizeof(username), NULL);
		SQLGetData(stmt_handle, 2, SQL_INTEGER, &news_id, sizeof(news_id), NULL);
		SQLGetData(stmt_handle, 3, SQL_C_CHAR, &the_objection, sizeof(the_objection), NULL);
		spams.set_objection(the_objection);
		spams.set_username(username);
		spams.set_news_number(news_id);
		spamcount++;
		spamlist.push_back(spams);
	}

	SQLFreeHandle(SQL_HANDLE_STMT, stmt_handle);
	SQLDisconnect(dbc_handle);
	SQLFreeHandle(SQL_HANDLE_DBC, dbc_handle);
	SQLFreeHandle(SQL_HANDLE_ENV, env_handle);
	return spamlist;
}


