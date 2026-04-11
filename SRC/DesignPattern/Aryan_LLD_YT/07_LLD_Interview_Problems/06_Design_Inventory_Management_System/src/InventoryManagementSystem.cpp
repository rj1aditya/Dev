#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

// ==================== ENUMS ====================

// ProductCategory Enum
enum class ProductCategory
{
    ELECTRONICS,
    CLOTHING,
    GROCERY,
    FURNITURE,
    OTHER
};

// InventoryOperation Enum
enum class InventoryOperation
{
    ADD,
    REMOVE,
    TRANSFER,
    ADJUST
};

// ==================== FORWARD DECLARATIONS ====================

class Product;
class Warehouse;
class ReplenishmentStrategy;

// ==================== PRODUCT CLASS ====================

class Product
{
protected:
    string sku;//stock keeping unit, unique identifier
    string name;
    double price;
    int quantity;
    int threshold;
    ProductCategory productCategory;

public:
    Product() : sku(""), name(""), price(0), quantity(0), threshold(0),
                productCategory(ProductCategory::OTHER) {}

    virtual ~Product() {}

    // Getters
    string getSku() const { return sku; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    int getThreshold() const { return threshold; }
    ProductCategory getProductCategory() const { return productCategory; }

    // Setters
    void setSku(const string &s) { sku = s; }
    void setName(const string &n) { name = n; }
    void setPrice(double p) { price = p; }
    void setQuantity(int q) { quantity = q; }
    void setThreshold(int t) { threshold = t; }
    void setCategory(ProductCategory pc) { productCategory = pc; }

    virtual void displayInfo() const
    {
        cout << "SKU: " << sku << ", Name: " << name << ", Price: " << price
             << ", Quantity: " << quantity << ", Threshold: " << threshold << endl;
    }
};

// ==================== CONCRETE PRODUCT CLASSES ====================

class ElectronicsProduct : public Product
{
private:
    string brand;
    int warrantyPeriod; // in months

public:
    ElectronicsProduct(const string &s, const string &n, double p, int q, int t)
        : brand(""), warrantyPeriod(0)
    {
        setSku(s);
        setName(n);
        setPrice(p);
        setQuantity(q);
        setThreshold(t);
        setCategory(ProductCategory::ELECTRONICS);
    }

    string getBrand() const { return brand; }
    void setBrand(const string &b) { brand = b; }

    int getWarrantyPeriod() const { return warrantyPeriod; }
    void setWarrantyPeriod(int w) { warrantyPeriod = w; }

    void displayInfo() const override
    {
        Product::displayInfo();
        cout << "  Brand: " << brand << ", Warranty: " << warrantyPeriod << " months" << endl;
    }
};

class ClothingProduct : public Product
{
private:
    string size;
    string color;

public:
    ClothingProduct(const string &s, const string &n, double p, int q, int t)
        : size(""), color("")
    {
        setSku(s);
        setName(n);
        setPrice(p);
        setQuantity(q);
        setThreshold(t);
        setCategory(ProductCategory::CLOTHING);
    }

    string getSize() const { return size; }
    void setSize(const string &s) { size = s; }

    string getColor() const { return color; }
    void setColor(const string &c) { color = c; }

    void displayInfo() const override
    {
        Product::displayInfo();
        cout << "  Size: " << size << ", Color: " << color << endl;
    }
};

class GroceryProduct : public Product
{
private:
    string expiryDate;
    bool refrigerated;

public:
    GroceryProduct(const string &s, const string &n, double p, int q, int t)
        : expiryDate(""), refrigerated(false)
    {
        setSku(s);
        setName(n);
        setPrice(p);
        setQuantity(q);
        setThreshold(t);
        setCategory(ProductCategory::GROCERY);
    }

    string getExpiryDate() const { return expiryDate; }
    void setExpiryDate(const string &d) { expiryDate = d; }

    bool isRefrigerated() const { return refrigerated; }
    void setRefrigerated(bool r) { refrigerated = r; }

    void displayInfo() const override
    {
        Product::displayInfo();
        cout << "  Expiry Date: " << expiryDate
             << ", Refrigerated: " << (refrigerated ? "Yes" : "No") << endl;
    }
};

// ==================== PRODUCT FACTORY ====================

class ProductFactory
{
public:
    Product *createProduct(ProductCategory category, const string &sku,
                           const string &name, double price, int quantity, int threshold)
    {
        switch (category)
        {
        case ProductCategory::ELECTRONICS:
            return new ElectronicsProduct(sku, name, price, quantity, threshold);
        case ProductCategory::CLOTHING:
            return new ClothingProduct(sku, name, price, quantity, threshold);
        case ProductCategory::GROCERY:
            return new GroceryProduct(sku, name, price, quantity, threshold);
        default:
            cout << "Unsupported product category" << endl;
            return nullptr;
        }
    }
};

// ==================== REPLENISHMENT STRATEGY ====================

class ReplenishmentStrategy
{
public:
    virtual ~ReplenishmentStrategy() {}
    virtual void replenish(Product *product) = 0;
};

// ==================== CONCRETE STRATEGIES ====================

class JustInTimeStrategy : public ReplenishmentStrategy
{
public:
    void replenish(Product *product) override
    {
        cout << "Applying Just-In-Time replenishment for " << product->getName() << endl;
        // Calculate optimal order quantity based on demand rate
    }
};

class BulkOrderStrategy : public ReplenishmentStrategy
{
public:
    void replenish(Product *product) override
    {
        cout << "Applying Bulk Order replenishment for " << product->getName() << endl;
        // Order in large quantities to minimize order costs
    }
};

// ==================== WAREHOUSE CLASS ====================

class Warehouse
{
private:
    int id;
    string name;
    string location;
    map<string, Product *> products; // SKU -> Product

public:
    Warehouse(const string &n) : id(0), name(n), location("") {}

    ~Warehouse()
    {
        for (auto &p : products)
        {
            delete p.second;
        }
    }

    void setLocation(const string &loc) { location = loc; }
    string getLocation() const { return location; }
    string getName() const { return name; }

    // Add a product to the warehouse
    void addProduct(Product *product, int quantity)
    {
        string sku = product->getSku();
        if (products.find(sku) != products.end())
        {
            // Product exists, update quantity
            products[sku]->setQuantity(products[sku]->getQuantity() + quantity);
        }
        else
        {
            // New product, add to inventory
            product->setQuantity(quantity);
            products[sku] = product;
        }
        cout << quantity << " units of " << product->getName()
             << " (SKU: " << sku << ") added to " << name
             << ". New quantity: " << getAvailableQuantity(sku) << endl;
    }

    // Remove a product from the warehouse
    bool removeProduct(const string &sku, int quantity)
    {
        if (products.find(sku) != products.end())
        {
            Product *product = products[sku];
            int currentQuantity = product->getQuantity();
            if (currentQuantity >= quantity)
            {
                // Sufficient inventory to remove
                product->setQuantity(currentQuantity - quantity);
                cout << quantity << " units of " << product->getName()
                     << " (SKU: " << sku << ") removed from " << name
                     << ". Remaining quantity: " << product->getQuantity() << endl;
                // If quantity becomes zero, remove the product
                if (product->getQuantity() == 0)
                {
                    products.erase(sku);
                    cout << "Product " << product->getName()
                         << " removed from inventory as quantity is now zero." << endl;
                }
                return true;
            }
            else
            {
                cout << "Error: Insufficient inventory. Requested: "
                     << quantity << ", Available: " << currentQuantity << endl;
                return false;
            }
        }
        else
        {
            cout << "Error: Product with SKU " << sku << " not found in " << name << endl;
            return false;
        }
    }

    // Get available quantity of a product
    int getAvailableQuantity(const string &sku) const
    {
        auto it = products.find(sku);
        if (it != products.end())
        {
            return it->second->getQuantity();
        }
        return 0; // Product not found
    }

    // Get a product by SKU
    Product *getProductBySku(const string &sku) const
    {
        auto it = products.find(sku);
        if (it != products.end())
        {
            return it->second;
        }
        return nullptr;
    }

    // Get all products in this warehouse
    vector<Product *> getAllProducts() const
    {
        vector<Product *> allProducts;
        for (const auto &p : products)
        {
            allProducts.push_back(p.second);
        }
        return allProducts;
    }

    // Display all products in warehouse
    void displayInventory() const
    {
        cout << "\n=== Inventory in " << name << " ===" << endl;
        for (const auto &p : products)
        {
            p.second->displayInfo();
        }
    }
};

// ==================== INVENTORY MANAGER (SINGLETON) ====================

class InventoryManager
{
private:
    static InventoryManager *instance;
    vector<Warehouse *> warehouses;
    ProductFactory *productFactory;
    ReplenishmentStrategy *replenishmentStrategy;

    // Private constructor
    InventoryManager(ReplenishmentStrategy *strategy)
        : productFactory(nullptr), replenishmentStrategy(strategy)
    {
        productFactory = new ProductFactory();
    }

public:
    // Singleton getInstance with thread safety (static initialization)
    static InventoryManager *getInstance(ReplenishmentStrategy *strategy = nullptr)
    {
        if (instance == nullptr && strategy != nullptr)
        {
            instance = new InventoryManager(strategy);
        }
        return instance;
    }

    ~InventoryManager()
    {
        for (auto w : warehouses)
        {
            delete w;
        }
        if (productFactory)
            delete productFactory;
    }

    // Strategy pattern method
    void setReplenishmentStrategy(ReplenishmentStrategy *strategy)
    {
        replenishmentStrategy = strategy;
    }

    // Warehouse management
    void addWarehouse(Warehouse *warehouse)
    {
        warehouses.push_back(warehouse);
    }

    void removeWarehouse(Warehouse *warehouse)
    {
        auto it = find(warehouses.begin(), warehouses.end(), warehouse);
        if (it != warehouses.end())
        {
            warehouses.erase(it);
        }
    }

    // Product inventory operations
    Product *getProductBySku(const string &sku)
    {
        for (Warehouse *warehouse : warehouses)
        {
            Product *product = warehouse->getProductBySku(sku);
            if (product != nullptr)
            {
                return product;
            }
        }
        return nullptr;
    }

    // Check stock levels and apply replenishment strategy if needed
    void checkAndReplenish(const string &sku)
    {
        Product *product = getProductBySku(sku);
        if (product != nullptr)
        {
            // If product is below threshold
            if (product->getQuantity() < product->getThreshold())
            {
                // Apply current replenishment strategy
                if (replenishmentStrategy != nullptr)
                {
                    replenishmentStrategy->replenish(product);
                }
            }
        }
    }

    // Global inventory check
    void performInventoryCheck()
    {
        for (Warehouse *warehouse : warehouses)
        {
            vector<Product *> allProducts = warehouse->getAllProducts();
            for (Product *product : allProducts)
            {
                if (product->getQuantity() < product->getThreshold())
                {
                    if (replenishmentStrategy != nullptr)
                    {
                        replenishmentStrategy->replenish(product);
                    }
                }
            }
        }
    }

    // Display all warehouses and their inventory
    void displayAllInventories() const
    {
        cout << "\n========== COMPLETE INVENTORY ==========" << endl;
        for (const Warehouse *warehouse : warehouses)
        {
            warehouse->displayInventory();
        }
    }
};

// Initialize static member
InventoryManager *InventoryManager::instance = nullptr;

// ==================== MAIN FUNCTION ====================

int main()
{
    cout << "============== Inventory Management System ==============" << endl;

    // Get the singleton instance of InventoryManager
    ReplenishmentStrategy *replenishmentStrategy = new JustInTimeStrategy();
    InventoryManager *inventoryManager = InventoryManager::getInstance(replenishmentStrategy);

    // Create and add warehouses
    Warehouse *warehouse1 = new Warehouse("Warehouse 1");
    warehouse1->setLocation("New York");

    Warehouse *warehouse2 = new Warehouse("Warehouse 2");
    warehouse2->setLocation("Los Angeles");

    inventoryManager->addWarehouse(warehouse1);
    inventoryManager->addWarehouse(warehouse2);

    cout << "\n--- Creating products using ProductFactory ---" << endl;

    // Create products using ProductFactory
    ProductFactory factory;
    Product *laptop = factory.createProduct(
        ProductCategory::ELECTRONICS, "SKU123", "Laptop", 1000.0, 50, 25);
    Product *tShirt = factory.createProduct(
        ProductCategory::CLOTHING, "SKU456", "T-Shirt", 20.0, 200, 100);
    Product *apple = factory.createProduct(
        ProductCategory::GROCERY, "SKU789", "Apple", 1.0, 100, 200);

    // Cast to specific types to set additional properties
    if (auto electronics = dynamic_cast<ElectronicsProduct *>(laptop))
    {
        electronics->setBrand("Dell");
        electronics->setWarrantyPeriod(24);
    }
    if (auto clothing = dynamic_cast<ClothingProduct *>(tShirt))
    {
        clothing->setSize("Medium");
        clothing->setColor("Blue");
    }
    if (auto grocery = dynamic_cast<GroceryProduct *>(apple))
    {
        grocery->setExpiryDate("2026-12-31");
        grocery->setRefrigerated(false);
    }

    cout << "\n--- Adding products to warehouses ---" << endl;

    // Add products to warehouses
    warehouse1->addProduct(laptop, 15);
    warehouse1->addProduct(tShirt, 20);
    warehouse2->addProduct(apple, 50);

    // Display current inventory
    inventoryManager->displayAllInventories();

    // Set replenishment strategy to Just-In-Time
    cout << "\n--- Setting replenishment strategy to Just-In-Time ---" << endl;
    inventoryManager->setReplenishmentStrategy(new JustInTimeStrategy());

    // Perform inventory check and replenish if needed
    inventoryManager->performInventoryCheck();

    // Switch replenishment strategy to Bulk Order
    cout << "\n--- Switching replenishment strategy to Bulk Order ---" << endl;
    inventoryManager->setReplenishmentStrategy(new BulkOrderStrategy());

    // Replenish a specific product if needed
    inventoryManager->checkAndReplenish("SKU123");

    // Remove some products and check
    cout << "\n--- Removing products ---" << endl;
    warehouse1->removeProduct("SKU456", 15);

    // Final inventory display
    inventoryManager->displayAllInventories();

    cout << "\n============== System Shutdown ==============" << endl;

    return 0;
}
