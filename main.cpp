#include <iostream>
#include <vector>
using namespace std;

void dijkstra(vector<vector<int>> graph, int startNode);
int getClosestNode(vector<int> distance, vector<int> vis);
void adatrip(vector<vector<int>> graph, vector<int> startNodes);

int main(){
    vector<vector<int>> graph; //i,j connection with graph[i][j] weight
    int startNode; //starting node
    int nodeNum; //number of nodes
    int sideNum; //number of connections
    vector<int> startNodes;
    int startNodeNum;

    //inputs
    cin >> nodeNum >> sideNum >> startNodeNum;

    for (int i = 0; i < nodeNum; i++){ //fill graph with NULL-s
        graph.push_back({});
        for (int j = 0; j < nodeNum; j++){
            graph[i].push_back(0);
        }
    }
    for (int i = 0; i < sideNum; i++){ //input the values to the graph
        int x, y, w;
        cin >> x >> y >> w;
        graph[x-1][y-1] = w; //bidirectional
        graph[y-1][x-1] = w; //bidirectional

    }

    for (int i = 0; i < startNodeNum; i++){
        startNodes.push_back(0);
        cin >> startNodes[i];
    }

    adatrip(graph, startNodes);
}

int getClosestNode(vector<int> distance, vector<bool> vis){
    int min = INT_MAX; //distance to the closest unvisited node
    int index; //the index of the closest unvisited node

    for (int i = 0; i < distance.size(); i++){
        if (distance[i] <= min && !vis[i]){
            min = distance[i];
            index = i;
        }
    }

    return index;
}

void dijkstra(vector<vector<int>> graph, int startNode){
    vector<int> distance; //vector to calculate the minimum distance to the i-th node
    vector<bool> vis; //is the i-th node visited or not
    
    for (int i = 0; i < graph.size(); i++){ //set all of the distances to max, set all nodes unvisited
        distance.push_back(INT_MAX);
        vis.push_back(false);
    }

    distance[startNode] = 0; //distance to the starting node is set to 0

    for (int i = 0; i < graph.size(); i++){
        int closestNode = getClosestNode(distance, vis);
        vis[closestNode] = true;

        for(int i = 0; i < graph.size(); i++){
            // updating the distance of neighbouring vertex
            if(!vis[i] && graph[closestNode][i] && distance[closestNode]!=INT_MAX && distance[closestNode] + graph[closestNode][i] < distance[i]){
                distance[i] = distance[closestNode] + graph[closestNode][i];
            }
        }
    }
    
    //finding and counting the fruthest distances
    int furthest = INT_MIN;
    int furthestNum = 0;

    for (int i = 0; i < distance.size(); i++){ //finding the furthest nodes distance
        if (distance[i] > furthest && distance[i] != INT_MAX){
            furthest = distance[i];
        }
    }

    for (int i = 0; i < distance.size(); i++){
        if (distance[i] == furthest){
            furthestNum++;
        }
    }

    cout << furthest << '\t' << furthestNum << '\n';

}

void adatrip(vector<vector<int>> graph, vector<int> startNodes){
    for (int i = 0; i < startNodes.size(); i++){
        dijkstra(graph, startNodes[i]);
    }
}
