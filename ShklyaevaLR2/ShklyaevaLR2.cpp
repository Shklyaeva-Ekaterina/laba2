#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
using namespace std;

class CompressStation {
    friend void CreateCompress(map<int, CompressStation>& stations, int& idcounterCs);
    friend int ViewComp(map<int, CompressStation> stations, string answer);
    friend void EditCompress(CompressStation& C, int workshops);
    friend int MenuComp();
    friend void SearchComp(map<int, CompressStation>& stations);
    friend void Workshops(map<int, CompressStation>& stations);
    friend std::ostream& operator << (std::ostream& os, const CompressStation& C);
public:
    string name;
    int workshop;
    int realworkshop;
    double effect;
};

class Pipe {
    friend void CreatePipe(map<int, Pipe>& pipes, int& idcounterTr);
    friend int ViewPipe(map<int, Pipe> pipes, string answer);
    friend void Repair(bool filt, map<int, Pipe>& pipes);
    friend void SearchPipe(map<int, Pipe>& pipes);
    friend void EditPipe(Pipe& P);
    friend void ReadFile(map<int, Pipe>& pipes, map<int, CompressStation>& stations);
    friend std::ostream& operator << (std::ostream& os, const Pipe& P);
public:
    string name;
    int length;
    int diametr;
    bool repair;
};

int MenuPipes();
int MenuComp();
void SaveFile(map<int, Pipe>& pipes, map<int, CompressStation>& stations);

int Menu();
void Mistake();
int EditMenu();

std::ostream& operator << (std::ostream& os, const Pipe & P)
{
    string rep;
    if (P.repair) {
        rep = "Under repair";
    }
    else {
        rep = "Not under repair";
    }
    return cout << "\nName: " << P.name << "\nLength: " << P.length << "\nDiametr: " << P.diametr << endl << rep << endl;
}

std::ostream& operator << (std::ostream& os, const CompressStation& C)
{
    return cout << "\nName: " << C.name << "\nAmount of workshops: " << C.workshop << "\nAmount of working workshops: " << C.realworkshop << "\nEffectiveness: " << C.effect << "\n";
}

int main()
{
    map<int, Pipe> pipes;
    map<int, CompressStation> stations;
    int idcounterTr = 1;
    int idcounterCs = 1;
    bool cycle = 1;
    while (cycle) {
        int choice;
        choice = Menu();
        switch (choice) {
        case 1:
            CreatePipe(pipes, idcounterTr);
            break;
        case 2:
            CreateCompress(stations, idcounterCs);
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
                SearchComp(stations);
                break;
            case 2:
                Workshops(stations);
                break;
            }
            break;
        case 7:
            SaveFile(pipes,stations);
            break;
        case 8:
            ReadFile(pipes, stations);
            break;
        case 0:
            cycle = 0;
            break;
        }
    }
};/////////////////////////////////////////////////////


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
    cout << ".  7.Save                            .\n";
    cout << ".  8.Read                            .\n";
    cout << ".  0.Exit                            .\n";
    cout << "......................................\n";
    while (1) {
        cin >> choice; // Считываем число
        // Проверяем, правильно ли введено число
        if (choice >= 0 && choice <= 8 && cin.good() && cin.peek() == '\n') {
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
    cout << ".  2.Edit by choice                  .\n";
    cout << ".  2.Delete                          .\n";
    cout << ".  2.Delete by choice                .\n";
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
void CreatePipe(map<int, Pipe>& pipes, int& idcounterTr) {
    Pipe P;
    cout << "\nCreation of a pipe.\n";
    cout << "Name the pipe:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (1) {
        getline(cin, P.name); // Считываем имя
        // Проверяем, было ли введено имя
        if (cin.good()) {
            // Если всё в порядке, выходим из цикла 
            break;
        }
        else {
            //cout << "You already have that pipe.\nTry another name:\n";//выводим сообщение об ошибке
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
    pipes[idcounterTr] = P;
    idcounterTr++;
}

int ViewPipe(map<int, Pipe> pipes, string answer) {
    if (pipes.size() != 0) {
        cout << "\nPipes\n";
        for (const auto& pair : pipes) {
            cout << "\nID: " << pair.first;
            cout << pair.second;
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

void Repair(bool filt, map<int, Pipe>& pipes) {
    map<int, Pipe> repair;
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
        int choice = EditMenu();
        Pipe P;
        switch (choice) {
        case 1:
            for (const auto& pair : repair) {
                P = pair.second;
                pipes.erase(pair.first);
                EditPipe(P);
                pipes[pair.first] = P;
            }
            break;
        case 2:
            cout << "Choose ids of pipes you want to edit (y/n):" << endl;
            for (const auto& pair : repair) {
                P = pair.second;
                pipes.erase(pair.first);
                cout << pair.first << endl;
                string answer;
                while (1) {
                    cin >> answer; // Считываем ответ
                    // Проверяем, правильно ли введен ответ
                    if (answer == "y" && cin.good() && cin.peek() == '\n') {
                        // Если всё в порядке, выходим из цикла
                        EditPipe(P);
                        pipes[pair.first] = P;
                        break;
                    }
                    else if (answer == "n" && cin.good() && cin.peek() == '\n') {
                        pipes[pair.first] = P;
                        // Если всё в порядке, выходим из цикла
                        break;
                    }
                    else {
                        Mistake();//выводим сообщение об ошибке
                    }
                }
            }
            break;
        case 3:
            for (const auto& pair : repair) {
                pipes.erase(pair.first);
            }
            break;
        case 4:
            cout << "Choose ids of pipes you want to delete (y/n):" << endl;
            for (const auto& pair : repair) {
                P = pair.second;
                pipes.erase(pair.first);
                cout << pair.first << endl;
                string answer;
                while (1) {
                    cin >> answer; // Считываем ответ
                    // Проверяем, правильно ли введен ответ
                    if (answer == "y" && cin.good() && cin.peek() == '\n') {
                        // Если всё в порядке, выходим из цикла
                        break;
                    }
                    else if (answer == "n" && cin.good() && cin.peek() == '\n') {
                        pipes[pair.first] = P;
                        // Если всё в порядке, выходим из цикла
                        break;
                    }
                    else {
                        Mistake();//выводим сообщение об ошибке
                    }
                }
            }
            break;
        }
    }
}

void SearchPipe(map<int, Pipe>& pipes) {
    string name;
    bool search=0;
    map<int, Pipe> found;
    cout << "Name the pipe you want to find:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name); // Считываем имя
    for (const auto& pair : pipes) {
        if (pair.second.name.find(name) != string::npos) {
            found[pair.first]=pair.second;
            cout << "\nID: " << pair.first;
            cout << pair.second;
            search = 1;
        }
    }
    if (search) {
        int choice = EditMenu();
        Pipe P;
        switch (choice) {
        case 1:
            for (const auto& pair : found) {
                P = pair.second;
                pipes.erase(pair.first);
                EditPipe(P);
                pipes[pair.first] = P;
            }
            break;
        case 2:
            cout << "Choose ids of pipes you want to edit (y/n):"<<endl;
            for (const auto& pair : found) {
                P = pair.second;
                pipes.erase(pair.first);
                cout << pair.first << endl;
                string answer;
                while (1) {
                    cin >> answer; // Считываем ответ
                    // Проверяем, правильно ли введен ответ
                    if (answer == "y" && cin.good() && cin.peek() == '\n') {
                        // Если всё в порядке, выходим из цикла
                        EditPipe(P);
                        pipes[pair.first] = P;
                        break;
                    }
                    else if (answer == "n" && cin.good() && cin.peek() == '\n') {
                        pipes[pair.first] = P;
                        // Если всё в порядке, выходим из цикла
                        break;
                    }
                    else {
                        Mistake();//выводим сообщение об ошибке
                    }
                }
            }
            break;
        case 3:
            for (const auto& pair : found) {
                pipes.erase(pair.first);
            }
            break;
        case 4:
            cout << "Choose ids of pipes you want to delete (y/n):" << endl;
            for (const auto& pair : found) {
                P = pair.second;
                pipes.erase(pair.first);
                cout << pair.first << endl;
                string answer;
                while (1) {
                    cin >> answer; // Считываем ответ
                    // Проверяем, правильно ли введен ответ
                    if (answer == "y" && cin.good() && cin.peek() == '\n') {
                        // Если всё в порядке, выходим из цикла
                        break;
                    }
                    else if (answer == "n" && cin.good() && cin.peek() == '\n') {
                        pipes[pair.first] = P;
                        // Если всё в порядке, выходим из цикла
                        break;
                    }
                    else {
                        Mistake();//выводим сообщение об ошибке
                    }
                }
            }
            break;
        }
    }
    else{
        cout << "You don't have that pipes\n";
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
void CreateCompress(map<int, CompressStation>& stations, int& idcounterCs) {
    CompressStation C;
    cout << "\nCreation of a compressor station.\n";
    cout << "Name the compressor station:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (1) {
        getline(cin, C.name); // Считываем имя
        // Проверяем, было ли введено имя
        if (cin.good()) {
            // Если всё в порядке, выходим из цикла 
            break;
        }
        else {
            //cout << "You already have that pipe.\nTry another name:\n";//выводим сообщение об ошибке
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
    stations[idcounterCs] = C;
    idcounterCs++;

}

int ViewComp(map<int, CompressStation> stations, string answer) {
    if (stations.size() != 0) {
        cout << "\nCompressor Stations\n";
        for (const auto& pair : stations) {
            cout << "\nID: " << pair.first;
            cout << pair.second;
        }
        return 1;
    }
    else {
        cout << "\nYou don't have " << answer << " stations yet\n";
        return 0;
    }
}

void EditCompress(CompressStation& C,int workshops) {
    if (C.workshop >= workshops) {// Считываем число
        C.realworkshop = workshops;
    }
    else {
        C.realworkshop = C.workshop;
    }
}

int MenuComp() {
    int choice;
    cout << "\n...............Choose.an.option...............\n";
    cout << ".  1.Search by name                          .\n";
    cout << ".  2.Search by percent of working workshops  .\n";
    cout << ".  0.Exit                                    .\n";
    cout << "..............................................\n";
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

void SearchComp(map<int, CompressStation>& stations) {
    string name;
    bool search = 0;
    map<int, CompressStation> found;
    cout << "Name the pipe you want to find:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name); // Считываем имя
    for (const auto& pair : stations) {
        if (pair.second.name.find(name) != string::npos) {
            found[pair.first] = pair.second;
            cout << "\nID: " << pair.first;
            cout << pair.second;
            search = 1;
        }
    }
    if (search) {
        int workshops;
        int choice = EditMenu();
        CompressStation C;
        switch (choice) {
        case 1:
            cout << "Specify the amount of working workshops:\n";
            while (1) {
                cin >> workshops;
                if (cin.good() && cin.peek() == '\n') {
                    // Если всё в порядке, выходим из цикла
                    break;
                }
                else {
                    Mistake();//выводим сообщение об ошибке
                }
            }
            for (const auto& pair : found) {
                C = pair.second;
                stations.erase(pair.first);
                EditCompress(C,workshops);
                stations[pair.first] = C;
            }
            break;
        case 2:
            cout << "Specify the amount of working workshops:\n";
            while (1) {
                cin >> workshops;
                if (cin.good() && cin.peek() == '\n') {
                    // Если всё в порядке, выходим из цикла
                    break;
                }
                else {
                    Mistake();//выводим сообщение об ошибке
                }
            }
            cout << "Choose ids of stations you want to edit (y/n):" << endl;
            for (const auto& pair : found) {
                C = pair.second;
                stations.erase(pair.first);
                cout << pair.first << endl;
                string answer;
                while (1) {
                    cin >> answer; // Считываем ответ
                    // Проверяем, правильно ли введен ответ
                    if (answer == "y" && cin.good() && cin.peek() == '\n') {
                        // Если всё в порядке, выходим из цикла
                        EditCompress(C, workshops);
                        stations[pair.first] = C;
                        break;
                    }
                    else if (answer == "n" && cin.good() && cin.peek() == '\n') {
                        stations[pair.first] = C;
                        // Если всё в порядке, выходим из цикла
                        break;
                    }
                    else {
                        Mistake();//выводим сообщение об ошибке
                    }
                }
            }
            break;
        case 3:
            for (const auto& pair : found) {
                stations.erase(pair.first);
            }
            break;
        case 4:
            cout << "Choose ids of stations you want to delete (y/n):" << endl;
            for (const auto& pair : found) {
                C = pair.second;
                stations.erase(pair.first);
                cout << pair.first << endl;
                string answer;
                while (1) {
                    cin >> answer; // Считываем ответ
                    // Проверяем, правильно ли введен ответ
                    if (answer == "y" && cin.good() && cin.peek() == '\n') {
                        // Если всё в порядке, выходим из цикла
                        break;
                    }
                    else if (answer == "n" && cin.good() && cin.peek() == '\n') {
                        stations[pair.first] = C;
                        // Если всё в порядке, выходим из цикла
                        break;
                    }
                    else {
                        Mistake();//выводим сообщение об ошибке
                    }
                }
            }
            break;
        }
    }
    else {
        cout << "You don't have that compressor station\n";
    }
}

void Workshops(map<int, CompressStation>& stations) {
    map<int, CompressStation> percents;
    int percent;

    cout << "Specify the percent of working workshops:\n";
    while (1) {
        cin >> percent; // Считываем число
        // Проверяем, правильно ли введено число
        if (percent > 0 && cin.good() && cin.peek() == '\n') {
            // Если всё в порядке, выходим из цикла
            break;
        }
        else {
            Mistake();//выводим сообщение об ошибке
        }
    }
    bool search = 0;
    for (const auto& pair : stations) {
        if (((abs(1.0 * pair.second.workshop - 1.0 * pair.second.realworkshop) / pair.second.workshop)*100.0 - 1.0 * percent) < 10.0){
            percents[pair.first] = pair.second;
            cout << "\nID: " << pair.first;
            cout << pair.second;
            search = 1;
        }
    }
    if (search) {
        int workshops;
        int choice = EditMenu();
        CompressStation C;
        switch (choice) {
        case 1:
            cout << "Specify the amount of working workshops:\n";
            while (1) {
                cin >> workshops;
                if (cin.good() && cin.peek() == '\n') {
                    // Если всё в порядке, выходим из цикла
                    break;
                }
                else {
                    Mistake();//выводим сообщение об ошибке
                }
            }
            for (const auto& pair : percents) {
                C = pair.second;
                stations.erase(pair.first);
                EditCompress(C,workshops);
                stations[pair.first] = C;
            }
            break;
        case 2:
            cout << "Specify the amount of working workshops:\n";
            while (1) {
                cin >> workshops;
                if (cin.good() && cin.peek() == '\n') {
                    // Если всё в порядке, выходим из цикла
                    break;
                }
                else {
                    Mistake();//выводим сообщение об ошибке
                }
            }
            cout << "Choose ids of stations you want to edit (y/n):" << endl;
            for (const auto& pair : percents) {
                C = pair.second;
                stations.erase(pair.first);
                cout << pair.first << endl;
                string answer;
                while (1) {
                    cin >> answer; // Считываем ответ
                    // Проверяем, правильно ли введен ответ
                    if (answer == "y" && cin.good() && cin.peek() == '\n') {
                        // Если всё в порядке, выходим из цикла
                        EditCompress(C, workshops);
                        stations[pair.first] = C;
                        break;
                    }
                    else if (answer == "n" && cin.good() && cin.peek() == '\n') {
                        stations[pair.first] = C;
                        // Если всё в порядке, выходим из цикла
                        break;
                    }
                    else {
                        Mistake();//выводим сообщение об ошибке
                    }
                }
            }
            break;
        case 3:
            for (const auto& pair : percents) {
                stations.erase(pair.first);
            }
            break;
        case 4:
            cout << "Choose ids of stations you want to delete (y/n):" << endl;
            for (const auto& pair : percents) {
                C = pair.second;
                stations.erase(pair.first);
                cout << pair.first << endl;
                string answer;
                while (1) {
                    cin >> answer; // Считываем ответ
                    // Проверяем, правильно ли введен ответ
                    if (answer == "y" && cin.good() && cin.peek() == '\n') {
                        // Если всё в порядке, выходим из цикла
                        break;
                    }
                    else if (answer == "n" && cin.good() && cin.peek() == '\n') {
                        stations[pair.first] = C;
                        // Если всё в порядке, выходим из цикла
                        break;
                    }
                    else {
                        Mistake();//выводим сообщение об ошибке
                    }
                }
            }
            break;
        }
    }
    else {
        cout << "You don't have that compressor station\n";
    }
}

void SaveFile(map<int, Pipe>& pipes,map<int, CompressStation>& stations) {
    string filename;
    cout << "Choose the file to save information:" << endl;
    while (1) {
        cin >> filename;
        // Проверяем, правильно ли введено число
        if (filename.length() > 4 && cin.good() && cin.peek() == '\n' && filename.compare(filename.length() - 4, 4, ".txt") == 0) {
            // Если всё в порядке, выходим из цикла
            break;
        }
        else {
            Mistake();//выводим сообщение об ошибке
        }
    }

    // Создаем объект ofstream для записи в файл
    ofstream outFile(filename);
    for (const auto& pair : pipes) {
        outFile << "p\n";
        outFile << pair.first;
        outFile << endl << pair.second.name << endl << pair.second.length << endl << pair.second.diametr << endl << pair.second.repair<<endl;
    }
    for (const auto& pair : stations) {
        outFile << "s\n";
        outFile << pair.first;
        outFile << endl << pair.second.name << endl << pair.second.workshop << endl << pair.second.realworkshop << endl << pair.second.effect<<endl;
    }
    // Закрываем файл
    outFile.close();
}

void ReadFile(map<int, Pipe>& pipes, map<int, CompressStation>& stations) {
    string filename;
    cout << "Choose the file to read information:" << endl;
    while (1) {
        cin >> filename;
        // Проверяем, правильно ли введено число
        if (filename.length() > 4 && cin.good() && cin.peek() == '\n' && filename.compare(filename.length() - 4, 4, ".txt") == 0) {
            // Если всё в порядке, выходим из цикла
            break;
        }
        else {
            Mistake();//выводим сообщение об ошибке
        }
    }
    ifstream inFile(filename);
    // Проверяем, удалось ли открыть файл
    if (inFile) {
        string line;
        // Чтение строк из файла
        string fromfile; 
        int lineNumber = 0;
        int mark=0;
        int id;
        while (getline(inFile, line)) {
            cout << line<<endl;
            inFile >> fromfile;
            if (fromfile == "p") {
                lineNumber = 0;
                mark = 1;
            }
            if (fromfile == "s") {
                lineNumber = 0;
                mark = 2;
            }
            if (mark==2) {
                CompressStation C;
                if (lineNumber == 1) { // Если это первая строка
                    // Извлекаем значение имени
                    id = stoi(fromfile);
                }
                if (lineNumber == 2) { // Если это первая строка
                    // Извлекаем значение имени
                    C.name=fromfile;
                }
                if (lineNumber == 3) {
                    C.workshop = stoi(fromfile);
                }
                if (lineNumber == 4) {
                    C.realworkshop = stoi(fromfile);
                }
                if (lineNumber == 5) {
                    C.effect = stod(fromfile);
                    cout << C;
                    stations[id] = C;
                }
            }
            else if (mark==1) {
                Pipe P;
                if (lineNumber == 1) { // Если это первая строка
                    // Извлекаем значение имени
                    id = stoi(fromfile);
                }
                if (lineNumber == 2) { // Если это первая строка
                    // Извлекаем значение имени
                    P.name=fromfile;
                }
                if (lineNumber == 3) {
                    // Извлекаем значение имени

                    P.length = stoi(fromfile);
                }
                if (lineNumber == 4) {
                    P.diametr = stoi(fromfile);
                }
                if (lineNumber == 5) {
                    if (fromfile == "1") {
                        P.repair = 1;
                    }
                    else {
                        P.repair = 0;
                    }
                    cout << P;

                    pipes[id] = P;
                }
            }
            lineNumber++;
        }
    }
    // Закрываем файл
    inFile.close();
}