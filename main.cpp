#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>

using namespace std;


string print_menu(){
    cout << "Voctrainer \n";
    cout << "Bitte treff eine Auswahl:\n";
    cout << "(1) Neue Voc hinzufuegen\n";
    cout << "(2) Voctest starten\n";
    cout << "(3) Voc anzeigen\n";
    string option;
    cin >> option;
    return option;
}

vector<string> load_text(string textFile){
    ifstream in(textFile);
    string str;
    vector<string> new_vector;
    while (getline(in, str))
    {
        if(str.size() > 0)
            new_vector.push_back(str);
    }
    return new_vector;
}

void speichern(string File, vector<string> sprache){
    ofstream output_file(File);
        ostream_iterator<std::string> output_iterator(output_file, "\n");
        copy(sprache.begin(), sprache.end(), output_iterator);
}

bool ask_word(vector<string> german, vector<string> english) {
    int random = rand() % german.size();
    string sel_elem = german[random];
    cout << "Uebersetze: " + sel_elem + "\n";
    string userInput;
    string right = english[random];
    cin >> userInput;
    if (userInput == right) {
        cout << "Richtig\n";
        return true;
    }
    else {
        cout << "Falsch \n" + sel_elem + " auf Englisch ist: " + right + "\n";
        return false;
    }
}

int main() {
    vector<string> german_voc = load_text("german_voc.txt");
    vector<string> english_voc = load_text("english_voc.txt");

    string option = print_menu();

    
    if(option == "1"){
        cout << "Welche Voc (Deutsch)?\n";
        string german_word;
        string english_word;
        cin >> german_word;
        cout << "Englisch?\n";
        cin >> english_word;
        //Deutsch
        german_voc.push_back(german_word);
        //Englisch
        english_voc.push_back(english_word);
        cout << "Voc hinzugefuegt\n";
        cout << "Voc insgesamt: "+ to_string(german_voc.size());

        speichern("./german_voc.txt", german_voc);
        speichern("./english_voc.txt", english_voc);    
    }

    if (option == "2"){
        cout << "VocTest wird gestartet...\n";
        cout << "Wie oft?\n";
        int j;
        int i = 0;
        cin >> j;
        int count = 0;
        while (i < j) {
            bool richtig;
            richtig = ask_word(german_voc, english_voc);
            i++;
            if (richtig == true) {
                count++;
            }
        }
        cout << "richtig: " + to_string(count) + "  von: " + to_string(j) + "\n";
    }
    if (option == "3"){
        string str3;
        ifstream in3("german_voc.txt");
        while (getline(in3, str3))
        {   
            if(str3.size() > 0)
                cout << str3 + "\n";
        }
    }

    return 0; 
}
