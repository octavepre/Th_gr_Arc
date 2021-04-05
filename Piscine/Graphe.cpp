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
///Exemple: par defaut 0 (les poid de la consigne appliqu�)
///Exemple 2: 1 represente skieur d�butant -> les noir lui prend 6x plus de temps
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
    int current = depart;
    std::vector <Sommet> listeChemin;
    listeChemin.push_back(*m_sommets[current]);
    Sommet pivot = listeChemin[0];
    int compteur=1;
    //std::cout << "[" << m_sommets[depart]->getNum() << "," << m_sommets[arriver]->getNum() << "]";
    //std::cout << "[" << pivot.getNum() <<"]";
    while(AllTrue(listeChemin) == false /*&& m_sommets[current]->getNum() != arriver*/)
    {
        ///On ajoute les sortants(successeurs) du chemin actuel dans les nouveaux chemin possible
        for(unsigned int i = 0 ; i < m_sommets[current]->size_succ() ; i++)
        {
             int transition = m_sommets[current]->getSuccNum(i)-1;
             //std::cout << "[" << m_sommets[transition]->getNum() << "]";
             ///Si le sommet n'a pas �t� visit� on l'ajoute dans les chemins potentiel
            if(m_sommets[transition]->getVisite() == false && m_sommets[current]->getVisite() == false)
            {
                Sommet preservationPred = *m_sommets[transition];
                preservationPred.push_pred(m_sommets[current]->getNum());
                for (int i = 0; i < pivot.size_pred() ; i++)
                {
                    preservationPred.push_pred(pivot.GetPred(i));
                }
                listeChemin.push_back(preservationPred);
            }
        }

        ///permet de ne pas compar� une distance de 0 avec le reste
        ///on enleve le sommet de d�part juste apres avoir ajouter ces successeurs
        if (compteur == 1)
        {
            listeChemin.erase(listeChemin.begin());
            pivot = listeChemin[0];
            compteur = 0;
        }
        ///on dit que le sommet qui a ajouter ces successeurs a �t� visit�
        m_sommets[current]->setVisiteToTrue();
        ///ainsi que tout les chemin qui ont le meme num�ro que lui
        setVisiteToTrueAll(listeChemin,current);


        for(int i = 0 ; i < listeChemin.size() ; i++)
        {

            if(pivot.calculPoid(m_sommets,depart) > listeChemin[i].calculPoid(m_sommets,depart) && listeChemin[i].getVisite() == false)
            {
                pivot = listeChemin[i];
            }
            else if (pivot.calculPoid(m_sommets,depart) == listeChemin[i].calculPoid(m_sommets,depart) && listeChemin[i].getVisite() == false)
            {
                pivot = listeChemin[i];
            }
        }
        std::cout<< "{" <<pivot.getNum()<<"}"<<pivot.calculPoid(m_sommets,depart)<<"|" << std::endl;
        if(pivot.getNum() == current)
        {
            for(int i = 0 ; i < listeChemin.size() ; i++)
            {
                if(listeChemin[i].getVisite() == false)
                {
                    pivot = listeChemin[i];
                }
            }
        }
        ///on change le numero du current qui est le numero du sommet qui est entrain d'etre utilis�
        current = pivot.getNum();


        ///TESTE/////////////////////////////////////////////////////////////////////////////////////////////////
        for (unsigned int i = 0 ; i < listeChemin.size() ; i++)
        {
            std::cout << listeChemin[i].getNum() <<std::endl;
        }
        std::cout <<std::endl<<std::endl;
    }
}

bool Graphe::AllTrue(std::vector <Sommet> listeChemin)const
{
    int compteur = 0;
    for(unsigned int  i = 0 ; i < listeChemin.size() ; i++)
    {
        if(m_sommets[listeChemin[i].getNum()]->getVisite() == true)
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
