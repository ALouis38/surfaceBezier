#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>

#include <QString>

#include "face.h"
#include "point.h"

using namespace std;

class FileManager
{
public:
    FileManager(QString fileName);

    void addPoint(Point& p);
    void addFace(Face& f);
    void generate();



private:
    QString fileName;
    vector<Face> faces;
    vector<Point> points;
};

#endif // FILEMANAGER_H
