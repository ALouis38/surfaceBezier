#ifndef FACE_H
#define FACE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Face
{
public:
    Face();
    void ajouterIndice(int i);
    const vector<int>& getListeIndices() const;
    string ecrireFace();
    void clear();

private:
    vector<int> listeIndices;
};

#endif // FACE_H
