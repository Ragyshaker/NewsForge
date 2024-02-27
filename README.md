# NewsForge
A news management system using C++ and SQL server DBMS

The News Management System is a C++ program designed to provide users with the latest news, filter news by category, rate news articles, and display them accordingly. This system integrates with a SQL Server database to manage user and administrator data securely.

For administrators:

Login: Administrators can log in using their credentials stored in the SQL Server database.
Post/Remove News: They can post new news articles or remove existing ones, with these actions being reflected in the database.
Update Existing News: Administrators have the ability to update the details of existing news articles, with changes being saved to the database.
Add New Category: They can add new categories such as Sport or Health and assign news articles to them, with category data being managed in the SQL Server database.
Display Average Rate: Administrators can view the average rating for a specific news article title, with this information being retrieved from the database.

For users:

Register/Login: Users can register by providing a username and password, and then log in using their credentials stored in the SQL Server database.
Display Latest News: Users can view the latest news articles fetched from the database.
Filter by Category: They can filter news articles based on specific categories they prefer, with category data being retrieved from the SQL Server database.
Rate News: Users have the option to rate news articles on a scale of 1 to 5, with their ratings being saved to the database.
Spam Reporting: Users have the option to report news articles as spam. If a user marks a post as spam, it will disappear from their news feed, and a count of how many users have reported it as spam will be displayed. However, the post remains visible to other users.
User Preferences: Users can customize their news feed based on their preferences, with the system fetching and displaying news articles accordingly from the database.
Comments Section: Each news article features a comments section where users can post comments. All users can view comments posted by others, fostering community engagement.

Key Features:

User Authentication: The system validates user login data against credentials stored in the SQL Server database to ensure secure access.
User Role Determination: It determines whether the user is an administrator or a regular user based on their credentials retrieved from the database.
News Filtering: Trivial or incorrect news articles with ratings below 2 are hidden from users, with this filtering being implemented based on data retrieved from the SQL Server database.
Descending Display: News articles are displayed in descending order according to their ratings, with this ordering being determined based on ratings data stored in the SQL Server database.
Customizable Categories: Users can choose which categories they prefer to view news articles from, with category data being retrieved from the SQL Server database.
Overall, the News Management System provides a user-friendly interface for accessing and managing news articles, integrating seamlessly with a SQL Server database to ensure efficient data storage and retrieval while maintaining security and reliability.
