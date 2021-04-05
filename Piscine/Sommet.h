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
    int size_succ()const{return m_succ.size();}
    int getSuccNum(int i);
    int size_pred()const{return m_chemin.size();}
    void push_pred(int i){m_chemin.push_back(i);}
    int GetPred(int i){return m_chemin[i];}
    void setVisiteToTrue(){m_visite = true;}
    int calculPoid(std::vector <Sommet*> m_sommet,int depart);
    int getPoidPred(int num);


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
    std::string getType() const {return m_type;}
    int getNumFirst()const{return m_lien.first->getNum();}

};

#endif // SOMMET_H_INCLUDED
