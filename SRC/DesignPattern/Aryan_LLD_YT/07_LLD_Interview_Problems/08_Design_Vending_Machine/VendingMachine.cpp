#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

using namespace std;

// Forward declarations
class VendingMachineContext;
class VendingMachineState;

// ==================== ENUMS ====================

// Enum representing different types of items in the vending machine
enum class ItemType
{
    COKE,
    PEPSI,
    JUICE,
    SODA
};

// Helper function to convert ItemType to string
string itemTypeToString(ItemType type)
{
    switch (type)
    {
    case ItemType::COKE:
        return "COKE";
    case ItemType::PEPSI:
        return "PEPSI";
    case ItemType::JUICE:
        return "JUICE";
    case ItemType::SODA:
        return "SODA";
    default:
        return "UNKNOWN";
    }
}

// Enum representing different types of Indian coins in the vending machine
enum class Coin
{
    ONE_RUPEE = 1,
    TWO_RUPEES = 2,
    FIVE_RUPEES = 5,
    TEN_RUPEES = 10
};

// Helper function to get coin value
int getCoinValue(Coin coin)
{
    return static_cast<int>(coin);
}

// Helper function to convert Coin to string
string coinToString(Coin coin)
{
    switch (coin)
    {
    case Coin::ONE_RUPEE:
        return "ONE_RUPEE";
    case Coin::TWO_RUPEES:
        return "TWO_RUPEES";
    case Coin::FIVE_RUPEES:
        return "FIVE_RUPEES";
    case Coin::TEN_RUPEES:
        return "TEN_RUPEES";
    default:
        return "UNKNOWN";
    }
}

// ==================== UTILITY CLASSES ====================

// Class representing an item in the vending machine
class Item
{
private:
    ItemType type;
    int price;

public:
    Item() : price(0) {}

    ItemType getType() const { return type; }
    void setType(ItemType t) { type = t; }

    int getPrice() const { return price; }
    void setPrice(int p) { price = p; }
};

// Class representing a slot in the vending machine that holds multiple items
// code will help to identify the item shelf, each shelf will have unique code and same items
class ItemShelf
{
private:
    int code;
    vector<Item> items;
    bool isSoldOut;

public:
    ItemShelf(int codeNum) : code(codeNum), isSoldOut(false) {}

    int getCode() const { return code; }
    void setCode(int c) { code = c; }

    vector<Item> &getItems() { return items; }
    const vector<Item> &getItems() const { return items; }

    bool checkIsSoldOut() const { return isSoldOut; }

    void setIsSoldOut(bool soldOut)
    {
        isSoldOut = soldOut;
    }

    void setItems(const vector<Item> &itemList)
    {
        items = itemList;
        if (isSoldOut)
        {
            setIsSoldOut(false);
        }
    }

    void addItem(const Item &item)
    {
        items.push_back(item);
        if (isSoldOut)
        {
            setIsSoldOut(false);
        }
    }

    void removeItem(const Item &item)
    {
        // Remove first occurrence (simple comparison by price and type)
        for (auto it = items.begin(); it != items.end(); ++it)
        {
            if (it->getType() == item.getType() && it->getPrice() == item.getPrice())
            {
                items.erase(it);
                break;
            }
        }
        if (items.empty())
        {
            setIsSoldOut(true);
        }
    }
};

// Class representing the inventory of the vending machine
class Inventory
{
private:
    vector<ItemShelf> inventory;

public:
    Inventory(int itemCount)
    {
        initialEmptyInventory(itemCount);
    }

    vector<ItemShelf> &getInventory() { return inventory; }
    const vector<ItemShelf> &getInventory() const { return inventory; }

    void setInventory(const vector<ItemShelf> &inv)
    {
        inventory = inv;
    }

    void initialEmptyInventory(int itemCount)
    {
        int startCode = 101;
        for (int i = 0; i < itemCount; i++)
        {
            ItemShelf shelf(startCode);
            inventory.push_back(shelf);
            startCode++;
        }
    }

    void addItem(const Item &item, int codeNumber)
    {
        for (auto &shelf : inventory)
        {
            if (shelf.getCode() == codeNumber)
            {
                shelf.addItem(item);
                return;
            }
        }
        throw runtime_error("Invalid Code");
    }

    Item getItem(int codeNumber)
    {
        for (auto &shelf : inventory)
        {
            if (shelf.getCode() == codeNumber)
            {
                if (shelf.checkIsSoldOut())
                {
                    throw runtime_error("Item already sold out");
                }
                else
                {
                    if (!shelf.getItems().empty())
                    {
                        return shelf.getItems()[0];
                    }
                }
            }
        }
        throw runtime_error("Invalid Code");
    }

    void updateSoldOutItem(int codeNumber)
    {
        for (auto &shelf : inventory)
        {
            if (shelf.getCode() == codeNumber)
            {
                if (shelf.getItems().empty())
                {
                    shelf.setIsSoldOut(true);
                }
            }
        }
    }

    void removeItem(int codeNumber)
    {
        for (auto &shelf : inventory)
        {
            if (shelf.getCode() == codeNumber)
            {
                if (!shelf.getItems().empty())
                {
                    shelf.getItems().erase(shelf.getItems().begin());
                }
                return;
            }
        }
        throw runtime_error("Invalid Code");
    }

    bool hasItems()
    {
        for (const auto &shelf : inventory)
        {
            if (!shelf.checkIsSoldOut())
            {
                return true;
            }
        }
        return false;
    }
};

// ==================== STATE PATTERN ====================

// Interface defining the common methods for all states
class VendingMachineState
{
public:
    virtual ~VendingMachineState() = default;
    virtual string getStateName() const = 0;
    virtual shared_ptr<VendingMachineState> next(VendingMachineContext *context) = 0;
};

// Forward declarations of concrete states
class IdleState;
class HasMoneyState;
class SelectionState;
class DispenseState;
class OutOfStockState;

// Class to hold vending machine data (inventory, coins, selection)
class VendingMachineData
{
private:
    Inventory inventory;
    vector<Coin> coinList;
    int selectedItemCode;

public:
    VendingMachineData(int inventorySize) : inventory(inventorySize), selectedItemCode(0) {}

    Inventory &getInventory() { return inventory; }
    const Inventory &getInventory() const { return inventory; }
    void setInventory(const Inventory &inv) { inventory = inv; }

    vector<Coin> &getCoinList() { return coinList; }
    const vector<Coin> &getCoinList() const { return coinList; }
    void setCoinList(const vector<Coin> &coins) { coinList = coins; }

    int getSelectedItemCode() const { return selectedItemCode; }
    void setSelectedItemCode(int code) { selectedItemCode = code; }

    void resetSelection() { selectedItemCode = 0; }

    int getBalance() const
    {
        int balance = 0;
        for (const auto &coin : coinList)
        {
            balance += getCoinValue(coin);
        }
        return balance;
    }

    void resetBalance() { coinList.clear(); }
};

// Context class that maintains state and handles transitions in the vending machine
class VendingMachineContext
{
private:
    shared_ptr<VendingMachineState> currentState;
    VendingMachineData machineData;

public:
    VendingMachineContext() : machineData(10)
    {
        currentState = static_pointer_cast<VendingMachineState>(make_shared<IdleState>());
        cout << "Initialized: " << currentState->getStateName() << endl;
    }

    shared_ptr<VendingMachineState> getCurrentState() const
    {
        return currentState;
    }

    void advanceState()
    {
        shared_ptr<VendingMachineState> nextState = currentState->next(this);
        currentState = nextState;
        cout << "Current state: " << currentState->getStateName() << endl;
    }

    void clickOnInsertCoinButton(Coin coin);
    void clickOnStartProductSelectionButton(int codeNumber);
    void selectProduct(int codeNumber);
    void dispenseItem(int codeNumber);
    void updateInventory(const Item &item, int codeNumber);

    // Delegate to machineData
    Inventory &getInventory() { return machineData.getInventory(); }
    const Inventory &getInventory() const { return machineData.getInventory(); }
    void setInventory(const Inventory &inv) { machineData.setInventory(inv); }

    vector<Coin> &getCoinList() { return machineData.getCoinList(); }
    const vector<Coin> &getCoinList() const { return machineData.getCoinList(); }
    void setCoinList(const vector<Coin> &coins) { machineData.setCoinList(coins); }

    int getSelectedItemCode() const { return machineData.getSelectedItemCode(); }
    void setSelectedItemCode(int code) { machineData.setSelectedItemCode(code); }
    void resetSelection() { machineData.resetSelection(); }

    int getBalance() const { return machineData.getBalance(); }
    void resetBalance() { machineData.resetBalance(); }
};

// ==================== CONCRETE STATES ====================

// Implementation of the Idle state
class IdleState : public VendingMachineState
{
public:
    IdleState()
    {
        cout << "Vending machine is now in Idle State" << endl;
    }

    string getStateName() const override
    {
        return "IdleState";
    }

    shared_ptr<VendingMachineState> next(VendingMachineContext *context) override;
};

// Implementation of the HasMoney state
class HasMoneyState : public VendingMachineState
{
public:
    HasMoneyState()
    {
        cout << "Vending machine is now in HasMoney State" << endl;
    }

    string getStateName() const override
    {
        return "HasMoneyState";
    }

    shared_ptr<VendingMachineState> next(VendingMachineContext *context) override;
};

// Implementation of the Selection state
class SelectionState : public VendingMachineState
{
public:
    SelectionState()
    {
        cout << "Vending machine is now in Selection State" << endl;
    }

    string getStateName() const override
    {
        return "SelectionState";
    }

    shared_ptr<VendingMachineState> next(VendingMachineContext *context) override;
};

// Implementation of the Dispense state
class DispenseState : public VendingMachineState
{
public:
    DispenseState()
    {
        cout << "Vending machine is now in Dispense State" << endl;
    }

    string getStateName() const override
    {
        return "DispenseState";
    }

    shared_ptr<VendingMachineState> next(VendingMachineContext *context) override
    {
        return static_pointer_cast<VendingMachineState>(make_shared<IdleState>());
    }
};

// Implementation of the OutOfStock state
class OutOfStockState : public VendingMachineState
{
public:
    OutOfStockState()
    {
        cout << "Vending machine is now in Out of Stock State" << endl;
    }

    string getStateName() const override
    {
        return "OutOfStockState";
    }

    shared_ptr<VendingMachineState> next(VendingMachineContext *context) override
    {
        if (context->getInventory().hasItems())
        {
            return static_pointer_cast<VendingMachineState>(make_shared<IdleState>());
        }
        return static_pointer_cast<VendingMachineState>(make_shared<OutOfStockState>());
    }
};

// ==================== STATE IMPLEMENTATIONS ====================

shared_ptr<VendingMachineState> IdleState::next(VendingMachineContext *context)
{
    if (!context->getInventory().hasItems())
    {
        return static_pointer_cast<VendingMachineState>(make_shared<OutOfStockState>());
    }
    if (!context->getCoinList().empty())
    {
        return static_pointer_cast<VendingMachineState>(make_shared<HasMoneyState>());
    }
    return static_pointer_cast<VendingMachineState>(make_shared<IdleState>());
}

shared_ptr<VendingMachineState> HasMoneyState::next(VendingMachineContext *context)
{
    if (!context->getInventory().hasItems())
    {
        return static_pointer_cast<VendingMachineState>(make_shared<OutOfStockState>());
    }
    if (context->getCoinList().empty())
    {
        return static_pointer_cast<VendingMachineState>(make_shared<IdleState>());
    }
    if (dynamic_cast<HasMoneyState *>(context->getCurrentState().get()))
    {
        return static_pointer_cast<VendingMachineState>(make_shared<SelectionState>());
    }
    return static_pointer_cast<VendingMachineState>(make_shared<HasMoneyState>());
}

shared_ptr<VendingMachineState> SelectionState::next(VendingMachineContext *context)
{
    if (!context->getInventory().hasItems())
    {
        return static_pointer_cast<VendingMachineState>(make_shared<OutOfStockState>());
    }
    if (context->getCoinList().empty())
    {
        return static_pointer_cast<VendingMachineState>(make_shared<IdleState>());
    }
    if (context->getSelectedItemCode() > 0)
    {
        return static_pointer_cast<VendingMachineState>(make_shared<DispenseState>());
    }
    return static_pointer_cast<VendingMachineState>(make_shared<SelectionState>());
}

// ==================== CONTEXT METHOD IMPLEMENTATIONS ====================

void VendingMachineContext::clickOnInsertCoinButton(Coin coin)
{
    if (dynamic_cast<IdleState *>(currentState.get()) ||
        dynamic_cast<HasMoneyState *>(currentState.get()))
    {
        cout << "Inserted " << coinToString(coin) << " worth " << getCoinValue(coin) << endl;
        machineData.getCoinList().push_back(coin);
        advanceState();
    }
    else
    {
        cout << "Cannot insert coin in " << currentState->getStateName() << endl;
    }
}

void VendingMachineContext::clickOnStartProductSelectionButton(int codeNumber)
{
    if (dynamic_cast<HasMoneyState *>(currentState.get()))
    {
        advanceState();
        selectProduct(codeNumber);
    }
    else
    {
        cout << "Product selection button can only be clicked in HasMoney state" << endl;
    }
}

void VendingMachineContext::selectProduct(int codeNumber)
{
    if (dynamic_cast<SelectionState *>(currentState.get()))
    {
        try
        {
            Item item = machineData.getInventory().getItem(codeNumber);

            int balance = machineData.getBalance();
            if (balance < item.getPrice())
            {
                cout << "Insufficient amount. Product price: " << item.getPrice()
                     << ", paid: " << balance << endl;
                return;
            }
            setSelectedItemCode(codeNumber);
            advanceState();
            dispenseItem(codeNumber);

            if (balance >= item.getPrice())
            {
                int change = balance - item.getPrice();
                cout << "Returning change: " << change << endl;
            }
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << endl;
        }
    }
    else
    {
        cout << "Products can only be selected in Selection state" << endl;
    }
}

void VendingMachineContext::dispenseItem(int codeNumber)
{
    if (dynamic_cast<DispenseState *>(currentState.get()))
    {
        try
        {
            Item item = machineData.getInventory().getItem(codeNumber);
            cout << "Dispensing: " << itemTypeToString(item.getType()) << endl;
            machineData.getInventory().removeItem(codeNumber);
            machineData.getInventory().updateSoldOutItem(codeNumber);
            resetBalance();
            resetSelection();
            advanceState();
        }
        catch (const exception &e)
        {
            cout << "Failed to Dispense the Product with code : " << codeNumber << endl;
        }
    }
    else
    {
        cout << "System cannot dispense in : " << currentState->getStateName() << endl;
    }
}

void VendingMachineContext::updateInventory(const Item &item, int codeNumber)
{
    if (dynamic_cast<IdleState *>(currentState.get()))
    {
        try
        {
            machineData.getInventory().addItem(item, codeNumber);
            cout << "Added " << itemTypeToString(item.getType()) << " to slot " << codeNumber << endl;
        }
        catch (const exception &e)
        {
            cout << "Error updating inventory: " << e.what() << endl;
        }
    }
    else
    {
        cout << "Inventory can only be updated in Idle state" << endl;
    }
}

// ==================== HELPER FUNCTIONS ====================

void fillUpInventory(VendingMachineContext &vendingMachine)
{
    for (int i = 0; i < 10; i++)
    {
        Item newItem;
        int codeNumber = 101 + i;

        if (i >= 0 && i < 3)
        {
            newItem.setType(ItemType::COKE);
            newItem.setPrice(12);
        }
        else if (i >= 3 && i < 5)
        {
            newItem.setType(ItemType::PEPSI);
            newItem.setPrice(9);
        }
        else if (i >= 5 && i < 7)
        {
            newItem.setType(ItemType::JUICE);
            newItem.setPrice(13);
        }
        else if (i >= 7 && i < 10)
        {
            newItem.setType(ItemType::SODA);
            newItem.setPrice(7);
        }

        for (int j = 0; j < 5; j++)
        {
            vendingMachine.updateInventory(newItem, codeNumber);
        }
    }
}

void displayInventory(VendingMachineContext &vendingMachine)
{
    vector<ItemShelf> &slots = vendingMachine.getInventory().getInventory();
    for (const auto &slot : slots)
    {
        const vector<Item> &items = slot.getItems();
        if (!items.empty())
        {
            cout << "CodeNumber: " << slot.getCode() << " Items: " << endl;
            for (const auto &item : items)
            {
                cout << "    - Item: " << itemTypeToString(item.getType())
                     << ", Price: " << item.getPrice() << endl;
            }
            cout << "SoldOut: " << (slot.checkIsSoldOut() ? "true" : "false") << endl;
        }
        else
        {
            cout << "CodeNumber: " << slot.getCode() << " Items: EMPTY"
                 << " SoldOut: " << (slot.checkIsSoldOut() ? "true" : "false") << endl;
        }
    }
}

// ==================== MAIN FUNCTION ====================

int main()
{
    VendingMachineContext vendingMachine;

    try
    {
        cout << "|" << endl;
        cout << "Filling up the inventory" << endl;
        cout << "|" << endl;
        fillUpInventory(vendingMachine);
        displayInventory(vendingMachine);

        cout << "|" << endl;
        cout << "Inserting coins" << endl;
        cout << "|" << endl;
        vendingMachine.clickOnInsertCoinButton(Coin::TEN_RUPEES);
        vendingMachine.clickOnInsertCoinButton(Coin::FIVE_RUPEES);

        cout << "|" << endl;
        cout << "Clicking on ProductSelectionButton" << endl;
        cout << "|" << endl;
        vendingMachine.clickOnStartProductSelectionButton(102);

        displayInventory(vendingMachine);
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
        displayInventory(vendingMachine);
    }

    return 0;
}
