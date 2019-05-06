#include<bits/stdc++.h>

using namespace std;


class Book
{

private:
	string name;
	string author;
	string publisher;
	int publish_year;
	int price;
	int count;

public:
	
	Book(string name, string author, string publisher, int publisher_year, int price, int count)
	{
		this->name = name;
		this->author = author;
		this->publisher = publisher_year;
		this->price = price;
		this->count = count;
	}

	string getName()
	{
		return name;
	}

	string getAuthor()
	{
		return author;
	}

	string getPubLisher()
	{
		return publisher;
	}

};



struct TrieNode
{
	map<char, TrieNode *> children;
	vector<Book *> books;
};


class Trie
{
private:
	TrieNode * root;
	string name;

public:
	Trie()
	{
		root = new TrieNode;
	}

	void insertSuffix(string s, Book * book)
	{
		TrieNode * curr = root;

		for (int i = 0; i < s.size(); ++i)
		{
			if (curr->children.find(s[i]) == curr->children.end())
				curr->children[s[i]] = new TrieNode;

			curr = curr->children[s[i]];
			curr->books.push_back(book);
		}
	}


	void insertBook(string s, Book * book)
	{
		for (int i = 0; i < s.size(); ++i)
			insertSuffix(s.substr(i), book);
	}


	vector<Book *> searchBooks(string s)
	{
		TrieNode * curr = root;

		for (int i = 0; i < s.size(); ++i)
		{
			if (curr->children.find(s[i]) == curr->children.end())
				return vector<Book * >();

			else
			{
				curr = curr->children[s[i]];
			}

		}

		return curr->books;
	}

};


class BookInventory
{
private:
	list<Book *> books;
	Trie Name;
	Trie Author;
	Trie Publisher;

public:

	void addNewBook(string name, string author, string publisher, int publisher_year, int price, int count)
	{
		Book * book = new Book(name, author, publisher, publisher_year, price, count);
		books.push_back(book);

		Name.insertBook(name, book);
		Author.insertBook(author, book);
		Publisher.insertBook(publisher, book);
	}


	void removeBook(Book book)
	{
		list<Book * >::iterator it;

		for (it = books.begin(); it != books.end(); ++it)
		{
			if ( (*it)->getName() == book.getName() )
				break;
		}

		if (it != books.end() ) 
		 books.erase(it);
	}


	void findByAuthor(string s)
	{
		vector<Book *> books = Author.searchBooks(s);

		if (books.size() == 0)
		{
			cout << "Not Available" << endl;
			return;
		}

		
		for (int i = 0; i < books.size(); ++i)
			cout << books[i]->getName()<<endl;


	}


	void findByName(string s)
	{
		vector<Book *> books = Name.searchBooks(s);

		if (books.size() == 0)
		{
			cout << "Not Available" << endl;
			return;
		}


		for (int i = 0; i < books.size(); ++i)
			cout << books[i]->getName() << endl;


	}

	void findByPublisher(string s)
	{
		vector<Book *> books = Publisher.searchBooks(s);

		if (books.size() == 0)
		{
			cout << "Not Available" << endl;
			return;
		}


		for (int i = 0; i < books.size(); ++i)
			cout << books[i]->getName() << endl;


	}

};

int main()
{
	BookInventory inventory;
	inventory.addNewBook("mycodemyway", "savar", "bhills", 2010, 1000, 10);
	inventory.addNewBook("javacodecourse", "savar", "bhills", 2010, 1000, 10);
	inventory.addNewBook("cppcodecourse", "chelsea", "bhills", 2010, 1000, 10);

	inventory.findByAuthor("savar");

	system("pause");
	return 0;

}
