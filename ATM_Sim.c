#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct Account
{
    long int acc_no;
    int pin;
    char name[50];
    float balance;
} acc;

void clearScreen();
void addDelay(int seconds);
void mainMenu();
int login(long int acc_no, int pin);
void createAccount();
void loginMenu();
void showProfile(long int acc_no);
void withdrawMoney(int amt, int pin, long int acc_no);
void depositMoney(int amt, int pin, long int acc_no);
int PinAuth(int pin, long int acc_no);
void changePin(int pin, long int acc_no);
void deleteAccount(long int acc_no);

int main()
{
    int choice, login_pin, authenticate, login_choice, withdraw_amt, withdraw_pin, deposit_amt, deposit_pin, change_pin_input, pin_auth, new_pin, del_acc_pin;
    char del_choice;
    long int login_acc;

    do
    {
        clearScreen();
        mainMenu();
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1:
                printf("Enter Account number: ");
                scanf("%ld", &login_acc);
                printf("Enter PIN: ");
                scanf("%d", &login_pin);
                authenticate = login(login_acc, login_pin);
                if (authenticate==1)
                {
                    do
                    {
                        clearScreen();
                        loginMenu();
                        printf("Enter Choice: ");
                        scanf("%d", &login_choice);

                        switch (login_choice)
                        {
                            case 1:
                                showProfile(login_acc);
                                addDelay(4);
                                break;

                            case 2:
                                printf("Enter amount to withdraw: ");
                                scanf("%d", &withdraw_amt);
                                printf("Enter PIN: ");
                                scanf("%d", &withdraw_pin);
                                withdrawMoney(withdraw_amt, withdraw_pin, login_acc);
                                addDelay(3);
                                break;

                            case 3:
                                printf("Enter amount to deposit: ");
                                scanf("%d", &deposit_amt);
                                printf("Enter PIN: ");
                                scanf("%d", &deposit_pin);
                                depositMoney(deposit_amt, deposit_pin, login_acc);
                                addDelay(3);
                                break;

                            case 4:
                                printf("Enter your existing PIN: ");
                                scanf("%d", &change_pin_input);
                                pin_auth = PinAuth(change_pin_input, login_acc);
                                if (pin_auth == 1)
                                {
                                    printf("Enter new PIN: ");
                                    scanf("%d", &new_pin);
                                    changePin(new_pin, login_acc);
                                    addDelay(3);
                                } else 
                                {
                                    printf("Incorrect PIN'\n");
                                    addDelay(3);
                                }
                                break;

                            case 5:
                                login_acc = 0;
                                login_pin = 0;
                                printf("Successfully Logout!\n");
                                login_choice = 5;
                                addDelay(3);
                                break;

                            case 6:
                                printf("Are you sure you want to delete your account? (Y/N): ");
                                scanf(" %c", &del_choice);
                                if (del_choice=='Y')
                                {
                                    printf("Enter PIN: ");
                                    scanf("%d", &del_acc_pin);
                                    pin_auth = PinAuth(del_acc_pin, login_acc);
                                    if (pin_auth == 1)
                                    {
                                        deleteAccount(login_acc);
                                        login_choice = 5;
                                        addDelay(3);
                                    } else {
                                        printf("Incorrect PIN'\n");
                                        addDelay(3);
                                    }
                                }
                                else if (del_choice == 'N')
                                {
                                    break;
                                }
                                else {
                                    printf("Invaid input.\n");
                                    addDelay(3);
                                }
                                break;

                            default: 
                                printf("INVALID INPUT");
                                addDelay(3);
                        }

                    } while (login_choice != 5);
                    
                } else 
                {
                    printf("Invalid login credentials.\n");
                    addDelay(3);
                }
                break;

            case 2:
                createAccount();
                addDelay(3);
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("INVALID INPUT\n");
                addDelay(3);
        }

    } while (choice!=3);

    return 0;
}

void mainMenu()
{
    printf("---MAIN MENU---\n");
    printf("1. Login\n");
    printf("2. Create Account\n");
    printf("3. Exit\n");
}

int login(long int acc_no, int pin)
{
    FILE *file = fopen("bank.dat", "rb");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    acc temp;
    int check = 0;
    while (fread(&temp, sizeof(acc), 1, file))
    {
        if (temp.acc_no==acc_no && temp.pin==pin)
        {
            check = 1;
            break;
        }
    }

    fclose(file);
    return check;
}

void createAccount()
{
    acc newAcc;
    printf("Enter Name: ");
    scanf("%s", &newAcc.name);
    printf("Enter Account number: ");
    scanf("%ld", &newAcc.acc_no);
    printf("Set a PIN: ");
    scanf("%d", &newAcc.pin);
    newAcc.balance = 0.00;

    FILE *file = fopen("bank.dat", "ab+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    acc temp;
    int acc_match = 0;
    while (fread(&temp, sizeof(acc), 1, file) == 1)
    {
        if (temp.acc_no==newAcc.acc_no)
        {
            acc_match = 1;
            printf("Account with this number already exists.\n");
            fclose(file);
            return;
        } 
    }

    fwrite(&newAcc, sizeof(acc), 1, file);
    printf("Account created successfully!\n");

    fclose(file);
}

void loginMenu()
{
    printf("-----MENU------\n");
    printf("1. Show profile\n");
    printf("2. Withdraw Money\n");
    printf("3. Deposit Money\n");
    printf("4. Change PIN\n");
    printf("5. Logout\n");
    printf("6. Delete Account\n");
}

void showProfile(long int acc_no)
{
    FILE *file = fopen("bank.dat", "rb");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    acc temp;
    while (fread(&temp, sizeof(acc), 1, file))
    {
        if (temp.acc_no == acc_no)
        {
            printf("Name: %s\n", temp.name);
            printf("Account Number: %ld\n", temp.acc_no);
            printf("Balance: %.2f\n", temp.balance);
            break;
        }
    }

    fclose(file);
}

void withdrawMoney(int amt, int pin, long int acc_no)
{
    FILE *file = fopen("bank.dat", "rb+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    acc temp;
    int found = 0;
    while(fread(&temp, sizeof(acc), 1, file))
    {
        if (temp.acc_no==acc_no && temp.pin==pin)
        {
            found = 1;
            if (temp.balance == 0 || temp.balance < amt)
            {
                printf("Insufficient balance.\n");
                break;
            }
            else
            {
                fseek(file, -sizeof(acc), SEEK_CUR);
                temp.balance -= amt;
                fwrite(&temp, sizeof(acc), 1, file);
                break;
            }
        }
    }
    if (found==1)
    {
        printf("%d amount is debited from your account successfully!\n", amt);
    }
    else printf("Incorrect PIN.\n");
    fclose(file);
}

void depositMoney(int amt, int pin, long int acc_no)
{
    FILE *file = fopen("bank.dat", "rb+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    acc temp;
    int found = 0;
    while(fread(&temp, sizeof(acc), 1, file))
    {
        if (temp.acc_no==acc_no && temp.pin==pin)
        {
            fseek(file, -sizeof(acc), SEEK_CUR);
            temp.balance += amt;
            fwrite(&temp, sizeof(acc), 1, file);
            found = 1;
            break;
        }
    }
    if (found==1)
    {
        printf("%d amount is credited to your account successfully!\n", amt);
    }
    else printf("Incorrect PIN.\n");
    fclose(file);
}

int PinAuth(int pin, long int acc_no)
{
    FILE *file = fopen("bank.dat", "rb");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    acc temp;
    int check = 0;
    while(fread(&temp, sizeof(acc), 1, file))
    {
        if (temp.acc_no==acc_no && temp.pin==pin)
        {
            check = 1;
            break;
        }
    }
    fclose(file);
    return check;
}

void changePin(int pin, long int acc_no)
{
    FILE *file = fopen("bank.dat", "rb+");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    acc temp;
    while(fread(&temp, sizeof(acc), 1, file))
    {
        if (temp.acc_no==acc_no)
        {
            temp.pin = pin;
            fseek(file, -sizeof(acc), SEEK_CUR);
            fwrite(&temp, sizeof(acc), 1, file);
            printf("PIN changed successfully!\n");
            break;
        }
    }
    
    fclose(file);
}

void deleteAccount(long int acc_no)
{
    FILE *file = fopen("bank.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (file == NULL || temp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    acc temp_acc;
    int found = 0;
    while (fread(&temp_acc, sizeof(acc), 1, file)==1)
    {
        if (temp_acc.acc_no != acc_no)
        {
            fwrite(&temp_acc, sizeof(acc), 1, temp);
        } else found=1;
    }

    fclose(file);
    fclose(temp);

    remove("bank.dat");
    rename("temp.dat", "bank.dat");

    if (found==1)
    {
        printf("Account deleted successfully.\n");
    }
    
}

void clearScreen()
{
    system("cls");
}

void addDelay(int seconds)
{
    Sleep(seconds * 1000);
}