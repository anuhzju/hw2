#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <string>
#include <set>
#include <vector>
#include <list>
#include <map>

class MyDataStore : public DataStore{
    public:
        MyDataStore();
        ~MyDataStore();

        void addProduct(Product *p) override;
        void addUser(User *u) override;
        std::vector<Product*> search(std::vector<std::string> &terms, int type) override;
        void dump(std::ostream &ofile) override;
        
        void addToCart(std::string username, Product* p);
        void viewCart(std::string username);
        void buyCart(std::string username);

    private:
        std::set<Product*> products_; 
        std::set<User*> users_;
        std::map<std::string, std::list<Product*>> cart_;

        //helper function to find user from username
        User* findUser(std::string username) const;
};

#endif