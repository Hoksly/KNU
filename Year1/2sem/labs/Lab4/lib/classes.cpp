#include "classes.hpp"
using namespace std;


Graph::Graph(int vertNumber) {
    for( int i = 0; i < vertNumber; ++i ) {
        toList.emplace_back(vector<int>());
        fromList.emplace_back(vector<int>());
    }
}

void Graph::AddEdge(int from, int to) {
    toList[from].push_back(to);
}

int Graph::GetNextVertices(int vertex, vector<int> &vertices) const {
    for( int n : toList[vertex] )
        vertices.push_back(n);
    return static_cast<int>(toList[vertex].size());
}

int Graph::GetPrevVertices(int vertex, vector<int> &vertices) const {
    for( int n : fromList[vertex] )
        vertices.push_back(n);
    return static_cast<int>(fromList[vertex].size());
}

int Graph::VerticesCount() const {
    return static_cast<int>(toList.size());
}

bool Graph::empty()
{
    return toList.empty();
}







int Segment::fitsIntoFaces(const vector<Face*>& faces, vector<Face*>& fits) const {
    int counter = 0;
    for( Face *face : faces ) {
        if( face->contains(this) ) {
            fits.push_back(face);
            ++counter;
        }
    }

    return counter;
}

int Segment::fitsIntoFaces(const vector<Face*>& faces) const {
    int counter = 0;
    for( Face *face : faces ) {
        if( face->contains(this) ) {
            ++counter;
        }
    }
    return counter;
}






bool Face::contains(const Segment* segment) const {
    set<int> contacts;
    segment->getContacts(contacts);
    for( int contact : contacts ) {
        if( find(cycle.begin(), cycle.end(), contact ) == cycle.end() )
            return false;
    }
    return true;
}

Face::Face(Face* original, vector<int> vertices) { // Copy because it might change
    int firstContact = -1, lastContact = -1;
    for( int i = 0; i < original->cycle.size(); ++i ) {
        if( original->cycle[i] == vertices[0] )
            firstContact = i;
        else if( original->cycle[i] == vertices[vertices.size() - 1])
            lastContact = i;
    }
    if( firstContact > lastContact )
        swap(firstContact, lastContact);
    if( vertices[0] == original->cycle[lastContact] )
        reverse(vertices.begin(), vertices.end());

    // Go from 0 to 1st contact, insert vertices, then add 2nd - last
    // Then go from 1st to 2nd, add reversed vertices
    vector<int> tmpCycle(original->cycle.begin() + firstContact + 1, original->cycle.begin() + lastContact);
    original->cycle.erase(original->cycle.begin() + firstContact + 1, original->cycle.begin() + lastContact);
    original->cycle.insert(original->cycle.begin() + firstContact + 1, vertices.begin() + 1, vertices.end() - 1);

    reverse(vertices.begin(), vertices.end());
    vertices.insert(vertices.end(), tmpCycle.begin(), tmpCycle.end());
    this->cycle = vector<int>(vertices);
}