#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <cstring>
#include <math.h>

#define HEIGHT 100
#define WIDTH 100

using namespace std;

int parseImage(string qstring)
{
    size_t pos_x = qstring.find("x=");
    size_t pos_and = qstring.find("&");
    size_t pos_y = qstring.find("y=");

    string x_val = qstring.substr(pos_x + 2, pos_and - (pos_x + 2));
    string y_val = qstring.substr(pos_y + 2);

    int x_val_int = stoi(x_val);
    int y_val_int = stoi(y_val);

    ///image1 left right

    // if(x_val_int < HEIGHT/2)
    //     return 0;
    // else
    //     return 1;

    ///image2 diagonal
    
    // if(x_val_int < y_val_int)
    //     return 1;
    // else
    //     return 0;

    ///image3 checkerboard

    // if(((x_val_int > third) && (x_val_int < 2*third) && ((y_val_int < third)||(y_val_int > 2*third))) || (((y_val_int > third) && (y_val_int < 2*third)) && ((x_val_int < third) || (x_val_int > 2*third))))
    //     return 0;
    // else
    //     return 1;


    ///image4 darts

    double vectorLen = sqrt( pow( abs(x_val_int - WIDTH/2) ,2) + pow( abs(y_val_int - HEIGHT/2) ,2) );

    //r1 = 20, r2 = 40, r3 = 50 fixed

    if((vectorLen > 20 && vectorLen < 40))
        return 5;
    else if(vectorLen < 20)
        return 10;
    else if(vectorLen > 40 && vectorLen < 50)
        return 1;
    else 
        return 0;

}

int main() {

    string req_method = getenv("REQUEST_METHOD");
    string q_string = getenv("QUERY_STRING");
    int bytes = atoi(getenv("CONTENT_LENGTH"));
    string postInputString;

    if(req_method == "GET")
    {
        cout << "Content-Type: text/html\n\n";
        cout << "<html>";
        cout << "<head><title>";
        cout << "GET</title></head>";
        cout << "<body>";
        cout << "<h1>";

        int res = -1;

        if(!q_string.empty())
        {
            res = parseImage(q_string);
        }

        // if(res)
        //     cout << "You just clicked on the black part!";
        // else
        //     cout << "You just clicked on the white part!";
        cout << "You gained " << res << " points!";

        cout << "</h1>";
        cout << "</body>";
        cout << "</html>";
    }
    else if(req_method == "POST")
    {
        cout << "Content-Type: text/html\n\n";
        cout << "<html>";
        cout << "<head><title>";
        cout << "POST</title></head>";
        cout << "<body>";
        cout << "<h1>";

        int res = -1;

        if(bytes>0)
        {
            cin >> postInputString;
            res = parseImage(postInputString);
        }

        // if(res)
        //     cout << "You just clicked on the black part!";
        // else
        //     cout << "You just clicked on the white part!";
        cout << "You gained " << res << " points!";

        cout << "</h1>";
        cout << "</body>";
        cout << "</html>";
    }
    else
    {
        cout << "Content-Type: text/html\n\n";
        cout << "<html>";
        cout << "<head><title>";
        cout << "ERR</title></head>";
        cout << "<body>";
        cout << "<h1>ERR</h1>";
        cout << "</body>";
        cout << "</html>";
    }
    return 0;
}
