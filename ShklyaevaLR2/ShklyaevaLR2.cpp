#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;


struct Pipe {
    string name;
    int length;
    int diametr;
    bool repair;
};

struct CompressStation {
    string name;
    int workshop;
    int realworkshop;
    double effect;
};

map<string, CompressStation> stations;
int Menu();
void Mistake();
void CreatePipe(map<string, Pipe>& pipes);
void CreateCompress();
int ViewPipe(map<string, Pipe> pipes,string answer);
void ViewComp();
int MenuPipes();
void Repair(bool filt, map<string, Pipe>& pipes);
void Search(map<string, Pipe> pipes);
int EditMenu();
void EditPipe(Pipe& P);
void EditCompress(CompressStation& C);
void SaveFile(Pipe& P, CompressStation& C);
void ReadFile(Pipe& P, CompressStation& C);

int main()
{
    map<string, Pipe> pipes;
    bool cycle = 1;
    while (cycle) {
        int choice;
        choice = Menu();//
        switch (choice) {
        case 1:
            CreatePipe(pipes);
            break;
        case 2:
            CreateCompress();
            break;
        case 3:
            ViewPipe(pipes,"any");
            break;
        case 4:
            ViewComp();
            break;
        case 5:
            bool filt;
            choice = MenuPipes();
            switch (choice) {
            case 1:
                filt = 1;
                Repair(filt, pipes);
                break;
            case 2:
                filt = 0;
                Repair(filt, pipes);
                break;
            case 3:
                Search(pipes);
                break;
            //case 0:
            //    break;
            }
            break;
        //case 6:
        //    SaveFile(P, C);
        //    break;
        case 0:
            cycle = 0;
            break;
        }
    }
};

int Menu() { // создаем меню для выбора действий
    int choice;
    cout << "\n...........Choose.an.option...........\n";
    cout << ".  1.Create a pipe                   .\n";
    cout << ".  2.Create a compressor station     .\n";
    cout << ".  3.View my pipes                   .\n";
    cout << ".  4.View my compressor stations     .\n";
    cout << ".  5.Search pipes                    .\n";
    cout << ".  6.Search compressor stations      .\n";
    //cout << ".  7.Save the information to a file  .\n";
    //cout << ".  8.Read the information from a file.\n";
    cout << ".  0.Exit                            .\n";
    cout << "......................................\n";
    while (1) {
        cin >> choice; // Считываем число
        // Проверяем, правильно ли введено число
        if (choice >= 0 && choice <= 6 && cin.good() && cin.peek() == '\n') {
            // Если всё в порядке, выходим из цикла
            break;
        }
        else {
            Mistake();//выводим сообщение об ошибке
        }
    }
    return choice;
};

void Mistake() {
    cout << "Incorrect input(((\nPlease try again:\n";
    cin.clear(); // Сбрасываем флаг ошибки
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем неправильный ввод
};

void CreatePipe(map<string, Pipe>& pipes) {
    Pipe P;
    cout << "\nCreation of a pipe.\n";
    cout << "Name the pipe:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (1) {
        getline(cin, P.name); // Считываем имя
        // Проверяем, было ли введено имя
        if (cin.good() && !(pipes.count(P.name))) {
            // Если всё в порядке, выходим из цикла 
            break;
        }
        else {
            cout << "You already have that pipe.\nTry another name:\n";//выводим сообщение об ошибке
            cin.clear(); // Сбрасываем флаг ошибки
            continue;
        }
    }
    cout << "Specify the lenght:\n";
    while (1) {
        cin >> P.length; // Считываем число
        // Проверяем, правильно ли введено число
        if (P.length > 0 && cin.good() && cin.peek() == '\n') {
            // Если всё в порядке, выходим из цикла
            break;
        }
        else {
            Mistake();//выводим сообщение об ошибке
        }
    }
    cout << "Specify the diametr:\n";
    while (1) {
        cin >> P.diametr; // Считываем число
        // Проверяем, правильно ли введено число
        if (P.diametr > 0 && cin.good() && cin.peek() == '\n') {
            // Если всё в порядке, выходим из цикла
            break;
        }
        else {
            Mistake();//выводим сообщение об ошибке
        }
    }
    cout << "Is it under repair?(y/n)\n";
    string answer;
    while (1) {
        cin >> answer; // Считываем ответ
        // Проверяем, правильно ли введен ответ
        if ((answer == "y" || answer == "n") && cin.good() && cin.peek() == '\n') {
            // Если всё в порядке, выходим из цикла
            break;
        }
        else {
            Mistake();//выводим сообщение об ошибке
        }
    }
    if (answer == "y") {
        P.repair = true;
    }
    else if (answer == "n") {
        P.repair = false;
    }
    pipes[P.name] = P;
}

void CreateCompress() {
    CompressStation C;
    cout << "\nCreation of a compressor station.\n";
    cout << "Name the compressor station:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (1) {
        getline(cin, C.name); // Считываем имя
        // Проверяем, было ли введено имя
        if (cin.good() &&!(stations.count(C.name))) {
            // Если всё в порядке, выходим из цикла
            break;
        }
        else {
            cout << "You already have that pipe.\nTry another name:\n";//выводим сообщение об ошибке
            cin.clear(); // Сбрасываем флаг ошибки
        }
    }
    cout << "Specify the amount of workshops:\n";
    while (1) {
        cin >> C.workshop; // Считываем число
        // Проверяем, правильно ли введено число
        if (C.workshop > 0 && cin.good() && cin.peek() == '\n') {
            // Если всё в порядке, выходим из цикла
            break;
        }
        else {
            Mistake();//выводим сообщение об ошибке
        }
    }
    cout << "Specify the amount of working workshops:\n";
    while (1) {
        cin >> C.realworkshop; // Считываем число
        // Проверяем, правильно ли введено число
        if (C.realworkshop >= 0 && C.realworkshop <= C.workshop && cin.good() && cin.peek() == '\n') {
            // Если всё в порядке, выходим из цикла
            break;
        }
        else {
            Mistake();//выводим сообщение об ошибке
        }
    }
    cout << "Specify the effectiveness:\n";
    while (1) {
        cin >> C.effect; // Считываем число
        // Проверяем, правильно ли введено число
        if (cin.good() && cin.peek() == '\n') {
            // Если всё в порядке, выходим из цикла
            break;
        }
        else {
            Mistake();//выводим сообщение об ошибке
        }
    }
    stations[C.name] = C;
}

int ViewPipe(map<string, Pipe> pipes, string answer) {
    if (pipes.size() != 0) {
        cout << "\nPipes\n";
        for (const auto& pair : pipes) {
            cout << "\nName: " << pair.second.name;
            cout << "\nLength: " << pair.second.length;
            cout << "\nDiametr: " << pair.second.diametr;
            if (pair.second.repair) {
                cout << "\nUnder repair" << "\n";
            }
            else {
                cout << "\nNot under repair" << "\n";
            }
        }
        return 1;
    }
    else {
        cout << "\nYou don't have" << answer << "pipes yet\n";
        return 0;
    }
}

void ViewComp() {
    if (stations.size() != 0) {
        cout << "\nCompressor Stations\n";
        for (const auto& pair : stations) {
            cout << "\nName: " << pair.second.name;
            cout << "\nAmount of workshops: " << pair.second.workshop;
            cout << "\nAmount of working workshops: " << pair.second.realworkshop;
            cout << "\nEffectiveness: " << pair.second.effect << "\n";
        }
    }
    else {
        cout << "\nYou don't have any stations yet\n";
    }
}

int MenuPipes() {
    int choice;
    cout << "\n...........Choose.an.option...........\n";
    cout << ".  1.Search pipes under repair       .\n";
    cout << ".  2.Search pipes not under repair   .\n";
    cout << ".  3.Search by name                  .\n";
    cout << ".  0.Exit                            .\n";
    cout << "......................................\n";
    while (1) {
        cin >> choice; // Считываем число
        // Проверяем, правильно ли введено число
        if (choice >= 0 && choice <= 3 && cin.good() && cin.peek() == '\n') {
            // Если всё в порядке, выходим из цикла
            break;
        }
        else {
            Mistake();//выводим сообщение об ошибке
        }
    }
    return choice;
}

void Repair(bool filt, map<string, Pipe>& pipes) {
    map<string, Pipe> repair;
    if (filt) {
        for (const auto& pair : pipes) {
            if (pair.second.repair) {
                repair[pair.first] = pair.second;
            }
        }
    }
    else {
        for (const auto& pair : pipes) {
            if (!pair.second.repair) {
                repair[pair.first] = pair.second;
            }
        }
    }
    int exist=ViewPipe(repair,"such");
    if (exist) {
        int choice;
        Pipe P;
        choice = EditMenu();
        switch (choice) {
        case 1:
            for (const auto& pair : repair) {
                P = pair.second;
                pipes.erase(pair.first);
                EditPipe(P);
                pipes[P.name] = P;
            }
            break;
        case 2:
            for (const auto& pair : repair) {
                P = pair.second;
                pipes.erase(pair.first);
            }
            break;
        }
    }
}

void Search(map<string, Pipe> pipes) {
    string name;
    cout << "Name the pipe you want to find:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name); // Считываем имя
    if (pipes.count(name)) {
        cout << "\nName: " << pipes[name].name;
        cout << "\nLength: " << pipes[name].length;
        cout << "\nDiametr: " << pipes[name].diametr;
        if (pipes[name].repair) {
            cout << "\nUnder repair" << "\n";
        }
        else {
            cout << "\nNot under repair" << "\n";
        }
    }
    else {
        cout << "You don't have that pipe\n";
    }
}

int EditMenu() {
    int choice;
    cout << "\n...........Choose.an.option...........\n";
    cout << ".  1.Edit                            .\n";
    cout << ".  2.Delete                          .\n";
    cout << ".  0.Exit                            .\n";
    cout << "......................................\n";
    while (1) {
        cin >> choice; // Считываем число
        // Проверяем, правильно ли введено число
        if (choice >= 0 && choice <= 2 && cin.good() && cin.peek() == '\n') {
            // Если всё в порядке, выходим из цикла
            break;
        }
        else {
            Mistake();//выводим сообщение об ошибке
        }
    }
    return choice;
}

void EditPipe(Pipe& P) {
    if (P.repair == 1) {
        P.repair = 0;
    }
    else {
        P.repair = 1;
    }
}

void EditCompress(CompressStation& C) {
    if (C.workshop > 0) {
        cout << "Specify the amount of working workshops again:\n";
        while (1) {
            cin >> C.realworkshop; // Считываем число
            // Проверяем, правильно ли введено число
            if (C.realworkshop >= 0 && C.realworkshop <= C.workshop && cin.good() && cin.peek() == '\n') {
                // Если всё в порядке, выходим из цикла
                break;
            }
            else {
                Mistake();//выводим сообщение об ошибке
            }
        }
    }
    else {
        cout << "You don't have a compressor station to edit";
    }
}

void SaveFile(Pipe& P, CompressStation& C) {
    if (P.length > 0) {
        // Создаем объект ofstream для записи в файл
        ofstream outFile("pipe.txt");
        // Запись данных в файл
        outFile << endl << P.name << endl << P.length << endl << P.diametr << endl << P.repair; // Записываем строку в файл
        // Закрываем файл
        outFile.close();
    }
    if (C.workshop > 0) {
        // Создаем объект ofstream для записи в файл
        ofstream outFile("compress.txt");
        // Запись данных в файл
        outFile << endl << C.name << endl << C.workshop << endl << C.realworkshop << endl << C.effect; // Записываем строку в файл
        // Закрываем файл
        outFile.close();
    }
}

void ReadFile(Pipe& P, CompressStation& C) {
    ifstream inFile("pipe.txt");
    // Проверяем, удалось ли открыть файл
    if (inFile) {
        string line;
        // Чтение строк из файла
        int lineNumber = 0; // Счетчик строк
        string fromfile; //
        while (getline(inFile, line)) {
            lineNumber++;
            // Проверяем, является ли это строка с возрастом
            switch(lineNumber){
            case 1:// Если это первая строка
                // Извлекаем значение имени
                inFile >> P.name;
                break;
            case 2:
                // Извлекаем значение имени
                inFile >> fromfile;
                P.length = stoi(fromfile);
                break;
            case 3:
                inFile >> fromfile;
                P.diametr = stoi(fromfile);
                break;
            case 4:
                inFile >> fromfile;
                if (fromfile == "1") {
                    P.repair = 1;
                }
                else {
                    P.repair = 0;
                }
                break;
            }
        }
        // Закрываем файл
        inFile.close();
        ifstream inFile("compress.txt");
        // Проверяем, удалось ли открыть файл
        if (inFile) {
            string line;
            // Чтение строк из файла
            int lineNumber = 0; // Счетчик строк
            string fromfile; //ПЕременная куда будут считываться данные из файла до их преобразования
            while (getline(inFile, line)) {
                lineNumber++;
                // Проверяем, является ли это строка с возрастом
                switch (lineNumber) {
                case 1: // Если это первая строка
                    // Извлекаем значение имени
                    inFile >> C.name;
                    break;
                case 2:
                    // Извлекаем значение имени
                    inFile >> fromfile;
                    C.workshop = stoi(fromfile);
                    break;
                case 3:
                    inFile >> fromfile;
                    C.realworkshop = stoi(fromfile);
                    break;
                case 4:
                    inFile >> fromfile;
                    C.effect = stod(fromfile);
                    break;
                }
            }
            // Закрываем файл
            inFile.close();
        }
    }
}