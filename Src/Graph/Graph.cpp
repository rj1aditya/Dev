#include<iostream>
#include<vector>
using namespace std;


void addedge( vector<int> adj[], int x,int y);

int main()
{
	vector<int> adj[5];
	
	addedge( adj, 0,1 );
	addedge( adj, 0,2 );
	addedge( adj, 1,2 );
	addedge( adj, 2,1 );
	addedge( adj, 2,3 );
	addedge( adj, 3,4 );
	addedge( adj, 4,1 );
	
	for( int i = 0; i < 5; i++ )
	{
		for( int j = 0; j < adj[i].size(); j++ )
		{
			cout<<adj[i][j]<<"->";
		}
		cout<<"end"<<endl;
	}
}

void addedge( vector<int> adj[], int x,int y)
{
	adj[x].push_back(y);
	adj[y].push_back(x);
}