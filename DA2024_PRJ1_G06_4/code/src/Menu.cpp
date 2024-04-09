#include "Menu.h"

#include <limits>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "City.h"
#include "Pipe.h"

using namespace std;

// -------------------- Constructor -------------------- //

Menu::Menu() {
    setUpMenu();
}

// ----------------------- SetUp ----------------------- //

void Menu::setUpMenu() {
    int input;

    system("clear || cls");
    cout << endl
         << "   Please select the data set:" << endl << endl
         << "     1. Small Data Set" << endl << endl
         << "     2. Large Data Set" << endl << endl
         << "     3. Custom Data Set" << endl << endl
         << "   Select your option: ";

    while (!(cin >> input)) {
        cout << endl << "   Please select a valid option: ";
        cin.clear(); cin.ignore(10000, '\n');
    }

    do {
        switch (input) {
            case 1:
                network.createNetwork(dataPath);
                subNetwork.createNetwork(dataPath);
                mainMenu(true);
                return;
            case 2:
                dataPath = "../data/large/";
                network.createNetwork(dataPath);
                subNetwork.createNetwork(dataPath);
                mainMenu(true);
                return;
            case 3:
                setUpCustom();
                network.createNetwork(dataPath);
                subNetwork.createNetwork(dataPath);
                mainMenu(true);
                return;
            default:
                cout << endl << "   Please select a valid option: ";
                while (!(cin >> input)) {
                    cout << endl << "   Please select a valid option: ";
                    cin.clear(); cin.ignore(10000, '\n');
                }
        }
    }
    while(true);
}

void Menu::setUpCustom() {
    string input;

    cout << endl << "   Please enter the data set's path: ";

    getline(cin >> ws, input);

    do {
        if (input.back() != '/')
            input.push_back('/');
        replace(input.begin(), input.end(), '\\', '/');
        ifstream testNetwork(input + "Cities.csv");
        if (testNetwork.good()) {
            dataPath = input; return;
        }
        cout << endl << "   Please enter a valid path: ";
        getline(cin >> ws, input);
    }
    while(true);
}

// --------------------- Main Menu --------------------- //

void Menu::mainMenu(bool isLoading) {
    int input;

    mainMenuOptions(isLoading);

    while (!(cin >> input)) {
        cout << endl << "   Please select a valid option : ";
        cin.clear(); cin.ignore(10000, '\n');
    }

    do {
        switch (input) {
            case 0:
                return;
            case 1:
                basicServiceMenu();
                return;
            case 2:
                lineFailuresMenu();
                return;
            case 9:
                if (confirmChoice(true)) setUpMenu();
                else mainMenu(false);
                return;
            default:
                cout << endl << "   Please select a valid option : ";
                while (!(cin >> input)) {
                    cout << endl << "   Please select a valid option : ";
                    cin.clear(); cin.ignore(10000, '\n');
                }
        }
    }
    while(true);
}

void Menu::mainMenuOptions(bool isLoading) {
    system("clear || cls");
    if (isLoading) {
        cout << endl
             << "   Water Supply Manager                     A.Neves | L.Cunha | V.Castro" << endl
             << "   ---------------------------------------------------------------------" << endl;
    }
    else
        cout << endl
             << "   Main Menu" << endl
             << "   ---------------------------------------------------------------------" << endl;

    cout << "   Please select your desired option by typing it on the selector intake" << endl << endl
         << "     1. Basic Service Metrics" << endl << endl
         << "     2. Reliability and Sensitivity to Failures" << endl << endl << endl
         << "     9. Change Data Set" << endl << endl
         << "     0. Exit application" << endl << endl
         << "   Select your option : ";
}

// ------------------- Basic Service ------------------- //

void Menu::basicServiceMenu() {
    int input;

    basicServiceMenuPrinter();

    while (!(cin >> input)) {
        cout << endl << "   Please select a valid option : ";
        cin.clear(); cin.ignore(10000, '\n');
    }

    do {
        switch (input) {
            case 0:
                return;
            case 1:
                basicMaxFlowMenu();
                return;
            case 2:
                basicWaterDemand();
                return;
            case 9:
                mainMenu(false);
                return;
            default:
                cout << endl << "   Please select a valid option : ";
                while (!(cin >> input)) {
                    cout << endl << "   Please select a valid option : ";
                    cin.clear(); cin.ignore(10000, '\n');
                }
        }
    }
    while(true);
}

void Menu::basicServiceMenuPrinter() {
    system("clear || cls");
    cout << endl
         << "   Basic Service Metrics" << endl
         << "   ---------------------------------------------------------------------" << endl
         << "   Please select your desired option by typing it on the selector intake" << endl << endl
         << "     1. Network Max Flow" << endl << endl
         << "     2. Cities Water Demand" << endl << endl << endl
         << "     9. Go back" << endl << endl
         << "     0. Exit application" << endl << endl
         << "   Select your option : ";
}

void Menu::basicMaxFlowMenu() {
    int input;

    basicMaxFlowMenuPrinter();

    while (!(cin >> input)) {
        cout << endl << "   Please select a valid option : ";
        cin.clear(); cin.ignore(10000, '\n');
    }

    do {
        switch (input) {
            case 0:
                return;
            case 1:
                basicMaxFlowAll();
                return;
            case 2:
                basicMaxFlowSingle();
                return;
            case 9:
                basicServiceMenu();
                return;
            default:
                cout << endl << "   Please select a valid option : ";
                while (!(cin >> input)) {
                    cout << endl << "   Please select a valid option : ";
                    cin.clear(); cin.ignore(10000, '\n');
                }
        }
    }
    while(true);
}

void Menu::basicMaxFlowMenuPrinter() {
    system("clear || cls");
    cout << endl
         << "   Max Flow" << endl
         << "   ---------------------------------------------------------------------" << endl
         << "   Please select your desired option by typing it on the selector intake" << endl << endl
         << "     1. View all data" << endl << endl
         << "     2. Select a specific city" << endl << endl << endl
         << "     9. Go back" << endl << endl
         << "     0. Exit application" << endl << endl
         << "   Select your option : ";
}

void Menu::basicMaxFlowAll() {
    int maxFlow = network.edmondsKarp();

    system("clear || cls");
    cout << endl
         << "   | NETWORK MAX FLOW |" << endl << endl;

    for (City* city : network.getCitySet())
        cout << "   " << city->getCode() << " | " << city->getName() << " -> " << city->getCapacityValue() - city->getCapacity() << endl << endl;

    cout << "   TOTAL NETWORK FLOW: " << maxFlow << endl << endl;

    if (confirmChoice(1))
    {
        string filename = getFilename();
        filename = "../output/" + filename + ".txt";

        ofstream outFile(filename);
        if(!outFile.is_open()) outFile.open(filename);

        outFile << "| NETWORK MAX FLOW |" << endl << endl;

        for (City* city : network.getCitySet())
            outFile << "" << city->getCode() << " | " << city->getName() << " -> " << city->getCapacityValue() - city->getCapacity() << endl << endl;

        outFile << "TOTAL NETWORK FLOW: " << maxFlow << endl;

        outFile.close();

        pressEnterToReturn();
        basicMaxFlowMenu();
        return;
    }

    basicMaxFlowMenu();
}

void Menu::basicMaxFlowSingle() {
    network.edmondsKarp();

    system("clear || cls");
    cout << endl << "   Please enter a valid city code : ";

    City* city = receiveNode<City>("C", true);

    cout << endl
         << "   ! FOUND !" << endl << endl
         << "   " << city->getCode() << " | " << city->getName() << " -> " << city->getCapacityValue() - city->getCapacity() << endl << endl;

    pressEnterToReturn();
    basicMaxFlowMenu();
}

void Menu::basicWaterDemand() {
    network.edmondsKarp();

    system("clear || cls");
    cout << endl
         << "   | NETWORK WATER DEMAND |" << endl << endl;

    for (City* city : network.getCitySet())
    {
        if (city->getCapacity() != 0)
        {
            cout << "   " << city->getCode() << " | " << city->getName() << endl
                 << "     Demand: " << int(city->getDemand()) << endl
                 << "     Actual Flow: " << city->getCapacityValue() - city->getCapacity() << endl
                 << "     Deficit: " << city->getCapacity() << endl << endl;
        }
    }

    if (confirmChoice(1))
    {
        string filename = getFilename();
        filename = "../output/" + filename + ".txt";

        ofstream outFile(filename);
        if(!outFile.is_open()) outFile.open(filename);

        outFile << "| NETWORK WATER DEMAND |" << endl << endl;

        for (City* city : network.getCitySet())
        {
            if (city->getCapacity() != 0)
            {
                outFile << "" << city->getCode() << " | " << city->getName() << endl
                        << "  Demand: " << int(city->getDemand()) << endl
                        << "  Actual Flow: " << city->getCapacityValue() - city->getCapacity() << endl
                        << "  Deficit: " << city->getCapacity() << endl;
            }
        }

        outFile.close();

        pressEnterToReturn();
        basicMaxFlowMenu();
        return;
    }

    basicServiceMenu();
}

// ------------------- Line Failures ------------------- //

void Menu::lineFailuresMenu() {
    int input;

    lineFailuresMenuPrinter();

    while (!(cin >> input)) {
        cout << endl << "   Please select a valid option : ";
        cin.clear(); cin.ignore(10000, '\n');
    }

    do {
        switch (input) {
            case 0:
                return;
            case 1:
                failuresRemoveReservoir();
                return;
            case 2:
                failuresRemoveStation();
                return;
            case 3:
                failuresRemovePipe();
            case 9:
                mainMenu(false);
                return;
            default:
                cout << endl << "   Please select a valid option : ";
                while (!(cin >> input)) {
                    cout << endl << "   Please select a valid option : ";
                    cin.clear(); cin.ignore(10000, '\n');
                }
        }
    }
    while(true);
}

void Menu::lineFailuresMenuPrinter() {
    system("clear || cls");
    cout << endl
         << "   Reliability and Sensitivity to Line Failures" << endl
         << "   ---------------------------------------------------------------------" << endl
         << "   Please select your desired option by typing it on the selector intake" << endl << endl
         << "     1. Remove a Reservoir" << endl << endl
         << "     2. Remove a Station" << endl << endl
         << "     3. Remove a Pipe" << endl << endl << endl
         << "     9. Return to Main Menu" << endl << endl
         << "     0. Exit application" << endl << endl
         << "   Select your option : ";
}

void Menu::failuresRemoveReservoir() {
    system("clear || cls");
    cout << endl << "   Please enter a valid reservoir code : ";

    auto* reservoir = receiveNode<Reservoir>("R", false);

    cout << endl
         << "   " << reservoir->getCode() << " " << reservoir->getName() << " has been removed from the network." << endl << endl
         << "   | CITIES AFFECTED |" << endl << endl;

    string r_code = reservoir->getCode(), r_name = reservoir->getName();

    subNetwork.removeReservoir(reservoir);
    network.edmondsKarp(); subNetwork.edmondsKarp();

    int n = 0;

    for (int i = 0; i < network.getCitySet().size(); i++) {
        City *city1 = network.getCitySet()[i];
        City *city2 = subNetwork.getCitySet()[i];
        if (city1->getCapacity() != city2->getCapacity()) {
            cout << "   " << city1->getCode() << " | " << city1->getName() << endl
                 << "     Old Flow: " << city1->getCapacityValue() - city1->getCapacity() << endl
                 << "     New Flow: " << city2->getCapacityValue() - city2->getCapacity() << endl
                 << "     Deficit: " << (city1->getCapacityValue() - city1->getCapacity()) -
                                        (city2->getCapacityValue() - city2->getCapacity()) << endl << endl;
            n++;
        }
    }

    if (n == 0) cout << "   No city has been affected." << endl << endl;

    if (confirmChoice(1))
    {
        string filename = getFilename();
        filename = "../output/" + filename + ".txt";

        ofstream outFile(filename);
        if(!outFile.is_open()) outFile.open(filename);

        outFile << "| CITIES AFFECTED |" << endl << endl;

        for (int i = 0; i < network.getCitySet().size(); i++) {
            City *city1 = network.getCitySet()[i];
            City *city2 = subNetwork.getCitySet()[i];
            if (city1->getCapacity() != city2->getCapacity()) {
                outFile << "" << city1->getCode() << " | " << city1->getName() << endl
                        << "  Old Flow: " << city1->getCapacityValue() - city1->getCapacity() << endl
                        << "  New Flow: " << city2->getCapacityValue() - city2->getCapacity() << endl
                        << "  Deficit: " << (city1->getCapacityValue() - city1->getCapacity()) -
                                            (city2->getCapacityValue() - city2->getCapacity()) << endl << endl;
                n++;
            }
        }

        if (n == 0) outFile << "No city has been affected." << endl;

        outFile << r_code << " " << r_name << " was removed from the network." << endl;

        outFile.close();

        subNetwork.deleteNetwork();
        subNetwork.createNetwork(dataPath);

        pressEnterToReturn();
        lineFailuresMenu();
        return;
    }

    subNetwork.deleteNetwork();
    subNetwork.createNetwork(dataPath);

    lineFailuresMenu();
}

void Menu::failuresRemoveStation() {
    system("clear || cls");
    cout << endl << "   Please enter a valid station code : ";

    auto* station = receiveNode<Station>("P", false);

    cout << endl
         << "   " << station->getCode() << " has been removed from the network." << endl << endl
         << "   | CITIES AFFECTED |" << endl << endl;

    string s_code = station->getCode();

    subNetwork.removeStation(station);
    network.edmondsKarp(); subNetwork.edmondsKarp();

    int n = 0;

    for (int i = 0; i < network.getCitySet().size(); i++) {
        City *city1 = network.getCitySet()[i];
        City *city2 = subNetwork.getCitySet()[i];
        if (city1->getCapacity() != city2->getCapacity()) {
            cout << "   " << city1->getCode() << " | " << city1->getName() << endl
                 << "     Old Flow: " << city1->getCapacityValue() - city1->getCapacity() << endl
                 << "     New Flow: " << city2->getCapacityValue() - city2->getCapacity() << endl
                 << "     Deficit: " << (city1->getCapacityValue() - city1->getCapacity()) -
                                        (city2->getCapacityValue() - city2->getCapacity()) << endl << endl;
            n++;
        }
    }

    if (n == 0) cout << "   No city has been affected." << endl << endl;

    if (confirmChoice(1))
    {
        string filename = getFilename();
        filename = "../output/" + filename + ".txt";

        ofstream outFile(filename);
        if(!outFile.is_open()) outFile.open(filename);

        outFile << "| CITIES AFFECTED |" << endl << endl;

        for (int i = 0; i < network.getCitySet().size(); i++) {
            City *city1 = network.getCitySet()[i];
            City *city2 = subNetwork.getCitySet()[i];
            if (city1->getCapacity() != city2->getCapacity()) {
                outFile << "" << city1->getCode() << " | " << city1->getName() << endl
                        << "  Old Flow: " << city1->getCapacityValue() - city1->getCapacity() << endl
                        << "  New Flow: " << city2->getCapacityValue() - city2->getCapacity() << endl
                        << "  Deficit: " << (city1->getCapacityValue() - city1->getCapacity()) -
                                            (city2->getCapacityValue() - city2->getCapacity()) << endl << endl;
                n++;
            }
        }

        if (n == 0) outFile << "No city has been affected." << endl;

        outFile << s_code << " has been removed from the network." << endl;

        outFile.close();

        subNetwork.deleteNetwork();
        subNetwork.createNetwork(dataPath);

        pressEnterToReturn();
        lineFailuresMenu();
        return;
    }

    subNetwork.deleteNetwork();
    subNetwork.createNetwork(dataPath);

    lineFailuresMenu();
}

void Menu::failuresRemovePipe() {
    system("clear || cls");
    cout << endl << "   | SOURCE |" << endl
         << endl << "   Please enter a valid station code : ";

    auto* src = receiveNode<Node>("", false);

    cout << endl << "   | TARGET |" << endl
         << endl << "   Please enter a valid station code : ";

    auto* dest = receiveNode<Node>("", false);

    Pipe* pipeSD = src->getPipeTo(dest);
    if (pipeSD != nullptr) pipeSD->setCapacity(0);
    Pipe* pipeDS = dest->getPipeTo(src);
    if (pipeDS != nullptr) pipeDS->setCapacity(0);

    network.edmondsKarp(); subNetwork.edmondsKarp();

    cout << endl
         << "   " << src->getCode() << " -> " << dest->getCode() << " has been removed from the network." << endl << endl
         << "   | CITIES AFFECTED |" << endl << endl;

    int n = 0;

    for (int i = 0; i < network.getCitySet().size(); i++)
    {
        City *city1 = network.getCitySet()[i];
        City *city2 = subNetwork.getCitySet()[i];
        if (city1->getCapacity() != city2->getCapacity()) {
            cout << "   " << city1->getCode() << " | " << city1->getName() << endl
                 << "     Old Flow: " << city1->getCapacityValue() - city1->getCapacity() << endl
                 << "     New Flow: " << city2->getCapacityValue() - city2->getCapacity() << endl
                 << "     Deficit: " << (city1->getCapacityValue() - city1->getCapacity()) -
                                        (city2->getCapacityValue() - city2->getCapacity()) << endl << endl;
            n++;
        }
    }

    if (n == 0) cout << "   No city has been affected." << endl << endl;

    if (confirmChoice(1))
    {
        string filename = getFilename();
        filename = "../output/" + filename + ".txt";

        ofstream outFile(filename);
        if(!outFile.is_open()) outFile.open(filename);

        outFile << "| CITIES AFFECTED |" << endl << endl;

        for (int i = 0; i < network.getCitySet().size(); i++)
        {
            City *city1 = network.getCitySet()[i];
            City *city2 = subNetwork.getCitySet()[i];
            if (city1->getCapacity() != city2->getCapacity()) {
                outFile << city1->getCode() << " | " << city1->getName() << endl
                        << "  Old Flow: " << city1->getCapacityValue() - city1->getCapacity() << endl
                        << "  New Flow: " << city2->getCapacityValue() - city2->getCapacity() << endl
                        << "  Deficit: " << (city1->getCapacityValue() - city1->getCapacity()) -
                                            (city2->getCapacityValue() - city2->getCapacity()) << endl << endl;
                n++;
            }
        }

        if (n == 0) outFile << "   No city has been affected." << endl << endl;

        outFile << src->getCode() << " -> " << dest->getCode() << " has been removed from the network." << endl;

        outFile.close();

        subNetwork.deleteNetwork();
        subNetwork.createNetwork(dataPath);

        pressEnterToReturn();
        lineFailuresMenu();
        return;
    }

    subNetwork.deleteNetwork();
    subNetwork.createNetwork(dataPath);

    lineFailuresMenu();
}

// ----------------- Auxiliary Functions ---------------- //

template<typename NodeType>
NodeType* Menu::receiveNode(const string& type, bool networkID) {
    string input;
    Node* nodeptr;

    getline(cin >> ws, input);

    do {
        if (networkID) nodeptr = network.findNode(input);
        else nodeptr = subNetwork.findNode(input);
        if (nodeptr != nullptr && (type.empty() || nodeptr->getCode().substr(0,1) == type))
            return dynamic_cast<NodeType *>(nodeptr);
        cout << endl << "   Please enter a valid code : ";
        getline(cin >> ws, input);
    }
    while(true);
}

bool Menu::confirmChoice(int flag) {
    int input;

    switch (flag) {
        case 0:
            cout << endl
                 << "   -------------------------" << endl << endl
                 << "   ! WARNING !" << endl << endl
                 << "   You're about to change the data set!" << endl << endl
                 << "     1. Confirm" << endl << endl
                 << "     2. Go back" << endl << endl
                 << "   Select your option : ";
            break;
        case 1:
            cout << "   -------------------------" << endl << endl
                 << "   Do you wish to save the results?" << endl << endl
                 << "     1. Save results to file" << endl << endl
                 << "     2. Go back" << endl << endl
                 << "   Select your option : ";
            break;
        case 2:
            cout << endl
                 << "     1. Advance" << endl << endl
                 << "     2. Retype" << endl << endl
                 << "   Select your option : ";
            break;
        default:
            throw invalid_argument("Invalid option selected.");
    }

    while (!(cin >> input)) {
        cout << endl << "   Please select a valid option : ";
        cin.clear(); cin.ignore(10000, '\n');
    }

    do {
        switch (input) {
            case 1:
                return true;
            case 2:
                return false;
            default:
                cout << endl << "   Please select a valid option : ";
                while (!(cin >> input)) {
                    cout << endl << "   Please select a valid option : ";
                    cin.clear(); cin.ignore(10000, '\n');
                }
        }
    }
    while(true);
}

void Menu::pressEnterToReturn() {
    cout << endl << "   Press ENTER to return...";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

string Menu::getFilename() {
    string input;

    cout << endl << "   Please enter the desired file name with no file extension: ";

    getline(cin >> ws, input);

    do {
        ifstream testNetwork("../output/" + input + ".txt");
        if (!testNetwork.good()) {
            cout << endl << "   The results will be saved under ./output/" + input + ".txt" << endl;
            if (confirmChoice(2)) return input;
        }
        else cout << endl << "   This file already exists!" << endl; system("sleep 0.5");
        cout << endl << "   Please enter the desired file name with no file extension: ";
        getline(cin >> ws, input);
    }
    while(true);
}

// -------------------- END OF FILE -------------------- //
