#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED
#include <iostream>
#include <vector>

class Personnage
{
private:
    std::string m_user;
    std::vector <int> m_pref;
public:
    Personnage(std::string user,std::vector <int> pref):m_user(user),m_pref(pref){}
    //void setUser(std::string user){m_user = user;}
    std::string getUser()const {return m_user;}
    int getPref(int j)const {return m_pref[j];}
};

#endif // PERSONNAGE_H_INCLUDED
