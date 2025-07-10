#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

struct Transaction {
    std::string type; // "Income" or "Expense"
    std::string description;
    double amount;
};

class FinanceManager {
private:
    std::vector<Transaction> transactions;

public:
    void addTransaction(const std::string& type, const std::string& description, double amount) {
        transactions.push_back({type, description, amount});
    }

    void showTransactions() const {
        std::cout << "\n--- Transaction History ---\n";
        for (const auto& t : transactions) {
            std::cout << std::setw(10) << t.type << " | "
                      << std::setw(20) << t.description << " | "
                      << std::fixed << std::setprecision(2) << t.amount << "\n";
        }
    }

    double calculateBalance() const {
        double balance = 0.0;
        for (const auto& t : transactions) {
            if (t.type == "Income") balance += t.amount;
            else if (t.type == "Expense") balance -= t.amount;
        }
        return balance;
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream file(filename);
        for (const auto& t : transactions) {
            file << t.type << "," << t.description << "," << t.amount << "\n";
        }
        file.close();
    }

    void loadFromFile(const std::string& filename) {
        transactions.clear();
        std::ifstream file(filename);
        std::string type, description;
        double amount;
        while (file.good()) {
            getline(file, type, ',');
            getline(file, description, ',');
            file >> amount;
            file.ignore(); // skip newline
            if (!type.empty()) {
                transactions.push_back({type, description, amount});
            }
        }
        file.close();
    }
};

int main() {
    FinanceManager manager;
    int choice;
    std::string desc, type;
    double amount;

    manager.loadFromFile("finance_data.txt");

    do {
        std::cout << "\n--- Personal Finance App ---\n";
        std::cout << "1. Add Income\n2. Add Expense\n3. View Transactions\n4. View Balance\n5. Save & Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;
        std::cin.ignore(); // clear newline

        switch (choice) {
            case 1:
                std::cout << "Enter description: ";
                getline(std::cin, desc);
                std::cout << "Enter amount: ";
                std::cin >> amount;
                manager.addTransaction("Income", desc, amount);
                break;
            case 2:
                std::cout << "Enter description: ";
                getline(std::cin, desc);
                std::cout << "Enter amount: ";
                std::cin >> amount;
                manager.addTransaction("Expense", desc, amount);
                break;
            case 3:
                manager.showTransactions();
                break;
            case 4:
                std::cout << "Current Balance: ₹" << manager.calculateBalance() << "\n";
                break;
            case 5:
                manager.saveToFile("finance_data.txt");
                std::cout << "Data saved. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid option.\n";
        }
    } while (choice != 5);

    return 0;
}



