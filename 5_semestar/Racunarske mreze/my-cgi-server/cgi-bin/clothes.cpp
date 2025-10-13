#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>

using namespace std;

void error(string str)
{
    cout << "<html><head><title>ERROR</title></head><body><h1>GRESKA: ";
    cout << str << "</h1></body></html>";
    exit(1);
}

void parse(string str)
{
    size_t tip_pos = str.find("tip=");
    if (tip_pos == string::npos)
        error("Niste uneli tip");

    size_t and_pos = str.find("&");
    if (and_pos == string::npos)
        error("Nepravilan query string 1");

    string tip_str = str.substr(tip_pos + 4, and_pos - (tip_pos + 4));

    tip_pos = str.find("tip=", tip_pos + 1);
    if (tip_pos != string::npos)
        error("Potrazili ste vise tipova odece. Nemamo ih na stanju!");

    size_t vel_pos = str.find("velicina=");
    if (vel_pos == string::npos)
        error("Niste uneli velicinu!");

    and_pos = str.find("&", and_pos + 1);
    if (and_pos == string::npos)
        error("Nepravilan query string 2");

    string vel_str = str.substr(vel_pos + 9, and_pos - (vel_pos + 9));

    size_t kol_pos = str.find("kolicina=");
    if (kol_pos == string::npos)
        error("Nema kolicine");

    string kol_str = str.substr(kol_pos + 9);
    int kol = stoi(kol_str);

    if (tip_str == "pantalone" && vel_str == "s" && kol == 2)
    {
        cout << "<html><head><title>OK</title></head><body><h1>USPEH! ";
        cout << "</h1></body></html>";
    }
    else
    {
        error("Nemam na stanju! else");
    }
}

int main(int argc, char *argvp[])
{
    string method = getenv("REQUEST_METHOD");
    string qstring = getenv("QUERY_STRING");
    int bytes = atoi(getenv("CONTENT_LENGTH"));
    string postInput;

    cout << "Content-Type: text/html\n\n";

    if (method == "GET")
    {
        if (!qstring.empty())
            parse(qstring);
        else
            error("Prazan query");
    }
    else if (method == "POST")
    {
        if (bytes > 0)
        {
            cin >> postInput;
            parse(postInput);
        }
        else
            error("Prazan post body");
    }
    else
    {
        error("Ni post ni put");
    }
}
