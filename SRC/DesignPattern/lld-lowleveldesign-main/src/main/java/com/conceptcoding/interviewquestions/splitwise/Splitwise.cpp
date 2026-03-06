#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <numeric>

using namespace std;

// ====================== USER ======================
class User
{
    string id;
    string name;

public:
    User(string id, string name) : id(id), name(name) {}
    string getId() { return id; }
    string getName() { return name; }
};

// ====================== SPLIT ======================
class Split
{
    shared_ptr<User> user;
    double amount;

public:
    Split(shared_ptr<User> u, double amt) : user(u), amount(amt) {}
    shared_ptr<User> getUser() { return user; }
    double getAmount() { return amount; }
};

// ====================== EXPENSE TYPES ======================
enum ExpenseSplitType
{
    EQUAL,
    EXACT,
    PERCENTAGE,
    SHARE
};

// ====================== EXPENSE ======================
class Expense
{
public:
    string id;
    string description;
    double amount;
    shared_ptr<User> paidBy;
    ExpenseSplitType type;
    vector<shared_ptr<Split>> splits;

    Expense(string id, string desc, double amt, shared_ptr<User> paidByUser,
            ExpenseSplitType t, vector<shared_ptr<Split>> &sp)
        : id(id), description(desc), amount(amt),
          paidBy(paidByUser), type(t), splits(sp) {}
};

// ====================== BALANCE SHEET ======================
class BalanceSheet
{
public:
    // balance[A][B] = A owes B this much money
    map<string, map<string, double>> balance;

    void updateBalance(const string &paidBy, vector<shared_ptr<Split>> &splits)
    {
        for (auto &split : splits)
        {
            string owedBy = split->getUser()->getId();
            double amt = split->getAmount();

            if (owedBy == paidBy)
                continue;

            balance[owedBy][paidBy] += amt; // owedBy -> paidBy
            balance[paidBy][owedBy] -= amt; // mirror entry
        }
    }

    void show()
    {
        cout << "\n========== BALANCES ==========\n";
        for (auto &a : balance)
        {
            for (auto &b : a.second)
            {
                if (b.second > 0)
                {
                    cout << a.first << " owes " << b.first << " : " << b.second << "\n";
                }
            }
        }
        cout << "==============================\n";
    }

    void showUserBalance(const string &userId)
    {
        cout << "\n---- Balance for " << userId << " ----\n";

        for (auto &entry : balance[userId])
        {
            if (entry.second > 0)
                cout << userId << " owes " << entry.first << " : " << entry.second << endl;
        }

        for (auto &mapEntry : balance)
        {
            if (mapEntry.second[userId] > 0)
                cout << mapEntry.first << " owes " << userId << " : "
                     << mapEntry.second[userId] << endl;
        }
    }
};

// ====================== EXPENSE CONTROLLER ======================
class ExpenseController
{
    shared_ptr<BalanceSheet> balanceSheet;

public:
    ExpenseController(shared_ptr<BalanceSheet> bs) : balanceSheet(bs) {}

    vector<shared_ptr<Split>> createEqualSplit(vector<shared_ptr<User>> &users, double amount)
    {
        vector<shared_ptr<Split>> splits;
        double perHead = amount / users.size();
        for (auto &u : users)
            splits.push_back(make_shared<Split>(u, perHead));
        return splits;
    }

    vector<shared_ptr<Split>> createExactSplit(vector<shared_ptr<User>> &users,
                                               vector<double> &exact)
    {
        vector<shared_ptr<Split>> splits;
        for (int i = 0; i < users.size(); i++)
            splits.push_back(make_shared<Split>(users[i], exact[i]));
        return splits;
    }

    vector<shared_ptr<Split>> createPercentSplit(vector<shared_ptr<User>> &users,
                                                 vector<double> &percent, double amount)
    {
        vector<shared_ptr<Split>> splits;
        for (int i = 0; i < percent.size(); i++)
            splits.push_back(make_shared<Split>(users[i], amount * percent[i] / 100));
        return splits;
    }

    vector<shared_ptr<Split>> createShareSplit(vector<shared_ptr<User>> &users,
                                               vector<int> &shares, double amount)
    {
        vector<shared_ptr<Split>> splits;
        int totalShares = accumulate(shares.begin(), shares.end(), 0);
        for (int i = 0; i < users.size(); i++)
            splits.push_back(make_shared<Split>(users[i], amount * shares[i] / totalShares));
        return splits;
    }

    shared_ptr<Expense> createExpense(
        string id, string desc, double amount, shared_ptr<User> paidBy,
        ExpenseSplitType type, vector<shared_ptr<User>> &users,
        vector<double> exact = {}, vector<double> percent = {}, vector<int> share = {})
    {
        vector<shared_ptr<Split>> splits;

        if (type == EQUAL)
            splits = createEqualSplit(users, amount);
        else if (type == EXACT)
            splits = createExactSplit(users, exact);
        else if (type == PERCENTAGE)
            splits = createPercentSplit(users, percent, amount);
        else
            splits = createShareSplit(users, share, amount);

        auto expense = make_shared<Expense>(id, desc, amount, paidBy, type, splits);

        balanceSheet->updateBalance(paidBy->getId(), splits);

        return expense;
    }
};

// ====================== GROUP ======================
class Group
{
public:
    string id;
    string name;
    vector<shared_ptr<User>> members;
    vector<shared_ptr<Expense>> expenses;

    shared_ptr<ExpenseController> expenseController;

    Group(shared_ptr<ExpenseController> ec) : expenseController(ec) {}

    void addMember(shared_ptr<User> user) { members.push_back(user); }

    shared_ptr<Expense> addExpense(string id, string desc, double amount,
                                   shared_ptr<User> paidBy, ExpenseSplitType type,
                                   vector<double> exact = {},
                                   vector<double> percent = {},
                                   vector<int> share = {})
    {
        auto expense = expenseController->createExpense(id, desc, amount,
                                                        paidBy, type, members,
                                                        exact, percent, share);

        expenses.push_back(expense);
        return expense;
    }
};

// ====================== CONTROLLERS ======================
class UserController
{
    vector<shared_ptr<User>> users;

public:
    void addUser(shared_ptr<User> u) { users.push_back(u); }

    shared_ptr<User> getUser(string id)
    {
        for (auto &u : users)
            if (u->getId() == id)
                return u;
        return nullptr;
    }
};

class GroupController
{
    vector<shared_ptr<Group>> groups;

public:
    shared_ptr<Group> createGroup(string id, string name, shared_ptr<User> creator,
                                  shared_ptr<ExpenseController> ec)
    {
        auto g = make_shared<Group>(ec);
        g->id = id;
        g->name = name;
        g->addMember(creator);
        groups.push_back(g);
        return g;
    }

    shared_ptr<Group> getGroup(string id)
    {
        for (auto &g : groups)
            if (g->id == id)
                return g;
        return nullptr;
    }
};

// ====================== SPLITWISE APP ======================
class Splitwise
{
    shared_ptr<BalanceSheet> balanceSheet;
    shared_ptr<ExpenseController> expenseController;
    UserController userController;
    GroupController groupController;

public:
    Splitwise()
    {
        balanceSheet = make_shared<BalanceSheet>();
        expenseController = make_shared<ExpenseController>(balanceSheet);
    }

    void demo()
    {
        auto u1 = make_shared<User>("U1", "Alice");
        auto u2 = make_shared<User>("U2", "Bob");
        auto u3 = make_shared<User>("U3", "Charlie");

        userController.addUser(u1);
        userController.addUser(u2);
        userController.addUser(u3);

        auto group = groupController.createGroup("G1", "Trip", u1, expenseController);
        group->addMember(u2);
        group->addMember(u3);

        group->addExpense("E1", "Lunch", 900, u1, EQUAL);

        vector<double> exact = {400, 300, 200};
        group->addExpense("E2", "Snacks", 900, u2, EXACT, exact);

        balanceSheet->show();
        balanceSheet->showUserBalance("U2");
    }
};

// ====================== MAIN ======================
int main()
{
    Splitwise s;
    s.demo();
    return 0;
}