#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Token {
    string type;
    string value;
};

struct Item 
{
    int quantity;
    string name;
    double price;
};

double applyDiscount(double total, int discount) 
{
    return total - (total * discount / 100);
}

vector<Token> tokenize(const string& input) {
    stringstream ss(input);
    vector<Token> tokens;
    string token;

    while (ss >> token) {
        if (isdigit(token[0])) {
            tokens.push_back({"Number", token});
        } 

else if (token == "@") 
{
            tokens.push_back({"Symbol", token});
        } 

else if (token == "+" || token == "-") 
{
            tokens.push_back({"Operator", token});
        } 

else if (token.find("discount") == 0) 
{
            tokens.push_back({"Discount Code", token});
        } 

else {
            tokens.push_back({"Item", token});
        }
    }

    return tokens;
}

int main() {
    string input;
    cout << "Enter billing expression: ";
    getline(cin, input);

    vector<Token> tokens = tokenize(input);
    
    // Display tokens
    cout << "\nTokens:\n";
    for (const auto& token : tokens) {
        cout << token.type << ": " << token.value << endl;
    }

    stringstream ss(input);
    vector<Item> items;
    double total = 0;
    string token;
    int discount = 0;

    while (ss >> token) {
        if (isdigit(token[0])) {
            Item item;
            item.quantity = stoi(token);
            ss >> item.name >> token; // Read name and @ symbol
            ss >> item.price;
            total += item.quantity * item.price;
            items.push_back(item);
        } else if (token.find("discount") == 0) {
            discount = stoi(token.substr(8)); // Extract discount %
        }
    }

    total = applyDiscount(total, discount);

    cout << "\nTotal Bill: " << fixed << total << endl;
    return 0;
}