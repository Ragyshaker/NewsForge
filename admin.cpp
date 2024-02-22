#include "admin.h"
#include<string>
#include <iostream>
#include <sql.h>
#include <sqlext.h>
#include<stdlib.h>
#include "news_management.h"
#include "admin.h"
void admin::admin_main_options()
{
	//string choice;
	while (true)
	{
		cout << "\npress 1 to post new" << endl;
		cout << "press 2 to remove new" << endl;
		cout << "press 3 to edit new" << endl;
		cout << "press 4 to add new category" << endl;
		getline(cin, choice);
		if (choice == "1")
		{
			post_new();
			break;
		}
		else if (choice == "2")
		{
			remove_new();
			break;
		}
		else if (choice == "3")
		{
			update_new();
			break;
		}
		else if (choice == "4")
		{
			add_newcategory();
			break;
		}
		else
		{
			cout << "\t\tERROR\nPlease check the number you entered\n" << endl;
		}
	}
}
void admin::delete_news_from_database(const string& news_number)
{
	// Declare variables for database connection
	SQLHANDLE sqlenvhandle;
	SQLHANDLE sqlconnectionhandle;
	SQLHANDLE sqlstatementhandle;
	SQLRETURN retcode;

	// Allocate an environment handle
	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlenvhandle);

	// Set the ODBC version
	SQLSetEnvAttr(sqlenvhandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

	// Allocate a connection handle
	SQLAllocHandle(SQL_HANDLE_DBC, sqlenvhandle, &sqlconnectionhandle);

	// Connect to the database
	retcode = SQLDriverConnect(sqlconnectionhandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=newsManagementSystem; UID=myID; PWD=myPW;", SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);

	// Allocate a statement handle
	SQLAllocHandle(SQL_HANDLE_STMT, sqlconnectionhandle, &sqlstatementhandle);

	// Execute the SQL query to update the news data
	std::string sql_query = "DELETE from News where number =" + news_number;
	retcode = SQLExecDirect(sqlstatementhandle, (SQLCHAR*)sql_query.c_str(), SQL_NTS);

	// Free resources and close the database connection
	SQLFreeHandle(SQL_HANDLE_STMT, sqlstatementhandle);
	SQLDisconnect(sqlconnectionhandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlconnectionhandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlenvhandle);
}
void admin::post_new()
{
	news_data news;
	string flag = "1";
	cout << "category :: ";
	getline(cin, news_category);
	transform(news_category.begin(), news_category.end(), news_category.begin(), [](unsigned char c) { return std::toupper(c); });
	news.set_category(news_category);
	if (news_management::categorylist.find(news_category) == news_management::categorylist.end()) {
		cout << "This category name does not exist press 1 to add it or press 0 to exit :: ";
		getline(cin, flag);
		if (flag == "1") {
			add_newcategory();
			
		}
		else
			return;
	}
	cout << "the title :: ";
	getline(cin, news_title);
	news.set_title(news_title);
	cout << "the describtion :: ";
	getline(cin, news_describtion);
	news.set_describtion(news_describtion);
	//cout << "your name :: ";
	//getline(cin, name);
	news.set_admin_name(name);
	news.set_number(news_management::news_next_number + 1);
	news_management::news_next_number++;
	news_management::categorylist[news_category].newslist[news.get_number()] = news;
	add_news_to_database(news_category, news_title, news_describtion, name);
	cout << "\t\tDONE!!!" << endl;
	//ha7oto fe el latest news w fe el category bta3to aked
}

void admin::remove_new()
{
	display_news_for_admin();
	cout << "Enter the news category";
	getline(cin, news_category);
	transform(news_category.begin(), news_category.end(), news_category.begin(), [](unsigned char c) { return std::toupper(c); });
	cout << "enter the number of news :: ";
	getline(cin, no_of_new);
	//check if the category exist in hashtable
	news_management::categorylist[news_category].newslist.erase(stoi(no_of_new));
	//news_management::categorylist[news_category].newslist[stoi(no_of_new)].show_data_for_admins();
	delete_news_from_database(no_of_new);
	cout << "\t\tDONE!!!" << endl;
}

void admin::update_new()//this function needs to 
{
	display_news_for_admin();
	while (true)// checking if the news number exist 
	{
		cout << "enter the category of news you want to update:: ";
		getline(cin, news_category);
		transform(news_category.begin(), news_category.end(), news_category.begin(), [](unsigned char c) { return std::toupper(c); });
		if (news_management::categorylist.count(news_category) == 0) {
			cout << "This category does not exist enter a right category name" << endl;
			continue;
		}
		cout << "enter the number of news you want to update:: ";
		getline(cin, no_of_new);
		if (news_management::categorylist[news_category].newslist.find(stoi(no_of_new)) != news_management::categorylist[news_category].newslist.end())
		{
			break;
		}
		else 
		{
			cout << "this news does not exist" << endl;
		}
	}
while (true)
	{
		cout << "press 1 to update title only " << endl;
		cout << "press 2 to update decribtion only" << endl;
		cout << "press 3 to update category only" << endl;
		cout << "press 4 to update title and category" << endl;
		cout << "press 5 to update title and decribtion :: " << endl;
		cout << "press 6 to update category and decribtion :: " << endl;
		cout << "press 7 to update title and category and decribtion :: " << endl;
		getline(cin, choice);
		if (choice == "1")
		{
	        cout << "the new title :: ";
	        getline(cin, news_title);
			news_management::categorylist[news_category].newslist[stoi(no_of_new)].set_title(news_title);
	        update_news_in_database(no_of_new, news_title, "0", "0");
	        cout << "\t\tDONE!!!" << endl;
			break;
		}
		else if (choice == "2")
		{
	        cout << "the new decribtion :: ";
	        getline(cin, the_new);
			news_management::categorylist[news_category].newslist[stoi(no_of_new)].set_describtion(the_new);
	        update_news_in_database(no_of_new, "0", "0", the_new);
	        cout << "\t\tDONE!!!" << endl;
			break;
		}
		else if (choice == "3")
		{
	        cout << "the new category :: ";
	        getline(cin, news_category);
			news_management::categorylist[news_category].newslist[stoi(no_of_new)].set_category(news_category);
	        update_news_in_database(no_of_new, "0", news_category, "0");
	        cout << "\t\tDONE!!!" << endl;
			break;
		}
		else if (choice == "4")
		{
	        cout << "the new title :: ";
         	getline(cin, news_title);
        	cout << "the new category :: ";
        	getline(cin, news_category);
			news_management::categorylist[news_category].newslist[stoi(no_of_new)].set_title(news_title);
			news_management::categorylist[news_category].newslist[stoi(no_of_new)].set_category(news_category);
	        update_news_in_database(no_of_new, news_title, news_category, "0");
	        cout << "\t\tDONE!!!" << endl;
			break;
		}
		else if (choice == "5")
		{
	        cout << "the new title :: ";
         	getline(cin, news_title);
        	cout << "the new description :: ";
	        getline(cin, the_new);
			news_management::categorylist[news_category].newslist[stoi(no_of_new)].set_title(news_title);
			news_management::categorylist[news_category].newslist[stoi(no_of_new)].set_describtion(the_new);
	        update_news_in_database(no_of_new, news_title, "0", the_new);
	        cout << "\t\tDONE!!!" << endl;
			break;
		}
		else if (choice == "6")
		{
	        cout << "the new category :: ";
	        getline(cin, news_category);
        	cout << "the new description :: ";
	        getline(cin, the_new);
			news_management::categorylist[news_category].newslist[stoi(no_of_new)].set_category(news_category);
			news_management::categorylist[news_category].newslist[stoi(no_of_new)].set_describtion(the_new);
	        update_news_in_database(no_of_new, "0", news_category, the_new);
	        cout << "\t\tDONE!!!" << endl;
			break;
		}
		else if (choice == "7"){
	        cout << "the new title :: ";
	        getline(cin, news_title);
	        cout << "the new description :: ";
	        getline(cin, the_new);
	        cout << "the new category :: ";
	        getline(cin, news_category);
			news_management::categorylist[news_category].newslist[stoi(no_of_new)].set_title(news_title);
			news_management::categorylist[news_category].newslist[stoi(no_of_new)].set_category(news_category);
			news_management::categorylist[news_category].newslist[stoi(no_of_new)].set_describtion(the_new);
	        update_news_in_database(no_of_new, news_title, news_category, the_new);
	        cout << "\t\tDONE!!!" << endl;
			break;
		}
		else
		{
			cout << "\t\tERROR\nPlease check the number you entered\n" << endl;
		}
	}
}

void admin::add_newcategory()
{
	bool flag = 0;
	category new_category;
	while (true)
	{
		cout << "enter the name of the new category :: ";
		getline(cin, news_category);
		transform(news_category.begin(), news_category.end(), news_category.begin(), [](unsigned char c) { return std::toupper(c); });
		if (news_management::categorylist.count(news_category) == 0) {
			new_category.set_name(news_category);
			news_management::categorylist[news_category] = new_category;
			add_category_to_database(news_category);
			cout << "Done\n";
			break;
		}
		else 
		{
			cout << "This category aleardy exist " << endl;
			cout << "Press 1 to try another name or press 0 to exist" << endl;
			cin >> flag;
		}
		if (!flag)
			break;
	}
	
}


void admin::display_news_for_admin()
{
	for ( auto category : news_management::categorylist)
	{
		news_management::categorylist[category.first].display_news_for_admins();
	}
}

void admin::set_admin_name(string name)
{
	this->name = name;
}

void admin::set_admin_password(string password)
{
	this->password = password;
}

void admin::add_category_to_database(string& category_name)
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

	string sqlStatement = "INSERT INTO Category (Name) VALUES (?)";
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hConn, &hStmt);
	retcode = SQLPrepare(hStmt, (SQLCHAR*)sqlStatement.c_str(), SQL_NTS);

	SQLLEN cbName = SQL_NTS;
	std::wstring wCategoryName(category_name.begin(), category_name.end());
	retcode = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 50, 0, (SQLPOINTER)wCategoryName.c_str(), 0, &cbName);

	retcode = SQLExecute(hStmt);

	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	SQLDisconnect(hConn);
	SQLFreeHandle(SQL_HANDLE_DBC, hConn);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}

void admin::add_news_to_database(const string& category, const string& title,const  string& description,const  string& admin_name)
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

	string sqlStatement = "INSERT INTO News (Category, Title, Description, AdminName, number) VALUES (?, ?, ?, ?,NEXT VALUE FOR newsSuquence)";
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hConn, &hStmt);
	retcode = SQLPrepare(hStmt, (SQLCHAR*)sqlStatement.c_str(), SQL_NTS);

	SQLLEN cbCategory = SQL_NTS;
	SQLLEN cbTitle = SQL_NTS;
	SQLLEN cbDescription = SQL_NTS;
	SQLLEN cbAdminName = SQL_NTS;
	std::wstring wCategory(category.begin(), category.end());
	std::wstring wTitle(title.begin(), title.end());
	std::wstring wDescription(description.begin(), description.end());
	std::wstring wAdminName(admin_name.begin(), admin_name.end());
	retcode = SQLBindParameter(hStmt, 1, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 50, 0, (SQLPOINTER)wCategory.c_str(), 0, &cbCategory);
	retcode = SQLBindParameter(hStmt, 2, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 255, 0, (SQLPOINTER)wTitle.c_str(), 0, &cbTitle);
	retcode = SQLBindParameter(hStmt, 3, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 1000, 0, (SQLPOINTER)wDescription.c_str(), 0, &cbDescription);
	retcode = SQLBindParameter(hStmt, 4, SQL_PARAM_INPUT, SQL_C_WCHAR, SQL_WVARCHAR, 50, 0, (SQLPOINTER)wAdminName.c_str(), 0, &cbAdminName);

	retcode = SQLExecute(hStmt);

	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
	SQLDisconnect(hConn);
	SQLFreeHandle(SQL_HANDLE_DBC, hConn);
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}


void admin::update_news_in_database(const string& news_number,const  string& title,const  string& category,const  string& describtion) {
	// Declare variables for database connection
	SQLHANDLE sqlenvhandle;
	SQLHANDLE sqlconnectionhandle;
	SQLHANDLE sqlstatementhandle;
	SQLRETURN retcode;

	SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlenvhandle);

	SQLSetEnvAttr(sqlenvhandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

	SQLAllocHandle(SQL_HANDLE_DBC, sqlenvhandle, &sqlconnectionhandle);

	retcode = SQLDriverConnect(sqlconnectionhandle, NULL, (SQLCHAR*)"DRIVER={SQL Server}; SERVER=localhost, 1433; DATABASE=newsManagementSystem; UID=myID; PWD=myPW;", SQL_NTS, NULL, 0, NULL, SQL_DRIVER_NOPROMPT);

	SQLAllocHandle(SQL_HANDLE_STMT, sqlconnectionhandle, &sqlstatementhandle);

	string sql_query;
	if (title == "0" && category == "0" && describtion != "0")//update describtion only
	{
		 sql_query = "UPDATE News SET description = '"  + describtion + "' WHERE number = '" + news_number + "'";
	}
	else if (title != "0" && category == "0" && describtion == "0")//update title only
	{
		 sql_query = "UPDATE News SET title = '"  + title + "' WHERE number = '" + news_number + "'";
	}
	else if (title == "0" && category != "0" && describtion == "0")//update category only
	{
		 sql_query = "UPDATE News SET category = '"  + category + "' WHERE number = '" + news_number + "'";
	}
	else if (title != "0" && category != "0" && describtion == "0")//update title and category 
	{
		sql_query = "UPDATE News SET title  = '" + title + "', category = '" + category + "' WHERE number = '" + news_number + "'";
	}
	else if (title != "0" && category == "0" && describtion != "0")//update title and describtion 
	{
		 sql_query = "UPDATE News SET title = '"  + title + "', describtion = '" + describtion + "' WHERE number = '" + news_number + "'";
	}
	else if (title == "0" && category != "0" && describtion != "0")//update category and describtion 
	{
		 sql_query = "UPDATE News SET category = '"  + category + "', describtion = '" + describtion + "' WHERE number = '" + news_number + "'";
	}
	else {//update all
		 sql_query = "UPDATE News SET title = '" + title + "', category = '" + category + "', description = '" + describtion + "' WHERE number = '" + news_number + "'";
	}
	retcode = SQLExecDirect(sqlstatementhandle, (SQLCHAR*)sql_query.c_str(), SQL_NTS);

	SQLFreeHandle(SQL_HANDLE_STMT, sqlstatementhandle);
	SQLDisconnect(sqlconnectionhandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlconnectionhandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlenvhandle);
}
