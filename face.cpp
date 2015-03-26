#include "face.h"

Face::Face() :
    listeIndices(0)
{
}

void Face::ajouterIndice(int i)
{
    listeIndices.push_back(i);
}

const vector<int> &Face::getListeIndices() const
{
    return listeIndices;
}

string Face::ecrireFace()
{
    string s("f");

    for (size_t i = 0; i < listeIndices.size(); ++i) {
        s += " " + to_string(listeIndices[i]);
    }

    return s;
}

void Face::clear()
{
    listeIndices.clear();
}


