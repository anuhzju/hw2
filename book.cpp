#include "book.h"
#include <sstream>
#include <iomanip>

//constructor
Book::Book(const std::string& category, const std::string& name, double price, int qty,
    const std::string& isbn, const std::string& author)
: Product(category, name, price, qty), isbn_(isbn), author_(author) {}

//destructor
Book::~Book() {}

//return relevant keywords for book type products
std::set<std::string> Book::keywords() const{
    std::set<std::string> keywords;

    // product name
    std::stringstream sName(name_);
    std::string word;
    while(sName >> word){
        keywords.insert(word);
    }

    //author name
    std::stringstream aName(author_);
    while(aName >> word){
        keywords.insert(word);
    }

    //whole isbn
    keywords.insert(isbn_);

    return keywords;
}

//display when outputting a hit
std::string Book::displayString() const{
    std::ostringstream os;
    
    os << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n"
        << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.\n";
    return os.str();
}

void Book::dump(std::ostream& os) const{
    os << "book\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << std::endl;
}

std::string Book::displayInfo() const{
    std::ostringstream os;
    os << "Author: " << author_ << " ISBN: " << isbn_;
    return os.str();
}