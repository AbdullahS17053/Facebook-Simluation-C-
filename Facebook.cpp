#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Object;
class post;
class page;
class user;
class memory;
class Date;
class Activity;
class Comment;

class helper
{
public:

	static int StringLenght(const char* str)
	{
		int i = 0;
		while (str[i] != '\0')//return length of string excluding null
		{
			i++;
		}
		return i;

	}

	static void StringCopy(char*& dest, char*& src) {
		int length = StringLenght(src);//deep copies strings
		int i = 0;
		for (i = 0; i < length; i++)
		{
			dest[i] = src[i];
		}
		dest[i] = '\0';
	}

	static char* GetStringFromBuffer(char* str)
	{
		char* string = new char[StringLenght(str) + 1];//allocates memory depending on size including 1 for null as well
		StringCopy(string, str);
		return string;
	}
	
	static bool compareString(const char* str1, const  char* str2)
	{
		if (StringLenght(str1) == StringLenght(str2))
		{
			int size = StringLenght(str2);
			for (int i = 0; i < size; ++i)
			{
				if (str1[i] != str2[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	static char* concatenate(const char* str)
	{
		char* string = new char[StringLenght(str) + 1];//allocates memory depending on size including 1 for null as well
		int length = StringLenght(str);//deep copies strings
		int i = 0;
		for (i = 0; i < length; i++)
		{
			string[i] = str[i];
		}
		string[i] = '\0';
		return string;
	}
};

class Object
{

protected:

	char* id;

public:

	Object()
	{
		id = NULL;
	}
	virtual void sharepost(post* obj)
	{

	}
	virtual void likepost(post* obj)
	{

	}
	virtual void AddPostToTimeline(post* postptr)
	{

	}
	virtual char* getId()
	{
		return 0;
	}
	virtual char* getName()
	{
		return 0;

	}
	virtual ~Object()
	{
		delete[] id;
		id = NULL;
	}
	virtual void listView() = 0;

};

class Date
{

private:

	int day;
	int month;
	int year;
	

public:

	static Date systemdate;

	Date()
	{
		day = month = year = 0;
	}

	void setSystemDate(int d, int m, int y)
	{
		systemdate.setDate(d, m, y);
		cout << "\n-------------------------------------------------------------------------------------------------------------\n\n";
		cout << "Command: Set current System date: ";
		systemdate.showdate();
		cout << "\n-------------------------------------------------------------------------------------------------------------\n\n";
		cout << "\nSystem Date: ";
		systemdate.showdate();
		cout << "\n";
	}

	void setDate(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
	}

	void loadDatefromfile(ifstream& fin)
	{
		fin >> day;
		fin >> month;
		fin >> year;
	}

	void showdate()
	{
		cout << "(" << day << "/" << month << "/" << year << ")" << endl;
	}

	bool checkMemoryDate(const Date& rhs)
	{
		if (day == rhs.day && month == rhs.month)
		{
			return true;
		}
		return false;
	}

	Date& operator=(const Date& rhs)
	{
		if (this != &rhs)
		{
			day = rhs.day;
			month = rhs.month;
			year = rhs.year;
		}
		return *this;
		
	}

	bool operator==(const Date& rhs)
	{
		if (day == rhs.day && month == rhs.month && year == rhs.year)
		{
			return true;
		}
		return false;
	}

	Date operator--(int)
	{
		Date temp;
		if (day == month == 1)
		{
			temp.day = 31;
			temp.month = 12;
			temp.year = year - 1;
			return temp;
		}
		else if (day == 1)
		{
			temp.month = month - 1;
			temp.year = year;
			if (month == 3)
			{
				temp.day = 28;
			}
			else if (month == 8)
			{
				temp.day = 31;
			}
			else if ((month == 5) || (month == 7) ||  month == 10 || month == 12)
			{
				temp.day = 30;
			}
			else
			{
				temp.day = 31;
			}
			return temp;
		}
		else if (day != 1)
		{
			temp.day = day - 1;
			temp.month = month;
			temp.year = year;
			return temp;
		}

	}

	int operator-(const Date& rhs)
	{
		if (day == rhs.day && month == rhs.month)
		{
			return (year - rhs.year);
		}
	}
};

Date Date::systemdate;

class Activity
{

private:

	int type;
	char* value;

public:

	Activity()
	{
		type = 0;
		value = NULL;
	}

	~Activity()
	{
		delete[] value;
		value = NULL;
	}

	void loadActivity(ifstream& fin)
	{
		char temp[80];
		fin >> type;
		fin.getline(temp, 80);
		value = helper::GetStringFromBuffer(temp);

	}

	void showActivity()
	{
		if (type == 1)
		{
			cout << " is feeling" << value << ".\n\n";
		}
		else if (type == 2)
		{
			cout << " is thinking about" << value << ".\n\n";
		}
		else if (type == 3)
		{
			cout << " is making" << value << ".\n\n";
		}
		else
		{
			cout << " is celebrating" << value << ".\n\n";
		}
	}
};

class comment
{

private:

	char* id;
	char* text;
	Object* commentby;

public:

	comment()
	{
		id = NULL;
		text = NULL;
		commentby = NULL;
	}

	~comment()
	{
		delete[] id;
		id = NULL;
		delete[] text;
		text = NULL;
		commentby = NULL;
	}

	comment(char* t,Object* ptr,int totalcomments)
	{
		id = helper::concatenate(("c" + to_string(totalcomments)).c_str());
		text = helper::GetStringFromBuffer(t);
		commentby = ptr;
	}

	void loadCommentId(ifstream& fin)
	{
		char temp[80];
		fin >> temp;
		id = helper::GetStringFromBuffer(temp);
	}

	void loadCommentData(Object* ptr, ifstream& fin)
	{
		char temp[80];
		commentby = ptr;
		fin.ignore();
		fin.getline(temp, 80);
		text = helper::GetStringFromBuffer(temp);
	}

	void showComment()
	{
		cout <<"\t\t\t" << commentby->getName() << " wrote: " << "' " << text << " '\n\n";
	}
};

class post
{
protected:

	char* id;
	char* text;
	Date shareddate;

private:

	int posttype;
	int likes;
	Activity* activity;
	comment** Comments;
	Object* sharedby;
	Object** likedby;
	int totalcomments;

public:

	post()
	{
		id = NULL;
		text = NULL;
		likes = 0;
		posttype = 0;
		sharedby = NULL;
		likedby = NULL;
		activity = NULL;
		Comments = NULL;
		totalcomments = 0;
	}

	post(char* t, Date date)
	{
		id = NULL;
		text = helper::GetStringFromBuffer(t);
		likes = 0;
		posttype = 0;
		shareddate = date;
		likedby = NULL;
		sharedby = NULL;
		activity = NULL;
		Comments = NULL;
		totalcomments = 0;
	}

	virtual ~post()
	{
		delete[] id;
		id = NULL;
		delete[] text;
		text = NULL;
		delete activity;
		sharedby = NULL;
		delete[] likedby;
		sharedby = NULL;
		int i;
		for (i = 0; i < totalcomments; i++)
		{
			delete Comments[i];
		}
		delete[] Comments;
	}

	void loadPostData(ifstream& fin)
	{
		char temp[80];
		activity = new Activity;
		fin >> posttype;
		fin >> temp;
		id = helper::GetStringFromBuffer(temp);
		shareddate.loadDatefromfile(fin);
		fin.ignore();
		fin.getline(temp, 80);
		text = helper::GetStringFromBuffer(temp);
		if (posttype == 2)
		{
			
			activity->loadActivity(fin);
		}
	
	}

	virtual void showOnTimeline()
	{
		
		cout << "---" << sharedby->getName();
		if (posttype == 2)
		{
			activity->showActivity();
			cout << "   '" << text << "'...";
		}
		else
		{
			cout << " shared " << "'" << text << "'...";
		}
		shareddate.showdate();
		cout <<"\n\t\t\tComments: \n\n";
		int i;
		if (totalcomments == 0)
		{
			cout << "\t\t\tNo comments yet! Check back later.\n\n";
		}
		else
		{
			for (i = 0; i < totalcomments; i++)
			{
				Comments[i]->showComment();
			}
		}
		cout << "\t\t\t\t\tEND OF POST\n\n\n";
	}

	virtual void showOnHome()
	{
		Date yesterday;
		int i;
		yesterday = (Date::systemdate)--;
		if ((shareddate == Date::systemdate) || (shareddate == yesterday))
		{
			cout << "---" << sharedby->getName();
			if (posttype == 2)
			{
				activity->showActivity();
				cout << "   '" << text << "'" << endl;
			}
			else
			{
				cout << " shared " << "'" << text << "'" << endl;
			}
			cout << "\n\t\t\tComments: \n\n";
			if (totalcomments == 0)
			{
				cout << "\t\t\tNo comments yet! Check back later.\n\n";
			}
			else
			{
				for (i = 0; i < totalcomments; i++)
				{
					Comments[i]->showComment();
				}
			}
			cout << "\t\t\t\t\tEND OF POST\n\n\n";

		}


	}

	void setSharedby(Object* obj)
	{
		sharedby = obj;
	}

	void setLikedby(Object* obj)
	{
		if (likes == 0)
		{
			likedby = new Object * [10];
		}
		if (likes < 10)
		{
			likedby[likes] = obj;
			likes++;
		}

	}

	void likePostByUser(Object* liker)
	{
		if (likes == 10)
		{
			cout << "\nPost has reached like limit. Please try liking later.\n";
			return;
		}
		else
		{
			cout << "\nPost liked!\n\n";
			likedby[likes] = liker;
			likes++;
		}

	}

	void likerListView(int i)
	{
		cout << likedby[i]->getId() << " - " << likedby[i]->getName() << "\n\n";
	}

	void likedList()
	{
		int i;
		cout << "Post liked by:\n\n";
		for (i = 0; i < likes; i++)
		{
			likedby[i]->listView();
			//likerListView(i)
		}
	}

	void addComment(comment* ptr)
	{
		if (totalcomments == 0)
		{
			Comments = new comment*[10];
		}
		if (totalcomments < 10)
		{
			Comments[totalcomments] = ptr;
			totalcomments++;
		}

	}

	void addCommentByUser(Object* commenter, char* c,int totalcomments)
	{
		if (totalcomments == 10)
		{
			cout << "Post has reached comment limit. Please try commenting later.\n";
			return;
		}
		else
		{
			cout << "\nComment added!\n\n";
			comment* usercomment = new comment(c, commenter,totalcomments);
			addComment((usercomment));
		}

	}

	bool isMemory()
	{
		if (shareddate.checkMemoryDate( Date::systemdate))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	virtual void createMemory(char* t,post* memorypost)
	{

	}

	char* getId()
	{
		return id;
	}

	Date getPostDate()
	{
		return shareddate;
	}

	char* getText()
	{
		return text;
	}

	Object* getSharedby()
	{
		return sharedby;
	}
};

class memory : public post
{
private:

	post* originalpost;

public:

	memory()
	{
		id = NULL;
		text = NULL;
		originalpost = NULL;
	}

	void createMemory(char* t, post* original,int totalposts)
	{
		id = helper::concatenate(("posts" + to_string(totalposts)).c_str());
		text = helper::GetStringFromBuffer(t);
		originalpost = original;
		shareddate = Date::systemdate;
	}

	void showOnTimeline()
	{
		cout << "~~~ " << originalpost->getSharedby()->getName() << " shared a memory ~~~...";
		shareddate.showdate();
		cout << "\n'" << text << "'\n";
		cout << "\n\t\t(" << shareddate - originalpost->getPostDate() << " years ago)\t\t\n\n";
		originalpost->showOnTimeline();
	}

	void showOnHome()
	{
		cout << "~~~ " << originalpost->getSharedby()->getName() << " shared a memory ~~~...\n";
		cout << "\n'" << text << "'\n";
		cout << "\n\t\t(" << shareddate - originalpost->getPostDate() << " years ago)\t\t\n\n";
		originalpost->showOnTimeline();
	}

	~memory()
	{

	}

};

class page : public Object
{
private:

	char* pagename;
	int likedusers;
	post** timeline;
	int totalposts;

public:

	page()
	{
		id = NULL;
		pagename = NULL;
		likedusers = 0;
		timeline = NULL;
		totalposts = 0;
	}

	~page()
	{
		delete[] pagename;
		pagename = NULL;
		int i;
		for (i = 0; i < totalposts; i++)
		{
			delete timeline[i];
		}
		delete[] timeline;
		timeline = NULL;
	}

	void operator=(const page& obj)
	{
		id = helper::GetStringFromBuffer(obj.id);
		pagename = helper::GetStringFromBuffer(obj.pagename);
		likedusers = obj.likedusers;

	}

	void loadPageData(ifstream& fin)
	{
		char temp[80];
		fin >> temp;
		id = helper::GetStringFromBuffer(temp);
		fin.ignore();
		fin.getline(temp, 80);
		pagename = helper::GetStringFromBuffer(temp);
	}

	void listView()
	{
		cout << id << " - " << pagename << "\n\n";
	}

	void viewPage()
	{
		int i;
		cout << pagename << "\n\n\n";
		for (i = 0; i < totalposts; i++)
		{
			timeline[i]->showOnTimeline();
			cout << "\n\n";
		}
	}

	void AddPostToTimeline(post* postptr)
	{
		if (totalposts == 0)
		{
			timeline = new post * [10];
		}
		timeline[totalposts] = postptr;
		totalposts++;

	}

	void showOnUserHome()
	{
		int i;
		for (i = 0; i < totalposts; i++)
		{
			timeline[i]->showOnHome();
		}
	}

	char* getId()
	{
		return id;

	}

	char* getName()
	{
		return pagename;
	}

};

class user: public Object
{
private:

	char* firstname;
	char* lastname;
	user** friendlist;
	page** likedpages;
	post** timeline;
	int totalfriends;
	int totallikedpages;
	int totalposts;

public:

	user()
	{
		id = NULL;
		firstname = NULL;
		lastname = NULL;
		friendlist = NULL;
		likedpages = NULL;
		totalfriends = 0;
		totallikedpages = 0;
		timeline = NULL;
		totalposts = 0;
	}

	~user() 
	{
		delete[] firstname;
		firstname = NULL;
		delete[] lastname;
		lastname = NULL;
		delete[] friendlist;
		friendlist = NULL;
		delete[] likedpages;
		likedpages = NULL;
		int i;
		for (i = 0; i < totalposts; i++)
		{
			delete timeline[i];
		}
		delete[] timeline;
		timeline = NULL;
	}

	void loadUserData(ifstream& fin, char**& tempids)
	{
		char temp[80];
		int i = 0, j = 0;
		fin >> temp;
		id = helper::GetStringFromBuffer(temp);
		fin >> temp;
		firstname = helper::GetStringFromBuffer(temp);
		fin >> temp;
		lastname = helper::GetStringFromBuffer(temp);
		fin >> temp;
		for (i = 0; i < 10; i++)
		{
			tempids[i] = 0;
		}
		i = 0;
		while (temp[0] != '-')
		{

			tempids[i] = helper::GetStringFromBuffer(temp);
			i++;
			fin >> temp;


		}
		if (temp[0] == '-')
		{
			tempids[i] = helper::GetStringFromBuffer(temp);

		}

	}

	void addFriend(user* frnd)
	{
		if (totalfriends == 0)
		{
			friendlist = new user * [10];
		}
		if (totalfriends < 10)
		{
			friendlist[totalfriends] = frnd;
			totalfriends++;
		}
		else
		{
			cout << "\nFriend list limit has been reached. Try adding a friend later.\n";
		}

	}

	void likePage(page* liked)
	{
		if (totallikedpages == 0)
		{
			likedpages = new page * [10];
		}
		if (totallikedpages < 10)
		{
			likedpages[totallikedpages] = liked;
			totallikedpages++;
		}
		else
		{
			cout << "\nLiked page limit has been reached. Try adding a friend later.\n";
		}
	}

	void AddPostToTimeline(post* postptr)
	{
		if (totalposts == 0)
		{
			timeline = new post * [10];
		}
		timeline[totalposts] = postptr;
		totalposts++;

	}

	void ViewTimeline()
	{
		int i;
		cout << firstname << " " << lastname << " --- Timeline\n\n\n";
		for (i = 0; i < totalposts; i++)
		{
			timeline[i]->showOnTimeline();
			cout << "\n\n";
		}
	}

	void ViewHomePage()
	{
		int i, j;
		cout << firstname << " " << lastname << " --- Home Page\n\n\n";
		for (i = 0; i < totalfriends; i++)
		{
			for (j = 0; j < friendlist[i]->totalposts; j++)
			{
				friendlist[i]->timeline[j]->showOnHome();
			}
		}
		for (i = 0; i < totallikedpages; i++)
		{
			likedpages[i]->showOnUserHome();
		}

	}

	void listView()
	{
		cout << id << " - " << firstname << "  " << lastname << "\n\n";
	}

	void ShowFriends()
	{
		int i;
		cout << firstname << " " << lastname << " Friend List\n\n";
		for (i = 0; i < totalfriends; i++)
		{
			friendlist[i]->listView();
		}
	}

	void ShowPages()
	{
		int i;
		cout << firstname << " " << lastname << " Liked Pages\n\n";
		for (i = 0; i < totallikedpages; i++)
		{
			likedpages[i]->listView();
		}


	}

	void showMemories()
	{
		int i;
		cout << "We hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\n\n\n";
		for (i = 0; i < totalposts; i++)
		{
			if (timeline[i]->getPostDate().checkMemoryDate(Date::systemdate) == true)
			{
				cout << "On this Day\n\n" << Date::systemdate - timeline[i]->getPostDate() << " Years Ago\n\n";
				timeline[i]->showOnTimeline();
				return;
			}
		}
		cout << "\n\nYou do not have any memories at this time. Check back later!.\n\n";

	}

	void shareMemory(post* memorypost, char* memorytext,int postsnum)
	{
		int i;
		if (checkMemory(memorypost) == true)
		{
			if (totalposts == 10)
			{
				cout << "\nTimeline limit reached. Try sharing memory later!\n\n";
				return;
			}
			
			for (i = 0; i < totalposts; i++)
			{
				timeline[totalposts - i] = timeline[totalposts - i - 1];
			}
			totalposts++;
			memory* temp = new memory;
			temp->createMemory(memorytext, memorypost,postsnum);
			timeline[0] = temp;
			cout << "\nMemory shared!\n\n";
		}
		else
		{
			cout << "\nPost does not belong to this user. Please try again.\n\n";
		}
		

	}

	bool checkMemory(post* memorypost)
	{
		int i;
		for (i = 0; i < totalposts; i++)
		{
			if (timeline[i] == memorypost)
			{
				return true;
			}
		}
		return false;
	}

	char* getId()
	{
		return id;
	}

	char* getName()
	{
		int i = 0, j = 0;
		char temp[50];
		char* name;
		while (firstname[i] != '\0')
		{
			temp[i] = firstname[i];
			i++;
		}
		temp[i++] = ' ';
		while (lastname[j] != '\0')
		{
			temp[i] = lastname[j];
			i++;
			j++;
		}
		temp[i] = '\0';
		name = helper::GetStringFromBuffer(temp);
		return name;
	}
	
};

class facebook
{
private:

	user** Users;
	page** Pages;
	post** Posts;
	comment** Comments;

	static int totalusers;
	static int totalpages;
	static int totalposts;
	static int totalcomments;

public:

	facebook()
	{
		Users = NULL;
		Pages = NULL;
		Posts = NULL;
		Comments = NULL;
	}

	~facebook()
	{
		int i;
		for (i = 0; i < totalpages; i++)
		{
			delete Pages[i];
		}
		delete[] Pages;
		Pages = NULL;
		for (i = 0; i < totalusers; i++)
		{
			delete Users[i];
		}
		delete[] Users;
		Users = NULL;
		delete[] Posts;
		Posts = NULL;
		delete[] Comments;
		Comments = NULL;
	}

	void loadFile(const char* username, const char* pagename, const char* postname, const char* commentsname)
	{
		loadPages(pagename);
		loadUsers(username);
		loadPosts(postname);
		loadComments(commentsname);
	}

	void loadPages(const char* pagename)
	{
		ifstream fin(pagename);
		int i;
		fin >> totalpages;
		Pages = new page * [totalpages];
		for (i = 0; i < totalpages; i++)
		{
			Pages[i] = new page;
			Pages[i]->loadPageData(fin);
		}

	}

	void loadUsers(const char* pagename)
	{
		ifstream fin(pagename);
		int i, j;
		char temp[80];
		fin >> totalusers;
		Users = new user * [totalusers];
		char*** tempids = new char** [totalusers];
		for (i = 0; i < totalusers; i++)
		{
			tempids[i] = new char* [10];
			Users[i] = new user;
			Users[i]->loadUserData(fin, tempids[i]);
			fin >> temp;
			while (temp[0] != '-')
			{
				Users[i]->likePage(searchPageFromId(temp));
				fin >> temp;
			}
		}
		for (i = 0; i < totalusers; i++)
		{
			j = 0;
			while (tempids[i][j][0] != '-')
			{
				Users[i]->addFriend(searchUserFromId(tempids[i][j]));
				j++;
			}
		}
		//deleting tempids
		for (i = 0; i < totalusers; i++)
		{
			for (j = 0; j < 10; j++)
			{
				delete[] tempids[i][j];
			}
		}
		delete[] tempids;
	}

	void loadPosts(const char* postname)
	{
		ifstream fin(postname);
		int i;
		char temp[80];
		fin >> totalposts;
		Object* objptr;
		Posts = new post * [totalposts];
		for (i = 0; i < totalposts; i++)
		{
			Posts[i] = new post;
			Posts[i]->loadPostData(fin);
			fin >> temp;
			if (temp[0] == 'p')
			{
				objptr = searchPageFromId(temp);
			}
			else
			{
				objptr = searchUserFromId(temp);
			}
			Posts[i]->setSharedby(objptr);
			objptr->AddPostToTimeline(Posts[i]);
			fin >> temp;
			while (temp[0] != '-')
			{
				if (temp[0] == 'p')
				{
					objptr = searchPageFromId(temp);
				}
				else
				{
					objptr = searchUserFromId(temp);
				}
				Posts[i]->setLikedby(objptr);
				fin >> temp;
			}
		}

	}

	void loadComments(const char* commentsname)
	{
		int i;
		ifstream fin(commentsname);
		fin >> totalcomments;
		Comments = new comment * [totalcomments];
		Object* objptr;
		for (i = 0; i < totalcomments; i++)
		{
			char temp[80];
			Comments[i] = new comment;
			Comments[i]->loadCommentId(fin);
			fin >> temp;
			searchPostFromId(temp)->addComment(Comments[i]);
			fin >> temp;
			if (temp[0] == 'p')
			{
				objptr = searchPageFromId(temp);
			}
			else
			{
				objptr = searchUserFromId(temp);
			}
			Comments[i]->loadCommentData(objptr, fin);



		}


	}

	page* searchPageFromId(char* ID)
	{
		int i;
		for (i = 0; i < totalpages; i++)
		{
			if (helper::compareString(ID, Pages[i]->getId()) == true)
			{
				return Pages[i];
			}

		}
		return NULL;

	}

	user* searchUserFromId(char* ID)
	{
		int i;
		for (i = 0; i < totalusers; i++)
		{
			if (helper::compareString(ID, Users[i]->getId()) == true)
			{
				return Users[i];
			}

		}
		return NULL;

	}

	post* searchPostFromId(char* ID)
	{
		int i;
		for (i = 0; i < totalposts; i++)
		{
			if (helper::compareString(ID, Posts[i]->getId()) == true)
			{
				return Posts[i];
			}

		}
		return NULL;

	}


	void run()
	{
		cout << "\nWelcome to Facebook!\n";

		char userid[10] = "u7";
		char userid2[50] = "u11";
		char pageid[10] = "p1";
		char postid[10] = "post5";
		char comment[50] = "Good Luck for your Resultttt";
		char comment1[50] = "Thanks for the wishes";
		char memorypost[10] = "post10";
		char memory[80] = "Never thought I will be specialist in this field...";

		user* currentuser;
		post* currentpost = searchPostFromId(postid);
		page* currentpage = searchPageFromId(pageid);
		
		Date::systemdate.setSystemDate(15,11,2017);
		setCurrentUser(userid, currentuser);

		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: View Friend List\n\n" << "-------------------------------------------------------------------------------------------------------------\n\n\n";
		currentuser->ShowFriends();
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: View Liked Pages\n\n" << "-------------------------------------------------------------------------------------------------------------\n" << endl;
		currentuser->ShowPages();
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: View Home\n\n" << "-------------------------------------------------------------------------------------------------------------\n" << endl;
		currentuser->ViewHomePage();
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: View Timeline\n\n" << "-------------------------------------------------------------------------------------------------------------\n" << endl;
		currentuser->ViewTimeline();
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: View Liked List\n\n" << "-------------------------------------------------------------------------------------------------------------\n" << endl;;
		currentpost->likedList();
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: LikePost(" << postid << ")\t\n\n" << "-------------------------------------------------------------------------------------------------------------\n" << endl;;
		currentpost->likePostByUser(currentuser);
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: View Liked List\n\n" << "-------------------------------------------------------------------------------------------------------------\n" << endl;;
		currentpost->likedList();
		postid[4] = '4';
		currentpost = searchPostFromId(postid);
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: PostComment(" << postid << "," << comment << ")\t\n\n" << "-------------------------------------------------------------------------------------------------------------\n" << endl;
		currentpost->addCommentByUser(currentuser, comment,++totalcomments);
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: ViewPost(" << postid << ")\t\n\n" << "------------------------------------------------------------------------------------------------------------ - \n" << endl;
		currentpost->showOnTimeline();
		postid[4] = '8';
		currentpost = searchPostFromId(postid);
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: PostComment(" << postid << "," << comment1 << ")\t\n\n" << "-------------------------------------------------------------------------------------------------------------\n" << endl;
		currentpost->addCommentByUser(currentuser, comment1,++totalcomments);
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: ViewPost(" << postid << ")\t\n\n" << "-------------------------------------------------------------------------------------------------------------\n" << endl;
		currentpost->showOnTimeline();
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: See Your Memories()\t\n\n" << "-------------------------------------------------------------------------------------------------------------\n" << endl;
		currentuser->showMemories();
		currentpost = searchPostFromId(memorypost);
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: ShareMemory(" << memorypost << "," << memory << ")\t\n\n" << "------------------------------------------------------------------------------------------------------------ - \n" << endl;
		currentuser->shareMemory(currentpost, memory,totalposts);
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: View Timeline\n\n" << "-------------------------------------------------------------------------------------------------------------\n" << endl;
		currentuser->ViewTimeline();
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: View Page " << pageid << "\n\n" << "------------------------------------------------------------------------------------------------------------ - \n" << endl;
		currentpage->viewPage();

		setCurrentUser(userid2, currentuser);

		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: View Home\n\n" << "-------------------------------------------------------------------------------------------------------------\n" << endl;
		currentuser->ViewHomePage();
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: View Timeline\n\n" << "-------------------------------------------------------------------------------------------------------------\n" << endl;
		currentuser->ViewTimeline();
		cout << "\nLeaving Facebook. Goodbye!\n";
	}

	void setCurrentUser(char* userid,user*& currentuser)
	{
		currentuser = searchUserFromId(userid);
		cout << "\n-------------------------------------------------------------------------------------------------------------" << endl << "\nCommand: Set current user '" << userid << "'\n\n" << "-------------------------------------------------------------------------------------------------------------\n\n\n";
		if (currentuser == NULL)
		{
			cout << "User not found.\n";
			return;
		}
		cout << currentuser->getName() << " set as current user.\n\n";
	}

};

int facebook::totalusers = 0;
int facebook::totalpages = 0;
int facebook::totalposts = 0;
int facebook::totalcomments = 0;

int main()
{
	facebook f;
	f.loadFile("users.txt", "pages.txt","posts.txt","comments.txt");
	f.run();

}