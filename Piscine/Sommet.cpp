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
        std::cout<<std::endl;
        std::cout << m_succ[i]->getNumSecond() << " ((Type : " << m_succ[i]->getType()<<  " // Poids : " << m_succ[i]->getPoid() << "))" <<" ";///AFFICHER LE POID A COTER DES SOMMETS EN SECONDE
    }
    std::cout<<std::endl;
}

int Sommet::getSuccNum(int i)
{
    return m_succ[i]->getNumSecond();
}

///COMPLETEMENT BUGUER
int Sommet::calculPoid(std::vector <Sommet*> m_sommet)
{

    int Totale = 0;
    //std::cout << "!" << Totale + m_sommet[m_chemin[0]-2]->getPoidPred(m_num) << "!";
    for (int i = 0 ; i < m_chemin.size()-1 ; i++)
    {
        //std::cout << "!" << m_sommet[m_chemin[i+1]-1]->getNum() << "!";
        Totale = Totale + m_sommet[m_chemin[i+1]-1]->getPoidPred(m_chemin[i]);
        //std::cout << "she" << m_sommet[m_chemin[i+1]-1]->getPoidPred(m_chemin[i]) << "she" << std::endl;
        //std::cout << Totale;
    }
    //std::cout << "!" << m_num << "!";
    Totale = Totale + m_sommet[m_chemin[0]-1]->getPoidPred(m_num);
    //std::cout << Totale;
    return Totale;
}

int Sommet::getPoidPred(int num)
{
    for (unsigned int j = 0; j < m_succ.size() ; j++)
    {
        //std::cout << "#" << m_succ[j]->getNumSecond() << "#" << std::endl;
        if(m_succ[j]->getNumSecond() == num)
        {
            //std::cout << "#" << m_succ[j]->getPoid()<<"#";
            return m_succ[j]->getPoid();
        }
    }
}
void Sommet::afficherPred(std::vector <Sommet*> m_sommet,int arriver)
{
    std::vector <int> chemin = m_chemin;
    std::vector <int> cheminA;
    std::reverse(chemin.begin(),chemin.end());
    for (unsigned int i = 0; i < chemin.size() ; i++)
    {
        std::cout << m_sommet[chemin[i]-1]->getNum() << "--";

    }
    std::cout << m_sommet[arriver]->getNum();
    ///rajouter l'arriver/////////////

    /*int Totale = 0;
    for (int i = 0 ; i < m_chemin.size()-1 ; i++)
    {
    std::cout << m_sommet[m_chemin[i+1]-1]->getPoidPred2(m_chemin[i],cheminA) << " + ";
    }
    std::cout << m_sommet[m_chemin[0]-1]->getPoidPred(m_num);
    std::cout << std::endl << std::endl << chemin.size() << cheminA.size();*/
}

int Sommet::getPoidPred2(int num,std::vector <int> &cheminA)
{
    for (unsigned int j = 0; j < m_succ.size() ; j++)
    {
        //std::cout << "#" << m_succ[j]->getNumSecond() << "#" << std::endl;
        if(m_succ[j]->getNumSecond() == num)
        {
            cheminA.push_back(m_succ[j]->getNum());
            return m_succ[j]->getPoid();
        }
    }
}
