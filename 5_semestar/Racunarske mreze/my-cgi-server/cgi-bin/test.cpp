#include <iostream>
#include <cstdlib>
#include <string.h>
#include <string>

using namespace std;

void exer(string str)
{
    cout << "<html><head><title>ERROR</title></head><body><h1>GRESKA: ";
    cout << str << "</h1></body></html>";
    exit(1);
}

void parse(string str)
{
    size_t imepos = str.find("ime=");
    size_t godinepos = str.find("godine=");
    size_t bojapos = str.find("boja=");
    size_t godpos = str.find("godina=");

    if (imepos == string::npos ||
        godinepos == string::npos ||
        bojapos == string::npos ||
        godpos == string::npos)
        exer("Greska, nema svih potrebnih argumenata!");

    size_t andpos = str.find("&");
    if (andpos == string::npos)
        exer("Nepravilan q string1");

    string ime = str.substr(imepos + 4, andpos - (imepos + 4));

    andpos = str.find("&", andpos + 1);
    if (andpos == string::npos)
        exer("Nepravilan q string2");

    int godine = stoi(str.substr(godinepos + 7, andpos - (godinepos + 7)));

    andpos = str.find("&", andpos + 1);
    if (andpos == string::npos)
        exer("Nepravilan q string3");

    string boja = str.substr(bojapos + 5, andpos - (bojapos + 5));

    string boja2 = "";
    bojapos = str.find("boja=", bojapos + 1);
    if (bojapos != string::npos)
    {
        andpos = str.find("&", andpos + 1);
        if (andpos == string::npos)
            exer("Nepravilan q string4");

        boja2 = str.substr(bojapos + 5, andpos - (bojapos + 5));
    }

    string boja3 = "";
    if (bojapos != string::npos)
    {
        bojapos = str.find("boja=", bojapos + 1);
        if (bojapos != string::npos)
        {
            andpos = str.find("&", andpos + 1);
            if (andpos == string::npos)
                exer("Nepravilan q string5");

            boja3 = str.substr(bojapos + 5, andpos - (bojapos + 5));
        }
    }

    int godina = stoi(str.substr(godpos + 7));

    cout << "<html><head><title>USPEH</title></head><body>";
    cout << "<h4>IME: " << ime << "</h4>";
    cout << "<h4>GODINE: " << godine << "</h4>";
    cout << "<h4>BOJA: " << boja << "</h4>";
    if (!boja2.empty())
        cout << "<h4>BOJA 2: " << boja2 << "</h4>";
    if (!boja3.empty())
        cout << "<h4>BOJA 3: " << boja3 << "</h4>";
    cout << "<h4>GODINA: " << godina << "</h4></body></html>";
}

int main(int argc, char *argv[])
{
    string method = getenv("REQUEST_METHOD");
    string qstring = getenv("QUERY_STRING");
    int bytes = atoi(getenv("CONTENT_LENGTH"));
    string postInput;

    cout << "Content-Type: text/html\n\n";

    if (method == "GET")
    {
        if (!qstring.empty())
        {
            parse(qstring);
        }
        else
            exer("q string prazan");
    }
    else if (method == "POST")
    {
        if (bytes > 0)
        {
            cin >> postInput;
            parse(postInput);
        }
        else
            exer("Prazan post body");
    }
    else
    {
        exer("Greska nije ni post ni get");
    }
}