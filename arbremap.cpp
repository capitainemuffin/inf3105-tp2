/**
 * Implémentation de <ArbreMap>, <ArbreMap::Noeud> et <ArbreMap::Iterateur>
 *
 * AUTEUR(S):
 *  1) Sofiane Selaoui SELS28049204
 */

#include "arbremap.h"

/**
 * Constructeur d'un <ArbreMap> vide
 */
ArbreMap::ArbreMap() :
        racine(NULL) {}

/**
 * Destructeur d'un <ArbreMap>
 */
ArbreMap::~ArbreMap() {
    vider(this->racine);
}

/**
 * Constructeur d'un Noeud
 *
 * @param cle la clé à insérer dans l'arbre
 * @param valeur la valeur associée à la clé
 */
ArbreMap::Noeud::Noeud(double cle, double valeur) :
        cle(cle),
        valeur(valeur),
        a(valeur),
        equilibre(0),
        gauche(NULL),
        droite(NULL) {}

/**
 * Mets à jour le Maxima de tous les Noeuds de l'arbre.
 *
 * @param racine premier Noeud de l'arbre.
 */
void ArbreMap::miseAjourMaxima(Noeud *&racine) {

    if (racine->gauche) miseAjourMaxima(racine->gauche);
    if (racine->droite) miseAjourMaxima(racine->droite);

    if (racine->gauche && racine->gauche->a > racine->valeur) {

        racine->a = racine->gauche->a;

    }

    if (racine->droite && racine->droite->a > racine->valeur) {

        racine->a = racine->droite->a;
    }

    if (!racine->droite && !racine->gauche) {

        racine->a = racine->valeur;
    }

}

/**
 * Retourne la valeur maximale des valeurs associées aux clés plus petites ou égales à <cle>
 *
 * @param cle
 *
 * @return maxima le maxima des valeurs plus petites ou égales à <cle>
 */
double ArbreMap::aGauche(double cle) const {

    double maxima = std::numeric_limits<double>::lowest();

    std::vector<std::pair<double, double>> v = this->jusqua(cle);

    for (auto &noeud : v) {

        if (noeud.second > maxima) maxima = noeud.second;

    }

    return maxima;
}

/**
 * Insère un <Noeud> dans <ArbreMap>
 *
 * @param cle début de l'intervale
 * @param valeur fin de l'intervale
 */
void ArbreMap::inserer(double cle, double valeur) {

    if (cle > valeur) {
        std::cerr << "La clé ne peut être plus grande que la valeur." << std::endl;
        exit(-6);
    }

    inserer(cle, valeur, this->racine);
    miseAjourMaxima(this->racine);
}

/**
 * Insère un <Noeud> dans <ArbreMap>
 *
 * @param cle début de l'intervale.
 * @param valeur fin de l'intervale.
 * @param noeud <Noeud> racine de <ArbreMap>
 *
 * @return True si la hauteur a augmentée, False sinon.
 */
bool ArbreMap::inserer(double cle, double valeur, Noeud *&noeud) {

    bool augmente = false;

    if (!noeud) {

        noeud = new Noeud(cle, valeur);
        augmente = true;

    } else if (cle < noeud->cle) {

        if (inserer(cle, valeur, noeud->gauche)) {

            noeud->equilibre++;

            if (noeud->equilibre == 1) {

                augmente = true;

            } else if (noeud->equilibre == 2) {

                if (noeud->gauche->equilibre == -1) rotationDroiteGauche(noeud->gauche);
                rotationGaucheDroite(noeud);

            } else {

                assert(noeud->equilibre == 0);
            }

        }

    } else if (cle > noeud->cle) {

        if (inserer(cle, valeur, noeud->droite)) {

            noeud->equilibre--;

            if (noeud->equilibre == -1) {

                augmente = true;

            } else if (noeud->equilibre == -2) {

                if (noeud->droite->equilibre == 1) rotationGaucheDroite(noeud->droite);

                rotationDroiteGauche(noeud);

            } else {

                assert(noeud->equilibre == 0);
            }

        }

    } else {

        noeud->valeur = valeur;

    }

    return augmente;
}

/**
 * Retourne le maxima de la Racine
 *
 * @return a Maxima de l'instance <ArbreMap>
 */
double ArbreMap::maxima() const {

    assert(this->racine);
    return this->racine->a;

}

/** *
 * Retourne le maxima d'un Noeud.
 *
 * @param cle la clé du Noeud
 *
 * @return le maxima du Noeud
 */
double ArbreMap::maxima(double cle) const {

    return aGauche(cle);
}

/**
 * Test si une valeur est dans une des intervales de <ArbreMap>
 *
 * @param cle la valeur à tester
 *
 * @return <std::string> "vrai" si est dans une intervale, "faux" sinon.
 */
std::string ArbreMap::appartient(double cle) const {

    std::string reponse;

    if (cle <= aGauche(cle)) {

        reponse = "vrai";

    } else {
        reponse = "faux";
    }

    return reponse;
}

/**
 * Retourne une liste des intervales dont la clé est plus petite ou égale à la
 * clé donnée en paramètre.
 *
 * @param cle la clé à tester
 *
 * @return std::vector <std::pair<double, double> > une liste des intervales
 */
std::vector<std::pair<double, double>> ArbreMap::jusqua(double cle) const {

    ArbreMap::Iterateur iter = debut();
    std::vector<std::pair<double, double>> v;

    while (iter.courant && std::get<0>((*this)[iter]) <= cle) {

        v.push_back(std::make_pair(std::get<0>((*this)[iter]), std::get<1>((*this)[iter])));
        ++iter;
    }

    return v;
}

/**
 * Fait la rotation de gauche à droite
 *
 * @param racine
 */
void ArbreMap::rotationGaucheDroite(Noeud *&racine) {

    Noeud *tmp = racine->gauche;

    int equilibreA = tmp->equilibre;
    int equilibreB = racine->equilibre;
    int nouveauEquilibreB = -(equilibreA > 0 ? equilibreA : 0) - 1 + equilibreB;
    int nouveauEquilibreA = (nouveauEquilibreB < 0 ? nouveauEquilibreB : 0) - 1 + equilibreA;

    tmp->equilibre = nouveauEquilibreA;
    racine->equilibre = nouveauEquilibreB;
    racine->gauche = tmp->droite;
    tmp->droite = racine;
    racine = tmp;
}

/**
 * Fait la rotation de droite à gauche
 *
 * @param racine
 */
void ArbreMap::rotationDroiteGauche(Noeud *&racine) {

    Noeud *tmp = racine->droite;

    int equilibreB = tmp->equilibre;
    int equilibreA = racine->equilibre;
    int nouveauEquilibreA = -(equilibreB < 0 ? equilibreB : 0) + 1 + equilibreA;
    int nouveauEquilibreB = (nouveauEquilibreA > 0 ? nouveauEquilibreA : 0) + 1 + equilibreB;

    tmp->equilibre = nouveauEquilibreB;
    racine->equilibre = nouveauEquilibreA;
    racine->droite = tmp->gauche;
    tmp->gauche = racine;
    racine = tmp;
}

/**
 * Supprime l'arbre
 */
void ArbreMap::vider() {

    vider(this->racine);
}

/**
 * Supprime le noeud et ses descendants.
 *
 * @param noeud racine du sous-arbre à supprimer
 */
void ArbreMap::vider(Noeud *&noeud) {

    if (noeud != NULL) {

        if (noeud->gauche != NULL) vider(noeud->gauche);
        if (noeud->droite != NULL) vider(noeud->droite);
        noeud = NULL;
        delete noeud;
    }
}

/**
 * Constructeur Iterateur
 *
 * @param arbre un arbre binaire ArbreMap
 */
ArbreMap::Iterateur::Iterateur(const ArbreMap &arbre) :
        courant(NULL) {}

ArbreMap::Iterateur::~Iterateur(){

	this->chemin.vider();
}

/**
 * Renvoi un itérateur pointant sur le plus petit <Noeud> de l'arbre.
 * @return iter <Iterateur>
 */
ArbreMap::Iterateur ArbreMap::debut() const {

    Iterateur iter(*this);

    Noeud *tmp = this->racine;

    if (tmp) {

        while (tmp->gauche) {

            iter.chemin.empiler(tmp);
            tmp = tmp->gauche;

        }

    }

    iter.courant = tmp;

    return iter;
}

/**
 * Surcharge de []. Accède à un élément de <ArbreMap> avec un <Iterateur>.
 * @param iter <Iterateur>
 * @return un <std::tuple> contenant la clé, la valeur et le maxima du Noeud.
 */
std::tuple<double, double, double> ArbreMap::operator[](const ArbreMap::Iterateur &iter) const {

    assert(this->racine && iter.courant);
    return std::make_tuple(iter.courant->cle, iter.courant->valeur, iter.courant->a);
}

/**
 * Surcharge de ++(). Pré-increment de <Iterateur>.
 *
 * @return l'itérateur
 */
ArbreMap::Iterateur &ArbreMap::Iterateur::operator++() {

    assert(courant);

    if (!this->chemin.vide()) {

        this->courant = this->chemin.depiler();

        Noeud *tmp = this->courant->droite;
        if (tmp != NULL) {

            this->chemin.empiler(tmp);
            tmp = tmp->gauche;

            while (tmp != NULL) {

                this->chemin.empiler(tmp);
                tmp = tmp->gauche;

            }

        }

    } else {

        this->courant = NULL;

    }

    return *this;
}
