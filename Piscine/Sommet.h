#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED
#include <iostream>
#include <vector>
//#include "Arete.h"
class Arete;

class Sommet
{
private:
    int m_num;
    std::string m_nomLieu;
    int m_altitude;
    std::vector <Arete*> m_succ;
    bool m_visite;

    std::vector <int> m_chemin;///POUR DIJKSTRA

public:
    Sommet(int num,std::string nomLieu,int altitude);
    int getNum()const{return m_num;}
    void addSucc(Arete* succ);
    void afficherS();
    std::string getNom()const{return m_nomLieu;}
    int getAltitude()const{return m_altitude;}
    bool getVisite()const{return m_visite;}

};

class Arete
{
private:
    int m_num;
    std::string m_trajet;
    int m_poid;
    std::pair <Sommet*,Sommet*> m_lien;
    std::string m_type;
public:
    Arete(int num,std::string nomTrajet,std::string type,Sommet* numero1,Sommet* numero2);
    int getNumSecond()const{return m_lien.second->getNum();}
    void afficherA();
    void calculPoid(int typeDescente);
    int getPoid()const{return m_poid;}

};

#endif // SOMMET_H_INCLUDED
