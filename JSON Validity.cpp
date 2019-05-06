#include<bits/stdc++.h>

using namespace std;

class TrieNode
{
public:
	TrieNode()
	{
		mIsLeaf = false;
	}

	vector<int> mValues;
	map<char, TrieNode *> mChildren;
	bool mIsLeaf;
};


class Trie
{
public:
	TrieNode * mRoot;

	Trie()
	{
		mRoot = new TrieNode();
	}



	bool insert(string path, int val)
	{
		TrieNode * curr = mRoot;

		for (int i = 0; i < path.size(); ++i)
		{
			char c = path[i];

			if ( curr->mIsLeaf )
				return false;

			if ( curr->mChildren.find(c) == curr->mChildren.end() )
			{
				curr->mChildren[c] = new TrieNode();
			}

			curr = curr->mChildren[c];

		}


		if (curr->mChildren.size() != 0)
			return false;


		curr->mIsLeaf = true;
		curr->mValues.push_back(val);

		return true;
	}

	void printJson();

};


void printNode(TrieNode * node, int level)
{
	string space = "";

	for (int i = 0; i < level; ++i)
	{
		space += '\t';
	}

	//cout << space;

	if (node->mIsLeaf)
	{
		cout << "[ ";

		for (int j = 0; j < node->mValues.size(); ++j)
		{
			cout << node->mValues[j] << ", ";
		}

		cout << "], "<<endl;

		return;
	}




	map<char, TrieNode *>::iterator it;

	cout << "{" << endl;

	for (it = node->mChildren.begin(); it != node->mChildren.end(); ++it)
	{
		cout << space << it->first<<" : ";

		printNode(it->second, level + 1);
	}

	cout <<space<< "}," << endl;

}




void Trie::printJson()
{
	printNode(mRoot, 1);

}






pair<bool , pair<string, int> > stringParse(string input)
{
	string path = "";
	int val;
	bool valid = true;

	if (input.size() <= 2)
	{
		valid = false;
	}


	else
	{

		for (int i = 0; i < input.size(); ++i)
		{
			char c = input[i];

			if ( isalpha(c) )
			{
				path += c;
			}

			else if (c == '<' ) //(c == '=' && i != input.size() - 2
			{
				valid = false;
				break;
			}

		}

		int i = input.size() - 1;

		string digit = "";

		while ( isdigit(input[i]) )
		{

			digit += input[i];
			i--;
		}


		if (input[i] != '=' || !isdigit(input[i + 1]) )
		{
			valid = false;
		}

		reverse(digit.begin(), digit.end() );

		val = atoi(digit.c_str());
	}

	return make_pair(valid, make_pair(path, val));

}

int main()
{
	Trie *pTemp = new Trie();




	vector<string> inputs;

	inputs.push_back( "a>b=2" );
	inputs.push_back( "a>c>e=3" );
	inputs.push_back("a>c>f=4");
	inputs.push_back( "b>a=5" );
	inputs.push_back("a>b>c=5" );
	inputs.push_back("b=7");
	inputs.push_back("a>b>c>d=99");
	inputs.push_back("a>b=9");
	inputs.push_back("a>b=99");
	inputs.push_back("a>b=1");

	for (int i = 0; i < inputs.size(); ++i)
	{
		pair<bool, pair<string, int> > temp = stringParse(inputs[i]);

		//cout << temp.second.first << " " << temp.second.second << endl;

		if (temp.first == false)
		{
			cout << "Invalid String : " << inputs[i] <<endl;
		}

		else
		{
			if ( pTemp->insert(temp.second.first, temp.second.second) )
			{

			}

			else
			{
				cout << "Invalid String : " << inputs[i] << endl;
			}
		}
	}

	pTemp->printJson();


	system("pause");
	return 0;
}

