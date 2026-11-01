# Budget Manager

A C console application for recording a small business's income, expenses and employee costs. Built as a Computer Science course project, with a restaurant used as the example business.

## What it does

- Stores employee names, roles, hourly rates and hours worked.
- Records variable expenses and income against a month.
- Maintains a separate list of recurring monthly expenses.
- Produces monthly and annual income, cost and profit summaries.
- Saves records to text files and loads them on the next run.

## Build and run

The project contains one source file, `Source.c`.

With GCC:

```bash
gcc -std=c11 -Wall -Wextra Source.c -o budget-manager
./budget-manager
```

With Visual Studio's Developer Command Prompt on Windows:

```bat
cl /W4 /TC Source.c /Fe:budget-manager.exe
budget-manager.exe
```

You can also add `Source.c` to an empty Visual Studio console project.

## Try it

1. Start the program and enter a business name.
2. Choose **Manage Specific Month** and select a month from 1 to 12.
3. Add an income entry and an expense, then open **Monthly Summary**.
4. Return to the main menu and select **Save & Exit**.
5. Restart from the same working directory to load the saved records.

The program creates these semicolon-separated files in its working directory:

| File | Contents |
| --- | --- |
| `employees.txt` | Employee details, hourly rates and hours |
| `expenses.txt` | Expense category, description, amount and month |
| `fixed_expenses.txt` | Recurring expense names and monthly amounts |
| `incomes.txt` | Income source, amount and month |

## Code organization

The application uses four structs: `Employee`, `Expense`, `Income` and `FixedExpense`. Each record collection grows through `realloc`. Separate functions handle menus, persistence and summary calculations.

## Model assumptions and limitations

Records are grouped by month number, without a year field. Employee hours are stored globally rather than per month. Monthly summaries reuse those hours, while the annual summary counts the stored salary total once; it is not a payroll history.

Amounts use floating-point numbers. Input bounds, allocation failures and file-write failures need stronger handling before this could be used with real business data. The on-screen expense-ratio comments are simple hard-coded rules, not financial advice.

This project focuses on procedural programming, dynamic arrays, data persistence and aggregation. It does not currently include automated tests.

[More projects](https://github.com/omerbenguigui)
