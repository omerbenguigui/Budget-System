#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ====== Structs ======
typedef struct {
    char name[50];
    char role[50];
    float hourlyRate;
    int hoursWorked;
} Employee;

typedef struct {
    char category[50];
    char description[100];
    float amount;
    int month;
} Expense;

typedef struct {
    char source[50];
    float amount;
    int month;
} Income;

typedef struct {
    char name[50];
    float monthlyAmount;
} FixedExpense;

// ====== Global Variables ======
Employee* employees = NULL;
int employeeCount = 0, employeeCapacity = 0;

Expense* expenses = NULL;
int expenseCount = 0, expenseCapacity = 0;

Income* incomes = NULL;
int incomeCount = 0, incomeCapacity = 0;

FixedExpense* fixedExpenses = NULL;
int fixedCount = 0, fixedCapacity = 0;

char businessName[50];
// ====== Utility Functions ======
void waitForEnter() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void welcomeScreen() {
    printf("==============================================\n");
    printf("       Welcome to the Budget Management System\n");
    printf("==============================================\n\n");
    printf("Manage employees, expenses, incomes and reports\n");
    printf("for your restaurant business - quickly and smartly!\n\n");
    printf("Press Enter to start...");
    waitForEnter();
}

void getBusinessName() {
    printf("\nPlease enter your business name: ");
    scanf(" %[^\n]", businessName);
}

void saveAllData() {
    FILE* f;

    f = fopen("employees.txt", "w");
    for (int i = 0; i < employeeCount; i++)
        fprintf(f, "%s;%s;%.2f;%d\n", employees[i].name, employees[i].role, employees[i].hourlyRate, employees[i].hoursWorked);
    fclose(f);

    f = fopen("expenses.txt", "w");
    for (int i = 0; i < expenseCount; i++)
        fprintf(f, "%s;%s;%.2f;%d\n", expenses[i].category, expenses[i].description,
            expenses[i].amount, expenses[i].month);
    fclose(f);

    f = fopen("fixed_expenses.txt", "w");
    for (int i = 0; i < fixedCount; i++)
        fprintf(f, "%s;%.2f\n", fixedExpenses[i].name, fixedExpenses[i].monthlyAmount);
    fclose(f);

    f = fopen("incomes.txt", "w");
    for (int i = 0; i < incomeCount; i++)
        fprintf(f, "%s;%.2f;%d\n", incomes[i].source, incomes[i].amount, incomes[i].month);
    fclose(f);
}

void loadAllData() {
    FILE* f;
    char name[50], role[50], category[50], description[100], source[50];
    float amount, rate;
    int hours, month;

    f = fopen("employees.txt", "r");
    while (f && fscanf(f, " %[^;];%[^;];%f;%d\n", name, role, &rate, &hours) == 4) {
        if (employeeCount == employeeCapacity) {
            employeeCapacity = employeeCapacity == 0 ? 10 : employeeCapacity * 2;
            employees = realloc(employees, sizeof(Employee) * employeeCapacity);
        }
        strcpy(employees[employeeCount].name, name);
        strcpy(employees[employeeCount].role, role);
        employees[employeeCount].hourlyRate = rate;
        employees[employeeCount].hoursWorked = hours;
        employeeCount++;
    }
    if (f) fclose(f);

    f = fopen("expenses.txt", "r");
    while (f && fscanf(f, " %[^;];%[^;];%f;%d\n", category, description, &amount, &month) == 4) {
        if (expenseCount == expenseCapacity) {
            expenseCapacity = expenseCapacity == 0 ? 10 : expenseCapacity * 2;
            expenses = realloc(expenses, sizeof(Expense) * expenseCapacity);
        }
        strcpy(expenses[expenseCount].category, category);
        strcpy(expenses[expenseCount].description, description);
        expenses[expenseCount].amount = amount;
        expenses[expenseCount].month = month;
        expenseCount++;
    }
    if (f) fclose(f);

    f = fopen("fixed_expenses.txt", "r");
    while (f && fscanf(f, " %[^;];%f\n", name, &amount) == 2) {
        if (fixedCount == fixedCapacity) {
            fixedCapacity = fixedCapacity == 0 ? 10 : fixedCapacity * 2;
            fixedExpenses = realloc(fixedExpenses, sizeof(FixedExpense) * fixedCapacity);
        }
        strcpy(fixedExpenses[fixedCount].name, name);
        fixedExpenses[fixedCount].monthlyAmount = amount;
        fixedCount++;
    }
    if (f) fclose(f);

    f = fopen("incomes.txt", "r");
    while (f && fscanf(f, " %[^;];%f;%d\n", source, &amount, &month) == 3) {
        if (incomeCount == incomeCapacity) {
            incomeCapacity = incomeCapacity == 0 ? 10 : incomeCapacity * 2;
            incomes = realloc(incomes, sizeof(Income) * incomeCapacity);
        }
        strcpy(incomes[incomeCount].source, source);
        incomes[incomeCount].amount = amount;
        incomes[incomeCount].month = month;
        incomeCount++;
    }
    if (f) fclose(f);
}
// ====== Employees ======
void addEmployee() {
    if (employeeCount == employeeCapacity) {
        employeeCapacity = employeeCapacity == 0 ? 10 : employeeCapacity * 2;
        employees = realloc(employees, sizeof(Employee) * employeeCapacity);
    }
    printf("Name: ");
    scanf(" %[^\n]", employees[employeeCount].name);
    printf("Role: ");
    scanf(" %[^\n]", employees[employeeCount].role);
    printf("Hourly rate: ");
    scanf("%f", &employees[employeeCount].hourlyRate);
    printf("Hours worked: ");
    scanf("%d", &employees[employeeCount].hoursWorked);
    employeeCount++;
    printf("Employee added.\n");
}

void printEmployees() {
    printf("\n--- Employees ---\n");
    for (int i = 0; i < employeeCount; i++) {
        printf("%d. %s (%s) - %.2f x %d hours\n", i + 1,
            employees[i].name, employees[i].role,
            employees[i].hourlyRate, employees[i].hoursWorked);
    }
}

void employeeMenu() {
    int ch;
    do {
        printf("\n--- Employee Menu ---\n");
        printf("1. Add Employee\n2. View Employees\n3. Back\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1) addEmployee();
        else if (ch == 2) printEmployees();
    } while (ch != 3);
}




// ====== Fixed Expenses ======
void addFixedMonthlyExpense() {
    if (fixedCount == fixedCapacity) {
        fixedCapacity = fixedCapacity == 0 ? 10 : fixedCapacity * 2;
        fixedExpenses = realloc(fixedExpenses, sizeof(FixedExpense) * fixedCapacity);
    }
    printf("Fixed expense name: ");
    scanf(" %[^\n]", fixedExpenses[fixedCount].name);
    printf("Monthly amount: ");
    scanf("%f", &fixedExpenses[fixedCount].monthlyAmount);
    fixedCount++;
    printf("Fixed monthly expense added.\n");
}

void printFixedExpenses() {
    float total = 0;
    printf("\n--- Fixed Monthly Expenses ---\n");
    for (int i = 0; i < fixedCount; i++) {
        printf("%d. %s - %.2f\n", i + 1, fixedExpenses[i].name, fixedExpenses[i].monthlyAmount);
        total += fixedExpenses[i].monthlyAmount;
    }
    printf("Total Fixed Expenses: %.2f\n", total);
}

void fixedExpensesMenu() {
    int ch;
    do {
        printf("\n--- Fixed Expenses Menu ---\n");
        printf("1. Add Fixed Expense\n2. View Fixed Expenses\n3. Back\nChoice: ");
        scanf("%d", &ch);
        if (ch == 1) addFixedMonthlyExpense();
        else if (ch == 2) printFixedExpenses();
    } while (ch != 3);
}
// ====== Monthly Logic ======
void addMonthlyExpense(int month) {
    if (expenseCount == expenseCapacity) {
        expenseCapacity = expenseCapacity == 0 ? 10 : expenseCapacity * 2;
        expenses = realloc(expenses, sizeof(Expense) * expenseCapacity);
    }
    printf("Category: ");
    scanf(" %[^\n]", expenses[expenseCount].category);
    printf("Description: ");
    scanf(" %[^\n]", expenses[expenseCount].description);
    printf("Total Cost: ");
    scanf("%f", &expenses[expenseCount].amount);
    expenses[expenseCount].month = month;
    expenseCount++;
    printf("Expense added for month %d.\n", month);
}

void addMonthlyIncome(int month) {
    if (incomeCount == incomeCapacity) {
        incomeCapacity = incomeCapacity == 0 ? 10 : incomeCapacity * 2;
        incomes = realloc(incomes, sizeof(Income) * incomeCapacity);
    }
    printf("Source: ");
    scanf(" %[^\n]", incomes[incomeCount].source);
    printf("Total Cost: ");
    scanf("%f", &incomes[incomeCount].amount);
    incomes[incomeCount].month = month;
    incomeCount++;
    printf("Income added for month %d.\n", month);
}

void viewMonthlyExpenses(int month) {
    float total = 0;
    printf("\n--- Expenses for Month %d ---\n", month);
    for (int i = 0, count = 0; i < expenseCount; i++) {
        if (expenses[i].month == month) {
            printf("%d. [%s] %s - %.2f\n", ++count,
                expenses[i].category, expenses[i].description,
                expenses[i].amount);
            total += expenses[i].amount;
        }
    }
    printf("Total Variable Expenses: %.2f\n", total);
}

void viewMonthlyIncomes(int month) {
    float total = 0;
    printf("\n--- Incomes for Month %d ---\n", month);
    for (int i = 0, count = 0; i < incomeCount; i++) {
        if (incomes[i].month == month) {
            printf("%d. [%s] %.2f\n", ++count, incomes[i].source, incomes[i].amount);
            total += incomes[i].amount;
        }
    }
    printf("Total Income: %.2f\n", total);
}

void monthlySummary(int month) {
    float salary = 0, variable = 0, incomeTotal = 0, fixed = 0;

    for (int i = 0; i < expenseCount; i++)
        if (expenses[i].month == month) variable += expenses[i].amount;

    for (int i = 0; i < incomeCount; i++)
        if (incomes[i].month == month) incomeTotal += incomes[i].amount;

    for (int i = 0; i < fixedCount; i++)
        fixed += fixedExpenses[i].monthlyAmount;

    for (int i = 0; i < employeeCount; i++)
        salary += employees[i].hourlyRate * employees[i].hoursWorked;

    float total = salary + variable + fixed;
    float profit = incomeTotal - total;

    printf("\n========== Monthly Summary (Month %d) ==========\n", month);
    printf("Total Income: %.2f\n", incomeTotal);
    printf("Salaries: %.2f | Variable: %.2f | Fixed: %.2f\n", salary, variable, fixed);
    printf("Total Expenses: %.2f\n", total);
    printf("Net Profit: %.2f\n", profit);
    printf("=====================================\n");

    // --- Feedback Section ---
    printf("\n--- Feedback & Analysis ---\n");

    float salaryRatio = (incomeTotal > 0) ? (salary / incomeTotal) * 100 : 0;
    float varRatio = (incomeTotal > 0) ? (variable / incomeTotal) * 100 : 0;
    float fixedRatio = (incomeTotal > 0) ? (fixed / incomeTotal) * 100 : 0;

    if (salaryRatio > 40)
        printf("- Salaries are %.1f%% of income - consider optimizing staff hours.\n", salaryRatio);
    else if (salaryRatio > 25)
        printf("- Salaries are %.1f%% of income - reasonable and controlled.\n", salaryRatio);
    else
        printf("- Salaries are %.1f%% of income - excellent efficiency!\n", salaryRatio);

    if (varRatio > 50)
        printf("- Variable expenses are %.1f%% - high. Check your suppliers or inventory usage.\n", varRatio);
    else
        printf("- Variable expenses are %.1f%% - seems balanced.\n", varRatio);

    if (fixedRatio > 30)
        printf("- Fixed expenses are %.1f%% - consider renegotiating rent or services.\n", fixedRatio);
    else
        printf("- Fixed expenses are %.1f%% - under control.\n", fixedRatio);

    if (profit > 5000)
        printf("Excellent month! Strong financial performance.\n");
    else if (profit > 1000)
        printf("Positive month. You’re on the right track.\n");
    else if (profit >= 0)
        printf("Slight profit. Worth reviewing minor optimizations.\n");
    else if (profit >= -1000)
        printf("Small loss - try to reduce avoidable expenses.\n");
    else
        printf("Major loss - urgent financial review is recommended.\n");
}

void resetMonthData(int month) {
    for (int i = 0; i < expenseCount; ) {
        if (expenses[i].month == month) {
            expenses[i] = expenses[--expenseCount];
        }
        else i++;
    }
    for (int i = 0; i < incomeCount; ) {
        if (incomes[i].month == month) {
            incomes[i] = incomes[--incomeCount];
        }
        else i++;
    }
    printf("All data for month %d has been reset.\n", month);
}

void manageMonthMenu(int month) {
    int choice;
    do {
        printf("\n--- Monthly Menu for Month %d ---\n", month);
        printf("1. Manage Employees\n");
        printf("2. Add Expenses\n");
        printf("3. Add Incomes\n");
        printf("4. View Expenses\n");
        printf("5. View Incomes\n");
        printf("6. Monthly Summary\n");
        printf("7. Reset This Month\n");
        printf("8. Back\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: employeeMenu(); break;
        case 2: addMonthlyExpense(month); break;
        case 3: addMonthlyIncome(month); break;
        case 4: viewMonthlyExpenses(month); break;
        case 5: viewMonthlyIncomes(month); break;
        case 6: monthlySummary(month); break;
        case 7: resetMonthData(month); break;
        }
    } while (choice != 8);
}

void annualSummary() {
    float incomeTotal = 0, expenseTotal = 0, salaryTotal = 0, fixedTotal = 0;
    for (int i = 0; i < incomeCount; i++) incomeTotal += incomes[i].amount;
    for (int i = 0; i < expenseCount; i++) expenseTotal += expenses[i].amount;
    for (int i = 0; i < fixedCount; i++) fixedTotal += fixedExpenses[i].monthlyAmount * 12;
    for (int i = 0; i < employeeCount; i++) salaryTotal += employees[i].hourlyRate * employees[i].hoursWorked;

    float total = expenseTotal + fixedTotal + salaryTotal;
    float profit = incomeTotal - total;

    printf("\n========== Annual Summary ==========\n");
    printf("Total Income: %.2f\n", incomeTotal);
    printf("Salaries: %.2f | Variable: %.2f | Fixed (Year): %.2f\n", salaryTotal, expenseTotal, fixedTotal);
    printf("Total Expenses: %.2f\n", total);
    if (profit >= 0)
        printf("Yearly Profit: %.2f\n", profit);
    else
        printf("Yearly Loss: %.2f\n", -profit);
}

// ====== Main Menu + Main ======
void mainMenu() {
    int choice;
    do {
        printf("\n==== Budget Manager - %s ====\n", businessName);
        printf("1. Annual Summary\n");
        printf("2. Manage Specific Month (1-12)\n");
        printf("3. Manage Fixed Expenses\n");
        printf("4. Reset All\n");
        printf("5. Save & Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: annualSummary(); break;
        case 2: {
            int month;
            printf("Enter month (1-12): ");
            scanf("%d", &month);
            if (month >= 1 && month <= 12)
                manageMonthMenu(month);
            else
                printf("Invalid month.\n");
            break;
        }
        case 3: fixedExpensesMenu(); break;
        case 4:
            employeeCount = 0;
            expenseCount = 0;
            incomeCount = 0;
            fixedCount = 0;
            printf("All data has been reset.\n");
            break;
        case 5:
            saveAllData();
            printf("Data saved. Goodbye!\n");
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);
}

int main() {
    welcomeScreen();
    getBusinessName();
    loadAllData();
    mainMenu();

    free(employees);
    free(expenses);
    free(incomes);
    free(fixedExpenses);
    return 0;
}
