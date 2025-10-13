#include <string>
#include <string.h>
#include <iostream>
#include <cstdlib>

#define WIDTH 100
#define HEIGHT 100

using namespace std;

void error(string str)
{
    cout << "<html><head><title>Greska</title></head><body><h1>";
    cout << str << "</h1><hr/><img src=\"../images/tuffluck.jpg\" alt=\"GRESKA ALO\"></body></html>";
    exit(1);
}

void parse(string str)
{
    size_t xpos = str.find("x=");
    size_t ypos = str.find("y=");
    size_t andpos = str.find("&");

    if(xpos == string::npos || ypos == string::npos || andpos == string::npos)
        error("Greska positions");

    string xstr = str.substr(xpos+2, andpos - (xpos+2));
    string ystr = str.substr(ypos+2, (ypos+2));

    int xval = stoi(xstr);
    int yval = stoi(ystr);

    string borw;

    if //bruh
    (
        (
            (xval < WIDTH/3) && (yval < HEIGHT/3)
        ) || 
        ( //ok znam da se pise heigth 
            (xval > (2* (WIDTH/3))) && ((yval > (HEIGHT/3)) && (yval < (2* (HEIGHT / 3))))
        )
    )
    {
        borw = "BLACK";
    }
    else
        borw = "WHITE";

    cout << "<html><head><title>OK</title></head><body><h1>VAS ZIVOT JE: ";
    cout << borw << "</h1><hr/></body></html>";

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
            error("Prazan query!");
    }
    else if(method == "POST")
    {
        cin >> postInput;
        if(bytes > 0)
            parse(postInput);
        else
            error("Prazan post body");
    }
    else
    {
        error("ni post ni put");
    }
}