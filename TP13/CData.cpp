#include "CData.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <string>

CData::CData()
{
	RecuperationDonnees();
}

int CData::maximum(UData& Data) const
{
    int MaxTemp = 0;
    float maxTemp = Data[MaxTemp].temperature;

    for (int i =0; i< Data.size(); ++i)
    {
        if (Data[i].temperature > maxTemp)
        {
            maxTemp = Data[i].temperature;
            MaxTemp = i;
        }
    }
    return MaxTemp;
}

int CData::minimum(UData& Data) const
{
	int MinTemp = 0;
    float minTemp = Data[0].temperature;

    for (int i = 0; i< Data.size(); ++i)
    {
        if (Data[i].temperature < minTemp)
        {
            minTemp = Data[i].temperature;
			MinTemp = i;
        }
    }
    return MinTemp;
}

// A revoir
std::vector<int> CData::RechercheDateTemperature(float temperature) const
{
	std::vector<int> Jeu_DeDonnees;

	for (const auto& d : m_vData)
	{
		if (d.temperature == temperature)
		{
			Jeu_DeDonnees.push_back(d.id);
		}
	}
    return Jeu_DeDonnees;
}

UData CData::MoyenneParAnnee() const
{
	// 126 années de données

	UData moyenneAnnee;
	size_t compteur_mois = 0;
    int annee = 1896;

    float somme_annee = 0;
	for (auto ele : m_vData)
	{
		if (compteur_mois == 12)
		{
            Donnee LaDonnee;
			LaDonnee.id = annee;
			LaDonnee.temperature = somme_annee / 12;
            if (moyenneAnnee.size() == 0)
            {
				LaDonnee.reference = nullptr; // Pas de référence pour la première donnée
			}
			else
				LaDonnee.reference = &moyenneAnnee.back(); // Prend la référence de la dernière donnée ajoutée

            moyenneAnnee.push_back(LaDonnee);

			// reset des données
            compteur_mois = 0;
			annee++;
			somme_annee = 0;
		}
		somme_annee += ele.temperature;
        compteur_mois++;
	}
    return moyenneAnnee;
}

UData CData::MoyenneToutLes10ans() const
{
	UData moyenneG = MoyenneParAnnee();
	UData moyenne10ans;
	int annee = moyenneG[0].id;
	float somme_annee = 0;
	int currentYear = 0;

    for (int i = 0; i < moyenneG.size(); ++i)
    {
        if (currentYear == 10)
        {
			Donnee LaDonnee;
			LaDonnee.id = annee;
			LaDonnee.temperature = somme_annee / 10;
            if (moyenne10ans.size() == 0)
            {
                LaDonnee.reference = nullptr; // Pas de référence pour la première donnée
            }
            else
				LaDonnee.reference = &moyenne10ans.back(); // Prend la référence de la dernière donnée ajoutée

			moyenne10ans.push_back(LaDonnee);
			
            // Reinitialiser le compteur de mois et la somme pour la nouvelle annee
			currentYear = 0;
			annee = moyenneG[i].id;
			somme_annee = 0;
        }
        somme_annee += moyenneG[i].temperature;
		currentYear++;
    }
	
	return moyenne10ans;
}

UData CData::MoyenneParSaison() const
{
	UData moyenneSaison;

	Donnee LaDonnee_printemp;
	Donnee LaDonnee_ete;
	Donnee LaDonnee_automne;
	Donnee LaDonnee_hiver;

	LaDonnee_printemp.temperature = 0;
	LaDonnee_ete.temperature = 0;
	LaDonnee_automne.temperature = 0;
	LaDonnee_hiver.temperature = 0;

	// compteur des saison
	int nb_p = 0; 
	int nb_e = 0; 
	int nb_a = 0; 
	int nb_h = 0;

    for (int i = 0; i < m_vData.size(); ++i)
    {
        std::string str_id = std::to_string(m_vData[i].id);

		std::string str_mois = str_id.substr(4, 2); // mieux car on évite les boucles ducoup c'est plus rapide et plus efficace
        int num = std::stoi(str_mois);

		if (num >= 3 && num <= 5)
		{
			LaDonnee_printemp.temperature += m_vData[i].temperature;
			nb_p++;
		}
		if (num >= 6 && num <= 8)
		{
			LaDonnee_ete.temperature += m_vData[i].temperature;
			nb_e++;
		}
		if (num >= 9 && num <= 11)
		{
			LaDonnee_automne.temperature += m_vData[i].temperature;
			nb_a++;
		}
		else
		{
			LaDonnee_hiver.temperature += m_vData[i].temperature;
			nb_h++;
		}
    }

	// Finition sur la completion des données

	LaDonnee_printemp.id = 1;
	LaDonnee_ete.id = 2;
	LaDonnee_automne.id = 3;
	LaDonnee_hiver.id = 4;

	LaDonnee_printemp.temperature /= nb_p;
	LaDonnee_ete.temperature /= nb_e;
	LaDonnee_automne.temperature /= nb_a;
	LaDonnee_hiver.temperature /= nb_h;

	LaDonnee_printemp.reference = nullptr;
	LaDonnee_ete.reference = &LaDonnee_printemp; 
	LaDonnee_automne.reference = &LaDonnee_ete; 
	LaDonnee_hiver.reference = &LaDonnee_automne; 

	moyenneSaison.push_back(LaDonnee_printemp);
	moyenneSaison.push_back(LaDonnee_ete);
	moyenneSaison.push_back(LaDonnee_automne);
	moyenneSaison.push_back(LaDonnee_hiver);

	return moyenneSaison;
}

std::array<std::array<float, 2>, 2> CData::courbeDeTendance(const UData& Data, float hauteur_max, float marge_gauche, float espace_dispo) const
{
	float sum_x = 0;
	float sum_y = 0;
	float sum_xy = 0;
	float sum_xx = 0;

	for (int i = 0; i < Data.size(); ++i) 
	{
		float x = static_cast<float>(i);
		float y = Data[i].temperature;

		sum_x += x;
		sum_y += y;
		sum_xy += x * y;
		sum_xx += x * x;
	}

	float a = (Data.size() * sum_xy - sum_x * sum_y) / (Data.size() * sum_xx - sum_x * sum_x);
	float b = (sum_y - a * sum_x) / Data.size();

	float x1 = 0;
	float x2 = static_cast<float>(Data.size() - 1);

	float y1 = a * x1 + b;
	float y2 = a * x2 + b;

	float temp_norm1 = (y1 + 50) / 100;
	float temp_norm2 = (y2 + 50) / 100;

	float pixel_x1 = marge_gauche + (x1 / (Data.size() - 1)) * espace_dispo;
	float pixel_x2 = marge_gauche + (x2 / (Data.size() - 1)) * espace_dispo;

	float pixel_y1 = hauteur_max * (1 - temp_norm1);
	float pixel_y2 = hauteur_max * (1 - temp_norm2);

	return { {{pixel_x1, pixel_y1}, {pixel_x2, pixel_y2}} };
}






void CData::RecuperationDonnees()
{
	std::string nomFichier = "aigoual_Mensuel.csv";
    std::ifstream fichier(nomFichier);
    std::string ligne;

    if (!fichier.is_open()) 
		std::cerr << "Erreur d'ouverture du fichier : " << nomFichier << std::endl;


    while (std::getline(fichier, ligne)) 
    {
        std::stringstream ss(ligne);
        std::string idStr, tempStr;

        std::getline(ss, idStr, ';');
        std::getline(ss, tempStr, ';');

        Donnee d;
        d.id = std::stoi(idStr);
        d.temperature = std::stof(tempStr);
        m_vData.push_back(d);
    }

    fichier.close();

}
