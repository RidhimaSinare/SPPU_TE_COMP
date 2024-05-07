#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

class ChatBot {
private:
    map<string,vector<string>> responses;

public:
    ChatBot() {
        responses["hi"] = {"Hello!", "Hi there!", "Hey!"};
        responses["how are you"] = {"I'm fine, thank you!", "Pretty good!", "Not too bad."};
        responses["bye"] = {"Goodbye!", "See you later!", "Bye!"};
    }

    string getResponse(const string& input) {
        string lowerInput = toLower(input);
        
        for (const auto& entry : responses) {
            if (lowerInput.find(entry.first) != string::npos) {
                return entry.second[rand() % entry.second.size()];
            }
        }
        
        return "I'm sorry, I don't understand.";
    }
};

int main() {
    ChatBot chatbot;

    string userInput;
    while (true) {
        cout << "You: ";
        getline(std::cin, userInput);

        if (toLower(userInput) == "exit") {
            cout << "ChatBot: Goodbye!\n";
            break;
        }

        cout << "ChatBot: " << chatbot.getResponse(userInput) << endl;
    }

    return 0;
}
