#include "clothing.h"
#include <sstream>

//constructor
Clothing::Clothing(const std::string& category, const std::string& name, double price, int qty,
    const std::string& size, const std::string& brand)
: Product(category, name, price, qty), size_(size), brand_(brand) {}

//destructor
Clothing::~Clothing() {}

//return relevant keywords for clothing type products
std::set<std::string> Clothing::keywords() const{
    std::set<std::string> keywords;

    // product name
    std::stringstream sName(name_);
    std::string word;
    while(sName >> word){
        keywords.insert(word);
    }

    //brand name
    std::stringstream bName(brand_);
    while(bName >> word){
        keywords.insert(word);
    }

    return keywords;
}

//display when outputting a hit
std::string Clothing::displayString() const{
    return name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";
}

void Clothing::dump(std::ostream& os) const{
    os << "clothing\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}