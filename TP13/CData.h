#pragma once

#include <vector>
#include <array>
#include "SData.h"

using UData = std::vector<Donnee>;

class CData
{
public:
	CData();
	
	// Accesseurs
	UData GetData() { return m_vData; }

	// Traitement de données
	int maximum(UData& Data) const;
	int minimum(UData& Data) const;

	std::vector<int> RechercheDateTemperature(float temperature ) const;

	UData MoyenneParAnnee() const;
	UData MoyenneToutLes10ans() const;
	UData MoyenneParSaison() const;

	std::array<std::array<float, 2>, 2> courbeDeTendance(const UData& Data, float hauteur_max, float marge_gauche, float espace_dispo) const;


private:
	UData m_vData;
	void RecuperationDonnees();
	
};
