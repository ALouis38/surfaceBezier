#include "face.h"
#include "point.h"
#include "filemanager.h"
#include <iostream>
#include <vector>

using namespace std;

vector<vector<Point>> listePoints;
vector<Face> listeFaces;

void commeTuVeux(){

}

Point rechercherPoint(QPointF p1, QPointF p2, double t)
{
    QPointF res(0,0);

    res.setX(p1.x()+t*(p2.x()-p1.x()));
    res.setY(p1.y()+t*(p2.y()-p1.y()));

    return res;
}

vector<Point> courbeDeBezier(vector<Point> lp){
    vector<Point> listeTmp1,listeTmp2,listeStep;
    listePointsFinaux.push_back(liste[0]);

    double tmp = 100.0;

    for (int t = 1; t < tmp; ++t) {
        listeTmp1 = liste;
        while (listeTmp1.size() > 1) {
            Point temp = listeTmp1[0];
            listeTmp2.clear();
            for (int i = 1; i < listeTmp1.size(); ++i) {
                listeTmp2.push_back(rechercherPoint(temp,listeTmp1[i],((double) t)/tmp));
                temp = listeTmp1[i];
            }

            listeTmp1.clear();
            listeTmp1 = listeTmp2;
        }

        QPointF res(int(listeTmp1[0].x() +0.5),int(listeTmp1[0].y() +0.5));
        listePointsFinaux.push_back(res);
    }

    listePointsFinaux.push_back(liste[liste.size()-1]);

    afficherListePoints(liste,qRgb(0,0,0));
    afficherListePoints(listePointsFinaux,qRgb(255,0,0));
    scene.update();
}

int main()
{
//    listePoints = vector<vector<Point>>(0);
    vector<Point> tmp;

    for (int j = 0; j < 4; ++j) {
//        listePoints[i].push_back(vector<Point>(0));
        tmp.clear();
        for (int i = 0; i < 5; ++i) {
            tmp.push_back(Point(i*10,j*10,((i+j)%2)*10));
        }
        listePoints.push_back(tmp);
    }

    Face f;

    for (int k = 0; k < 12; ++k) {
        f.clear();
        int i = k%4;
        int j = k/4;
        f.ajouterIndice(j*5 + i +1) ;
        f.ajouterIndice(j*5 + i+1 +1);
        f.ajouterIndice((j+1)*5 + i+1 +1);
        f.ajouterIndice((j+1)*5 + i +1);
        listeFaces.push_back(f);
    }

    FileManager fm(QString("test2.obj"));

    for (int j = 0; j < 4; ++j) {
        for (int i = 0; i < 5; ++i) {
            fm.addPoint(listePoints[j][i]);
        }
    }

    for (int i = 0; i < 12; ++i) {
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


