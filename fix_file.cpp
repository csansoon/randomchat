#include <iostream>
using namespace std;

bool is_valid(string& line)
{
    int i = 0;
    while (i < 6)
    {
        if (line[i] != '/')
        {
            if (line[i] < '0' or line[i] > '9')
                return false;
        }
        ++i;
    }
    return true;
}


int main()
{
    string line, line_aux;
    getline(cin,line);
    while (getline(cin,line_aux))
    {
        if (is_valid(line_aux)) //l_aux IS VALID
        {
            cout << line << endl;
            line = line_aux;
        }
        else
        {
            line = line + "\n" + line_aux;
        }
    }
    cout << line;
}
