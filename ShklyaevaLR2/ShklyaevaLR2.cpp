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
    //double percent = (workshop - realworkshop) / workshop * 100;
};

int Menu();
void Mistake();
int EditMenu();

void CreatePipe(map<string, Pipe>& pipes);
int ViewPipe(map<string, Pipe> pipes, string answer);
int MenuPipes();
void Repair(bool filt, map<string, Pipe>& pipes);
void SearchPipe(map<string, Pipe>& pipes);
void EditPipe(Pipe& P);

void CreateCompress(map<string, CompressStation>& stations);
int ViewComp(map<string, CompressStation> stations, string answer);
void EditCompress(CompressStation& C);
int MenuComp();
void SearchComp(map<string, CompressStation>& stations);
void Workshops(map<string, CompressStation>& stations);

int main()
{
    map<string, CompressStation> stations;
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
            CreateCompress(stations);
            break;
        case 3:
            ViewPipe(pipes,"any");
            break;
        case 4:
            ViewComp(stations,"any");
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
                SearchPipe(pipes);
                break;
            }
            break;
        case 6:
            choice = MenuComp();
            switch (choice) {
            case 1:
                Workshops(stations);
                break;
            case 2:
                SearchComp(stations);
                break;
            }
            break;
        case 0:
            cycle = 0;
            break;
        }
    }
};


//Общие функции
int Menu() { // создаем меню для выбора действий
    int choice;
    cout << "\n...........Choose.an.option...........\n";
    cout << ".  1.Create a pipe                   .\n";
    cout << ".  2.Create a compressor station     .\n";
    cout << ".  3.View my pipes                   .\n";
    cout << ".  4.View my compressor stations     .\n";
    cout << ".  5.Search pipes                    .\n";
    cout << ".  6.Search compressor stations      .\n";
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


//Функции для работы с трубами
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
        cout << "\nYou don't have " << answer << " pipes yet\n";
        return 0;
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
    int exist = ViewPipe(repair, "such");
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

void SearchPipe(map<string, Pipe>& pipes) {
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
        int choice = EditMenu();
        Pipe P;
        switch (choice) {
        case 1:
            P = pipes[name];
            pipes.erase(name);
            EditPipe(P);
            pipes[name] = P;
            break;
        case 2:
            P = pipes[name];
            pipes.erase(name);
            break;
        }
    }
    else {
        cout << "You don't have that pipe\n";
    }
}

void EditPipe(Pipe& P) {
    if (P.repair == 1) {
        P.repair = 0;
    }
    else {
        P.repair = 1;
    }
}


//Функции для работы с КС
void CreateCompress(map<string, CompressStation>& stations) {
    CompressStation C;
    cout << "\nCreation of a compressor station.\n";
    cout << "Name the compressor station:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (1) {
        getline(cin, C.name); // Считываем имя
        // Проверяем, было ли введено имя
        if (cin.good() && !(stations.count(C.name))) {
            // Если всё в порядке, выходим из цикла 
            break;
        }
        else {
            cout << "You already have that station.\nTry another name:\n";//выводим сообщение об ошибке
            cin.clear(); // Сбрасываем флаг ошибки
            continue;
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

int ViewComp(map<string, CompressStation> stations, string answer) {
    if (stations.size() != 0) {
        cout << "\nCompressor Stations\n";
        for (const auto& pair : stations) {
            cout << "\nName: " << pair.second.name;
            cout << "\nAmount of workshops: " << pair.second.workshop;
            cout << "\nAmount of working workshops: " << pair.second.realworkshop;
            cout << "\nEffectiveness: " << pair.second.effect << "\n";
        }
        return 1;
    }
    else {
        cout << "\nYou don't have " << answer << " stations yet\n";
        return 0;
    }
}

void EditCompress(CompressStation& C) {
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
}

int MenuComp() {
    int choice;
    cout << "\n..............Choose.an.option..............\n";
    cout << ".   1.Search by percent of unused workshops.\n";
    cout << ".   2.Search by name                       .\n";
    cout << ".   0.Exit                                 .\n";
    cout << "............................................\n";
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

void SearchComp(map<string, CompressStation>& stations) {
    string name;
    cout << "Name the station you want to find:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name); // Считываем имя
    if (stations.count(name)) {
        cout << "\nCompressor Stations\n";
        cout << "\nName: " << stations[name].name;
        cout << "\nAmount of workshops: " << stations[name].workshop;
        cout << "\nAmount of working workshops: " << stations[name].realworkshop;
        cout << "\nEffectiveness: " << stations[name].effect << "\n";
        int choice = EditMenu();
        CompressStation C;
        switch (choice) {
        case 1:
            C = stations[name];
            stations.erase(name);
            EditCompress(C);
            stations[name] = C;
            break;
        case 2:
            C = stations[name];
            stations.erase(name);
            break;
        }
    }
    else {
        cout << "You don't have that compressor station\n";
    }
}

void Workshops(map<string, CompressStation>& stations) {
    map<string, CompressStation> percents;
    double percent;
    double rpercent;
    cout << "Specify the percent of unused workshops:\n";
    while (1) {
        cin >> percent; // Считываем число
        // Проверяем, правильно ли введено число
        if (percent >= 0 && percent <= 100 && cin.good() && cin.peek() == '\n') {
            // Если всё в порядке, выходим из цикла
            break;
        }
        else {
            Mistake();//выводим сообщение об ошибке
        }
    }
    for (const auto& pair : stations) {
        rpercent = (static_cast<double>(pair.second.workshop - pair.second.realworkshop) / pair.second.workshop) * 100;
        cout << rpercent;
        if (rpercent==percent) {
            percents[pair.first] = pair.second;
        }
    }
    int exist = ViewComp(percents, "such");
    if (exist) {
        int choice;
        CompressStation C;
        choice = EditMenu();
        switch (choice) {
        case 1:
            for (const auto& pair : percents) {
                C = pair.second;
                stations.erase(pair.first);
                EditCompress(C);
                stations[C.name] = C;
            }
            break;
        case 2:
            for (const auto& pair : percents) {
                C = pair.second;
                stations.erase(pair.first);
            }
            break;
        }
    }
}
