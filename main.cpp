#include "face.h"
#include "point.h"
#include "filemanager.h"
#include <iostream>
#include <vector>

using namespace std;

vector<vector<Point>> listePoints;
vector<vector<Point>> listePointsFinaux;
vector<Face> listeFaces;
int nbLigne = 4;
int nbColonne = 5;

Point rechercherPoint(Point p1, Point p2, double t)
{
    Point res(0, 0, 0);

    res.setX(p1.getX()+t*(p2.getX()-p1.getX()));
    res.setY(p1.getY()+t*(p2.getY()-p1.getY()));
    res.setZ(p1.getZ()+t*(p2.getZ()-p1.getZ()));

    return res;
}

Point courbeDeBezier(vector<Point> &lp, double t) {
    vector<Point> listeTmp1;
    vector<Point> listeTmp2;
    //vector<Point> res(0);

    //res->push_back(lp[0]);
    //double tmp = 100.0;

    //for (int t = 0; t < 100; ++t) {
        listeTmp1 = lp;
        while (listeTmp1.size() > 1) {
            //Point temp = listeTmp1[0];
            listeTmp2.clear();
            for (size_t i = 1; i < listeTmp1.size(); ++i) {
                listeTmp2.push_back(rechercherPoint(listeTmp1[i-1], listeTmp1[i], t));
                //temp = listeTmp1[i];
            }

            listeTmp1.clear();
            listeTmp1 = listeTmp2;
        }

        //res.push_back(listeTmp1[0]);
    //}

    //res->push_back(lp[lp.size()-1]);
    return listeTmp1[0];
}

Point B(float u, float v) {
    vector<Point> bju;
    for (int j = 0; j < nbLigne; ++j) {
        bju.push_back(courbeDeBezier(listePoints[j], u));
    }
    return courbeDeBezier(bju, v);
}

void commeTuVeux()
{
    vector<Point> tmp;

    for (float u = 0; u < 1.0f; u+=0.1f) {
        tmp.clear();
        for (float v = 0; v < 1.0f; v+=0.1f) {
            tmp.push_back(B(u, v));
        }
        listePointsFinaux.push_back(tmp);
    }
}

int main()
{
    vector<Point> tmp;

    for (int j = 0; j < nbLigne; ++j) {
        tmp.clear();
        for (int i = 0; i < nbColonne; ++i) {
            tmp.push_back(Point(i*10,j*10,((i+j)%2)*10));
        }
        listePoints.push_back(tmp);
    }

    commeTuVeux();
    size_t nbLigne = listePointsFinaux.size();
    size_t nbColonne = listePointsFinaux[0].size();

    Face f;
    for (size_t k = 0; k < (nbLigne-1)*(nbColonne-1); ++k) {
        f.clear();
        int i = k%(nbColonne-1);
        int j = k/(nbColonne-1);
        f.ajouterIndice(j*nbColonne + i +1) ;
        f.ajouterIndice(j*nbColonne + i+1 +1);
        f.ajouterIndice((j+1)*nbColonne + i+1 +1);
        f.ajouterIndice((j+1)*nbColonne + i +1);
        listeFaces.push_back(f);
    }

    FileManager fm(QString("test_final.obj"));

    for (size_t j = 0; j < nbLigne; ++j) {
        for (size_t i = 0; i < nbColonne; ++i) {
            fm.addPoint(listePointsFinaux[j][i]);
        }
    }

    for (int i = 0; i < (nbLigne-1)*(nbColonne-1); ++i) {
        fm.addFace(listeFaces[i]);
    }

    fm.generate();
//    Point p1(1.2,2.2,3.3);
//    Point p2(1.4,4.2,3.93);
//    Point p3(7.9,5.5,7.3);
//    Point p4(15.6,6.9,4.3);
//    Point p5(1.2,2.2,20.3);
//    Point p6(6.6,9.12,14.3);

//    Face f1;
//    f1.ajouterIndice(1);
//    f1.ajouterIndice(3);
//    f1.ajouterIndice(4);
//    f1.ajouterIndice(6);

//    Face f2;
//    f2.ajouterIndice(2);
//    f2.ajouterIndice(5);
//    f2.ajouterIndice(6);

//    FileManager fm2(QString("test.obj"));
//    fm2.addPoint(p1);
//    fm2.addPoint(p2);
//    fm2.addPoint(p3);
//    fm2.addPoint(p4);
//    fm2.addPoint(p5);
//    fm2.addPoint(p6);

//    fm2.addFace(f1);
//    fm2.addFace(f2);

//    fm2.generate();

    return 0;
}


