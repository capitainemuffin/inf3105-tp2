/**
 * Éxecution du TP2
 *
 * AUTEUR(S):
 *  1) Sofiane Selaoui SELS28049204
 */

#include "arbremap.h"
#include <sstream>
#include <cctype>
#include <algorithm>
#include <iomanip>
std::ostream &operator<<(std::ostream &os, std::vector<std::pair<double, double>> v) {

	os << "[";

	auto it = v.begin();

	while(it != v.end()){

		os << "( " << it->first << ", " << it->second << " )" ;
		++it;
		if(it != v.end()) os << ", ";

	}

	os << "]";

    return os;
}

/**
 * Éxecution principale
 *
 * @return code 0
 */
int main() {

    ArbreMap arbre = ArbreMap();
    std::string commande;
    std::cout << std::fixed << std::setprecision(1);
	while(std::getline(std::cin,commande)){

		// Enlever tous les espaces 
		commande.erase(
			std::remove_if(commande.begin(), commande.end(), ::isspace), 
			commande.end());

		if (commande.front() == '(' && commande.back() == '.' && commande.at(commande.length()-2) == ')'){

			/**
     		* Choix 1 : insertion "(<double>, <double>)."
     		*/			

			double cle, valeur;
			std::stringstream cle_str(commande.substr(1, commande.find(',') - 1));
			std::stringstream valeur_str(commande.substr(commande.find(',') + 1, commande.length() - 2));

			cle_str >> cle;
			valeur_str >> valeur;

			if(cle_str.fail() || valeur_str.fail()) {
				std::cerr << "Valeur invalide pour la commande 'Insertion'." << std::endl;
				exit(-1);
			}

			arbre.inserer(cle, valeur);

		} else if (commande.compare("max?") == 0) {

			/**
     		* Choix 2 : maxima "max?"
     		*/

    		std::cout << arbre.maxima() << std::endl;

    	} else if (commande.back() == '?' && std::isdigit(commande.front())) {

			/**
     		* Choix 3 : appartient "<double>?"
     		*/

    		double valeur;
    		std::stringstream valeur_str(commande.substr(0, commande.length() - 1));

			if(valeur_str.fail()) {
				std::cerr << "Valeur invalide pour la commande 'Appartient'." << std::endl;
				exit(-2);
			}

    		valeur_str >> valeur;
     		std::cout << arbre.appartient(valeur) << std::endl;


     	} else if (commande.back() == '?' && commande.substr(0, 5).compare("donne") == 0){

     		/**
     		* Choix 4 : donne "donne<double>?"
     		*/

     		double valeur;
     		std::stringstream valeur_str(commande.substr(5, commande.length() - 2));
     		valeur_str >> valeur;

			if(valeur_str.fail()) {
				std::cerr << "Valeur invalide pour la commande 'Donne'." << std::endl;
				exit(-3);
			}

			double resultat = arbre.maxima(valeur);

			if (resultat == std::numeric_limits<double>::lowest()) {

				std::cout << "-inf" << std::endl;

			} else {

				std::cout << resultat << std::endl;

			}

    	} else if (commande.back() == '?' && commande.substr(0, 5).compare("avant") == 0) {

    		/**
     		* Choix 5 : avant "<double>?"
     		*/

    		double valeur;
     		std::stringstream valeur_str(commande.substr(5, commande.length() - 2));
     		valeur_str >> valeur;

     		if(valeur_str.fail()) {
				std::cerr << "Valeur invalide pour la commande 'Avant'." << std::endl;
				exit(-4);
			}

			std::cout << arbre.jusqua(valeur) << std::endl;

		} else if (commande.compare("q.") == 0){

			/**
			* Choix 6 : quitter 
			*/

			arbre.vider();
			exit(0);

		} else {

			std::cerr << "Commande non reconnue." << std::endl;
			exit(-5);

		}

	}

    return 0;
}
