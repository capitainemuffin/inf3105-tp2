/**
 * Déclarations pour ArbreMap, Noeud et Iterateur
 *
 * AUTEUR(S):
 *  1) Sofiane Selaoui SELS28049204
 *
 */

#if !defined(__ARBREMAP_H__)
#define __ARBREMAP_H__
#include "pile.h"
#include <cassert>
#include <utility>
#include <vector>
#include <string>
#include <tuple>

/**
 * Représentation d'un ArbreMap
 */
class ArbreMap {

public:

    ArbreMap();
    ~ArbreMap();

    //méthodes avec clé/valeur

    void inserer(double, double);
    double maxima() const;
    double maxima(double) const;
    std::vector<std::pair<double, double> > jusqua(double) const;
    double aGauche(double);
    std::string appartient(double) const;

    //méthodes avec Iterateur

    class Iterateur;
    Iterateur debut() const;
    Iterateur recherche(double) const;
    Iterateur egalOuPrecedent(double) const;

    //surcharge d'opérateurs
    friend std::istream& operator>>(std::istream&, ArbreMap&);
    std::tuple<double, double, double> operator[] (const Iterateur& ) const;

    /**
     * Représentation d'un Noeud
     */
    class Noeud {

    public:

        Noeud(double, double);
        double cle;
        double valeur;
        double a;
        int equilibre;
        Noeud *gauche, *droite;

    };

    Noeud* racine;

    //méthodes avec Noeud

    bool inserer(double, double, Noeud*& noeud);
    void rotationGaucheDroite(Noeud*&);
    void rotationDroiteGauche(Noeud*&);
    void copier(const Noeud*, Noeud*&) const;
    void vider(Noeud*&);
    void miseAjourMaxima(Noeud*&);

    /**
     * Représentation d'un Itérateur
     */
    class Iterateur {

    public:

        Iterateur(const ArbreMap&);
        Iterateur(const Iterateur&);
        Iterateur(const Iterateur&, Noeud*);

        // surcharge d'opérateurs

        operator bool() const;
        bool operator !() const;
        bool operator == (const Iterateur&) const;
        bool operator != (const Iterateur&) const;
        Iterateur& operator ++ ();

    private:

        const ArbreMap& arbre_associe;
        Pile<Noeud*> chemin;
        Noeud* courant;

        friend class ArbreMap;

    };

};

#endif

