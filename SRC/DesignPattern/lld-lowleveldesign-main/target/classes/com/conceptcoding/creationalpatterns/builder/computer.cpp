#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

using namespace std;

/*
    ✔ Clean Builder Pattern in Modern C++ (C++11+)
    ✔ Computer object is immutable (all fields const)
    ✔ Builder performs all validation
    ✔ clone() recreates object using Builder (no raw copying)
    ✔ Uses unique_ptr for RAII (no manual delete)
*/

class Computer
{
public:
    // Forward declaration so friend refers to the nested Builder
    class Builder;

private:
    friend class Builder; // allows Builder to access private constructor

    // Immutable configuration fields
    const string ram;
    const string storage;
    const string cpu;
    const string gpu;
    const string graphicsCard;
    const string camera;
    const string biometric;

public:
    /*
        ===================================================
                       INNER BUILDER CLASS
        ===================================================
    */
    class Builder
    {
        friend class Computer; // allows Computer to read Builder fields

    private:
        // Builder's temporary fields
        string ram = "4GB";       // default optional
        string storage = "256GB"; // default optional
        string cpu;               // REQUIRED
        string gpu = "";          // optional
        string graphicsCard = ""; // optional
        string camera = "2MP";    // default optional
        string biometric = "";    // optional

    public:
        // CPU is mandatory (builder won't compile w/o CPU)
        explicit Builder(const string &cpuValue)
        {
            if (cpuValue.empty())
                throw runtime_error("CPU is required!");
            cpu = cpuValue;
        }

        // Fluent API setters
        Builder &setRam(const string &r)
        {
            if (r.empty())
                throw runtime_error("RAM cannot be empty!");
            ram = r;
            return *this;
        }

        Builder &setStorage(const string &s)
        {
            if (s.empty())
                throw runtime_error("Storage cannot be empty!");
            storage = s;
            return *this;
        }

        Builder &setGpu(const string &g)
        {
            gpu = g;
            return *this;
        }

        Builder &setGraphicsCard(const string &g)
        {
            graphicsCard = g;
            return *this;
        }

        Builder &setCamera(const string &c)
        {
            camera = c;
            return *this;
        }

        Builder &setBiometric(const string &b)
        {
            biometric = b;
            return *this;
        }

        /*
            Build → returns unique_ptr<Computer>
            Ensures validation and no memory leaks.
        */
        unique_ptr<Computer> build() const
        {
            if (cpu.empty())
                throw runtime_error("CPU is required!");
            if (ram.empty())
                throw runtime_error("RAM is required!");
            if (storage.empty())
                throw runtime_error("Storage is required!");
            // Direct new inside friend context to avoid private-ctor access issues with make_unique
            return unique_ptr<Computer>(new Computer(*this));
        }
    };

    // Prevent copying to avoid expensive accidental copies
    Computer(const Computer &) = delete;
    Computer &operator=(const Computer &) = delete;

    /*
        ===================================================
                       CLONE FUNCTION
        ===================================================
        ✔ Rebuilds object using Builder
        ✔ Maintains validation logic
        ✔ Safe, modern, consistent with Builder semantics
    */
    unique_ptr<Computer> clone() const
    {
        return Computer::Builder(cpu)
            .setRam(ram)
            .setStorage(storage)
            .setGpu(gpu)
            .setGraphicsCard(graphicsCard)
            .setCamera(camera)
            .setBiometric(biometric)
            .build();
    }

private:
    /*
        Private constructor — only Builder can create objects.
        Reads all Builder fields.
    */
    explicit Computer(const Builder &b)
        : ram(b.ram),
          storage(b.storage),
          cpu(b.cpu),
          gpu(b.gpu),
          graphicsCard(b.graphicsCard),
          camera(b.camera),
          biometric(b.biometric)
    {
    }

public:
    // Display method
    void displaySpecs() const
    {
        cout << "\n=== Computer Specifications ===\n";
        cout << "CPU: " << cpu << "\n";
        cout << "RAM: " << ram << "\n";
        cout << "Storage: " << storage << "\n";
        cout << "GPU: " << gpu << "\n";
        cout << "Graphics Card: " << graphicsCard << "\n";
        cout << "Camera: " << camera << "\n";
        cout << "Biometric: " << biometric << "\n";
    }
};

int main()
{
    try
    {
        auto pc1 = Computer::Builder("Intel i7")
                       .setRam("16GB")
                       .setStorage("512GB")
                       .setGpu("RTX 3060")
                       .setGraphicsCard("Nvidia GTX Series")
                       .setCamera("12MP")
                       .setBiometric("FaceID")
                       .build();

        cout << "Original PC:";
        pc1->displaySpecs();

        // Clone the same Computer object
        auto pc2 = pc1->clone();

        cout << "\nCloned PC:";
        pc2->displaySpecs();
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}