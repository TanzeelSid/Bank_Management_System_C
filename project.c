#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Define a structure to hold account information
struct Account {
    int accountNumber;
    char name[50];
    char password[20];
    float balance;
};

// Maximum number of accounts
#define MAX_ACCOUNTS 100
struct Account accounts[MAX_ACCOUNTS];
int accountCount = 0;
int loggedInIndex = -1; // To track the logged-in user (-1 means no user logged in)

// Function prototypes
void createAccount();
void loginAccount();
void logoutAccount();
void depositMoney();
void withdrawMoney();
void transferMoney();
void displayAccountDetails();
void exitSystem();
bool getConfirmation(const char *message);
int getValidatedInteger(const char *message);

int main() {
    int choice;

    do {
        printf("\n=== Banking Management System ===\n");
        if (loggedInIndex == -1) {
            printf("1. Create Account\n");
            printf("2. Login to Account\n");
            printf("3. Exit\n");
        } else {
            printf("1. Deposit Money\n");
            printf("2. Withdraw Money\n");
            printf("3. Transfer Money\n");
            printf("4. Display Account Details\n");
            printf("5. Logout\n");
        }
        choice = getValidatedInteger("Enter your choice: ");

        if (loggedInIndex == -1) {
            // Menu for non-logged-in users
            switch (choice) {
                case 1: createAccount(); break;
                case 2: loginAccount(); break;
                case 3: exitSystem(); break;
                default: printf("Invalid choice! Please try again.\n");
            }
        } else {
            // Menu for logged-in users
            switch (choice) {
                case 1: depositMoney(); break;
                case 2: withdrawMoney(); break;
                case 3: transferMoney(); break;
                case 4: displayAccountDetails(); break;
                case 5: logoutAccount(); break;
                default: printf("Invalid choice! Please try again.\n");
            }
        }
    } while (choice != 3 || loggedInIndex != -1);

    return 0;
}

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Cannot create more accounts. Limit reached.\n");
        return;
    }

    struct Account newAccount;
    newAccount.accountNumber = accountCount + 1;

    printf("Enter name: ");
    scanf(" %[^\n]", newAccount.name);
    printf("Set a password: ");
    scanf(" %s", newAccount.password);
    newAccount.balance = 0;

    accounts[accountCount] = newAccount;
    accountCount++;

    printf("\nAccount created successfully!\n");
    printf("Account Number: %d\n", newAccount.accountNumber);
    printf("Name: %s\n", newAccount.name);
    printf("Password: %s\n", newAccount.password);

    if (!getConfirmation("Do you want to return to the main menu? (1 for Yes, 0 for No): ")) {
        exitSystem();
    }
}

void loginAccount() {
    int accNum = getValidatedInteger("Enter account number: ");
    char password[20];

    printf("Enter password: ");
    scanf(" %s", password);

    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accNum && strcmp(accounts[i].password, password) == 0) {
            printf("Login successful! Welcome, %s.\n", accounts[i].name);
            loggedInIndex = i; // Store the logged-in account index
            return;
        }
    }

    printf("Invalid account number or password.\n");

    if (!getConfirmation("Do you want to return to the main menu? (1 for Yes, 0 for No): ")) {
        exitSystem();
    }
}

void logoutAccount() {
    printf("Logged out successfully. See you next time!\n");
    loggedInIndex = -1; // Reset the logged-in index
}

void depositMoney() {
    if (loggedInIndex == -1) return;

    float amount;
    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    if (amount > 0) {
        accounts[loggedInIndex].balance += amount;
        printf("Deposit successful! New balance: %.2f\n", accounts[loggedInIndex].balance);
    } else {
        printf("Invalid amount.\n");
    }

    if (!getConfirmation("Do you want to return to the main menu? (1 for Yes, 0 for No): ")) {
        exitSystem();
    }
}

void withdrawMoney() {
    if (loggedInIndex == -1) return;

    float amount;
    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    if (amount > 0 && accounts[loggedInIndex].balance >= amount) {
        accounts[loggedInIndex].balance -= amount;
        printf("Withdrawal successful! New balance: %.2f\n", accounts[loggedInIndex].balance);
    } else {
        printf("Insufficient balance or invalid amount.\n");
    }

    if (!getConfirmation("Do you want to return to the main menu? (1 for Yes, 0 for No): ")) {
        exitSystem();
    }
}

void transferMoney() {
    if (loggedInIndex == -1) return;

    int toAccount = getValidatedInteger("Enter account number to transfer to: ");
    int toIndex = -1;
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == toAccount) {
            toIndex = i;
            break;
        }
    }

    if (toIndex == -1) {
        printf("Recipient account not found.\n");
        return;
    }

    float amount;
    printf("Enter amount to transfer: ");
    scanf("%f", &amount);

    if (amount > 0 && accounts[loggedInIndex].balance >= amount) {
        accounts[loggedInIndex].balance -= amount;
        accounts[toIndex].balance += amount;
        printf("Transfer successful! Your new balance: %.2f\n", accounts[loggedInIndex].balance);
    } else {
        printf("Insufficient balance or invalid amount.\n");
    }

    if (!getConfirmation("Do you want to return to the main menu? (1 for Yes, 0 for No): ")) {
        exitSystem();
    }
}

void displayAccountDetails() {
    if (loggedInIndex == -1) return;

    printf("\n=== Account Details ===\n");
    printf("Account Number: %d\n", accounts[loggedInIndex].accountNumber);
    printf("Name: %s\n", accounts[loggedInIndex].name);
    printf("Balance: %.2f\n", accounts[loggedInIndex].balance);

    if (!getConfirmation("Do you want to return to the main menu? (1 for Yes, 0 for No): ")) {
        exitSystem();
    }
}

void exitSystem() {
    printf("Exiting the system. Thank you!\n");
    exit(0);
}

bool getConfirmation(const char *message) {
    int choice;
    printf("%s", message);
    scanf("%d", &choice);
    return choice == 1;
}

int getValidatedInteger(const char *message) {
    int value;
    char buffer[100];

    while (true) {
        printf("%s", message);
        if (scanf("%d", &value) == 1) {
            return value;
        } else {
            // Clear invalid input
            scanf("%s", buffer);
            printf("Invalid input. Please enter a number.\n");
        }
    }
}