#include<bits/stdc++.h>

using namespace std;

bool checkStart(string regex, int &i , string pattern, int &j)
{
	i++;

	while (i < regex.size() && isalpha(regex[i]) )
	{
		if ( j >= pattern.size() )
			return false;

		if( regex[i] != pattern[j] )
			return false;
		
		i++;
		j++;
	}

	return true;
}


bool checkStar(char c, string pattern, int &j)
{
	if(pattern[j] != c)
	
	while (j < pattern.size() && pattern[j] == c)
		j++;

	return true;

}

bool checkDot(string regex, int &i, string pattern, int &j)
{
	i++;
	j++;

	while (i < regex.size() && j < pattern.size() && isalpha(regex[i]) )
	{
		if ( regex[i] != pattern[j] )
			return false;

		i++;
		j++;
	}
	return true;
}

bool checkDollar(string regex, int i, string pattern, int j)
{
	i--;

	while (i >= 0 && !isalpha(regex[i]))
	{
		if (j < 0)
			return false;

		if (regex[i] != pattern[j])
			return false;

		i--;
		j--;
	}

	return true;
}

bool isMatch(string regex, string pattern)
{
	int i = 0; 
	int j = 0;

	if (regex[i] == '^')
	{
		if ( !checkStart(regex, i, pattern, j) )
			return false;
	}


	while ( i < regex.size() )
	{
		if (j >= pattern.size() && regex[i] != '$')
			return false;

		if (regex[i] == '*')
		{
			if (!checkStar(regex[i - 1], pattern, j))
				return false;

			i++;
		}

		else if (regex[i] == '.')
		{
			if ( !checkDot(regex, i, pattern, j) )
				return false;

		}

		else if (regex[i] == '$')
		{
			if (!checkDollar(regex, i, pattern, j))
				return false;
		}

		else if (pattern[j] != regex[i])
			return false;


		i++;
		j++;
	}

	return true;

}



int main()
{

	string regex;
	string pattern;

	cin >> regex >> pattern;

	cout << (bool)isMatch(regex, pattern)<<endl<<endl;

	system("pause");

	return 0;
}