#include <iostream>
#include <vector>
#include <queue>
using namespace std;
void bfs(vector<vector<int>> graph, int start) {
	bool *visited = new bool(10);
	for(int i=0;i<10;i++)   visited[i]=false;
    
    queue<int> q;
    q.push(start);
    while(!q.empty()){
        int t = q.front();
        q.pop();
        if(visited[t] == false){
            cout<<t<<" ";
            visited[t]=true;
            for(auto it=graph[t].begin();it!=graph[t].end();it++){
                if(visited[*it] == false)  q.push(*it);
            }
        }
    }
    delete [] visited;
}
int main(){
    int init_graph[10][10] = {  {0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
				    {0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
				    {0, 1, 0, 0, 0, 1, 1, 0, 1, 1},
				    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
				    {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
				    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
				    {0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
				    {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
				    {0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
				    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0} };
	int n = 10;
	vector<vector<int>> graph(n, vector<int>());
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (init_graph[i][j]) graph[i].push_back(j);
		}
	}

	bfs(graph, 0);
    return 0;
}
