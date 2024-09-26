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

map<string, Pipe> pipes;
map<string, CompressStation> stations;
void Menu();
void Mistake();
void CreatePipe();
void CreateCompress();
void ViewPipe();
void ViewComp();
void EditPipe(Pipe& P);
void EditCompress(CompressStation& C);
void SaveFile(Pipe& P, CompressStation& C);
void ReadFile(Pipe& P, CompressStation& C);

int main()
{
    bool cycle = 1;
    while (cycle) {
        int choice;
        Menu();//
        while (1) {
            cin >> choice; // ��������� �����
            // ���������, ��������� �� ������� �����
            if (choice >= 0 && choice <= 6 && cin.good() && cin.peek() == '\n') {
                // ���� �� � �������, ������� �� �����
                break;
            }
            else {
                Mistake();//������� ��������� �� ������
            }
        }
        switch (choice) {
        case 1:
            CreatePipe();
            break;
        case 2:
            CreateCompress();
            break;
        case 3:
            ViewPipe();
                        //for (const auto& pair : stations) {
            //    std::cout << pair.first << ": " << pair.second.workshop << std::endl;
            //}
            break;
        case 4:
            ViewComp();
        //    EditPipe(P);
        //    break;
        //case 5:
        //    EditCompress(C);
        //    break;
        //case 6:
        //    SaveFile(P, C);
        //    break;
        //case 0:
        //    cycle = 0;
        //    break;
        }
    }
};

void Menu() { // ������� ���� ��� ������ ��������
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
};

void Mistake() {
    cout << "Incorrect input(((\nPlease try again:\n";
    cin.clear(); // ���������� ���� ������
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������� ������������ ����
};

void CreatePipe() {
    Pipe P;
    cout << "\nCreation of a pipe.\n";
    cout << "Name the pipe:\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (1) {
        getline(cin, P.name); // ��������� ���
        // ���������, ���� �� ������� ���
        if (cin.good() && !(pipes.count(P.name))) {
            // ���� �� � �������, ������� �� ����� 
            break;
        }
        else {
            cout << "You already have that pipe.\nTry another name:\n";//������� ��������� �� ������
            cin.clear(); // ���������� ���� ������
            continue;
        }
    }
    cout << "Specify the lenght:\n";
    while (1) {
        cin >> P.length; // ��������� �����
        // ���������, ��������� �� ������� �����
        if (P.length > 0 && cin.good() && cin.peek() == '\n') {
            // ���� �� � �������, ������� �� �����
            break;
        }
        else {
            Mistake();//������� ��������� �� ������
        }
    }
    cout << "Specify the diametr:\n";
    while (1) {
        cin >> P.diametr; // ��������� �����
        // ���������, ��������� �� ������� �����
        if (P.diametr > 0 && cin.good() && cin.peek() == '\n') {
            // ���� �� � �������, ������� �� �����
            break;
        }
        else {
            Mistake();//������� ��������� �� ������
        }
    }
    cout << "Is it under repair?(y/n)\n";
    string answer;
    while (1) {
        cin >> answer; // ��������� �����
        // ���������, ��������� �� ������ �����
        if ((answer == "y" || answer == "n") && cin.good() && cin.peek() == '\n') {
            // ���� �� � �������, ������� �� �����
            break;
        }
        else {
            Mistake();//������� ��������� �� ������
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
        getline(cin, C.name); // ��������� ���
        // ���������, ���� �� ������� ���
        if (cin.good() &&!(stations.count(C.name))) {
            // ���� �� � �������, ������� �� �����
            break;
        }
        else {
            cout << "You already have that pipe.\nTry another name:\n";//������� ��������� �� ������
            cin.clear(); // ���������� ���� ������
        }
    }
    cout << "Specify the amount of workshops:\n";
    while (1) {
        cin >> C.workshop; // ��������� �����
        // ���������, ��������� �� ������� �����
        if (C.workshop > 0 && cin.good() && cin.peek() == '\n') {
            // ���� �� � �������, ������� �� �����
            break;
        }
        else {
            Mistake();//������� ��������� �� ������
        }
    }
    cout << "Specify the amount of working workshops:\n";
    while (1) {
        cin >> C.realworkshop; // ��������� �����
        // ���������, ��������� �� ������� �����
        if (C.realworkshop >= 0 && C.realworkshop <= C.workshop && cin.good() && cin.peek() == '\n') {
            // ���� �� � �������, ������� �� �����
            break;
        }
        else {
            Mistake();//������� ��������� �� ������
        }
    }
    cout << "Specify the effectiveness:\n";
    while (1) {
        cin >> C.effect; // ��������� �����
        // ���������, ��������� �� ������� �����
        if (cin.good() && cin.peek() == '\n') {
            // ���� �� � �������, ������� �� �����
            break;
        }
        else {
            Mistake();//������� ��������� �� ������
        }
    }
    stations[C.name] = C;
}

void ViewPipe() {
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
    }
    else {
        cout << "\nYou don't have any pipes yet\n";
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

void EditPipe(Pipe& P) {
    if (P.length > 0) {
        cout << "Is it under repair?(y/n)\n";
        string answer;
        while (1) {
            cin >> answer; // ��������� �����
            // ���������, ��������� �� ������ �����
            if ((answer == "y" || answer == "n") && cin.good() && cin.peek() == '\n') {
                // ���� �� � �������, ������� �� �����
                break;
            }
            else {
                Mistake();//������� ��������� �� ������
            }
        }
        if (answer == "y") {
            P.repair = true;
        }
        else if (answer == "n") {
            P.repair = false;
        }
    }
    else {
        cout << "You don't have a pipe to edit";
    }
}

void EditCompress(CompressStation& C) {
    if (C.workshop > 0) {
        cout << "Specify the amount of working workshops again:\n";
        while (1) {
            cin >> C.realworkshop; // ��������� �����
            // ���������, ��������� �� ������� �����
            if (C.realworkshop >= 0 && C.realworkshop <= C.workshop && cin.good() && cin.peek() == '\n') {
                // ���� �� � �������, ������� �� �����
                break;
            }
            else {
                Mistake();//������� ��������� �� ������
            }
        }
    }
    else {
        cout << "You don't have a compressor station to edit";
    }
}

void SaveFile(Pipe& P, CompressStation& C) {
    if (P.length > 0) {
        // ������� ������ ofstream ��� ������ � ����
        ofstream outFile("pipe.txt");
        // ������ ������ � ����
        outFile << endl << P.name << endl << P.length << endl << P.diametr << endl << P.repair; // ���������� ������ � ����
        // ��������� ����
        outFile.close();
    }
    if (C.workshop > 0) {
        // ������� ������ ofstream ��� ������ � ����
        ofstream outFile("compress.txt");
        // ������ ������ � ����
        outFile << endl << C.name << endl << C.workshop << endl << C.realworkshop << endl << C.effect; // ���������� ������ � ����
        // ��������� ����
        outFile.close();
    }
}

void ReadFile(Pipe& P, CompressStation& C) {
    ifstream inFile("pipe.txt");
    // ���������, ������� �� ������� ����
    if (inFile) {
        string line;
        // ������ ����� �� �����
        int lineNumber = 0; // ������� �����
        string fromfile; //
        while (getline(inFile, line)) {
            lineNumber++;
            // ���������, �������� �� ��� ������ � ���������
            switch(lineNumber){
            case 1:// ���� ��� ������ ������
                // ��������� �������� �����
                inFile >> P.name;
                break;
            case 2:
                // ��������� �������� �����
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
        // ��������� ����
        inFile.close();
        ifstream inFile("compress.txt");
        // ���������, ������� �� ������� ����
        if (inFile) {
            string line;
            // ������ ����� �� �����
            int lineNumber = 0; // ������� �����
            string fromfile; //���������� ���� ����� ����������� ������ �� ����� �� �� ��������������
            while (getline(inFile, line)) {
                lineNumber++;
                // ���������, �������� �� ��� ������ � ���������
                switch (lineNumber) {
                case 1: // ���� ��� ������ ������
                    // ��������� �������� �����
                    inFile >> C.name;
                    break;
                case 2:
                    // ��������� �������� �����
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
            // ��������� ����
            inFile.close();
        }
    }
}