#include<bits/stdc++.h>

using namespace std;

class Line
{
public:

	Line(int n, string text)
	{
		number = n;
		content = text;
	}

	void addText(string text)
	{
		content = text;
	}

	int number;
	string content;
};


list< Line * > textPad;
int padSize;

stack< pair <int, Line *> > undoStack;

stack< pair< int, Line *> > redoStack;

//map<int, pair<bool, Line *> > lineNumber;


void insert(int n, string text)
{
	n--;

	try
	{
		if (n < 0)
			throw "Invalid Line Number";

		else if (textPad.size() != 0 && n >= textPad.size())
			n = textPad.size();


		if (n == textPad.size())
		{
			Line * pTemp = new Line(n + 1, text);
			textPad.push_back(pTemp);
			undoStack.push(make_pair(2, pTemp));
		}

		else
		{
			int line_count = 0;

			list<Line *>::iterator curr;

			for (curr = textPad.begin(); line_count < n && curr != textPad.end(); ++curr)
			{
				line_count++;
			}

			Line * pTemp = new Line(n, text);

			textPad.insert(curr, pTemp);
			undoStack.push(make_pair(2, *curr));

			curr++;

			while (curr != textPad.end())
			{

				(*curr)->number += 1;

				curr++;
			}

		}

		padSize++;

	}

	catch (const char * c)
	{
		cout << c << endl;
	}
}


void deleteLine(int n)
{


	try
	{
		if (n <= 0 || n >= textPad.size())
			throw "Invalid Line Number";


		int line_count = 1;

		list<Line *>::iterator curr;
		list<Line *>::iterator prev;

		for (curr = textPad.begin(); line_count < n && curr != textPad.end(); ++curr)
		{
			line_count++;
		}


		Line * pTemp = (*curr);
		undoStack.push(make_pair(1, pTemp));
		prev = curr;
		curr++;
		textPad.erase(prev, curr);

		padSize--;
	}

	catch (const char * c)
	{
		cout << c << endl;
	}

}


void deleteLines(int n, int m)
{
	n--;
	m--;

	try
	{
		padSize -= (m - n) + 1;
		if (n <= 0 || n >= textPad.size())
			throw "Invalid Line Number";


		int line_count = 1;


		list<Line *>::iterator curr;
		list<Line *>::iterator prev;

		for (curr = textPad.begin(); line_count < n + 1 && curr != textPad.end(); ++curr)
		{
			prev = curr;
			line_count++;
		}


		list<Line *>::iterator  pLineN = curr;

		for (curr; line_count < m + 1 && curr != textPad.end(); ++curr)
		{
			prev = curr;
			line_count++;
		}


		list<Line *>::iterator  pLineM = curr;

		//undoStack.push(make_pair(1, pTemp));

		textPad.erase(pLineN, pLineM++);


	}

	catch (const char * c)
	{
		cout << c << endl;
	}

}


void undo()
{
	pair<int, Line *> operation = undoStack.top();
	redoStack.push(operation);
	undoStack.pop();

	switch (operation.first)
	{
	case 1: insert(operation.second->number, operation.second->content);
		break;

	case 2:deleteLine(operation.second->number);
		break;

	}
}



void redo()
{
	pair<int, Line *> operation = redoStack.top();
	undoStack.push(operation);
	redoStack.pop();

	switch (operation.first)
	{

	case 1:deleteLine(operation.second->number);
		break;

	case 2: insert(operation.second->number, operation.second->content);
		break;

	}
}



vector<string> copy(int n, int m)
{
	vector<string> ans;

	int line_count = 1;

	list<Line *>::iterator curr;

	for (curr = textPad.begin(); line_count < n && curr != textPad.end(); ++curr)
	{
		line_count++;
	}

	for (curr; line_count <= m && curr != textPad.end(); ++curr)
	{
		ans.push_back((*curr)->content);
		line_count++;
	}

	return ans;

}


void displayLine(int n, int m)
{
	if (m > padSize)
		m = padSize;

	vector<string> ans = copy(n, m);

	for (int i = 0; i < ans.size(); ++i)
	{
		cout << endl;


		for (int j = 0; j < ans[i].size(); ++j)
		{
			cout << ans[i][j];
		}
	}
}




int main()
{
	padSize = 0;

	insert(1, "Hey");
	insert(2, "What is new");
	insert(3, "It's been so long");
	insert(4, "How are you?");
	cout << padSize;

	displayLine(1, 4);
	cout << endl << endl << endl;
	insert(4, "Where were you?");

	displayLine(1, 5);
	cout << endl << endl << endl;

	deleteLine(2);
	cout << endl << endl << endl;

	displayLine(1, 5);
	cout << textPad.size();
	cout << endl << endl << endl;
	undo();

	displayLine(1, 5);
	cout << padSize;
	cout << endl << endl << endl;

	redo();

	displayLine(1, 5);
	cout << padSize;
	cout << endl << endl << endl;

	system("pause");

	return 0;

}

//list functions to learn