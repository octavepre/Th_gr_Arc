#include <iostream>
#include "Graphe.h"
#include "Sommet.h"


void menu(Graphe& ski)
{
    int menu=0;
    do
    {
        system("cls");
        std::cout << "SUPER TRAVELLER 3000"<<std::endl;
        std::cout << "Vous aide a vous trouvez le meilleur chemin selon VOTRE niveau" << std::endl;
        std::cout << "0. Afficher toute les stations" <<std::endl;
        std::cout << "1. Chercher l'itineraire le plus rapide" <<std::endl;
        std::cout << "2. Chercher l'itineraire le plus court" <<std::endl;
        std::cout << "3. Vos chemin prefere" <<std::endl;
        std::cout << "4. Creer profile" << std::endl;
        std::cout << "5. Flot max" <<std::endl;
        std::cout << "6. Quitter" <<std::endl;
        do
        {
            std::cin >> menu;
        }
        while(menu < 0 || menu > 6);

        switch (menu)
        {
        case 0:///on afficher tout les sommet avec leur adjacence
        {
            system("cls");
            ski.afficher();
            system("pause");
            break;
        }
        case 1: /// on cherche l'itineraire le plus rapide a l'aide de dijkstra
        {
            int depart=0,arriver=0;
            do
            {
                system("cls");
                std::cout << "Dans quel station etes vous ?" << std::endl;
                std::cin >> depart;
                std::cout << "Dans quel station souhaitez vous vous rendre ?" << std::endl;
                std::cin >> arriver;
            }
            while(depart < 1 || depart > 37 || arriver < 1 || arriver > 37 ||depart == arriver);
            system("cls");
            ski.setPoidDescente(DEFAULT);///On set les poid en temps
            ski.Dijkstra(depart-1,arriver-1,0);
            std::cout<<std::endl<<"0. Quitter"<<std::endl;
            int shee;
            do
            {
                std::cin >> shee;
            }
            while(shee != 0);
            break;
        }
        case 2:///on cherche le chemin le plus court entre une station et une autre soit BFS
        {
            int depart=0,arriver=0;
            do
            {
                system("cls");
                std::cout << "Dans quel station etes vous ?" << std::endl;
                std::cin >> depart;
            }
            while(depart < 1 || depart > 37);
            system("cls");
            ski.BFS(depart-1);
            std::cout<<std::endl<<"0. Quitter"<<std::endl;
            int shee;
            do
            {
                std::cin >> shee;
            }
            while(shee != 0);
            break;
        }
        case 3:///On utilise les fichier pour aller chercher les preference ainsi quel es username
        {
            ski.setUtiliserToFalse();
            system("cls");
            ski.setPoidDescente (1);///on set les poid avec les preferences
            system("cls");
            int depart=0,arriver=0;
            if(ski.getUtiliser() == true)///si on a trouver un username qui convient
            {
                do
                {
                    system("cls");
                    std::cout << "Dans quel station etes vous ?" << std::endl;
                    std::cin >> depart;
                    std::cout << "Dans quel station souhaitez vous vous rendre ?" << std::endl;
                    std::cin >> arriver;
                }
                while(depart < 1 || depart > 37 || arriver < 1 || arriver > 37 ||depart == arriver);
                system("cls");
                //  std::cout << "SHEEEEEE";
                ski.Dijkstra(depart-1,arriver-1,1);///on effectue un dijkstra avec les poid set en preference
                std::cout<<std::endl<<"0. Quitter"<<std::endl;
                int shee;
                do
                {
                    std::cin >> shee;
                }
                while(shee != 0);
            }
            else if(ski.getUtiliser() == false)
            {
                std::cout << "Il n'existe pas de compte a ce nom." << std::endl;
                system("pause");
            }
            break;
        }
        case 4:
        {
            ski.setPoidDescente (2);///on enregistre les préference
            break;
        }
        case 5:///FLOT CASSER
        {
            //system("cls");
            int source = 0,puit = 0;

            do
            {
                system("cls");
                std::cout << "Choisissez une source." << std::endl;
                std::cin >> source;
                 std::cout << "Choisissez un puit." << std::endl;
                 std::cin >> puit;
            }
            while(source < 1 || source > 37 || puit < 1 || puit > 37 || puit == source);
            ///Inutile on a deja les adjacence
            //ski.CreaMatriceAdja();

            ///https://www.youtube.com/watch?v=GoVjOT30xwo&ab_channel=QuinstonPimenta
            ///Pour les flots je me suis inspiré de ca
            //ski.Clear(source-1,puit-1);
            ski.Flot(source,puit);
            std::cout << std::endl;
            system("pause");
            break;
        }
        case 6:///Quitte
        {
            system("cls");
            //std::cout << "SHEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE";
            //std::cout << "Eh merce";
            //ski.BFS2(2,6);
            system("pause");
            break;
        }
        }
    }
    while(menu != 6);
}


int main()
{
    Graphe ski("data_arcs.txt");
    menu(ski);
    return 0;
}
