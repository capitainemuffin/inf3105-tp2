/**
 * Éxecution du TP2
 *
 * AUTEUR(S):
 *  1) Sofiane Selaoui SELS28049204
 */

#include "arbremap.h"
#include <iostream>
#include <iomanip>
#include <utility>

std::ostream &operator<<(std::ostream &os, std::vector<std::pair<double, double>>& v) {

	os << "[";

	for(auto& pair : v){
		os << "(" << pair.first << ", " << pair.second << ")";
	}

	os << "]" << std::endl;

    return os;
}

/**
 * Surcharge de >>, pour insérer une intervalle dans l'arbre
 * @param le stream
 * @param arbre l'arbre binaire
 * @return le stream
 */
std::istream &operator>>(std::istream &is, ArbreMap &arbre) {

    double cle, valeur;
    char vir, parentheseD, point;
    is >> cle >> vir >> valeur >> parentheseD >> point;

    if (!is.fail() && vir == ',' && parentheseD == ')' && point == '.') {

        arbre.inserer(cle, valeur);

    } else {

        std::cerr << "Commande non reconnue." << std::endl;
        exit(-1);

    }

    return is;

}

/**
 * Éxecution principale
 *
 * @return code 0
 */
int main() {

    ArbreMap arbre = ArbreMap();

    std::string commande;

	while(std::getline(std::cin,commande)){

		commande.erase(
			std::remove_if(commande.begin(), commande.end(), ::isspace), 
			commande.end());

		std::cout << "La commande : " << commande << std::endl;


		if (commande.front() == '(' && commande.back() == '.'){

		} else if () {
			
		}

		std::cout << (commande[0] == '(');

	/**
     * Choix 1 : insertion "(<double>, <double>)."
     */

    //std::cin >> arbre >> std::ws;

    /**
     * Choix 2 : maxima "max?"
     */

    //std::cout << arbre.maxima() << std::endl;

    /**
     * Choix 3 : appartient "<double>?"
     */

    //std::cout << arbre.appartient(valeur) << std::endl;

    /**
     * Choix 4 : donne "donne<double>?"
     */

    //std::cout << arbre.maxima(valeur) << std::endl;


    /**
     * Choix 5 : avant "<double>?"
     */

	}

    return 0;
}