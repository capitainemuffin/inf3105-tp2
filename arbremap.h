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
#include <iostream>
#include <limits>

/**
 * Représentation d'un ArbreMap
 */
class ArbreMap {

public:

    /**
    * Constructeur d'un <ArbreMap> vide
    */
    ArbreMap();

    /**
    * Destructeur d'un <ArbreMap>
    */
    ~ArbreMap();

    /**
    * Insère un <Noeud> dans <ArbreMap>
    *
    * @param cle début de l'intervale
    * @param valeur fin de l'intervale
    */
    void inserer(double, double);

    /**
    * Retourne le maxima de la Racine
    *
    * @return a Maxima de l'instance <ArbreMap>
    */
    double maxima() const;

    /** *
    * Retourne le maxima d'un Noeud.
    *
    * @param cle la clé du Noeud
    *
    * @return le maxima du Noeud
    */
    double maxima(double) const;

    /**
    * Retourne une liste des intervales dont la clé est plus petite ou égale à la
    * clé donnée en paramètre.
    *
    * @param cle la clé à tester
    *
    * @return std::vector <std::pair<double, double> > une liste des intervales
    */
    std::vector<std::pair<double, double>> jusqua(double) const;

    /**
    * Retourne la valeur maximale des valeurs associées aux clés plus petites ou égales à <cle>
    *
    * @param cle
    *
    * @return maxima le maxima des valeurs plus petites ou égales à <cle>
    */
    double aGauche(double) const;

    std::string appartient(double) const;

    //méthodes avec Iterateur

    class Iterateur;

    /**
    * Renvoi un itérateur pointant sur le plus petit <Noeud> de l'arbre.
     *
    * @return iter <Iterateur>
    */
    Iterateur debut() const;

    /**
    * Surcharge de []. Accède à un élément de <ArbreMap> avec un <Iterateur>.
    *
    * @param iter <Iterateur>
    *
    * @return un <std::tuple> contenant la clé, la valeur et le maxima du Noeud.
    */
    std::tuple<double, double, double> operator[](const Iterateur &) const;

    /**
    * Représentation d'un Noeud
    */
    class Noeud {

    public:

        /**
        * Constructeur d'un Noeud
        *
        * @param cle la clé à insérer dans l'arbre
        * @param valeur la valeur associée à la clé
        */
        Noeud(double, double);

        double cle;
        double valeur;
        double a;
        int equilibre;
        Noeud *gauche, *droite;

    };

    Noeud *racine;

    //méthodes avec Noeud

    /**
    * Insère un <Noeud> dans <ArbreMap>
    *
    * @param cle début de l'intervale.
    * @param valeur fin de l'intervale.
    * @param noeud <Noeud> racine de <ArbreMap>
    *
    * @return True si la hauteur a augmentée, False sinon.
    */
    bool inserer(double, double, Noeud *&noeud);

    /**
    * Fait la rotation de gauche à droite
    *
    * @param racine
    */
    void rotationGaucheDroite(Noeud *&);

    /**
    * Fait la rotation de droite à gauche
    *
    * @param racine
    */
    void rotationDroiteGauche(Noeud *&);

    /**
    * Supprime l'arbre
    */
    void vider();

    /**
    * Supprime le noeud et ses descendants.
    *
    * @param noeud racine du sous-arbre à supprimer
    */
    void vider(Noeud *&);

    /**
    * Mets à jour le Maxima de tous les Noeuds de l'arbre.
    *
    * @param racine premier Noeud de l'arbre.
    */
    void miseAjourMaxima(Noeud *&);

    /**
     * Représentation d'un Itérateur
     */
    class Iterateur {

    public:

        /**
        * Constructeur Iterateur
        *
        * @param arbre un arbre binaire ArbreMap
        */
        explicit Iterateur(const ArbreMap &);

        /**
        * Surcharge de ++(). Pré-increment de <Iterateur>.
        *
        * @return l'itérateur
        */
        Iterateur &operator++();

    private:

        const ArbreMap &arbre_associe;
        Pile<Noeud *> chemin;
        Noeud *courant;

        friend class ArbreMap;

    };

};

#endif

