#include "Graphe.h"

void questionnaire()
{
    std::cout << std::endl;
    std::cout << "1. Pas Empreintable" << std::endl;
    std::cout << "2. Je n'aime pas" << std::endl;
    std::cout << "3. Pas d'avis/neutre" << std::endl;
    std::cout << "4. J'aime" << std::endl;
    std::cout << "5. J'adore !/C'est ce que je cherche !" << std::endl;
}

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
    case 1:
    {
        for (int i = 0 ; i < 12; i++)
        {
            system("cls");
            int P = 0;
            if(i==0)
                std::cout << "Aimez vous les pistes verte ?" << std::endl;
            if(i==1)
                std::cout << "Aimez vous les pistes bleu ?" << std::endl;
            if(i==2)
                std::cout << "Aimez vous les pistes rouge ?" << std::endl;
            if(i==3)
                std::cout << "Aimez vous les pistes noir ?" << std::endl;
            if(i==4)
                std::cout << "Aimez vous les pistes de kilometre lance ?" << std::endl;
            if(i==5)
                std::cout << "Aimez vous les snowpark ?" << std::endl;
            if(i==6)
                std::cout << "Aimez vous les telepherique ?" << std::endl;
            if(i==7)
                std::cout << "Aimez vous les telecabine ?" << std::endl;
            if(i==8)
                std::cout << "Aimez vous les telesiege debrayable ?" << std::endl;
            if(i==9)
                std::cout << "Aimez vous les telesiege ?" << std::endl;
            if(i==10)
                std::cout << "Aimez vous les teleski ?" << std::endl;
            if(i==11)
                std::cout << "Aimez vous prendre le bus ?" << std::endl;

            questionnaire();
            do
            {
                std::cin >> P;
            }
            while (P < 1 || P > 5);

            for (unsigned int j = 0 ; j < m_aretes.size() ; j++)
            {
                m_aretes[j]->calculPoid2(P);
            }
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
    while(AllTrue(listeChemin) == false /*&& m_sommets[current]->getNum() != arriver+1*/)
    {
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
        /*if(listeChemin.size() !=0 )
            std::cout << "{" <<pivot.getNum()<<"}"<<pivot.calculPoid(m_sommets)<<"|" << std::endl;*/
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
    }
    else
    {
        int compt = 0;
        float minute = pivot.calculPoid(m_sommets);
        std::cout << "Temps totale en minutes :" << (minute)/100/60 << std::endl;
        //pivot.afficherPred(m_sommets,arriver);
        std::vector <int> chemin = pivot.getChemin();
        std::reverse(chemin.begin(),chemin.end());
        for (unsigned int i = 0; i < chemin.size()-1; i++)
        {
            std::cout << m_sommets[chemin[i]-1]->getNum() << " --> ";
            std::cout << findTypeArreteMin(m_sommets[chemin[i]-1]->getNum(), m_sommets[chemin[i+1]-1]->getNum());
            std::cout << " --> ";
            //std::cout << "--" << compt << "--";
            compt++;
        }
        std::cout << m_sommets[chemin[compt]-1]->getNum() << " --> " ;
        std::cout << findTypeArreteMin(m_sommets[chemin[compt]-1]->getNum(), m_sommets[arriver]->getNum());
        std::cout << " --> "<< m_sommets[arriver]->getNum()  ;
        std::cout << std::endl << std::endl;
    }
}

bool Graphe::AllTrue(std::vector <Sommet> listeChemin)const
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

std::string Graphe::findTypeArreteMin(int SommetD, int SommetA)
{
    std::vector<Arete*> cherche = m_aretes;
    std::vector<Arete*> tri;
    for(int i=0; i<cherche.size(); i++)
    {
        if((cherche[i]->getNumFirst() == SommetD) && (cherche[i]->getNumSecond() == SommetA))
        {
            tri.push_back(cherche[i]);
        }
    }
    int en_desordre = 1; // TRI A BULLE
    while (en_desordre)
    {
        en_desordre = 0;
        for (int j=0; j < tri.size()-1; j++)
        {
            if(tri[j]->getPoid() > tri[j+1]->getPoid())
            {
                std::swap(tri[j+1], tri[j]);
                en_desordre = 1;
            }
        }
    }
    return tri[0]->getType();
}

