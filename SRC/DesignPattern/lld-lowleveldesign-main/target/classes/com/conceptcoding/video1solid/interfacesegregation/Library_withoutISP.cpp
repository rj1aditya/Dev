#pragma once
#include <string>
#include <chrono>

class ILibraryItem {
public:
    virtual ~ILibraryItem() = default;

    // Properties
    virtual std::string getAuthor() const = 0;
    virtual void setAuthor(const std::string& author) = 0;

    virtual std::chrono::system_clock::time_point getBorrowDate() const = 0;
    virtual void setBorrowDate(const std::chrono::system_clock::time_point& date) = 0;

    virtual std::string getBorrower() const = 0;
    virtual void setBorrower(const std::string& borrower) = 0;

    virtual int getCheckOutDurationInDays() const = 0;
    virtual void setCheckOutDurationInDays(int days) = 0;

    virtual std::string getLibraryId() const = 0;
    virtual void setLibraryId(const std::string& id) = 0;

    virtual int getPages() const = 0;
    virtual void setPages(int pages) = 0;

    virtual std::string getTitle() const = 0;
    virtual void setTitle(const std::string& title) = 0;

    // Methods
    virtual void CheckIn() = 0;
    virtual void CheckOut(const std::string& borrower) = 0;
    virtual std::chrono::system_clock::time_point GetDueDate() const = 0;
};

// This interface is used by 4 different clients, but most of them are not using all of the methods defined in this interface.
// So this is breaking the ISP. How to solve this.
// By segregating this Fat interface into small interface we could achieve ISP.

#pragma once
#include "ILibraryItem.h"
#include <string>
#include <chrono>

class AudioBook : public ILibraryItem {
private:
    std::string libraryId;
    std::string title;
    std::string author;
    int pages = -1; // Not useful for AudioBook, breaking ISP
    int checkOutDurationInDays = 14;
    std::string borrower;
    std::chrono::system_clock::time_point borrowDate;
    int runtimeInMinutes; // Extra property

public:
    // Getters and setters
    std::string getLibraryId() const override { return libraryId; }
    void setLibraryId(const std::string& id) override { libraryId = id; }

    std::string getTitle() const override { return title; }
    void setTitle(const std::string& t) override { title = t; }

    std::string getAuthor() const override { return author; }
    void setAuthor(const std::string& a) override { author = a; }

    int getPages() const override { return pages; }
    void setPages(int p) override { pages = p; }

    int getCheckOutDurationInDays() const override { return checkOutDurationInDays; }
    void setCheckOutDurationInDays(int days) override { checkOutDurationInDays = days; }

    std::string getBorrower() const override { return borrower; }
    void setBorrower(const std::string& b) override { borrower = b; }

    std::chrono::system_clock::time_point getBorrowDate() const override { return borrowDate; }
    void setBorrowDate(const std::chrono::system_clock::time_point& date) override { borrowDate = date; }

    int getRuntimeInMinutes() const { return runtimeInMinutes; }
    void setRuntimeInMinutes(int minutes) { runtimeInMinutes = minutes; }

    // Methods
    void CheckOut(const std::string& borrowerName) override {
        borrower = borrowerName;
        borrowDate = std::chrono::system_clock::now();
    }

    void CheckIn() override {
        borrower.clear();
    }

    std::chrono::system_clock::time_point GetDueDate() const override {
        return borrowDate + std::chrono::hours(24 * checkOutDurationInDays);
    }
};
// So this class is dependent on ILibraryItem's method (int pages) 
// which is not used in this class, so breaking the ISP.
//for an audiobook, the concept of "pages" does not make sense and is not used. This forces the class to include unnecessary code, violating the Interface Segregation Principle (ISP), which states that classes should not be forced to depend on methods they do not use.


#pragma once
#include "ILibraryItem.h"
#include <string>
#include <chrono>
#include <stdexcept>

// ReferenceBooks are very huge books like dictionary, 
// encyclopedia which generally remain in library only.
class ReferenceBook : public ILibraryItem {
private:
    std::string libraryId;
    std::string title;
    std::string author;
    int pages;
    int checkOutDurationInDays = 0; // Not required
    std::string borrower; // Not required
    std::chrono::system_clock::time_point borrowDate; // Not required

public:
    std::string getLibraryId() const override { return libraryId; }
    void setLibraryId(const std::string& id) override { libraryId = id; }

    std::string getTitle() const override { return title; }
    void setTitle(const std::string& t) override { title = t; }

    std::string getAuthor() const override { return author; }
    void setAuthor(const std::string& a) override { author = a; }

    int getPages() const override { return pages; }
    void setPages(int p) override { pages = p; }

    int getCheckOutDurationInDays() const override { return checkOutDurationInDays; }
    void setCheckOutDurationInDays(int days) override { checkOutDurationInDays = days; }

    std::string getBorrower() const override { return borrower; }
    void setBorrower(const std::string& b) override { borrower = b; }

    std::chrono::system_clock::time_point getBorrowDate() const override { return borrowDate; }
    void setBorrowDate(const std::chrono::system_clock::time_point& date) override { borrowDate = date; }

    // Methods not required for ReferenceBook
    void CheckOut(const std::string& /*borrower*/) override {
        throw std::logic_error("CheckOut not implemented for ReferenceBook");
    }

    void CheckIn() override {
        throw std::logic_error("CheckIn not implemented for ReferenceBook");
    }

    std::chrono::system_clock::time_point GetDueDate() const override {
        throw std::logic_error("GetDueDate not implemented for ReferenceBook");
    }
};

// So this class is dependent on ILibraryItem's methods 
// which are not used in this class, so breaking the ISP.

#pragma once
#include "ILibraryItem.h"
#include <string>
#include <vector>
#include <chrono>

class DVD : public ILibraryItem {
private:
    std::string libraryId;
    std::string title;
    std::string author = ""; // For DVD, usually Director or Producer
    int pages = -1; // Not required
    int checkOutDurationInDays = 14;
    std::string borrower;
    std::chrono::system_clock::time_point borrowDate;
    std::vector<std::string> actors; // Extra property
    int runtimeInMinutes; // Extra property

public:
    std::string getLibraryId() const override { return libraryId; }
    void setLibraryId(const std::string& id) override { libraryId = id; }

    std::string getTitle() const override { return title; }
    void setTitle(const std::string& t) override { title = t; }

    std::string getAuthor() const override { return author; }
    void setAuthor(const std::string& a) override { author = a; }

    int getPages() const override { return pages; }
    void setPages(int p) override { pages = p; }

    int getCheckOutDurationInDays() const override { return checkOutDurationInDays; }
    void setCheckOutDurationInDays(int days) override { checkOutDurationInDays = days; }

    std::string getBorrower() const override { return borrower; }
    void setBorrower(const std::string& b) override { borrower = b; }

    std::chrono::system_clock::time_point getBorrowDate() const override { return borrowDate; }
    void setBorrowDate(const std::chrono::system_clock::time_point& date) override { borrowDate = date; }

    std::vector<std::string> getActors() const { return actors; }
    void setActors(const std::vector<std::string>& a) { actors = a; }

    int getRuntimeInMinutes() const { return runtimeInMinutes; }
    void setRuntimeInMinutes(int minutes) { runtimeInMinutes = minutes; }

    void CheckOut(const std::string& borrowerName) override {
        borrower = borrowerName;
        borrowDate = std::chrono::system_clock::now();
    }

    void CheckIn() override {
        borrower.clear();
    }

    std::chrono::system_clock::time_point GetDueDate() const override {
        return borrowDate + std::chrono::hours(24 * checkOutDurationInDays);
    }
};

// So this class is dependent on ILibraryItem's methods (author, pages) 
// which are not used in this class, so breaking the ISP.

#pragma once
#include "ILibraryItem.h"
#include <string>
#include <chrono>

// All the methods inherited from the interface would be useful in Book 
// client so it is not breaking any ISP.
class Book : public ILibraryItem {
private:
    std::string libraryId;
    std::string title;
    std::string author;
    int pages;
    int checkOutDurationInDays = 14;
    std::string borrower;
    std::chrono::system_clock::time_point borrowDate;

public:
    std::string getLibraryId() const override { return libraryId; }
    void setLibraryId(const std::string& id) override { libraryId = id; }

    std::string getTitle() const override { return title; }
    void setTitle(const std::string& t) override { title = t; }

    std::string getAuthor() const override { return author; }
    void setAuthor(const std::string& a) override { author = a; }

    int getPages() const override { return pages; }
    void setPages(int p) override { pages = p; }

    int getCheckOutDurationInDays() const override { return checkOutDurationInDays; }
    void setCheckOutDurationInDays(int days) override { checkOutDurationInDays = days; }

    std::string getBorrower() const override { return borrower; }
    void setBorrower(const std::string& b) override { borrower = b; }

    std::chrono::system_clock::time_point getBorrowDate() const override { return borrowDate; }
    void setBorrowDate(const std::chrono::system_clock::time_point& date) override { borrowDate = date; }

    void CheckOut(const std::string& borrowerName) override {
        borrower = borrowerName;
        borrowDate = std::chrono::system_clock::now();
    }

    void CheckIn() override {
        borrower.clear();
    }

    std::chrono::system_clock::time_point GetDueDate() const override {
        return borrowDate + std::chrono::hours(24 * checkOutDurationInDays);
    }
};