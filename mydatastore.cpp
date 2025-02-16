#include "mydatastore.h"
#include "util.h"

#include <string>
#include <set>
#include <vector>

MyDataStore::MyDataStore(){}

MyDataStore::~MyDataStore(){}

void MyDataStore::addProduct(Product *p)
{
    products_.insert(p);
}

void MyDataStore::addUser(User *u)
{
    users_.insert(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string> &terms, int type) const
{
    std::vector<Product*> result;
    std::set<std::string> termsSet(terms.begin(), terms.end()); //turn terms from vector to set
    std::set<Product*>::iterator it;
    //AND (intersection)
    if (type == 0){
        for (it = products_.begin(); it != products_.end(); ++it){
            std::set<std::string> prodKW = (*it)->keywords();
            if (!setIntersection(prodKW, termsSet).empty()){
                result.push_back(*it);
            }
        }
    }
    //OR (union)
    if (type == 1){
        for (it = products_.begin(); it != products_.end(); ++it){
            std::set<std::string> prodKW = (*it)->keywords();
            if (!setUnion(prodKW, termsSet).empty()){
                result.push_back(*it);
            }
        }
    }
    return result;
}

void MyDataStore::dump(std::ostream &ofile) const
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