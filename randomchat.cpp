#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
using namespace std;

const string    reset       = "\033[1;0m";
const string    red         = "\033[1;31m";
const string    green       = "\033[1;32m";
const string    yellow      = "\033[1;33m";
const string    blue        = "\033[1;34m";
const string    magenta     = "\033[1;35m";
const string    cyan        = "\033[1;36m";
const string    white       = "\033[1;37m";
const string    red_b       = "\033[1;41m";
const string    green_b     = "\033[1;42m";
const string    yellow_b    = "\033[1;43m";
const string    blue_b      = "\033[1;44m";
const string    magenta_b   = "\033[1;45m";
const string    cyan_b      = "\033[1;46m";
const string    white_b     = "\033[1;47m";
const string    inverse     = "\033[1;7m";

int name_cycle;
map<string,string> names;

string name_color(string& name)
{
    if (names.find(name) == names.end())
    {
        switch(names.size()%6)
        {
            case 0:
                names[name] = cyan;
                break;
            case 1:
                names[name] = magenta;
                break;
            case 2:
                names[name] = yellow;
                break;
            case 3:
                names[name] = blue;
                break;
            case 4:
                names[name] = green;
                break;
            case 5:
                names[name] = red;
                break;
        }
    }
    return names[name];
}

struct input {
    string full;
    string date;
    string hour;
    string name;
    string text;
    int time;
    int position;
};
struct archivador
{
    string name;
    int size;
    bool borrar;
};


int time_number(string time)
{
    int anyo = 0, mes = 0, dia = 0;
    int i = 0;
    while (time[i] != '/' and time[i] != '-' and time[i] != '.')
    {
        dia = dia * 10 + time[i] - '0';
        ++i;
    }
    ++i;
    while (time[i] != '/' and time[i] != '-' and time[i] != '.')
    {
        mes = mes * 10 + time[i] - '0';
        ++i;
    }
    ++i;
    while (i < time.size())
    {
        anyo = anyo * 10 + time[i] - '0';
        ++i;
    }
    if (anyo < 100) anyo += 2000;
    return dia + mes*30 + anyo*365;
}

int namePos(string& s)
{
    int i = 0;
    while (s[i] != '-') ++i;
    return i + 2;
}

void separar(input& line)
{
    int guion = 12;
    while (line.full[guion] != '-') ++guion;
    int hour_pos = guion - 5;
    while (line.full[hour_pos] != ' ') --hour_pos;
    int name_pos = guion + 2;
    while (line.full[name_pos] != ':') ++name_pos;

    line.hour = line.full.substr(hour_pos + 1, guion - hour_pos - 2);
    line.date = line.full.substr(0, hour_pos);
    line.name = line.full.substr(guion + 2, name_pos - guion - 2);    
    line.time = time_number(line.date);
    line.text = line.full.substr(name_pos + 2, line.full.size() - name_pos - 2);
}


int main()
{
    input line;
    int n_archivos, tamano_min;
    int context;
    cout << blue_b << "Cuántos archivos?" << reset << blue << " ";
    cin >> n_archivos;
    vector <archivador> archivo(n_archivos);
    cout << reset << blue_b << "Seleccionar archivos:" << reset << blue << " ";
    string nombre_archivo;
    for (int i = 0; i < n_archivos; ++i)
    {
        cin >> archivo[i].name;
        archivo[i].borrar = false;
        if (archivo[i].name[archivo[i].name.size() - 1] == '*')
        {
            archivo[i].borrar = true;
            archivo[i].name.pop_back();
            //cout << endl << green << "[DEBUG]: New file name = \"" << archivo[i].name << "\"" << reset << endl;
        }
        ifstream file("Chats/" + archivo[i].name);

        archivo[i].size = 0;
        while (getline(file,line.full)) ++archivo[i].size;
        if (archivo[i].size <= 0) {cout << reset << red_b <<"[ERROR]: Archivo " << reset << red << archivo[i].name << reset << red_b << " vacío o no encontrado en la carpeta Chats." << reset << endl; return -1;}
        if (i == 0) tamano_min = archivo[i].size;
        if (archivo[i].size < tamano_min) tamano_min = archivo[i].size;
    }
    cout << reset;
    
    //cout << blue_b << "Seleccionar contexto (1 - " << tamano_min << "):" << reset << blue << " ";
    cout << blue_b << "Cuántos mensajes?" << reset << blue << " ";

    while (cin >> context)
    {
        cout << reset;
        if (context < 1 or context > tamano_min) cout << red_b << "[ERROR]: Contexto fuera de rango [1 - " << tamano_min << "]." << reset << endl;
        else
        {
            system("clear");
            //++context;
            srand(time(NULL));
            archivador temp = archivo[rand() % n_archivos]; //Seleccionar un archivo aleatorio entre los seleccionados
            ifstream file2(temp.name);
            int rango = temp.size - context;
            int random;
            if (rango == 0) random = context;
            else random = (rand() % rango) + context;
            string first_date_s;
            int first_date_i;
            for (int i = 0; i < random; ++i) 
            {
                getline(file2,line.full);
                separar(line);
                if (i >= random - context)
                {
                    if (i == random - context) {first_date_s = line.date; first_date_i = line.time; }
                    //Imprimir mensajes
                    cout << line.hour << " " << name_color(line.name) << line.name << reset << ": " << line.text << endl;;
                }
            }
            cout << blue_b << "Date?" << reset << " " << blue;
            string answer;
            cin >> answer;
            cout << reset;
            int answer_time = time_number(answer);
            if (answer_time == first_date_i) cout << green_b << "CORRECTO! La fecha es " << reset << green << first_date_s << reset << green_b << "!" << reset << endl;
            else
            {
                cout << red_b << "INCORRECTO! La fecha correcta era " << reset << red << first_date_s << reset << red_b << "!" << endl;
                int diferencia = first_date_i - answer_time;
                if (diferencia < 0) diferencia *= -1;
                cout << "Diferencia de " << reset << red;
                if (diferencia / 365 > 0)
                {
                    if (diferencia/365 == 1) cout << diferencia/365 << " año ";
                    else cout << diferencia/365 << " años ";
                    diferencia %= 365;
                }
                if (diferencia / 30 > 0)
                {
                    if (diferencia/30 == 1) cout << diferencia/30 << " mes ";
                    else cout << diferencia/30 << " meses ";
                    diferencia %= 30;
                }
                if (diferencia > 0)
                {
                    if (diferencia == 1) cout << diferencia << " dia";
                    else cout << diferencia << " dias";
                }
                cout << reset << endl;
                if (n_archivos > 1) cout << blue_b << "Fuente:" << reset << blue << " " << temp.name << endl << reset;
            }
            //cout << endl << blue_b << "Seleccionar contexto (1 - " << tamano_min << "):" << reset << blue << " ";
            cout << endl << blue_b << "Cuántos mensajes?" << reset << blue << " ";
        }
    }
    cout << reset << endl;
    for (int i = 0; i < n_archivos; ++i)
    {
        if (archivo[i].borrar)
        {
            if (remove(archivo[i].name.c_str()) == 0)
            {
                cout << red_b << "File " << reset << red << archivo[i].name << reset << red_b << " deleted successfully." << reset << endl;
            }
            else
            {
                cout << red_b << "Error deleting " << reset << red << archivo[i].name << reset << red_b << "!" << reset << endl;
            }
        }
    }
}
