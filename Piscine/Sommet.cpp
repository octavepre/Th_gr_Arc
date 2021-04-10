#include "Sommet.h"

Sommet::Sommet(int num,std::string nomLieu,int altitude):m_num(num),m_nomLieu(nomLieu),m_altitude(altitude),m_visite(false),m_state(0){}

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

void Sommet::getSuc(std::vector<int>* suc)
{
    for(unsigned int i = 0 ; i < m_succ.size() ; i++)
    {
        std::cout << m_succ[i]->getNumSecond() << " ";
        suc->push_back(m_succ[i]->getNumSecond());
    }
}

int Sommet::getSuccNum(int i)
{
    return m_succ[i]->getNumSecond();
}
///getSuccPoid ?

int Sommet::calculPoid(std::vector <Sommet*> m_sommet)
{

    int Totale = 0;
    //std::cout << "!" << Totale + m_sommet[m_chemin[0]-2]->getPoidPred(m_num) << "!";
    for (int i = 0 ; i < m_chemin.size()-1 ; i++)
    {
        //std::cout << "!" << m_sommet[m_chemin[i+1]-1]->getNum() << "!";
        //std::cout << m_PoidCheminArete.size() << std::endl;

        //Totale = Totale + m_sommet[m_chemin[i+1]-1]->getPoidPred2(m_chemin[i],m_PoidCheminArete[i+1]);
        Totale = Totale + m_sommet[m_chemin[i+1]-1]->getPoidPred(m_chemin[i],m_cheminArete[i+1]);

        //std::cout << "she" << m_sommet[m_chemin[i+1]-1]->getPoidPred2(m_chemin[i],m_PoidCheminArete[i+1]) << "she" << std::endl;
        //std::cout << Totale;
    }
    //std::cout << "!" << m_num << "!";
    Totale = Totale + m_sommet[m_chemin[0]-1]->getPoidPred(m_num,m_cheminArete[0]);
    //std::cout << Totale;
    return Totale;
}

int Sommet::getPoidPred(int num,int numArete)
{
    for (unsigned int j = 0; j < m_succ.size() ; j++)
    {
        //std::cout << "#" << m_succ[j]->getNumSecond() << "#" << std::endl;
        if(m_succ[j]->getNumSecond() == num && m_succ[j]->getNum() == numArete)
        {
            //std::cout << "#" << m_succ[j]->getPoid()<<"#";
            return m_succ[j]->getPoid();
        }
    }
}
void Sommet::afficherPred(std::vector <Sommet*> m_sommet,std::vector <Arete*> m_aretes)
{
    std::cout << getNum() << "<---";
    for(unsigned int i = 0; i <m_chemin.size() ; i++)
    {
        if(i<m_chemin.size()-1){
        std::cout << "|" << m_aretes[m_cheminArete[i]-1]->getType() << "|{" << m_aretes[m_cheminArete[i]-1]->getNom() << "} ";
        std::cout << m_sommet[m_chemin[i]-1]->getNum();
        std::cout << "<---";}
        else{
        std::cout << "|" << m_aretes[m_cheminArete[i]-1]->getType() << "|{" << m_aretes[m_cheminArete[i]-1]->getNom() << "} ";
        std::cout << m_sommet[m_chemin[i]-1]->getNum();
        }
    }
    std::cout << std::endl;
}

void Sommet::setPrede(Sommet* b)
{
    m_predecesseur.push_back(b);
    for(size_t i(0); i < (b->getPrede().size()); i++)
    {
        m_predecesseur.push_back(b->getPrede()[i]);
    }
}



int Sommet::getPoid(int i)const{return m_succ[i]->getPoid();}
int Sommet::size_poidPred()const{return m_PoidCheminArete.size();}
int Sommet::getPoidChemin(int i)const{return m_PoidCheminArete[i];}
int Sommet::getNumArete(int i)const{return m_succ[i]->getNum();}
