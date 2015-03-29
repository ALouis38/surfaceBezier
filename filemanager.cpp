#include "filemanager.h"

FileManager::FileManager(QString fileName)
{
    this->fileName = QString("/home/henry/Documents/Qt_Project/surfacesBSplines/") + fileName;
}

void FileManager::addPoint(Point &p)
{
    points.push_back(p);
}

void FileManager::addFace(Face &f)
{
    faces.push_back(f);
}

void FileManager::generate()
{
    ofstream fichier(fileName.toStdString(), ios::out | ios::trunc);  // ouverture en écriture avec effacement du fichier ouvert

    if(fichier)
    {
        for (size_t i = 0; i < points.size(); ++i) {
            fichier << points[i].ecrirePoint() << endl;
        }

        for (size_t j = 0; j < faces.size(); ++j) {
            fichier << faces[j].ecrireFace() << endl;
        }

        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;
}
