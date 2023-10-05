#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <ios>
#include <fstream>

class info {

    public:

    // First and Last Name
    std::string firstName, lastName;

    // Birth Date
    std::string birthMonth, birthDay, birthYear;

    // Arrays for Name and Birthdate
    std::string names[2];
    std::string birthDate[3];

    // Vector for extra keywords
    std::vector<std::string> moreStr;
    std::string others;

    // Vector for extra numbers
    std::vector<int> moreNums;
    int nums;

    std::ofstream wordlist;

    std::vector<std::string> sChars;

    // Constructor to get info from user
    // Store in array and vector
    info() {
        std::cout << "Enter First Name: ";
        std::cin >> firstName;

        std::cout << "Enter Last Name: ";
        std::cin >> lastName;

        std::cout << "Enter Birth Month: ";
        std::cout << "(Enter 'n' if unknown): ";
        std::cin >> birthMonth;

        std::cout << "Enter Birth Day: ";
        std::cout << "(Enter 'n' if unknown): ";
        std::cin >> birthDay;

        std::cout << "Enter Birth Year ";
        std::cout << "(Enter 'n' if unknown): ";
        std::cin >> birthYear;

        names[0] = firstName;
        names[1] = lastName;

        birthDate[0] = birthMonth;
        birthDate[1] = birthDay;
        birthDate[2] = birthYear;

        std::cout << "Enter other words: " << std::endl;
        std::cout << "(Type words and press Enter. Press 'n' when done): ";
        std::getline(std::cin, others);

        while ((std::cin >> others) && others != "n") {
            moreStr.push_back(others);
        }

        std::cout << "Enter other numbers: " << std::endl;
        std::cout << "(Type numbers and press Enter. Press 'n' when done): ";

        while ((std::cin >> nums) && nums != 'n') {
            moreNums.push_back(nums);
        }

        wordlist.open("wordlist.txt", std::ofstream::trunc);
        wordlist.close();

        sChars.push_back("!");
        sChars.push_back("@");
        sChars.push_back("#");
        sChars.push_back("$");
        sChars.push_back("%");
        sChars.push_back("^");
        sChars.push_back("&");
        sChars.push_back("*");
    }

    template<class T>
    // Function to output names and words only
    void outputWords(T list, int i) {

        wordlist.open("wordlist.txt", std::ios_base::app | std::ios_base::out);

        std::transform(list[i].begin(), list[i].end(), list[i].begin(), ::tolower);
        wordlist << list[i] << std::endl;
        std::transform(list[i].begin(), list[i].end(), list[i].begin(), ::toupper);
        wordlist << list[i] << std::endl;
        std::transform(list[i].begin(), list[i].end(), list[i].begin(), ::tolower);
        list[i][0] = toupper(list[i][0]);
        wordlist << list[i] << std::endl;
    }

    template <class T>
    // Function to output names, words and bday combos
    void outputBdayList(T list, int i, int x, int (*func)(int), bool cap) {

        std::string check = (birthDate[x] != "n") ? birthDate[x] : "";
        std::string check0 = (birthDate[0] != "n") ? birthDate[0] : "";
        std::string check1 = (birthDate[1] != "n") ? birthDate[1] : "";
        std::string check2 = (birthDate[2] != "n") ? birthDate[2] : "";

        std::transform(list[i].begin(), list[i].end(), list[i].begin(), func);

        if (cap == true) {
            list[i][0] = toupper(list[i][0]);
        }

        if (check != "") {
            wordlist << list[i] << check << std::endl;
        }
        wordlist << list[i] << check << check1 << std::endl;
        wordlist << list[i] << check << check1 << check2 << std::endl;
        wordlist << list[i] << check << check2 << check1 << std::endl;
        wordlist << list[i] << check << check2 << std::endl;
        wordlist << list[i] << check << check0 << std::endl;
        wordlist << list[i] << check << check0 << check1 << std::endl;
        wordlist << list[i] << check << check0 << check2 << std::endl;
        wordlist << list[i] << check << check1 << check0 << std::endl;
        wordlist << list[i] << check << check2 << check0 << std::endl;
    }

    template <class T>
    // Function to output names, words, and number combos
    void outputWordsNums(T list, int i, int x) {

        // Lowercase names
        std::transform(list[i].begin(), list[i].end(), list[i].begin(), ::tolower);
        wordlist << list[i] << moreNums[x] << std::endl;
        // Uppercase names
        std::transform(list[i].begin(), list[i].end(), list[i].begin(), ::toupper);
        wordlist << list[i] << moreNums[x] << std::endl;
        // Capitalized names
        std::transform(list[i].begin(), list[i].end(), list[i].begin(), ::tolower);
        list[i][0] = toupper(list[i][0]);
        wordlist << list[i] << moreNums[x] << std::endl;

        //wordlist.close();
    }

    template <class T>
    // Function to loop list
    void loopList(T list, int times) {
        for (int i = 0; i < times; i++) {
            outputWords(list, i);

            // Names + birthdates
            for (int x = 0; x < 3; x++) {
                outputBdayList(list, i, x, tolower, false);
                outputBdayList(list, i, x, toupper, false);
                outputBdayList(list, i, x, tolower, true);
            }

            // Names + extra numbers
            for (int y = 0; y < moreNums.size(); y++) {
                outputWordsNums(list, i, y);
            }

            wordlist.close();
        }
    }

    // Function to output list
    void createList() {
        // Names
        loopList(names, 2);
        // Keywords
        loopList(moreStr, moreStr.size());
    }

    // Function to remove duplicates, sort list, and re-output to file
    void createFile(std::ofstream &wl) {
        std::ifstream file("wordlist.txt");
        std::string str;
        std::vector<std::string> file_contents;
        while (std::getline(file, str)) {
            file_contents.push_back(str);
        }  

        wl.open("wordlist.txt", std::ofstream::trunc);

        for (int i = 0; i < file_contents.size(); i++) {

            std::sort( file_contents.begin(), file_contents.end() );
            file_contents.erase( unique( file_contents.begin(), file_contents.end() ), file_contents.end() );

            wl << file_contents[i] << std::endl;
        }

        file.close();
        wl.close();
    }

    // Function to add special characters to each combo
    void addschars(std::ofstream &wl) {
        std::ifstream file("wordlist.txt");
        std::string str;
        std::vector<std::string> file_contents;
        while (std::getline(file, str)) {
            file_contents.push_back(str);
        }

        wl.open("wordlist.txt", std::ios_base::app | std::ios_base::out);

        for(int i = 0; i < file_contents.size(); i++) {
            for (int x = 0; x < sChars.size(); x++) {
                wl << file_contents[i] << sChars[x] << std::endl;
            }
        }

        file.close();
        wl.close();
    }
};

int main() {
    info input;
    input.createList();
    input.createFile(input.wordlist);
    input.addschars(input.wordlist);
}
