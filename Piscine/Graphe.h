#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED
#include <vector>
#include <queue>
#include "Sommet.h"
//#include "Arete.h"
#include <fstream>
#define DEFAULT 0
#include <algorithm>

class Graphe
{
private:
    std::vector <Sommet*> m_sommets;
    std::vector <Arete*> m_aretes;
    int m_ordre;
    std::vector<std::vector<int>> m_matAdjacence;
    bool m_utiliser;
public:
    Graphe(std::string nomFichier);
    void afficher();
    void setPoidDescente(int typeDescente);
    void Dijkstra(int depart,int arriver,int affichage);
    void BFS(int S0);
    bool AllTrue(std::vector <Sommet> listeChemin)const;
    void setVisiteToTrueAll(std::vector <Sommet>& PleaseWork,int current);
    void CreaMatriceAdja();
    void setUtiliserToTrue(){m_utiliser = true;}
    void setUtiliserToFalse(){m_utiliser = false;}
    bool getUtiliser()const{return m_utiliser;}
    void Clear(int source,int puit);
    void Flot(int source,int puit);
    //bool BFS2(int source,int puit);
    int BFS2(int source,int puit);
};

#endif // GRAPHE_H_INCLUDED
