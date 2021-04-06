#include "Graphe.h"


Graphe::Graphe(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    m_ordre=0;
    ifs >> m_ordre;
    for (int i = 0 ; i < m_ordre ; i++)
    {
        int num=0, altitude=0;
        std::string nomLieu;
        ifs >> num >> nomLieu >> altitude;
        Sommet* sommet = new Sommet(num,nomLieu,altitude);
        m_sommets.push_back(sommet);///LE NUMERO 0 DU VECTOR EST LE NUMERO 1 DES SOMMETS
    }
    int tailleArete=0;
    ifs >> tailleArete;
    for(int i = 0 ; i<tailleArete ; i++)
    {
        int num=0,numero1=0,numero2=0;
        std::string nomTrajet,type;
        ifs >> num >> nomTrajet >> type >> numero1 >> numero2;
        Arete* arete = new Arete(num,nomTrajet,type,m_sommets[numero1-1],m_sommets[numero2-1]);
        m_aretes.push_back(arete);
        m_sommets[numero1-1]->addSucc(arete);
    }
    setPoidDescente(DEFAULT);
}

void Graphe::afficher()
{
    std::cout << "Lise des Sommets: " << std::endl;
    for(unsigned int i = 0 ; i < m_sommets.size() ; i++)
    {
        //std::cout << "      Arrete " << i+1;
        m_sommets[i]->afficherS();
        std::cout << std::endl;
    }
}

///la variable typeDescente permettra plus tard de changer le temps pour faire une piste d'un skieur selon son niveau
///Exemple: par defaut 0 (les poid de la consigne appliqué)
///Exemple 2: 1 represente skieur débutant -> les noir lui prend 6x plus de temps
///donc recalcul du temps a partir cette fonction
void Graphe::setPoidDescente(int typeDescente)
{
    switch (typeDescente)
    {
    case 0:
        {
            for(unsigned int i = 0 ; i < m_aretes.size() ; i++)
            {
                m_aretes[i]->calculPoid(typeDescente);
            }
            break;
        }
    }
}

void Graphe::Dijkstra(int depart,int arriver)
{
    //std::cout << depart;
    int current = depart;
    int fin = arriver;
    std::vector <Sommet> listeChemin;
    listeChemin.push_back(*m_sommets[current]);
    Sommet pivot = listeChemin[0];
    int compteur=1;
    //std::cout << "[" << m_sommets[depart]->getNum() << "," << m_sommets[arriver]->getNum() << "]";
    //std::cout << "[" << pivot.getNum() <<"]";
    while(AllTrue(listeChemin) == false && m_sommets[current]->getNum() != arriver+1)
    {
        //std::cout << "Etape 1 faite:je rentre" << std::endl;
        ///On ajoute les sortants(successeurs) du chemin actuel dans les nouveaux chemin possible
        for(unsigned int i = 0 ; i < m_sommets[current]->size_succ() ; i++)
        {
             int transition = m_sommets[current]->getSuccNum(i)-1;
             int poid = m_sommets[current]->getPoid(i);
             //std::cout << "[" << m_sommets[transition]->getNum() << "]";
             ///Si le sommet n'a pas été visité on l'ajoute dans les chemins potentiel
            if(m_sommets[transition]->getVisite() == false && m_sommets[current]->getVisite() == false)
            {
                Sommet preservationPred = *m_sommets[transition];
                preservationPred.push_poidPred(poid);
                preservationPred.push_pred(m_sommets[current]->getNum());
                for (int i = 0; i < pivot.size_pred() ; i++)
                {
                    preservationPred.push_pred(pivot.GetPred(i));///il va le chercher dans m_chemin
                }
                for(unsigned int i = 0 ; i < pivot.size_poidPred() ; i++)
                {
                    preservationPred.push_poidPred(pivot.getPoidChemin(i));
                }
                listeChemin.push_back(preservationPred);
            }
        }
        //std::cout << "Etape 2 faite:je'accede au succ" << std::endl;
        ///permet de ne pas comparé une distance de 0 avec le reste
        ///on enleve le sommet de départ juste apres avoir ajouter ces successeurs
        if (compteur == 1)
        {
            listeChemin.erase(listeChemin.begin());
            if(listeChemin.size() !=0 )
                pivot = listeChemin[0];
            compteur = 0;
        }

        ///on dit que le sommet qui a ajouter ces successeurs a été visité
        m_sommets[current]->setVisiteToTrue();
        ///ainsi que tout les chemin qui ont le meme numéro que lui
        setVisiteToTrueAll(listeChemin,current + 1);
        //std::cout << "Etape 3 faite:je passe ce qu'il faut en True" << std::endl;

        ///METTRE LA LE POID DES ARRETE DANS LE CHEMIN
        for(int i = 0 ; i < listeChemin.size() ; i++)
        {

            if(pivot.calculPoid(m_sommets) > listeChemin[i].calculPoid(m_sommets) && listeChemin[i].getVisite() == false)
            {
                pivot = listeChemin[i];
            }
            else if (pivot.calculPoid(m_sommets) == listeChemin[i].calculPoid(m_sommets) && listeChemin[i].getVisite() == false)
            {
                pivot = listeChemin[i];
            }
        }
        //std::cout << "Etape 4 faite:j'ai comparé les chemins et je prend le plus cours pas utilisé" << std::endl;


        /*if(listeChemin.size() !=0 )
            std::cout<< "{" <<pivot.getNum()<<"}"<<pivot.calculPoid(m_sommets)<<"|" << std::endl;*/

        if(pivot.getNum() == current + 1)
        {
            for(int i = 0 ; i < listeChemin.size() ; i++)
            {
                if(listeChemin[i].getVisite() == false)
                {
                    pivot = listeChemin[i];
                }
            }
        }
         //std::cout << "Etape 5 faite:peut etre ai'je ete dans un cul de sac et j'en sors peut etre en changenat de sommet" << std::endl;
        ///on change le numero du current qui est le numero du sommet qui est entrain d'etre utilisé
        current = pivot.getNum()-1;


        ///TESTE/////////////////////////////////////////////////////////////////////////////////////////////////
        /*for (unsigned int i = 0 ; i < listeChemin.size() ; i++)
        {
            std::cout << listeChemin[i].getNum() <<std::endl;
        }
        //std::cout << "Etape 6 wtf" << std::endl;
        std::cout <<std::endl<<std::endl;*/

    }
    ///Pour aller trouver le bon dans tout ceux qu'on a vu
    for(int i = 0;  i < listeChemin.size() ; i++)
    {
        if(pivot.calculPoid(m_sommets) > listeChemin[i].calculPoid(m_sommets) && listeChemin[i].getNum() == m_sommets[arriver]->getNum())
            {
                pivot = listeChemin[i];
            }
    }
    if(pivot.getNum() != arriver + 1)
    {
        std::cout << "Desoler il n'y y a pas de chemin possible pour aller a cette station." << std::endl;
    }else
    {
        std::cout << "Poid totale :" << pivot.calculPoid(m_sommets) << std::endl;
        pivot.afficherPred(m_sommets,arriver);
    }
}

bool Graphe::AllTrue(std::vector <Sommet> listeChemin)const ///LE PROBLEME VIEN DE LA
{

    int compteur = 0;
    for(unsigned int  i = 0 ; i < listeChemin.size() ; i++)
    {
        if(m_sommets[listeChemin[i].getNum()-1]->getVisite() == true)
        {
            compteur++;
        }
    }
    if(compteur == listeChemin.size())
    {
        return true;
    }
    else if (compteur != listeChemin.size())
    {
        return false;
    }
}
void Graphe::setVisiteToTrueAll(std::vector <Sommet>& listeChemin,int current)
{
    for(unsigned int i = 0; i < listeChemin.size() ; i++)
    {
        if (listeChemin[i].getNum() == current)
        {
            listeChemin[i].setVisiteToTrue();
        }

    }
}
