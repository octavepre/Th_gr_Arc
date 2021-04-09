#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <vector>
#include <queue>
#include "Sommet.h"
//#include "Arete.h"
#include <fstream>
#define DEFAULT 0

class Graphe
{
private:
    std::vector <Sommet*> m_sommets;
    std::vector <Arete*> m_aretes;
    int m_ordre;
    bool m_utiliser;
public:
    Graphe(std::string nomFichier);
    void afficher();
    void setPoidDescente(int typeDescente);
    void Dijkstra(int depart,int arriver,int affichage);
    void BFS(int S0);
    bool AllTrue(std::vector <Sommet> listeChemin)const;
    void setVisiteToTrueAll(std::vector <Sommet>& PleaseWork,int current);
    void setUtiliserToTrue(){m_utiliser = true;}
    void setUtiliserToFalse(){m_utiliser = false;}
    bool getUtiliser()const{return m_utiliser;}
};

#endif // GRAPHE_H_INCLUDED
