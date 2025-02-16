#include "mydatastore.h"
#include "util.h"

#include <string>
#include <set>
#include <vector>

MyDataStore::MyDataStore() {}

MyDataStore::~MyDataStore() {
    //delete products_
    std::set<Product*>::iterator pIt;
    for(pIt = products_.begin(); pIt != products_.end(); ++pIt){
        delete *pIt;
    }
    //delete users_
    std::set<User*>::iterator uIt;
    for(uIt = users_.begin(); uIt != users_.end(); ++uIt){
        delete *uIt;
    }
    //delete cart_
    std::map<User*, std::list<Product*>>::iterator cIt;
    for (cIt = cart_.begin(); cIt != cart_.end(); ++cIt){
        cIt -> second.clear();
    }
    cart_.clear();
}

void MyDataStore::addProduct(Product *p)
{
    products_.insert(p);
}

void MyDataStore::addUser(User *u)
{
    users_.insert(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string> &terms, int type)
{
    std::vector<Product*> result;

    // parse terms into valid words and store in validTerms
    std::set<std::string> validTerms;
    std::vector<std::string>::iterator tIt;
    for (tIt = terms.begin(); tIt != terms.end(); tIt++){
        std::set<std::string> parsedWords = parseStringToWords(*tIt);
        validTerms.insert(parsedWords.begin(), parsedWords.end());
    }

    // AND (intersection)
    if (type == 0){
        for (std::set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
            std::set<std::string> prodKW = (*it)->keywords();
            std::set<std::string> lowerProdKW;

            for (std::set<std::string>::iterator pIt = prodKW.begin(); pIt != prodKW.end(); ++pIt){
                lowerProdKW.insert(convToLower(*pIt));
            }

            bool containsAll = true;
            for (std::set<std::string>::iterator vIt = validTerms.begin(); vIt != validTerms.end(); ++vIt){
                if (lowerProdKW.find(*vIt) == lowerProdKW.end()){ // FIXED CHECK
                    containsAll = false;
                    break;
                }
            }

            if (containsAll){
                result.push_back(*it);
            }
        }
    }
    // OR (union)
    else if (type == 1){
        for (std::set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
            std::set<std::string> prodKW = (*it)->keywords();
            std::set<std::string> lowerProdKW;

            for (std::set<std::string>::iterator pIt = prodKW.begin(); pIt != prodKW.end(); ++pIt){
                lowerProdKW.insert(convToLower(*pIt));
            }
            
            bool containAny = false;
            for (std::set<std::string>::iterator vIt = validTerms.begin(); vIt != validTerms.end(); ++vIt){
                if (lowerProdKW.find(*vIt) != lowerProdKW.end()){ // FIXED CHECK
                    containAny = true;
                    break;
                }
            }

            if (containAny){
                result.push_back(*it);
            }
        }
    }
    return result;
}

void MyDataStore::dump(std::ostream &ofile)
{
    ofile << "<products>" << std::endl;

    std::set<Product*>::iterator pIt;
    for (pIt = products_.begin(); pIt != products_.end(); ++pIt){
        (*pIt) -> dump(ofile);
    }
    
    ofile << "</products>\n<users>" << std::endl;

    std::set<User*>::iterator uIt;
    for (uIt = users_.begin(); uIt != users_.end(); ++uIt){
        (*uIt) -> dump(ofile);
    }
    
    ofile << "</users>" << std::endl;
}

void MyDataStore::addToCart(std::string username, Product* p){
    User* currUser = findUser(username);
    if (currUser){
        cart_[currUser].push_back(p);
    }
    else {
        std::cout << "Invalid request" << std::endl;
    }
}

void MyDataStore::viewCart(std::string username){
    User* currUser = findUser(username);
    if (currUser){
        int index = 1;
        for (Product *p : cart_[currUser]){
            std::cout << index << ". ";
            std::cout << p -> displayString() << std::endl;
        }
    }
    else {
        std::cout << "Invalid username" << std::endl;
    }
}

void MyDataStore::buyCart(std::string username){
    User* currUser = findUser(username);
    if (currUser){
        std::list<Product*>::iterator it;
        for (it = cart_[currUser].begin(); it != cart_[currUser].end(); ++it){
            if ((currUser -> getBalance() >= (*it) -> getPrice())
                && ((*it) -> getQty() > 0)){
                currUser->deductAmount((*it) -> getPrice());
                (*it)->subtractQty(1);
                it = cart_[currUser].erase(it);
            }
            else {
                ++it;
            }
        }
    }
    else {
        std::cout << "Invalid username" << std::endl;
    }
}

User* MyDataStore::findUser(std::string username) const{
    for (User* u : users_){
        if ((*u).getName() == username){
            return u;
        }
    }
    return nullptr;
}