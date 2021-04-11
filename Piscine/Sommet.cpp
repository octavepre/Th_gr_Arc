#include "Sommet.h"

Sommet::Sommet(int num,std::string nomLieu,int altitude):m_num(num),m_nomLieu(nomLieu),m_altitude(altitude),m_visite(false),m_state(0){}

void Sommet::addSucc(Arete* succ)
{
    m_succ.push_back(succ);
}

///fonction d'affichage
void Sommet::afficherS()
{
    std::cout << "Station " << getNom() << " : ";
    for(unsigned int i = 0 ; i < m_succ.size() ; i++)
    {
        std::cout<<std::endl;
        std::cout << m_succ[i]->getNumSecond() << " ((Type : " << m_succ[i]->getType()<<  " // Poids : " << m_succ[i]->getPoid() << "))" <<" ";///AFFICHER LE POID A COTER DES SOMMETS EN SECONDE
    }
    std::cout<<std::endl;
}

///permet de recuperer les succ
void Sommet::getSuc(std::vector<int>* suc, std::vector<int>* flo)
{
    for(unsigned int i = 0 ; i < m_succ.size() ; i++)
    {
        //std::cout << m_succ[i]->getNumSecond() << " ";
        suc->push_back(m_succ[i]->getNumSecond());
        //std::cout << m_succ[i]->getFlow() << " " ;
        flo->push_back(m_succ[i]->getFlo());
    }
}

///permet de recuperer le numero du successeur
int Sommet::getSuccNum(int i)
{
    return m_succ[i]->getNumSecond();
}
///getSuccPoid ?

///calcul le poid avec les predecesseur dans dijkstra
int Sommet::calculPoid(std::vector <Sommet*> m_sommet)
{
    int Totale = 0;
    for (int i = 0 ; i < m_chemin.size()-1 ; i++)
    {
        Totale = Totale + m_sommet[m_chemin[i+1]-1]->getPoidPred(m_chemin[i],m_cheminArete[i+1]);
    }
    Totale = Totale + m_sommet[m_chemin[0]-1]->getPoidPred(m_num,m_cheminArete[0]);
    return Totale;
}

///recupere le poid s'un sommet a partir du precedecesseur
int Sommet::getPoidPred(int num,int numArete)
{
    for (unsigned int j = 0; j < m_succ.size() ; j++)
    {
        //std::cout << "#" << m_succ[j]->getNumSecond() << "#" << std::endl;
        if(m_succ[j]->getNumSecond() == num && m_succ[j]->getNum() == numArete)/// en regardant l'arrete a prendre et le sommet a prendre
        {
            //std::cout << "#" << m_succ[j]->getPoid()<<"#";
            return m_succ[j]->getPoid();
        }
    }
}
///affiche les predecesseur dans dijkstra
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

///garder les predecesseur dans le BFS
void Sommet::setPrede(Sommet* b)
{
    m_predecesseur.push_back(b);
    for(size_t i(0); i < (b->getPrede().size()); i++)
    {
        m_predecesseur.push_back(b->getPrede()[i]);
    }
}

///UTILISER DANS LES FLOT MAIS FLOT NON OPERATIONNEL
std::vector<Arete*> Sommet::getPredeA()const
{
    return m_predecesseurA;
}
///UTILISER DANS LES FLOT MAIS FLOT NON OPERATIONNEL
void Sommet::setPrede2(Sommet* b,Arete* a)
{
    m_predecesseur.push_back(b);
    for(size_t i(0); i < (b->getPrede().size()); i++)
    {
        m_predecesseur.push_back(b->getPrede()[i]);
    }
    m_predecesseurA.push_back(a);
    for(size_t i(0); i < (b->getPredeA().size()); i++)
    {
        m_predecesseurA.push_back(b->getPredeA()[i]);
    }
}

///permet de reset le BFS
void Sommet::restorePrede()
{
    m_predecesseur.clear();
    m_predecesseurA.clear();
}

///UTILISER DANS LES FLOT MAIS FLOT NON OPERATIONNEL
Arete* Sommet::getSucc(int i)
{
    return m_succ[i];
}

///UTILISER DANS LES FLOT MAIS FLOT NON OPERATIONNEL
int Sommet::flowMax()
{
    Arete* pivot = m_predecesseurA[0];
    int Max=0;

    for(unsigned int i = 0; i < m_predecesseurA.size() ; i ++)
    {
        if(pivot->getFlo() > m_predecesseurA[i]->getFlo())
        {
            //std::cout << pivot->getFlow() << std::endl;
            pivot = m_predecesseurA[i];
        }
    }
    Max = pivot->getFlo();
    for(unsigned int i = 0; i < m_predecesseurA.size() ; i ++)
    {
        m_predecesseurA[i]->MoinsFlow(pivot->getFlo());
    }
    //std::cout << "[" << Max << "]" << std::endl;
    return Max;
}

int Sommet::getPoid(int i)const{return m_succ[i]->getPoid();}
int Sommet::size_poidPred()const{return m_PoidCheminArete.size();}
int Sommet::getPoidChemin(int i)const{return m_PoidCheminArete[i];}
int Sommet::getNumArete(int i)const{return m_succ[i]->getNum();}

int Sommet::getFlow(int S)const
{
    for (int i(0); i<m_succ.size() ; i++)
    {
        if(m_succ[i]->getNumSecond() == S)
        {
            return m_succ[i]->getFlo();
        }
    }
}

void Sommet::setFlow(int S,int B)
{
    for (int i(0); i<m_succ.size() ; i++)
    {
        if(m_succ[i]->getNumSecond() == S)
        {
            m_succ[i]->setFlow(B);
        }
    }
}
