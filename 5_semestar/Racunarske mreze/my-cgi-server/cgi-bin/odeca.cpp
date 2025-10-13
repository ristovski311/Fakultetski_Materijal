#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void error(string str)
{
    cout << "<html><head><title>ERROR</title></head><body><h1>" << str;
    cout << "</h1></body></html>\n";
}

void parse(string str)
{
    size_t boja_pos_1 = str.find("boja=");

    if(boja_pos_1 == string::npos)
    {
        error("Error, niste uneli boju! " + str);
        return;
    } 

    size_t velicina_pos = str.find("vel=");

    if(velicina_pos == string::npos)
    {
        error("Error, niste uneli velicinu! " + str);
        return;
    } 

    size_t kolicina_pos = str.find("kolicina=");

    if(kolicina_pos == string::npos)
    {
        error("Error, niste uneli kolicinu! " + str);
        return;
    }

    size_t boja_pos_2 = str.find("boja=", boja_pos_1+1);

    if(boja_pos_2 != string::npos)
    {
        error("Error, nemamo trenutno na stanju! " + str);
        return;
    }

    size_t and_pos = str.find("&");

    string boja_val = str.substr(boja_pos_1 + 5, and_pos - (boja_pos_1 + 5));

    and_pos = str.find("&", and_pos+1);

    string vel_val = str.substr(velicina_pos + 4, and_pos - (velicina_pos + 4));

    string kol_val = str.substr(kolicina_pos + 9);
    int kol_val_int;
    try
    {
        kol_val_int = stoi(kol_val);
    }
    catch(const std::exception& e)
    {
        error("Error, invalid kolicina entered! " + str );
        return;
    }
    
    if(kol_val_int == 2 && boja_val == "bela")
    {
        cout << "<html><head><title>USPESNO</title></head><body><h1>" << "Uspesno ste porucili 2 bele majice velicine " << vel_val;
        cout << "</h1><hr/><h4>" << str;
		
		cout << "</h4></body></html>\n";
    }
    else
    {
        error("Nemamo trenutno na stanju 1! " + str);
    }


}

int main()
{
    string method = getenv("REQUEST_METHOD");
    string q_string = getenv("QUERY_STRING");
    int bytes = atoi(getenv("CONTENT_LENGTH"));
    string inputPost;

    cout << "Content-Type: text/html\n\n";

    if(method == "GET")
    {
        if(!q_string.empty())
        {
            parse(q_string);
        }
        else
            error("Error, query string is empty!");
    }
    else if(method == "POST")
    {
        if(bytes > 0)
        {
            cin >> inputPost;
            parse(inputPost);
        }
        else
        {
            error("Error, post method body is empty!");
        }
    }
    else
    {
        error("Error, invalid method!");
    }



    return 0;
}