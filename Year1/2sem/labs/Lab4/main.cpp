#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include "lib/classes.hpp"
using namespace std;




int findMinSegment(const vector<Segment*>& segments, const vector<Face*>& faces) {
    if( segments.empty() )
        return -1;
    int least = -1;
    int minValue = INT32_MAX;
    for( int i = 0; i < segments.size(); ++i ) {
        int curr = segments[i]->fitsIntoFaces(faces);
        if( curr < minValue ) {
            least = i;
            minValue = curr;
        }
    }

    return least;
}

void dfsForSegments(const Graph& graph, int vertex, const Graph& Gplane, vector<char>& visited, Segment *seg, set<int>& contacts) {
    vector<int> next;
    visited[vertex] = 1;
    graph.GetNextVertices(vertex, next);
    for( int n : next ) {
        if( !Gplane.isolated(n) ) {// If n in Gplane
            contacts.insert(n);
            seg->AddEdge(n, vertex);
        }
        else if( !visited[n] ) {
            dfsForSegments(graph, n, Gplane, visited, seg, contacts);
        }
        seg->AddEdge(vertex, n);
    }
}

Segment *findSegment(const Graph& graph, int vertex, const Graph& Gplane) {
    // Traverse using DFS, add edges into the segment
    vector<char> visited(graph.VerticesCount(), 0);
    auto seg = new Segment(graph.VerticesCount());
    set<int> contacts;
    dfsForSegments(graph, vertex, Gplane, visited, seg, contacts);
    seg->addContacts(contacts);

    return seg;
}

void splitIntoSegments(const Graph& graph, const vector<int>& contacts, vector<Segment*>& segments, Graph& Gplane) {
    vector<int> next;
    set<pair<int, int>> PrevEdges;
    for (int vertex : contacts) {
        graph.GetNextVertices(vertex, next);
        for (int n : next) {
            // First check Gplane, then - if visited
            if (!Gplane.areAdjacent(n, vertex) && PrevEdges.find(make_pair(vertex, n)) == PrevEdges.end()) {
                Segment *newSegment = nullptr;
                if( !Gplane.isolated(n) ) { // If already laid
                    newSegment = new Segment(max(n, vertex) + 1, set<int> {vertex, n});
                    newSegment->AddEdge(vertex, n);
                    newSegment->AddEdge(n, vertex);
                    PrevEdges.insert(make_pair(vertex, n));
                    PrevEdges.insert(make_pair(n, vertex));
                }
                else {
                    newSegment = findSegment(graph, n, Gplane);
                    // Mark used edges
                    if (newSegment != nullptr) {
                        set<int> segContacts;
                        vector<int> segNext;
                        newSegment->getContacts(segContacts);
                        for (int v : segContacts) {
                            newSegment->GetNextVertices(v, segNext);
                            for (int segN : segNext) {
                                PrevEdges.insert(make_pair(v, segN));
                                PrevEdges.insert(make_pair(segN, v));
                            }
                            segNext.clear();
                        }
                    }
                }
                segments.push_back(newSegment);
            }
            next.clear();
        }
    }
}

bool dfs(const Segment& seg, vector<int>& path, vector<char>& visited, int vertex) {
    vector<int> next;
    visited[vertex] = 1;
    seg.GetNextVertices(vertex, next); // all vertices connected with that vertex
    for( int n : next ) {
        if( !visited[n] ) {
            if( seg.isContact(n) ) {
                path.push_back(n);
                path.push_back(vertex);
                return true;
            }
            else {
                bool res = dfs(seg, path, visited, n);
                if( res ) {
                    path.push_back(vertex);
                    return res;
                } else {
                    continue;
                }
            }
        }
    }
    return false;
}

void findPath(const Segment& seg, vector<int>& path) {
    vector<char> visited(seg.VerticesCount(), 0);
    set<int> contacts;
    seg.getContacts(contacts);
    int vertex = *contacts.begin();
    dfs(seg, path, visited, vertex); 
}

int findCycle(const Graph& graph, vector<int>& contacts, vector<char>& color, int parent = -1, int vertex = 0) {
    color[vertex] = 'g';
    vector<int> next;
    graph.GetNextVertices(vertex, next);
    for( int n : next ) {
        if( color[n] == 'w' ) {
            int res = findCycle(graph, contacts, color, vertex, n);
            if( res != vertex && res != -1) {
                contacts.push_back(vertex);
                return res;
            } else return -1;
        }
        else if( color[n] == 'g' && parent != n ) {
            contacts.push_back(n);
            contacts.push_back(vertex);
            return n;
        }
    }
    color[vertex] = 'b';

    return 1;
}

//Why by adding const to Graph it does not compile???
bool is_planar(Graph& graph) { // Assume there are no bridges
    if(graph.empty())
        return true;

    Graph Gplane(graph.VerticesCount()); // Graph that we will 'draw'
    vector<int> contacts; // indexes of verteces in drawn graph
    vector<Segment*> segments; // all available segments, changes during algoritm
    vector<Face*> faces; // just all available faces, chanes during algoritm

    vector<char> color(static_cast<unsigned>(graph.VerticesCount()), 'w'); // all colors are 'w' at the begining
    //(debag) Assumption: if ret number is not -1 -> segmentation fault error during next part
    cout << endl <<"Ret: " << findCycle(graph, contacts, color) << endl;
    //cout << "Size: " << contacts.size() << endl;
    
    for( int i = 0; i < contacts.size(); ++i ) {
        Gplane.AddEdge(contacts[i], contacts[(i + 1) % contacts.size()]);
        Gplane.AddEdge(contacts[(i + 1) % contacts.size()], contacts[i]);
    }
    // We are starting with two faces: innier one and outter

    faces.emplace_back(new Face(contacts)); // same functional as push_back, but not exactly...
    reverse(contacts.begin(), contacts.end()); // they have same vertices,, but if the would be in same order, it may broke algoritm
    faces.emplace_back(new Face(contacts));


    splitIntoSegments(graph, contacts, segments, Gplane);

    while( !segments.empty() ) {
        int tmp = findMinSegment(segments, faces); //choosing index of Segment with minimal number of faces
        Segment *least = segments[tmp]; // pointer to it
        segments.erase(segments.begin() + tmp);
        vector<Face*> faceForSplit;
        if (least->fitsIntoFaces(faces, faceForSplit) == 0) { // That means graph is planar, exiting
            for( Segment *seg : segments )
                delete seg;
            for( Face *face : faces )
                delete face;
            delete least;

            return false;
        }
        // Find a path from one contact vertex to another
        // Then split the face, adding this path
        vector<int> path;
        findPath(*least, path); //
        for( int i = 0; i + 1 < path.size(); ++i ) {
            Gplane.AddEdge(path[i], path[i + 1]);
            Gplane.AddEdge(path[i + 1], path[i]);
        }
        //each addition of edge divide one's of faces on two
        Face *newFace = new Face(faceForSplit[0], path);
        faces.push_back(newFace); // Split faces
        if( path.size() != least->VerticesCount() ) {
            splitIntoSegments(*least, path, segments, Gplane);
        }
        delete least;
    }

    for( Segment *seg : segments )
        delete seg;
    for( Face *face : faces )
        delete face;

    return true;
}

int main() {
    //cout << "H" << endl;
    int vertices = 0, edges = 0, from = 0, to = 0;
    cin >> vertices >> edges;
    Graph graph(vertices);
    //cout << "E: " << edges << endl; 
    for( int i = 0; i < edges; ++i ) {
        cin >> from >> to;
        graph.AddEdge(from, to);
        graph.AddEdge(to, from);
    }

    cout << (is_planar(graph) ? "YES" : "NO") << '\n';

    return 0;
}