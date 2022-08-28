#include <cstdio>
#include <iostream>
using namespace std;

int main()
{
    int numOfVertices = 0, numOfArcs = 0, s = 0, t = 0;
	cout << "hello from " << "Algorithms__Ford–Fulkerson" << "!\n";
	
    while (numOfVertices <= 0) {
        cout << "Enter the number of vertices in the graph\n";
        cin >> numOfVertices;
    }

    while (numOfArcs <= 0) 
    {
		cout << "Enter the number of vertices in the graph\n"; //TODO fix this 
        cin >> numOfVertices;
    }

    while (s <= 0) {
		cout << "Enter v1\n";
		cin >> s;
    }

    while (t <= 0) {
        cout << "Enter t\n"; 
		cin >> t;
    }
    return 0;
}