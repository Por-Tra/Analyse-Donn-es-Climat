#define NOMINMAX
#include <Windows.h>
#include <tchar.h>

// Musique
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "CData.h"

#define LIBGRAPH2_LEVEL 4
#include <LibGraph2.h>
using namespace LibGraph2;

#include <iostream>

// Type d'affichage de données
enum ModeDonnees {
    DONNEES_BRUTES,
    MOYENNE_PAR_ANNEE,
    MOYENNE_PAR_10ANS,
    MOYENNE_PAR_SAISON
};

// Type de graphique
enum ModeGraphique {
    BARRES,
    POINTS_GRAPH,
    POINTS_LIGNES,
    COURBE_TENDANCE
};

int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    float SIZE_X = 1700;
    float SIZE_Y = 1000;

    ILibGraph2* pLibgraph = GetLibGraph2();
    pLibgraph->show(CSize{ SIZE_X, SIZE_Y });

    // varible de gestion de case
    bool played_music = false;
	bool afficher_courbreTendance = false;

    // varaible utilitaire
    float marge_gauche = 20;
    float marge_droite = 10;
    float espace_disponible = SIZE_X - marge_gauche - marge_droite-15;
    float hauteur_max = 900;

	float save_espace_disponible = espace_disponible;
	float save_hauteur_max = hauteur_max;

    CData donnees_meteo;
    evt e;

    ModeDonnees modeDonnees = DONNEES_BRUTES;
    ModeGraphique modeGraphique = BARRES;

    while (pLibgraph->waitForEvent(e))
    {
        switch (e.type)
        {
        case evt_type::evtRefresh:
        {
            pLibgraph->beginPaint();

            float y_zero = hauteur_max * 0.5;

            UData data;

            switch (modeDonnees)
            {
            case DONNEES_BRUTES:
                data = donnees_meteo.GetData();
                break;
            case MOYENNE_PAR_ANNEE:
                data = donnees_meteo.MoyenneParAnnee();
                break;
            case MOYENNE_PAR_10ANS:
                data = donnees_meteo.MoyenneToutLes10ans();
                break;
            case MOYENNE_PAR_SAISON:
                data = donnees_meteo.MoyenneParSaison();
                break;
            }

            int nb_points = data.size();
            
            float pas_x = espace_disponible / (float)(nb_points - 1);
            float largeur_barre = std::min(pas_x * 0.8, 10.0);


            float min = donnees_meteo.minimum(data);
            float max = donnees_meteo.maximum(data);

            float x = marge_gauche;

            std::vector<CPoint> points;

            for (int i = 0; i < nb_points; ++i)
            {
                float temp_norm = (data[i].temperature + 50) / 100;
                float y = hauteur_max * (1 - temp_norm);

                if (modeGraphique == BARRES) 
                {
                    float hauteur = abs(y - y_zero);
                    float y_debut = (y < y_zero) ? y : y_zero;

                    if (i == min) 
                    {
                        pLibgraph->setSolidBrush(MakeARGB(255, 0, 0, 255));
                    }
                    else if (i == max) 
                    {
                        pLibgraph->setSolidBrush(MakeARGB(255, 255, 0, 0));
                    }
                    else 
                    {
                        if (data[i].temperature > 0) 
                        {
                            pLibgraph->setPen(MakeARGB(255, 255, 110, 110), 1);
                            pLibgraph->setSolidBrush(MakeARGB(255, 255, 110, 110));
                        }
                        else 
                        {
                            pLibgraph->setPen(MakeARGB(255, 110, 100, 255), 1);
                            pLibgraph->setSolidBrush(MakeARGB(255, 110, 110, 255));
                        }
                    }

                    pLibgraph->drawRectangle(CRectangle{ CPoint{ x - largeur_barre / 2, y_debut }, CSize{ largeur_barre, hauteur } });
                }

                else if (modeGraphique == POINTS_GRAPH || modeGraphique == POINTS_LIGNES || modeGraphique == COURBE_TENDANCE) 
                {
                    CPoint pt = CPoint{ x, y };
                    if (i == min) 
                    {
                        pLibgraph->setPen(MakeARGB(255, 0, 0, 255), 1); // Contour bleu
                        pLibgraph->setSolidBrush(MakeARGB(255, 0, 0, 255)); // Remplissage bleu
                    }
                    else if (i == max) 
                    {
                        pLibgraph->setPen(MakeARGB(255, 255, 0, 0), 1); // Contour rouge
                        pLibgraph->setSolidBrush(MakeARGB(255, 255, 0, 0)); // Remplissage rouge
                    }
                    else if (data[i].temperature > 0) 
                    {
                        pLibgraph->setPen(MakeARGB(255, 255, 110, 110), 1);
                        pLibgraph->setSolidBrush(MakeARGB(255, 255, 110, 110));
                    }
                    else 
                    {
                        pLibgraph->setPen(MakeARGB(255, 110, 110, 255), 1);
                        pLibgraph->setSolidBrush(MakeARGB(255, 110, 110, 255));
                    }

                    pLibgraph->drawEllipse(CRectangle{ pt, CSize{ 8, 8 } });
                    points.push_back(pt);

                    if (modeGraphique == POINTS_LIGNES && i > 0) {
                        pLibgraph->setPen(MakeARGB(255, 0, 0, 0), 2);
                        pLibgraph->drawLine(points[i - 1], pt);
                    }
                    else
                    {
                        if (modeGraphique == COURBE_TENDANCE)
                        {
                            auto result = donnees_meteo.courbeDeTendance(data, hauteur_max, marge_gauche, espace_disponible);
                            pLibgraph->setPen(MakeARGB(255, 255, 0, 255), 3);
                            pLibgraph->drawLine(CPoint{ result[0][0], result[0][1] }, CPoint{ result[1][0], result[1][1] });
                        }
                    }
                }

                if (i == min) 
                {
                    pLibgraph->setSolidBrush(MakeARGB(255, 0, 0, 255));
                    pLibgraph->drawString("Min", CPoint{ x, y - 30 });
                    pLibgraph->drawString(std::to_string(data[i].temperature), CPoint{ x, y - 50 });
                }
                if (i == max) 
                {
                    pLibgraph->setSolidBrush(MakeARGB(255, 255, 0, 0));
                    pLibgraph->drawString("Max", CPoint{ x - 50, y - 20 });
                    pLibgraph->drawString(std::to_string(data[i].temperature), CPoint{ x - 50, y - 40 });
                }
                x += pas_x;
            }

            // Affichage des axes
            pLibgraph->setPen(MakeARGB(255, 0, 255, 255), 2);

            if (modeGraphique == BARRES) 
            {
                // Axe Y
                pLibgraph->drawLine(CPoint{ marge_gauche - 5, 0 }, CPoint{ marge_gauche - 5, hauteur_max });
            }

            // Axe X
            pLibgraph->drawLine(CPoint{ marge_gauche - 5, y_zero }, CPoint{ SIZE_X - marge_droite, y_zero });

            // Légendes des graphiques
            pLibgraph->setSolidBrush(MakeARGB(255, 0, 0, 0));
            CString texteDonnees;
            switch (modeDonnees)
            {
            case DONNEES_BRUTES: texteDonnees = "Donnees brutes"; break;
            case MOYENNE_PAR_ANNEE: texteDonnees = "Moyenne par annee"; break;
            case MOYENNE_PAR_10ANS: texteDonnees = "Moyenne pour 10 ans"; break;
            case MOYENNE_PAR_SAISON: texteDonnees = "Moyenne par saison"; break;
            }

            CString texteGraphique;
            switch (modeGraphique)
            {
            case BARRES: texteGraphique = "Graphique en barres"; break;
            case POINTS_GRAPH: texteGraphique = "Graphique en points"; break;
            case POINTS_LIGNES: texteGraphique = "Points relies par lignes"; break;
            case COURBE_TENDANCE: texteGraphique = "Courbe de tendance"; break;
            }

            CString legendedonne = texteDonnees;
            CString legendegraph = texteGraphique;
            CString instruction = "| A: Moyenne annuelle \n| Z: Moyenne 10 ans \n| S: Moyenne par saisons \n| E: Donnees brutes \n| B = barres \n| P = points \n| L = points+lignes \n| T = courbe de tendance \n| M : couper / allumer la musique\n| C/V : regler l'axe X des donnees\n| W/X : regler l'axe Y des donnees\n| R : Reset les axes\n----------------------------------------------------";
            CString legendeY = " Y = temperature en degres, axe X -> Y = 0";

            pLibgraph->drawString(legendedonne, CPoint{ 20, 10 });
            pLibgraph->drawString(legendegraph, CPoint{ 20, 30 });
            pLibgraph->setSolidBrush(MakeARGB(255, 0, 0, 255));
            pLibgraph->drawString(instruction, CPoint{ SIZE_X-250, 0 });
            pLibgraph->setSolidBrush(MakeARGB(255, 0, 0, 0));
            pLibgraph->drawString(legendeY, CPoint{ 15, 100 });

            pLibgraph->endPaint();
            break;
        }
        case evt_type::evtKeyDown:
            switch (e.vkKeyCode) 
            {
            case 'E':
                afficher_courbreTendance = false;
                modeDonnees = DONNEES_BRUTES;
                pLibgraph->askForRefresh();
                break;
            case 'A':
                afficher_courbreTendance = false;
                modeDonnees = MOYENNE_PAR_ANNEE;
                pLibgraph->askForRefresh();
                break;
            case 'Z':
                afficher_courbreTendance = false;
                modeDonnees = MOYENNE_PAR_10ANS;
                pLibgraph->askForRefresh();
                break;
            case 'S':
                afficher_courbreTendance = false;
                modeDonnees = MOYENNE_PAR_SAISON;
                pLibgraph->askForRefresh();
                break;

            case 'B':
                modeGraphique = BARRES;
                pLibgraph->askForRefresh();
                break;
            case 'P':
                modeGraphique = POINTS_GRAPH;
                pLibgraph->askForRefresh();
                break;
            case 'L':
                modeGraphique = POINTS_LIGNES;
                pLibgraph->askForRefresh();
                break;

            case 'M':
                if (played_music) 
                {
                    PlaySound(NULL, 0, 0);
                    played_music = false;
                }
                else 
                {
                    PlaySound(TEXT("doom.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
                    played_music = true;
                }
                break;

            case 'T':
                if (afficher_courbreTendance)
                {
                    afficher_courbreTendance = false;
                    pLibgraph->askForRefresh();
                }
                else
                {
                    afficher_courbreTendance = true;
                    UData data = donnees_meteo.GetData();
                    auto result = donnees_meteo.courbeDeTendance(data, 900, 20, SIZE_X - 20 - 10);
                    pLibgraph->setPen(MakeARGB(255, 255, 0, 255), 3);
                    pLibgraph->drawLine(CPoint{ result[0][0], result[0][1] },CPoint{ result[1][0], result[1][1] });
                }
                break;

            case 'C':
                afficher_courbreTendance = false;
                espace_disponible += 10;
				pLibgraph->askForRefresh();
                break;
			case 'V':
                afficher_courbreTendance = false;
				espace_disponible -= 10;
				pLibgraph->askForRefresh();
				break;
            case 'W':
                afficher_courbreTendance = false;
				hauteur_max += 10;
				pLibgraph->askForRefresh();
                break;
			case 'X':
                afficher_courbreTendance = false;
				hauteur_max -= 10;
				pLibgraph->askForRefresh();
				break;
            case 'R':
				afficher_courbreTendance = false;
				espace_disponible = save_espace_disponible;
				hauteur_max = save_hauteur_max;
				pLibgraph->askForRefresh();
                break;

            case VK_ESCAPE:
                return 0;
            }
            break;
        }
    }
    if (played_music)
    {
        PlaySound(NULL, 0, 0);
    }
    ReleaseLibGraph2();
    return 0;
}
