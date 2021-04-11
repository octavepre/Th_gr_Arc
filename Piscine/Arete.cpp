#include "Sommet.h"

Arete::Arete(int num,std::string nomTrajet,std::string type,Sommet* numero1,Sommet* numero2)
    :m_num(num),m_trajet(nomTrajet),m_type(type),m_utiliser(false)
{
    m_lien = std::make_pair(numero1,numero2);
}



void Arete::calculPoid(int typeDescente)///Permet de calculer le temps pour chaque piste en seconde*100
{
    m_flow = 1000000;
    if (m_type == "V")///Verte
    {
        m_poid = (m_lien.first->getAltitude() - m_lien.second->getAltitude())*(5*60);///300s = 5 mn
    }
    else if (m_type == "B") ///Bleue
    {
        m_poid = (m_lien.first->getAltitude() - m_lien.second->getAltitude())*(4*60);///300s = 4 mn
    }
    else if (m_type == "R")  ///Rouge
    {
        m_poid = (m_lien.first->getAltitude() - m_lien.second->getAltitude())*(3*60);///3mn = 180s
    }
    else if (m_type == "N")  ///Noir
    {
        m_poid = (m_lien.first->getAltitude() - m_lien.second->getAltitude())*(2*60);///2mn = 120s
    }
    else if (m_type == "KL") ///Kilometre lancé
    {
        m_poid = (m_lien.first->getAltitude() - m_lien.second->getAltitude())*10;///10 second pour descendre 100m
    }
    else if (m_type == "TPH") ///Telephérique
    {
        m_poid = 4*60 + (m_lien.second->getAltitude() - m_lien.first->getAltitude())*(2*60);
        m_flow = 1200; //EN SKIEUR/HEURE
    }
    else if (m_type == "TC") ///Telecabine
    {
        m_poid = 2*60 + (m_lien.second->getAltitude() - m_lien.first->getAltitude())*(3*60);
        m_flow = 2200;
    }
    else if (m_type == "TSD")///Telesiege debrayable
    {
        m_poid = 1*60 + (m_lien.second->getAltitude() - m_lien.first->getAltitude())*(3*60);
        m_flow = 2500;
    }
    else if (m_type == "TS") ///Telesiege
    {
        m_poid = 1*60 + (m_lien.second->getAltitude() - m_lien.first->getAltitude())*(4*60);
        m_flow = 1800;
    }
    else if (m_type == "TK") ///Teleski
    {
        m_poid = 1*60 + (m_lien.second->getAltitude() - m_lien.first->getAltitude())*(4*60);
        m_flow = 800;
    }
    else if (m_type == "BUS") ///Bus
    {
        //std::cout << "{" << m_lien.first->getNum() << "}";
        if((m_lien.first->getNom() == "arc1600" && m_lien.second->getNom()=="arc2000")||(m_lien.second->getNom() == "arc1600" && m_lien.first->getNom()=="arc2000"))
        {
            m_poid = 40*60*100;
        }
        else if((m_lien.first->getNom() == "arc1600" && m_lien.second->getNom()=="arc1800")||(m_lien.second->getNom() == "arc1600" && m_lien.first->getNom()=="arc1800"))
        {
            m_poid = 30*60*100;
        }
        m_flow = 300;
    }
    else if (m_type == "SURF")
    {
        m_poid = (m_lien.first->getAltitude() - m_lien.second->getAltitude())*(10*60);
    }
}

void Arete::calculPoid2(int P)///Change le poid des aretes selon les preference du user
{
    if(m_type == "V" || m_type == "B" || m_type == "R" || m_type == "N" || m_type == "KL" || m_type == "SURF")
    {

        switch(P)
        {
        case 1:
        {
            m_poid = 10000000;///Quand c'est pas empreintable on met un nombre tres elever
            break;
        }
        case 2:
        {
            m_poid = 20;///on reduit au fur et a mesur
            break;
        }
        case 3:
        {
            m_poid = 6;
            break;
        }
        case 4:
        {
            m_poid = 3;
            break;
        }
        case 5:
        {
            m_poid = 0;
            break;
        }
        }
    }
    if(m_type == "TPH" || m_type == "TC" || m_type == "TSD" || m_type == "TS" || m_type == "TK" || m_type == "BUS")
    {
        switch(P)///on multiplie les valeur precedente pas 1.5 pour rajouter un aspect negatif au remonter
        {
        case 1:
        {
            m_poid = 10000000*1.5;
            break;
        }
        case 2:
        {
            m_poid = 20*1.5;
            break;
        }
        case 3:
        {
            m_poid = 6*1.5;
            break;
        }
        case 4:
        {
            m_poid = 3*1.5;
            break;
        }
        case 5:
        {
            m_poid = 0 + 2;
            break;
        }
        }
    }
}


void Arete::calculFlow()///permet de calculer flot
{
    if(m_type == "V" || m_type == "B" || m_type == "R" || m_type == "N" || m_type == "KL" || m_type == "SURF")///pour les piste on met un flot "illimité"
    {
        m_flow = 1000000;
    }
    ///pour le remonter on rentre les valeur de la consigne
    if(m_type == "TPH")
    {
        m_flow = 1200;
    }
    if(m_type == "TC")
    {
        m_flow = 2200;
    }
    if(m_type == "TSD")
    {
        m_flow = 2500;
    }
    if(m_type == "TS")
    {
        m_flow = 1800;
    }
    if(m_type == "TK")
    {
        m_flow = 800;
    }
    if(m_type == "BUS")
    {
        m_flow = 300;
    }
}

