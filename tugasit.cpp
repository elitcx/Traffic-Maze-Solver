#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int dr[4] = {-1,1,0,0};
int dc[4] = {0,0,1,-1};

struct Node{
    int r, c, cost;
    bool operator>(const Node &other) const{
        return cost > other.cost;
    }
};

int main(){
    int n,m;
    Node start, end;
    bool found = false;
    cout << "Masukkan banyak baris: "; cin >> n;
    cout << "Masukkan banyak kolom: "; cin >> m;
    vector<vector<int>> grid(n, vector<int>(m));
    cout << "Masukkan grid (-1 = Bangunan, 0 = Mulai/Akhir, Integer untuk bobot kemacetan jalan): \n";
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            int tile;
            cin >> tile;
            if (tile == 0 && !found){
                start.r = i;
                start.c = j;
                start.cost = 0;
                found = true;
            } else if (tile == 0 && found){
                end.r = i;
                end.c = j;
                end.cost = INF;
            }
            grid[i][j] = tile;
        }
    }
    int sr = start.r, sc = start.c, er = end.r, ec = end.c;
    vector<vector<int>> dist(n, vector<int>(m, INF));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1,-1}));
    vector<pair<int,int>> path;
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    dist[sr][sc] = 0;
    pq.push(start);
    while(!pq.empty()){
        Node curNode = pq.top();
        pq.pop();
        int cr = curNode.r, cc = curNode.c, cost = curNode.cost;
        if (cost > dist[cr][cc]) continue;
        if (cr == er && cc == ec){
            while (cr != -1 && cc != -1) {
                path.push_back({cr, cc});
                auto p = parent[cr][cc];
                cr = p.first;
                cc = p.second;
            }
            reverse(path.begin(), path.end());
            break;
        }

        for (int i = 0; i < 4; i++){
            int nr = cr + dr[i];
            int nc = cc + dc[i];

            if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
            if (grid[nr][nc] == -1) continue;

            int newdist = cost + grid[nr][nc];
            if (newdist < dist[nr][nc]){
                dist[nr][nc] = newdist;
                parent[nr][nc] = {cr,cc};
                pq.push({nr, nc, dist[nr][nc]});
            }
        }
    }
    if (dist[er][ec] != INF) {
        cout << "Jalur dengan tingkat kemacetan paling sedikit:\n";
        for (int i = 0; i < path.size(); i++) {
            cout << "(" << path[i].first << "," << path[i].second << ")";
            if (i + 1 < path.size()) cout << " -> ";
        }
        cout << "\nTotal tingkat kemacetan: " << dist[er][ec] << "\n";

        vector<vector<char>> view(n, vector<char>(m, ' '));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == -1) view[i][j] = '#'; // building
                else view[i][j] = '.';                  // road
            }
        }
        for (auto [r,c] : path) view[r][c] = '*';
        view[sr][sc] = 'S';
        view[er][ec] = 'E';
        cout << "\nGrid dengan jalur:\n";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << view[i][j] << " ";
            }
            cout << "\n";
        }
    } else{
        cout << "Tidak ada jalur yang mungkin.\n";
    }
}