class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int e=edges.size();
        int n=colors.size(); //Nodes

        vector<vector<int>> adj(n, vector<int>());
        vector<int> indegree(n,0);


        for(int i=0; i<e; i++){
            int u =edges[i][0];
            int v =edges[i][1];
            adj[u].push_back(v);
            indegree[v]++;
        }

        queue<int> q;
        for(int k=0 ; k<n; k++){
            if(indegree[k]==0){
                q.push(k);
            }
        }

        vector<vector<int>> count(n , vector<int>(26, 0));
        for(int z=0; z<n; z++){
            count[z][colors[z]-'a'] +=1;
        }

        int max_count=0;
        int visited=0;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            visited++;
            max_count = max( max_count , *max_element(count[u].begin(), count[u].end()));
            for(auto v: adj[u]){
                for(int col=0; col<26; col++){
                    count[v][col] = max( count[v][col] , count[u][col] + (colors[v]-'a'==col ? 1 : 0));
                }
                indegree[v]--;
                if(indegree[v]==0){
                    q.push(v);
                }
            }
        }
        if(visited==n) return max_count;
        return -1;
    }
};