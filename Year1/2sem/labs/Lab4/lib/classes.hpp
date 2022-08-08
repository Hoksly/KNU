#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

// Face == грань
class Face;

class Graph {
public:
    ~Graph() = default;
    explicit Graph(int vertNumber);
    void AddEdge(int from, int to);
    int VerticesCount() const;
    bool areAdjacent(int v1, int v2) const { return find(toList[v1].begin(), toList[v1].end(), v2) != toList[v1].end(); }
    bool isolated(int v) const { return toList[v].empty() && fromList[v].empty(); }
    int GetNextVertices(int vertex, vector<int>& vertices) const;
    int GetPrevVertices(int vertex, vector<int>& vertices) const;
    bool empty();

private:
    vector<vector<int>> toList;
    vector<vector<int>> fromList;
};

class Segment : public Graph {
public:
    explicit Segment(int vertNumber) : Graph(vertNumber) {} //first type segment
    Segment(int vertNumber, set<int> contacts) : Graph(vertNumber), contactVertices(move(contacts)) {} // sub graph (second type)
    void addContacts(const set<int>& contacts) { contactVertices.insert(contacts.begin(), contacts.end()); }
    int fitsIntoFaces(const vector<Face*>&, vector<Face*>&) const;
    int fitsIntoFaces(const vector<Face*>&) const;
    void getContacts(set<int>& contacts) const { contacts = contactVertices; }
    bool isContact(int vertex) const { return find(contactVertices.begin(), contactVertices.end(), vertex) != contactVertices.end(); }
private:
    set<int> contactVertices; // just set of all contact vertices
};


class Face {
public:
    explicit Face(vector<int> vertices) : cycle(move(vertices)) {}
    Face(Face*, vector<int> vertices);
    bool contains(const Segment*) const;
private:
    vector<int> cycle; // Face lies at the right side
};