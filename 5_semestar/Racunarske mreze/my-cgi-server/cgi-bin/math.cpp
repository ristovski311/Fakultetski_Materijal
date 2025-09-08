#include <iostream>
#include <cmath>
#include <string>
#include <string.h>
#include <cstdlib>

using namespace std;

void error(string err)
{
    cout << "<html><head><title>ERROR";
    cout << "</title></head><body>";
    cout << "<p>" << err;
    cout << "</p></body></html>\n";
    return;
}

void parse(string qstr)
{
    ///q string treba da izlega: prvi=1&drugi=2

    size_t pos_prvi = qstr.find("prvi=");
    size_t pos_and = qstr.find("&");
    size_t pos_drugi = qstr.find("drugi=");

    if(pos_prvi == string::npos)
        error("Error, prvi not found!");
    if(pos_drugi == string::npos)
        error("Error, drugi not found!");

    string prvi_val = qstr.substr(pos_prvi + 5, pos_and -  (pos_prvi + 5));
    string drugi_val = qstr.substr(pos_drugi + 6);

    int prvi_val_int;
    int drugi_val_int;

    try
    {
        prvi_val_int = stoi(prvi_val);
    }
    catch(const std::exception& e)
    {
        string errmsg(e.what());
        error("Error: " + errmsg);
        return;
    }   
    
    try
    {
        drugi_val_int = stoi(drugi_val);
    }
    catch(const std::exception& e)
    {
        string errmsg(e.what());
        error("Error: " + errmsg);
        return;
    }

    int res = prvi_val_int + drugi_val_int;

    cout << "<html><head><title>RESULT";
    cout << "</title></head><body>";
    cout << "<p>The sum of numbers is " << res;
    cout << "</p></body></html>\n";
    
}


int main()
{
    string q_string = getenv("QUERY_STRING");
    string method = getenv("REQUEST_METHOD");
    int bytes = atoi(getenv("CONTENT_LENGTH"));
    string inputPostString;
    
    cout << "Content-Type: text/html\n\n";

    if(method == "GET")
    {
        if(!q_string.empty())
        {
            parse(q_string);
        }
        else
        {
            error("Error, no query parameters!");

        }
    }
    else if(method == "POST")
    {
        cin >> inputPostString;

        if(bytes > 0)
        {
            parse(inputPostString);
        }
        else
        {
            error("Error, empty post body!");

        }
    }
    else
    {
        error("Error, wrong method!");

    }

    return 0;

}