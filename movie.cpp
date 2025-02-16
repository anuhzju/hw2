#include "movie.h"
#include <sstream>
#include <iomanip>


//constructor
Movie::Movie(const std::string& category, const std::string& name, double price, int qty,
    const std::string& genre, const std::string& rating)
: Product(category, name, price, qty), genre_(genre), rating_(rating) {}

Movie::~Movie() {}

//return relevant keywords for movie type products
std::set<std::string> Movie::keywords() const{
    std::set<std::string> keywords;

    // product name
    std::stringstream sName(name_);
    std::string word;
    while(sName >> word){
        keywords.insert(word);
    }

    //genre
    keywords.insert(genre_);

    return keywords;
}

//display when outputting a hit
std::string Movie::displayString() const{
    std::ostringstream os;
    
    os << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n"
        << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.\n";
    return os.str();
}

void Movie::dump(std::ostream& os) const{
    os << "movie\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}