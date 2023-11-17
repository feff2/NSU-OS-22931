#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

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

int main() {
    FILE* file_in = fopen("file.txt", "r");
    vector<TableCell> table;
    int offset_counter = 0;
    while (!feof(file_in)){
        char lineBuffer[1001];
        fgets(lineBuffer, 1000, file_in);
        int str_length = strlen(lineBuffer);
        if (lineBuffer[str_length - 1] == '\n'){
            str_length--;
        }
        cout << lineBuffer << " " << str_length << endl;
        TableCell cell = TableCell(offset_counter, str_length);
        offset_counter += str_length + 2;
        table.push_back(cell);
    }

    for (auto i:table) {
        cout << i.offset << " " << i.length << endl;
    }

    cout << table.size();
    int input_console;
    cin >> input_console;

    while (input_console != 0){
        if (input_console < 1 || table.size() < input_console){
            fprintf(stderr, "Requested index out of range\n");
        } else {
            TableCell query = table[input_console - 1];
            char lineBuffer[1001] = {0};
            if (fseek(file_in, query.offset, SEEK_SET) == -1L){
                fprintf(stderr, "Seek Error\n");
            } else {
                int result = fread(lineBuffer, 1, query.length, file_in);
                if (result != query.length){
                    fprintf(stderr, "Ошибка чтения\n");
                }else{
                    cout << lineBuffer << endl;
                }
            }
        }
        cin >> input_console;
    }
    return 0;
}
