#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <signal.h>

using namespace std;

//Функция, вызываемая при генерации сигнала SIGALRM
// function, calling when generating a signal SIGALRM
void MyAlarm (int var){
    cout << "End work";
    _Exit(0); //Р—Р°РІРµСЂС€РµРЅРёРµ СЂР°Р±РѕС‚С‹ РїСЂРѕРіСЂР°РјРјС‹
}


class TableCell{
    public:
        string line;
        TableCell(string line) {
            this->line = std::move(line);
        }
        TableCell() {
            this->line = "";
        }
};

static void rtrim(string &s) {
    s.erase(s.find_last_not_of(" \n\r\t")+1);
}

int main() {
    signal (SIGALRM, MyAlarm);
    ifstream file_in;
    file_in.open("file.txt");
    vector<TableCell> table;
    int offset;
    while (!file_in.eof()){
        string lineBuffer;
        getline(file_in, lineBuffer);
        rtrim(lineBuffer);
        TableCell cell = TableCell(lineBuffer);
        table.push_back(cell);
    }
    alarm(5);
    int input_console;
    cin >> input_console;
    file_in.clear();
    while (input_console != 0){
        if (input_console < 1 || table.size() < input_console){
            fprintf(stderr, "Requested index out of range\n");
        } else {
            TableCell query = table[input_console - 1];
            cout << query.line << endl;
        }
        alarm(5);
        cin >> input_console;
    }
    return 0;
}
