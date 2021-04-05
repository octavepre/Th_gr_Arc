#include "Sommet.h"

Sommet::Sommet(int num,std::string nomLieu,int altitude):m_num(num),m_nomLieu(nomLieu),m_altitude(altitude),m_visite(false){}

void Sommet::addSucc(Arete* succ)
{
    m_succ.push_back(succ);
}

void Sommet::afficherS()
{
    std::cout << "Sommet " << getNom() << " : ";
    for(unsigned int i = 0 ; i < m_succ.size() ; i++)
    {
        std::cout << m_succ[i]->getNumSecond() << "(" << m_succ[i]->getPoid() << ")" <<" ";///AFFICHER LE POID A COTER DES SOMMETS EN SECONDE
    }
}
