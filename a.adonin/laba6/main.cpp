#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>   //Для alarm
#include <signal.h>   //Для signal

using namespace std;

//Функция, вызываемая при генерации сигнала SIGALRM
// function, calling when generating a signal SIGALRM
void MyAlarm (int var){
    cout << "End work";
    _Exit(0); //Завершение работы программы
}


class TableCell{
    public:
        int offset;
        int length;
        TableCell(int of, int len) {
            this->offset = of;
            this->length = len;

        }
        TableCell() {
            this->offset = 0;
            this->length = 0;
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
        offset = file_in.tellg();
        getline(file_in, lineBuffer);
        rtrim(lineBuffer);
        int str_length = lineBuffer.size();
//        cout << lineBuffer << " " << str_length << endl;
        TableCell cell = TableCell(offset, str_length);
        table.push_back(cell);
    }

//    for (auto i:table) {
//        cout << i.offset << " " << i.length << endl;
//    }
//    cout << table.size();
    alarm(5);
    int input_console;
    cin >> input_console;
    file_in.clear();
    while (input_console != 0){
        if (input_console < 1 || table.size() < input_console){
            fprintf(stderr, "Requested index out of range\n");
        } else {
            TableCell query = table[input_console - 1];
            char lineBuffer[1001] = {0};
            file_in.seekg(query.offset, std::ifstream::beg);
            if (file_in.eof()){
                fprintf(stderr, "Seek Error\n");
            } else {
                file_in.read(lineBuffer, query.length);
                if (file_in.fail()){
                    fprintf(stderr, "Ошибка чтения\n");
                }else{
                    cout << lineBuffer << endl;
                }
            }
        }
        alarm(5);
        cin >> input_console;
    }
    return 0;
}
