#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    string line;
    string fechaa, fecham, fechad;
    string hora;
    string name;
    string message;
    bool multimedia;
    while (getline(cin,line))
    {
        int offm = 0;
        int offd = 0;
        fechaa = line.substr(3,2);
        if (line[6] == '0') ++offm;
        fecham = line.substr(6 + offm, 2 - offm);
        if (line[9] == '0') ++offd;
        fechad = line.substr(9 + offd, 2 - offd);

        if (line[14] == '0')  hora = line.substr(15, 4);
        else                        hora = line.substr(14, 5);

        int i = 25;
        name = "";
        while (line[i] != '"')
        {
            name += line[i];
            ++i;
        }

        int j = line.size() - 2;
        if (line[j] == '"') multimedia = false;
        else
        {
            multimedia = true;
            while (line[j] != '"') --j;
        }
        
        //if (multimedia) message = "<Multimedia omitido>";
        //else
        //{
            j = j-2;
            i = i + 3;
            message = line.substr(i, j-i);
        //}
        if (not multimedia)
        cout << fechad << "/" << fecham << "/" << fechaa << " " << hora << " - " << name << ": " << message << endl;
    }
}