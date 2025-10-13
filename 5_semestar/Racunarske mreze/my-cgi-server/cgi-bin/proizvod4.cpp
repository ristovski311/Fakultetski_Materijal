#include <iostream>
#include <string.h>
#include <string>
#include <cstdlib>

using namespace std;

void error(string str)
{
	cout << "<html><head><title>error</title><body><h1>" << str;
	cout << "</h1></body></html>";
	exit(1);
}

void parse(string str)
{
	size_t broj1 = str.find("broj1=");
	size_t ampersand = str.find("&");
	
	int nums[4];
	
	if(broj1 == string::npos)
		error("Nema broj 1");
	else
	{
		string num = str.substr(broj1 + 6, ampersand - (broj1 + 6)); 
		nums[0] = stoi(num);
	}

	size_t broj2 = str.find("broj2=");
	ampersand = str.find("&", ampersand+1);
	
	if(broj1 == string::npos)
		error("Nema broj 2");
	else
	{
		string num = str.substr(broj2 + 6, ampersand - (broj2 + 6)); 
		nums[1] = stoi(num);
	}
	
	
	size_t broj3 = str.find("broj3=");
	ampersand = str.find("&", ampersand+1);

	
	if(broj1 == string::npos)
		error("Nema broj 3");
	else
	{
		string num = str.substr(broj3 + 6, ampersand - (broj3 + 6)); 
		nums[2] = stoi(num);
	}
	
	size_t broj4 = str.find("broj4=");
	ampersand = str.find("&", ampersand+1);
	
	if(broj1 == string::npos)
		error("Nema broj 4");
	else
	{
		string num = str.substr(broj4 + 6, ampersand - (broj4 + 6)); 
		nums[3] = stoi(num);
	}
	
	int res = 1;
	for(int i = 0; i < 4; i++)
		res *= nums[i];
	
	cout << "<html><head><title>Uspeh</title><body><h1>Proizvod: " << res;
	cout << "</h1></body></html>";
}

int main(int argc, char* argv[])
{
	string method = getenv("REQUEST_METHOD");
	string q_string = getenv("QUERY_STRING");
	int bytes = atoi(getenv("CONTENT_LENGTH"));
	string postInput;
	
	cout << "Content-Type: text/html\n\n";
	
	if(method == "GET")
	{
		if(!q_string.empty())
			parse(q_string);
		else
			error("Greska prazan query string");
	}
	else if(method == "POST")
	{
		cin >> postInput;
		if(bytes > 0)
			parse(postInput);
		else
			error("Greska prazan post body");
	}
	else
	{
		error("Greska metode");
	}
}