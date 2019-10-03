#include "No.h"
#include <iostream>

No::No()
{
    prox = NULL;
    id = -1;
    user = "";
}

No::~No()
{
    delete prox;
}

int No::getId(){
    return id;
}

void No::setId(int val){
    id = val;
}

No* No::getProx(){
    return prox;
}

void No::setProx(No* p){
    prox = p;
}

string No::getUser()
{
    return user;
}

void No::setUser(string userr)
{
    user = userr;
}
