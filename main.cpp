#include "face.h"
#include "point.h"
#include "filemanager.h"
#include <iostream>
#include <vector>

using namespace std;

vector<vector<Point>> grille;
vector<vector<Point>> grilleFinale;
vector<Face> listeFaces;

vector<float> tabU;
vector<float> tabV;
int degreK;
int degreL;
int nbLigne;
int nbColonne;

size_t chercherJ(const vector<float> &noeuds, float t) {
    size_t j = 0;
    while (j < noeuds.size()-1 && noeuds[j] < t) {
        j++;
    }
    return j;
}

Point rechercherPoint(Point p1, Point p2, double t)
{
    Point res(0, 0, 0);

    res.setX(p1.getX()+t*(p2.getX()-p1.getX()));
    res.setY(p1.getY()+t*(p2.getY()-p1.getY()));
    res.setZ(p1.getZ()+t*(p2.getZ()-p1.getZ()));

    return res;
}

float calculOmega(const vector<float> noeuds, int i, int k, float t) {
    if (noeuds[i] < noeuds[i+k]) {
        return (t - noeuds[i])/(noeuds[i+k]-noeuds[i]);
    } else {
        return 0;
    }
}

#include <cassert>

Point courbeBSplines(const vector<Point> &listePoint, const vector<float> &noeuds, int degre, float t) {
    int k = degre;
    //int n = int(listePoint.size())-1;

    //float t = noeuds[indice];
    vector<Point> etageDuDessus;
    vector<Point> listeTmp;

    //int j = chercherJ(noeuds, t);
    int j = floor(t);
    // Initialization de etageDuDessus, ok !
    for (int var = 0; var < k+1; ++var) {
        etageDuDessus.push_back(listePoint[j-k+var]);
    }

    // Calcul du d(j,k)
    for (int r = 1; r < k+1; ++r) {
        for (size_t i = 1; i < etageDuDessus.size(); ++i) {
            //double om = calculOmega(noeuds, j-k+r+i-1, k-r+1, t);
            float om = calculOmega(noeuds, j-k+r+i-1, k-r+1, t);
            double nouvX = om * etageDuDessus[i].getX() + (1.0-om) * etageDuDessus[i-1].getX();
            double nouvY = om * etageDuDessus[i].getY() + (1.0-om) * etageDuDessus[i-1].getY();
            double nouvZ = om * etageDuDessus[i].getZ() + (1.0-om) * etageDuDessus[i-1].getZ();
            listeTmp.push_back(Point(nouvX,nouvY,nouvZ));
        }

        etageDuDessus = listeTmp;
        listeTmp.clear();
    }

    assert(etageDuDessus.size() == 1);
    return etageDuDessus[0];
}

Point S(float u, float v) {
    vector<Point> listeTmp;
    for (int j = 0; j < nbLigne; ++j) {
        listeTmp.push_back(courbeBSplines(grille[j], tabV, degreL, v));
    }
    return courbeBSplines(listeTmp, tabU, degreK, u);
}

void commeTuVeux()
{
    degreK = 3;  // Pour u
    degreL = 3;  // Pour v
    int m = int(grille[0].size())-1;  // i € [0,  m]
    int n = int(grille.size())-1;     // j € [0,  n]

    assert(m+degreK+1 == 9);
    assert(m+degreL+1 == 9);

//    tabU = {0, 0, 0, 1, 2, 3, 4, 4, 4};
//    tabV = {0, 0, 0, 1, 2, 3, 4, 4, 4};
    tabU = vector<float>(m+degreK+2);
    for (size_t u = 0; u < tabU.size(); ++u) {
        tabU[u] = u;
    }
    tabV = vector<float>(n+degreL+2);
    for (size_t v = 0; v < tabV.size(); ++v) {
        tabV[v] = v;
    }

    vector<Point> listeTmp;
    for (float u = tabU[degreK]; u <= tabU[m+1]; u += 0.1) {
        for (float v = tabV[degreL]; v <= tabV[n+1]; v += 0.1) {
            listeTmp.push_back(S(u, v));
        }
        grilleFinale.push_back(listeTmp);
        listeTmp.clear();
    }
}

int main()
{

    vector<Point> tmp;
    tmp.push_back(Point(0,0,0));
    tmp.push_back(Point(2,0,0));
    tmp.push_back(Point(5,0,0));
    tmp.push_back(Point(7,0,0));
    tmp.push_back(Point(10,0,0));
    tmp.push_back(Point(12,0,0));
    grille.push_back(tmp);
    tmp.clear();

    tmp.push_back(Point(0,2,0));
    tmp.push_back(Point(2,2,1));
    tmp.push_back(Point(5,2,2));
    tmp.push_back(Point(7,2,3));
    tmp.push_back(Point(10,2,1));
    tmp.push_back(Point(12,2,0));
    grille.push_back(tmp);
    tmp.clear();

    tmp.push_back(Point(0,5,0));
    tmp.push_back(Point(2,5,1));
    tmp.push_back(Point(5,5,2));
    tmp.push_back(Point(7,5,3));
    tmp.push_back(Point(10,5,1));
    tmp.push_back(Point(12,5,0));
    grille.push_back(tmp);
    tmp.clear();

    tmp.push_back(Point(0,7,0));
    tmp.push_back(Point(2,7,-1));
    tmp.push_back(Point(5,7,-2));
    tmp.push_back(Point(7,7,-3));
    tmp.push_back(Point(10,7,-1));
    tmp.push_back(Point(12,7,0));
    grille.push_back(tmp);
    tmp.clear();

    tmp.push_back(Point(0,10,0));
    tmp.push_back(Point(2,10,-1));
    tmp.push_back(Point(5,10,-2));
    tmp.push_back(Point(7,10,-3));
    tmp.push_back(Point(10,10,-1));
    tmp.push_back(Point(12,10,0));
    grille.push_back(tmp);
    tmp.clear();

    tmp.push_back(Point(0,12,0));
    tmp.push_back(Point(2,12,0));
    tmp.push_back(Point(5,12,0));
    tmp.push_back(Point(7,12,0));
    tmp.push_back(Point(10,12,0));
    tmp.push_back(Point(12,12,0));
    grille.push_back(tmp);
    tmp.clear();

    nbLigne = grille.size();
    nbColonne = grille[0].size();

    commeTuVeux();

    size_t nbFaceLigne = grilleFinale.size();
    size_t nbFaceColonne = grilleFinale[0].size();

    cout << nbFaceLigne << endl;
    cout << nbFaceColonne << endl;

    Face f;
    for (size_t k = 0; k < (nbFaceLigne-1)*(nbFaceColonne-1); ++k) {
        f.clear();
        int i = k%(nbFaceColonne-1);
        int j = k/(nbFaceColonne-1);
        f.ajouterIndice(j*nbFaceColonne + i +1) ;
        f.ajouterIndice(j*nbFaceColonne + i+1 +1);
        f.ajouterIndice((j+1)*nbFaceColonne + i+1 +1);
        f.ajouterIndice((j+1)*nbFaceColonne + i +1);
        listeFaces.push_back(f);
    }

    FileManager fm(QString("polyedre.obj"));

    for (size_t j = 0; j < nbFaceLigne; ++j) {
        for (size_t i = 0; i < nbFaceColonne; ++i) {
            fm.addPoint(grilleFinale[j][i]);
        }
    }

    for (size_t i = 0; i < (nbFaceLigne-1)*(nbFaceColonne-1); ++i) {
        fm.addFace(listeFaces[i]);
    }

    fm.generate();

    return 0;
}


