#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <string>
#include <set>
#include <vector>

class MyDataStore : public DataStore{
    public:
        MyDataStore();
        ~MyDataStore();

        void addProduct(Product *p);
        void addUser(User *u);
        std::vector<Product*> search(std::vector<std::string> &terms, int type) const;
        void dump(std::ostream &ofile) const;

    private:
        std::set<Product*> products_; 
        std::set<User*> users_;
};

#endif