/*
    This file demonstrates the Interface Segregation Principle (ISP) in C++ by splitting a "fat" library item interface into several smaller, focused interfaces.
    - IIdentifiable: For basic identity properties (LibraryId, Title).
    - IAuthorable: For items that have an author (e.g., books).
    - IPageable: For items that have pages (e.g., books).
    - IBorrowable: For items that can be borrowed (checkout/checkin logic).

    By using these interfaces, each library item class (Book, AudioBook, DVD, ReferenceBook, etc.) can inherit only the interfaces relevant to its needs.
    This avoids forcing classes to implement unused methods and properties, making the code cleaner, more maintainable, and fully compliant with ISP.
*/
#pragma once
#include <string>
#include <chrono>

// Basic identity
class IIdentifiable {
public:
    virtual ~IIdentifiable() = default;
    virtual std::string getLibraryId() const = 0;
    virtual void setLibraryId(const std::string& id) = 0;
    virtual std::string getTitle() const = 0;
    virtual void setTitle(const std::string& title) = 0;
};

// Author info
class IAuthorable {
public:
    virtual ~IAuthorable() = default;
    virtual std::string getAuthor() const = 0;
    virtual void setAuthor(const std::string& author) = 0;
};

// Page info (for books only)
class IPageable {
public:
    virtual ~IPageable() = default;
    virtual int getPages() const = 0;
    virtual void setPages(int pages) = 0;
};

// Borrowable items
class IBorrowable {
public:
    virtual ~IBorrowable() = default;
    virtual std::string getBorrower() const = 0;
    virtual void setBorrower(const std::string& borrower) = 0;
    virtual std::chrono::system_clock::time_point getBorrowDate() const = 0;
    virtual void setBorrowDate(const std::chrono::system_clock::time_point& date) = 0;
    virtual int getCheckOutDurationInDays() const = 0;
    virtual void setCheckOutDurationInDays(int days) = 0;
    virtual void CheckOut(const std::string& borrower) = 0;
    virtual void CheckIn() = 0;
    virtual std::chrono::system_clock::time_point GetDueDate() const = 0;
};

//e.g.

class Book : public IIdentifiable, public IAuthorable, public IPageable, public IBorrowable {
    // Same as your current Book class — no changes needed
};

class AudioBook : public IIdentifiable, public IAuthorable, public IBorrowable {
private:
    int runtimeInMinutes;
public:
    int getRuntimeInMinutes() const;
    void setRuntimeInMinutes(int minutes);
    // Implement required interfaces only
};

class DVD : public IIdentifiable, public IAuthorable, public IBorrowable {
private:
    std::vector<std::string> actors;
    int runtimeInMinutes;
public:
    std::vector<std::string> getActors() const;
    void setActors(const std::vector<std::string>&);
    int getRuntimeInMinutes() const;
    void setRuntimeInMinutes(int);
    // Implement required interfaces only
};

class ReferenceBook : public IIdentifiable, public IAuthorable, public IPageable {
    // No borrowing logic — clean ISP compliance
};