#include "user.h"
#include "admin.h"
#include "news_management.h"
#include<queue>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include"news_management.h"
#include <cctype>

string user::get_user_name()
{
	return name;

}
void user::user_register()
{
	while (true)
	{
		cout << "\t\t\t\t REGISTER PAGE " << endl;
		cout << "Enter your username: ";
		getline( cin, name);
		cout << "Enter a strong password: ";
		getline(cin, password);
		if (news_management::userslist.count(name) == 0 && news_management::adminlist.count(name) == 0)
			break;
		cout << "\nThis username already exists. Please choose a different username and password.\n";
	}
	add_user_to_database(name, password);
	news_management::userslist[name] = password;
	cout << "\nRegistration successful!\n";
}
void user::main_options()
{
	while (true)
	{
		cout << "\npress 1 display the latest news " << endl;
		cout << "press 2 to display specific categories " << endl;
		cout << "press 3 to display all news " << endl;
		getline(cin, class_choice);
		if (class_choice == "1" || class_choice == "2" || class_choice == "3")
		{
			break;
		}
		else
		{
			cout << "\t\tERROR\nPlease check the number you entered\n\n";
		}
	}
	if (class_choice == "1")
	{
		display_latest_news();
	}
	else if (class_choice == "2")
	{
		filter(); // display by specific categories 
	}
	else
	{
		display_all();
	}

}
void user::filter() // display by specific categories 
{
	string category,number_of_categories;
	display_categories();
	int counter_of_categories = news_management::categorylist.size();
	cout<<"enter how many categories you want :: ";
	getline(cin, number_of_categories);
	cout << "enter the categories you prefer\n";
	int forloop = stoi(number_of_categories);
	if(forloop>counter_of_categories){
		forloop = counter_of_categories;
	}
	for (int i = 1; i <= forloop; i++) {
		cout << "category name :: " << endl;
			getline(cin, category);
			transform(category.begin(), category.end(), category.begin(), [](unsigned char c) { return std::toupper(c); });
		if (news_management::categorylist.count(category) == 0) {
			cout << "this category does not exist\n";
			continue;
		}
		prefered_categories.push(category);
	}
	
	while (!prefered_categories.empty())
	{
		for (auto it : news_management::categorylist[prefered_categories.front()].newslist) {
			if (contains(news_management::categorylist[prefered_categories.front()].newslist[it.first].spam_list, name))
				continue;
			news_management::categorylist[prefered_categories.front()].newslist[it.first].show_data();
		}
		prefered_categories.pop();
	}
}
void user::display_all()
{
	while (true)
	{
		cout << "press 1 to display all news by rate" << endl;
		cout << "press 2 to display all news by latest time" << endl;
		getline(cin, class_choice);
		if (class_choice == "1" || class_choice == "2")
		{
			break;
		}
		else
		{
			cout << "\t\tERROR\nPlease check the number you entered\n\n";
		}

	}
	if (class_choice == "1")
	{
		display_news_by_rate();
	}
	else
	{
		display_news_by_date();
	}
}
void user::user_action()//this function needs a random access(hashtables would be usefull)
{
	while (true)
	{
		cout << "press 1 to rate news" << endl;
		cout << "press 2 to comment the new" << endl;
		cout << "press 3 to report spam :: ";
		getline(cin , class_choice);
		if (class_choice == "1" || class_choice == "2" || class_choice == "3")
		{
			//display_news_by_date();
			break;
		}
		else
		{
			cout << "\t\tERROR\nPlease check the number you entered\n\n";
		}
	}
	if (class_choice == "1")
	{
		list<rate>the_new_rates;
		string categoryy, news_number, the_rate, flag = "1";
		while(flag =="1")
		{
			rate new_rate;
			cout << "enter the news category ::";
			getline(cin, categoryy);
			transform(categoryy.begin(), categoryy.end(), categoryy.begin(), [](unsigned char c) { return std::toupper(c); });
			if (news_management::categorylist.count(categoryy) == 0) {
				cout << "This category does not exist enter a right category name\n";
				continue;
			}
			cout << "enter the news number you want to rate ::";
			getline(cin, news_number);
			if (news_management::categorylist[categoryy].newslist.count(stoi(news_number)) == 0) {
				cout << "This news number does not exist enter a right news number\n";
				continue;
			}
			new_rate.set_username(name);
			new_rate.set_news_number(stoi(news_number));
			cout << "enter your rate :: ";
			getline(cin, the_rate);
			new_rate.set_rate(stof(the_rate));
			the_new_rates.push_back(new_rate);
			news_management::categorylist[categoryy].newslist[stoi(news_number)].rate_list.push_back(new_rate);
			news_management::categorylist[categoryy].newslist[stoi(news_number)].compute_avg_rate(stof(the_rate));
		
			cout << "Done\n";
			cout << "press 1 if you want to rate another news or press 0 to exit";
			getline(cin, flag);
			
		}
		add_rates_to_database(the_new_rates);
		cout << "\t\tdone\n" << endl;

	}
	else if (class_choice == "2")
	{
		list<comment>the_new_comments;
		string categoryy, news_number, the_comment, flag = "1";
		while (flag == "1")
		{
			comment new_comment;
			cout << "enter the news category ::";
			getline(cin, categoryy);
			transform(categoryy.begin(), categoryy.end(), categoryy.begin(), [](unsigned char c) { return std::toupper(c); });
			if (news_management::categorylist.count(categoryy) == 0) {
				cout << "This category does not exist enter a right category name\n";
				continue;
			}
			cout << "enter the news number you want to comment ::";
			getline(cin, news_number);
			if (news_management::categorylist[categoryy].newslist.count(stoi(news_number)) == 0) {
				cout << "This news number does not exist enter a right news number\n";
				continue;
			}
			new_comment.set_username(name);
			new_comment.set_news_number(stoi(news_number));
			cout << "enter your comment :: ";
			getline(cin, the_comment);
			new_comment.set_comment(the_comment);
			news_management::categorylist[categoryy].newslist[stoi(news_number)].comment_list.push_back(new_comment);
			the_new_comments.push_back(new_comment);
			cout << "Done\n";
			cout << "press 1 if you want to add another comment or press 0 to exit :: ";
			getline(cin, flag);

		}
		add_comments_to_database(the_new_comments);
		cout << "\t\tdone\n" << endl;

	}
	else
	{
		list<spam>the_new_spams;
		string categoryy, news_number, the_objection, flag = "1";
		while (flag == "1")
		{
			spam new_spam;
			cout << "enter the news category ::";
			getline(cin, categoryy);
			transform(categoryy.begin(), categoryy.end(), categoryy.begin(), [](unsigned char c) { return std::toupper(c); });
			if (news_management::categorylist.count(categoryy) == 0) {
				cout << "This category does not exist enter a right category name\n";
				continue;
			}
			cout << "enter the news number you want to spam ::";
			getline(cin, news_number);
			if (news_management::categorylist[categoryy].newslist.count(stoi(news_number)) == 0) {
				cout << "This news number does not exist enter a right news number\n";
				continue;
			}
			new_spam.set_username(name);
			new_spam.set_news_number(stoi(news_number));
			cout << "enter your objection :: ";
			getline(cin, the_objection);
			new_spam.set_objection(the_objection);
			news_management::categorylist[categoryy].newslist[stoi(news_number)].spam_list.push_back(new_spam);
			the_new_spams.push_back(new_spam);
			cout << "Done\n";
			cout << "press 1 if you want to spam another news or press 0 to exit :: ";
			getline(cin, flag);

		}
		add_spams_to_database(the_new_spams);
		cout << "\t\tdone\n" << endl;
	}
}
void user::set_user_name(string name)
{
	this->name = name;
}
void user::set_password(string password)
{
	this->password = password;
}
void user::add_user_to_database(const string& username, const string& password)
{
	SQLHANDLE env_handle;
	SQLHANDLE dbc_handle;
	SQLHANDLE stmt_handle;
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env_handle);
	SQLSetEnvAttr(env_handle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, env_handle, &dbc_handle);
	SQLCHAR* connection_string = (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=newsManagementSystem; UID=myID; PWD=myPW;";
	SQLSMALLINT connection_string_length = SQL_NTS;
	SQLRETURN rc = SQLDriverConnect(dbc_handle, NULL, connection_string, connection_string_length, NULL, 1024, NULL, SQL_DRIVER_NOPROMPT);

	if (rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error connecting to SQL server" << endl;
		return;
	}
	SQLAllocHandle(SQL_HANDLE_STMT, dbc_handle, &stmt_handle);

	SQLCHAR* query = (SQLCHAR*)"INSERT INTO users (username, password) VALUES (?, ?)";
	SQLLEN query_length = SQL_NTS;
	SQLRETURN prepare_rc = SQLPrepare(stmt_handle, query, query_length);

	if (prepare_rc != SQL_SUCCESS && prepare_rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error preparing SQL query" << endl;
		return;
	}
	SQLCHAR* new_username = (SQLCHAR*)username.c_str();
	SQLCHAR* new_password = (SQLCHAR*)password.c_str();
	SQLLEN new_username_length = SQL_NTS;
	SQLLEN new_password_length = SQL_NTS;
	SQLBindParameter(stmt_handle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 256, 0, new_username, 256, &new_username_length);
	SQLBindParameter(stmt_handle, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, 256, 0, new_password, 256, &new_password_length);

	SQLRETURN execute_rc = SQLExecute(stmt_handle);

	if (execute_rc != SQL_SUCCESS && execute_rc != SQL_SUCCESS_WITH_INFO) {
		cout << "Error executing SQL query" << endl;
		return;
	}
	SQLFreeHandle(SQL_HANDLE_STMT, stmt_handle);
	SQLDisconnect(dbc_handle);
	SQLFreeHandle(SQL_HANDLE_DBC, dbc_handle);
	SQLFreeHandle(SQL_HANDLE_ENV, env_handle);
}
void user::display_news_by_date()
{
	multiset<news_data,user::news_compare_by_date> news_set;
	
	for (const auto& category : news_management:: categorylist) {
		for (auto news : news_management::categorylist[category.first].newslist) {
			if (contains(news_management::categorylist[category.first].newslist[news.first].spam_list, name))
				continue;
			news_set.emplace(news.second);
		}
	}
	for (auto it = news_set.begin(); it != news_set.end(); ++it) {
		it->show_data();
		cout << "--------------------------------------------------------------------------------" << endl;
	}
}
bool user::contains(list<spam>list, string value)
{
	auto it = find_if(list.begin(), list.end(), [&]( spam& obj) {
		return obj.get_username() == value;
		});
	return it != list.end();
}
void user::display_news_by_rate()
{
	multiset<news_data > news_set;
	for (const auto& category : news_management::categorylist) {
		for (auto news : news_management::categorylist[category.first].newslist) {
			if (contains(news_management::categorylist[category.first].newslist[news.first].spam_list, name))
				continue;
			news_set.emplace(news.second);
		}
	}
	
	for (auto it = news_set.rbegin(); it != news_set.rend(); ++it) {
		it->show_data();
		cout << "--------------------------------------------------------------------------------------------" << endl;
	}

}
void user::display_latest_news()
{
	multiset<news_data, user::news_compare_by_date> news_set;
	for (const auto& category : news_management::categorylist) {
		for (auto news : news_management::categorylist[category.first].newslist) {
			if (contains(news_management::categorylist[category.first].newslist[news.first].spam_list, name))
				continue;
			news_set.emplace(news.second);
		}
	}
	int counter = 1;
	for (auto it = news_set.begin(); it != news_set.end(); ++it) {
		it->show_data();
		cout << "---------------------------------------------------------------------------------------------" << endl;
		if (counter > 10)
			break;
		counter++;
	}
}
void user::display_categories()
{
	for (auto category : news_management::categorylist)
	{
		cout << category.first << " "<<endl;
	}
	cout << endl;
}
void user::add_rates_to_database(list<rate> &rate_list)
{
	SQLHENV hEnv = SQL_NULL_HANDLE;
	SQLHDBC hConn = SQL_NULL_HANDLE;
	SQLHSTMT hStmt = SQL_NULL_HANDLE;
	SQLRETURN retcode;
	SQLCHAR* connStr = (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=newsManagementSystem; UID=myID; PWD=myPW;";
	SQLSMALLINT connStrLen = SQL_NTS;
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	retcode = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hConn);
	retcode = SQLDriverConnect(hConn, NULL, connStr, connStrLen, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

	string sqlStatement = "INSERT INTO rateTo (userName, newsNumber, rate) VALUES (?, ?, ?)";
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hConn, &hStmt);
	retcode = SQLPrepare(hStmt, (SQLCHAR*)sqlStatement.c_str(), SQL_NTS);

	for (auto  r : rate_list) {
		SQLLEN cbUserName = SQL_NTS;
		SQLLEN cbNewsNumber = 0;
		SQLLEN cbRate = 0;

		wstring wUserName(r.username.begin(), r.username.end());
		retcode = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 50, 0, (SQLPOINTER)wUserName.c_str(), 0, &cbUserName);
		retcode = SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &(r.news_number), 0, &cbNewsNumber);
		retcode = SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_FLOAT, SQL_FLOAT, 0, 0, &(r.news_rate), 0, &cbRate);

		retcode = SQLExecute(hStmt);

		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) {
			
			SQLCHAR sqlstate[6], message[SQL_MAX_MESSAGE_LENGTH];
			SQLINTEGER native_error;
			SQLSMALLINT message_length;

			SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, 1, sqlstate, &native_error, message, SQL_MAX_MESSAGE_LENGTH, &message_length);
			cerr << "Error inserting rate: " << message << endl;
		}
	}

	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	SQLDisconnect(hConn);
	SQLFreeHandle(SQL_HANDLE_DBC, hConn);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}
void user::add_comments_to_database(list<comment> comments)
{
	SQLHENV hEnv = SQL_NULL_HANDLE;
	SQLHDBC hConn = SQL_NULL_HANDLE;
	SQLHSTMT hStmt = SQL_NULL_HANDLE;
	SQLRETURN retcode;
	SQLCHAR* connStr = (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=newsManagementSystem; UID=myID; PWD=myPW;";
	SQLSMALLINT connStrLen = SQL_NTS;
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	retcode = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hConn);
	retcode = SQLDriverConnect(hConn, NULL, connStr, connStrLen, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

	string sqlStatement = "INSERT INTO writeComment (userName, newsNumber, comment) VALUES (?, ?, ?)";
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hConn, &hStmt);
	retcode = SQLPrepare(hStmt, (SQLCHAR*)sqlStatement.c_str(), SQL_NTS);

	for (auto c : comments) {
		SQLLEN cbUserName = SQL_NTS;
		SQLLEN cbNewsNumber = 0;
		SQLLEN cbComment = SQL_NTS;
		
		wstring wUserName(c.username.begin(), c.username.end());
		wstring wUsercomment(c.news_comment.begin(), c.news_comment.end());
		retcode = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 50, 0, (SQLPOINTER)wUserName.c_str(), 0, &cbUserName);
		retcode = SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &(c.news_number), 0, &cbNewsNumber);
		retcode = SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 50, 0, (SQLPOINTER)wUsercomment.c_str(), 0, &cbComment);
		retcode = SQLExecute(hStmt);

		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) {
			
			SQLCHAR sqlstate[6], message[SQL_MAX_MESSAGE_LENGTH];
			SQLINTEGER native_error;
			SQLSMALLINT message_length;

			SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, 1, sqlstate, &native_error, message, SQL_MAX_MESSAGE_LENGTH, &message_length);
			cerr << "Error inserting rate: " << message << endl;
		}
	}

	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	SQLDisconnect(hConn);
	SQLFreeHandle(SQL_HANDLE_DBC, hConn);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}
void user::add_spams_to_database(list<spam> spams)
{
	SQLHENV hEnv = SQL_NULL_HANDLE;
	SQLHDBC hConn = SQL_NULL_HANDLE;
	SQLHSTMT hStmt = SQL_NULL_HANDLE;
	SQLRETURN retcode;
	SQLCHAR* connStr = (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=newsManagementSystem; UID=myID; PWD=myPW;";
	SQLSMALLINT connStrLen = SQL_NTS;
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
	retcode = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hConn);
	retcode = SQLDriverConnect(hConn, NULL, connStr, connStrLen, NULL, 0, NULL, SQL_DRIVER_COMPLETE);

	string sqlStatement = "INSERT INTO reportSpam (userName, newsNumber, objection) VALUES (?, ?, ?)";
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hConn, &hStmt);
	retcode = SQLPrepare(hStmt, (SQLCHAR*)sqlStatement.c_str(), SQL_NTS);

	for (auto s : spams) {
		SQLLEN cbUserName = SQL_NTS;
		SQLLEN cbNewsNumber = 0;
		SQLLEN cbObjection = SQL_NTS;

		wstring wUserName(s.username.begin(), s.username.end());
		wstring wUserObjection(s.objection.begin(), s.objection.end());
		retcode = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 50, 0, (SQLPOINTER)wUserName.c_str(), 0, &cbUserName);
		retcode = SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &(s.news_number), 0, &cbNewsNumber);
		retcode = SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 50, 0, (SQLPOINTER)wUserObjection.c_str(), 0, &cbObjection);

		retcode = SQLExecute(hStmt);

		if (retcode != SQL_SUCCESS && retcode != SQL_SUCCESS_WITH_INFO) {
			SQLCHAR sqlstate[6], message[SQL_MAX_MESSAGE_LENGTH];
			SQLINTEGER native_error;
			SQLSMALLINT message_length;

			SQLGetDiagRec(SQL_HANDLE_STMT, hStmt, 1, sqlstate, &native_error, message, SQL_MAX_MESSAGE_LENGTH, &message_length);
			cerr << "Error inserting rate: " << message << endl;
		}
	}

	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	SQLDisconnect(hConn);
	SQLFreeHandle(SQL_HANDLE_DBC, hConn);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}
user::~user()
{

}