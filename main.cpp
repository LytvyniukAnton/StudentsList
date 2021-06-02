#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

struct Student //структура студента
{
    string name;
    string surname;
    double avgMark;
    int attended;
    bool succeeded;
};

Student parseString(string line)  //метод принимает сроку, парсит ее и возрщ студента
{
    Student s;
    int i = 0;

    s.name = "";
    while(i < line.size() && line[i] != ',') //читаем строку до запятой
    {
        s.name += line[i++];  //копируем каждый символ
    }

    i++;

    s.surname = ""; //аналогично
    while(i < line.size() && line[i] != ',')
    {
        s.surname += line[i++];
    }

    i++;

    string buffer = "0";
    while(i < line.size() && line[i] != ',') //посимвольно копируем до ,
    {
        buffer += line[i++];
    }
    s.avgMark = stod(buffer); //переводим в дробь

    i++;

    buffer = "0"; //аналогично
    while(i < line.size() && line[i] != ',')
    {
        buffer += line[i++];
    }

    s.attended = stoi(buffer);  //переводим в целое

    s.succeeded = s.attended > 5 && s.avgMark > 4;  //если условие истенно - в succeeded запишится true

    return s;
}

void printList(Student* students, int size)  //функция вывода списка
{
    cout << "Succeeded Name                Surname             Avg mark Attended\n";
    for(int i=0;i<size;i++)
    {
        cout << "    " << (students[i].succeeded?"+":" ") << "     "
             << setw(20) << left << students[i].name
             << setw(20) << left << students[i].surname
             << setw(8) << right << setprecision(3) << students[i].avgMark
             << "   " << setw(2) << right << students[i].attended << endl;
         //setw - ширина поля
         //left, right - выравниваем по краю
         //setprecision(2) - два знака после запятой
    }
}

int main()
{
    Student students[100];  //массив студентов
    int size = 0; //кол студентов

    string fileName;

    cout << "File name > "; //вводим имя файла
    getline(cin, fileName);

    ifstream file(fileName);

    if(!file.is_open()) //если не открылся
    {
        cout << "Cant open the file!\n";
        return 1;
    }

    while(!file.eof()) //пока не конец файла
    {
        string line;
        getline(file, line); //считываем строку

        if(line != "") //если строка не пустая
            students[size++] = parseString(line);  //парсим и результат записываем в массив
    }

    printList(students, size);  //вывод списка

    return 0;
}
