#define NOMINMAX
#include <Windows.h>
#include <tchar.h>
/*
#define LIBGRAPH2_LEVEL 2
#include <LibGraph2.h>
using namespace LibGraph2;

#include <iostream>
using namespace std;

int APIENTRY _tWinMain(HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPTSTR    lpCmdLine,
  int       nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  //Affiche la fenêtre graphique avec une taille par défaut
  show(400, 400);

  //Boucle principale d'événements
  evt_type evt;
  int nKeyCode, nMouseX, nMouseY;
  bool bShowDisk = true;
  while(waitForEvent(evt, nKeyCode, nMouseX, nMouseY))
  {
    switch(evt)  //En fonction du type du dernier événement
    {
    case evt_type::evtRefresh:  //Raffraichissement de l'affichage (tout redessiner)
      //Utiliser éventuellement les fonctions beginPaint() / endPaint() pour activer le backbuffer
      beginPaint();
        //Utiliser ici les fonctions de dessins
        //Choisit un stylo rouge d'épaisseur 5 pixels traçant des pointillés
        setPen(MakeARGB(255,255,0,0), 5.0f, LibGraph2::pen_DashStyles::Dash); 
        //Choisit un pinceau jaune
        setSolidBrush(MakeARGB(255,255,255,0));
        //Dessine un rectangle avec le stylo et le pinceau sélectionné
        drawRectangle(20,40,200,100);
        //Choisit un pinceau cyan translucide
        setSolidBrush(MakeARGB(128,0,255,255));
        //Dessine une ellipse
        if(bShowDisk)
          drawEllipse(100,100,200,200);
      endPaint();
      break;

    case evt_type::evtKeyDown:  //Enfoncement d'une touche
      switch(nKeyCode) //En fonction de la touche enfoncée
      {
      case 'H':
        hideConsole();
        break;
      case 'C':
        showConsole();
        break;
      }
      break;

    case evt_type::evtMouseDown:  //Déplacement de la souris
      cout<<"Clic de souris en position : "<<nMouseX<<", "<<nMouseY<<endl;
      bShowDisk = !bShowDisk;
      askForRefresh();
      break;
    }
  }

  ReleaseLibGraph2();
  return 0;
}
*/

/*
#define LIBGRAPH2_LEVEL 4
#include <LibGraph2.h>
using namespace LibGraph2;

#include <iostream>
using namespace std;

int APIENTRY _tWinMain(HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPTSTR    lpCmdLine,
  int       nCmdShow)
{
  UNREFERENCED_PARAMETER(hPrevInstance);
  UNREFERENCED_PARAMETER(lpCmdLine);

  //Affiche la fenêtre graphique avec une taille par défaut
  ILibGraph2* pLibgraph = GetLibGraph2();
  pLibgraph->show(CSize{ 400, 400 });

  //Boucle principale d'événements
  evt e;
  bool bShowDisk = true;
  while (pLibgraph->waitForEvent(e))
  {
    switch (e.type)  //En fonction du type du dernier événement
    {
    case evt_type::evtRefresh:  //Raffraichissement de l'affichage (tout redessiner)
      //Utiliser éventuellement les fonctions beginPaint() / endPaint() pour activer le backbuffer
      pLibgraph->beginPaint();
        //Utiliser ici les fonctions de dessins
        //Choisit un stylo rouge d'épaisseur 5 pixels traçant des pointillés
        pLibgraph->setPen(MakeARGB(255, 255, 0, 0), 5.0f, LibGraph2::pen_DashStyles::Dash);
        //Choisit un pinceau jaune
        pLibgraph->setSolidBrush(MakeARGB(255, 255, 255, 0));
        //Dessine un rectangle avec le stylo et le pinceau sélectionné
        pLibgraph->drawRectangle(CRectangle{ CPoint{20, 40}, CSize{200, 100} });
        //Choisit un pinceau cyan translucide
        pLibgraph->setSolidBrush(MakeARGB(128, 0, 255, 255));
        //Dessine une ellipse
        if (bShowDisk)
          pLibgraph->drawEllipse(CRectangle{ CPoint{100, 100}, CSize{200, 200} });
        pLibgraph->endPaint();
      break;

    case evt_type::evtKeyDown:  //Enfoncement d'une touche
      switch (e.vkKeyCode) //En fonction de la touche enfoncée
      {
      case 'H':
        pLibgraph->hideConsole();
        break;
      case 'C':
        pLibgraph->showConsole();
        break;
      }
      break;

    case evt_type::evtMouseDown:  //Déplacement de la souris
      cout << "Clic de souris en position : " << e.x<< ", " << e.y << endl;
      bShowDisk = !bShowDisk;
      pLibgraph->askForRefresh();
      break;
    }
  }

  ReleaseLibGraph2();
  return 0;
}
*/

//#include <chrono>
//#define LIBGRAPH2_LEVEL 4
//#include <LibGraph2.h>
//using namespace LibGraph2;
//
//#include <iostream>
//using namespace std;
//
//int APIENTRY _tWinMain(HINSTANCE hInstance,
//  HINSTANCE hPrevInstance,
//  LPTSTR    lpCmdLine,
//  int       nCmdShow)
//{
//  UNREFERENCED_PARAMETER(hPrevInstance);
//  UNREFERENCED_PARAMETER(lpCmdLine);
//
//  //Affiche la fenêtre graphique avec une taille par défaut
//  ILibGraph2* pLibgraph = GetLibGraph2();
//  pLibgraph->show(CSize{ 400, 400 });
//
//  //Boucle principale d'événements
//  evt e;
//  bool bShowDisk = true;
//  auto tpStartBounce = chrono::high_resolution_clock::now();
//
//  while (pLibgraph->waitForEvent(e))
//  {
//    switch (e.type)  //En fonction du type du dernier événement
//    {
//    case evt_type::evtRefresh:  //Raffraichissement de l'affichage (tout redessiner)
//      //Utiliser éventuellement les fonctions beginPaint() / endPaint() pour activer le backbuffer
//      pLibgraph->beginPaint();
//      //Utiliser ici les fonctions de dessins
//      //Choisit un stylo rouge d'épaisseur 5 pixels traçant des pointillés
//      pLibgraph->setPen(MakeARGB(255, 255, 0, 0), 5.0f, LibGraph2::pen_DashStyles::Dash);
//      //Choisit un pinceau jaune
//      pLibgraph->setSolidBrush(MakeARGB(255, 255, 255, 0));
//      //Dessine un rectangle avec le stylo et le pinceau sélectionné
//      pLibgraph->drawRectangle(CRectangle{ CPoint{20, 40}, CSize{200, 100} });
//      //Choisit un pinceau cyan translucide
//      pLibgraph->setSolidBrush(MakeARGB(128, 0, 255, 255));
//      //Dessine une ellipse
//      if (bShowDisk)
//      {
//        auto tpCurrent = chrono::high_resolution_clock::now();
//        chrono::duration<float, chrono::seconds::period> dur = tpCurrent - tpStartBounce;
//        
//        float y = max(100.0f * (dur.count() - 1.0f) * (dur.count() - 1.0f) + 100.f, 100.0f);
//        if (dur.count() >= 2)
//          tpStartBounce = tpCurrent;
//
//        pLibgraph->drawEllipse(CRectangle{ CPoint{100, y}, CSize{200, 200} });
//        pLibgraph->askForRefresh();
//      }
//      pLibgraph->endPaint();
//      break;
//
//    case evt_type::evtKeyDown:  //Enfoncement d'une touche
//      switch (e.vkKeyCode) //En fonction de la touche enfoncée
//      {
//      case 'H':
//        pLibgraph->hideConsole();
//        break;
//      case 'C':
//        pLibgraph->showConsole();
//        break;
//      }
//      break;
//
//    case evt_type::evtMouseDown:  //Déplacement de la souris
//      cout << "Clic de souris en position : " << e.x << ", " << e.y << endl;
//      bShowDisk = !bShowDisk;
//      pLibgraph->askForRefresh();
//      break;
//    }
//  }
//
//  ReleaseLibGraph2();
//  return 0;
//}