#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct Row
{
    int id;
    string name;

    string serialize() const
    {
        return to_string(id) + "," + name;
    }

    static Row deserialize(const string &str)
    {
        Row row;
        stringstream ss(str);
        string temp;

        getline(ss, temp, ',');
        row.id = stoi(temp);
        getline(ss, row.name, ',');

        return row;
    }
};

void clearConsole()
{
    system("clear");
}

Row readRow(int id);

void insertRow(int id, const string &name)
{
    ofstream file("table.txt", ios::app);
    if (file.is_open())
    {
        Row row = {id, name};

        file << row.serialize() << "\n";
        file.close();
        cout << "Row inserted successfully.\n";
    }
    else
    {
        cerr << "Error opening file.\n";
    }
}

void readRows()
{
    ifstream file("table.txt");
    string line;

    if (file.is_open())
    {
        cout << "┌──────┬────────────┐\n";
        cout << "│ " << left << setw(4) << "ID" << " │ " << setw(10) << "Name" << " │\n";
        cout << "├──────┼────────────┤\n";

        while (getline(file, line))
        {
            Row row = Row::deserialize(line);
            cout << "│ " << setw(4) << row.id << " │ " << setw(10) << row.name << " │\n";
        }
        cout << "└──────┴────────────┘\n";

        file.close();
    }
    else
    {
        cerr << "Error opening file.\n";
    }
}

Row readRow(int id)
{
    ifstream file("table.txt");
    string line;
    Row row;
    row.id = 0;
    row.name = "";

    if (file.is_open())
    {
        while (getline(file, line))
        {
            Row row = Row::deserialize(line);
            if (row.id == id)
            {
                file.close();
                return row;
            }
        }
    }
    else
    {
        cerr << "Error opening file.\n";
    }

    return row;
}

void updateRow(int id, const string &newName)
{
    ifstream file("table.txt");
    vector<Row> rows;
    string line;

    while (getline(file, line))
    {
        Row row = Row::deserialize(line);
        if (row.id == id)
        {
            row.name = newName;
        }
        rows.push_back(row);
    }
    file.close();

    ofstream outFile("table.txt", ios::trunc);
    for (const auto &row : rows)
    {
        outFile << row.serialize() << "\n";
    }
    outFile.close();
    cout << "Row updated successfully.\n";
}

void deleteRow(int id)
{
    ifstream file("table.txt");
    vector<Row> rows;
    string line;

    while (getline(file, line))
    {
        Row row = Row::deserialize(line);
        if (row.id != id)
        {
            rows.push_back(row);
        }
    }
    file.close();

    ofstream outFile("table.txt", ios::trunc);

    for (const auto &row : rows)
    {
        outFile << row.serialize() << "\n";
    }
    outFile.close();
    cout << "Row deleted successfully.\n";
}

int main()
{
    int choice;
    while (true)
    {
        cout << "\nSelect an operation:\n";
        cout << "1. Insert Row\n";
        cout << "2. Read All Rows\n";
        cout << "3. Update Row\n";
        cout << "4. Delete Row\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int id;
            string name;
            cout << "Enter ID: ";
            cin >> id;
            Row row = readRow(id);

            if (row.id == id)
            {
                cout << "ID already taken by anorher object.\n";
                continue;
            }

            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            insertRow(id, name);
        }
        else if (choice == 2)
        {
            clearConsole();
            readRows();
        }
        else if (choice == 3)
        {
            int id;
            string name;
            cout << "Enter ID to update: ";
            cin >> id;
            cout << "Enter New Name: ";
            cin.ignore();
            getline(cin, name);
            updateRow(id, name);
        }
        else if (choice == 4)
        {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;
            deleteRow(id);
        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}
