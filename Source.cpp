
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <list>
#include <vector>
#include <limits.h>
using namespace std;

class Graph
{
	int V;    // No. of vertices
	list<int> *adj;    // Pointer to an array containing adjacency lists
	bool isCyclicUtil(int v, bool visited[], bool *rs);  // used by isCyclic()
public:
	Graph(int V);   // Constructor
	void addEdge(int v, int w);   // to add an edge to graph
	bool isCyclic();    // returns true if there is a cycle in this graph
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}


bool Graph::isCyclicUtil(int v, bool visited[], bool *recStack)
{
	if(visited[v] == false)
	{
		// Mark the current node as visited and part of recursion stack
		visited[v] = true;
		recStack[v] = true;

		// Recur for all the vertices adjacent to this vertex
		list<int>::iterator i;
		for(i = adj[v].begin(); i != adj[v].end(); ++i)
		{
			if ( !visited[*i] && isCyclicUtil(*i, visited, recStack) )
				return true;
			else if (recStack[*i])
				return true;
		}

	}
	recStack[v] = false;  // remove the vertex from recursion stack
	return false;
}

// Returns true if the graph contains a cycle, else false.
bool Graph::isCyclic()
{
	// Mark all the vertices as not visited and not part of recursion
	// stack
	bool *visited = new bool[V];
	bool *recStack = new bool[V];
	for(int i = 0; i < V; i++)
	{
		visited[i] = false;
		recStack[i] = false;
	}

	// Call the recursive helper function to detect cycle in different
	// DFS trees
	for(int i = 0; i < V; i++)
		if (isCyclicUtil(i, visited, recStack))
			return true;

	return false;
}


int transaction_count(string *operation,int n)
{
	string transaction_number_string;
	int transaction_number;
	int arr[100]={0};
	int*arr2;
	int count=0;

	for(int i=0;i<n;i++)
	{
		transaction_number_string=operation[i].substr (1,2);
		transaction_number = atoi(transaction_number_string.c_str()); 
		arr[transaction_number]++;
	}

	for(int i=0;i<100;i++)
	{
		if(arr[i]>0)
			count++;
	}
	arr2=new int[count];

	return count;

}

int variable_count(string *operation,int n)
{
	char variable_char;
	int variable_number;
	int arr[123]={0};
	int*arr2;
	int count=0;

	for(int i=0;i<n;i++)
	{
		if(operation[i][4]!=NULL){
			variable_char=operation[i][4];
			variable_number = int(variable_char); 
			arr[variable_number]++;
		}
	}

	for(int i=0;i<123;i++)
	{
		if(arr[i]>0)
			count++;
	}
	arr2=new int[count];

	return count;
}

int main()
{
	int n;
	std::cin >>n;
	string *operation = new string [n];
	char act;
	char var_char;
	int var_number;
	string transaction_string;
	int transaction_number;
	int arr[124][100] ;
	int line;
	vector <int> vvv[1000];
	for(int i=0;i<124;i++)
		for(int j=0;j<100;j++)
			arr[i][j]=-1;

	int z;
	int min_transaction=1000;
	int max_transaction=0;
	bool cascadeless=true;
	bool recoverable =true;

	for(int i=0;i<n;i++)
		std::cin>>operation[i];



	Graph g(transaction_count(operation,n)+1);

	for(int i=0;i<n;i++)
	{
		transaction_string=operation[i].substr (1,2);
		transaction_number = atoi(transaction_string.c_str()); 

		if(transaction_number<min_transaction)
			min_transaction=transaction_number;
		if(transaction_number>max_transaction)
			max_transaction=transaction_number;

		act=operation[i][3];
		if(operation[i][4]!=NULL){
			var_char=operation[i][4];
			var_number = int(var_char); 
		}

		if(act=='W')
		{
			vvv[transaction_number].push_back(((i+1)*100000)+(87*1000)+(var_number));
			if(arr[var_number][transaction_number]==-1)
				arr[var_number][transaction_number]=1;
			else if(arr[var_number][transaction_number]==0)
				arr[var_number][transaction_number]=2;

			for(int j=0;j<transaction_count(operation,n)+1;j++)
			{
				if(j!=transaction_number)
				{
					if(arr[var_number][j]==1 || arr[var_number][j]==0 || arr[var_number][j]==2 || arr[var_number][j]==10 || arr[var_number][j]==11 || arr[var_number][j]==12)
					{
						g.addEdge(j, transaction_number);
					}
				}
			}
		}
		if(act=='R')
		{
			vvv[transaction_number].push_back(((i+1)*100000)+(82*1000)+(var_number));
			if(arr[var_number][transaction_number]==-1)
				arr[var_number][transaction_number]=0;
			else if(arr[var_number][transaction_number]==1)
				arr[var_number][transaction_number]=2;
			for(int j=0;j<transaction_count(operation,n)+1;j++)
			{
				if(j!=transaction_number)
				{
					if(arr[var_number][j]==1 || arr[var_number][j]==2 || arr[var_number][j]==11 || arr[var_number][j]==12)
					{
						g.addEdge(j, transaction_number);

						//Cascadeless
						/*if(arr[var_number][j]==1 || arr[var_number][j]==2)
							cascadeless=false;
							*/
					}
				}
			}
		}
		
		if(act=='C')
		{
			vvv[transaction_number].push_back(i+1);
			for(int j=0;j<124;j++)
			{
				if(arr[j][transaction_number]==1)
					arr[j][transaction_number]=(11);
				else if(arr[j][transaction_number]==2)
					arr[j][transaction_number]=(12);
				else if(arr[j][transaction_number]==0)
				{
					//Recoverable
					/*for(int k=0;k<transaction_count(operation,n)+1;k++)
					{
						if(k!=transaction_number)
						{
							if(arr[j][k]==1 || arr[j][k]==2)
							{
								recoverable = false;
								z=transaction_number;
							}

							if(recoverable==false)
								for(int l=0;l<124;l++)
									if(arr[l][z]==10)
										recoverable = true;
							
						}

					}*/

					arr[j][transaction_number]=(10);
				}
			}			
		}
	}

	int v_num1;
	int v_num2;
	int act_num;
	int line_num1;
	int line_num2;
	bool flag=false;

	for(int i=min_transaction;i<=max_transaction;i++)
	{
		for(int j=min_transaction;j<=max_transaction;j++)
		{
			if(i!=j)
			{
				for(int k=0;k<vvv[i].size();k++)
				{
					act_num=((vvv[i][k])/1000)%100;
					v_num1=(vvv[i][k])%1000;
					line_num1=(vvv[i][k])/100000;
					if(act_num==87)
					{
						for(int l=0;l<vvv[j].size();l++)
						{
							act_num=((vvv[j][l])/1000)%100;
							v_num2=(vvv[j][l])%1000;
							line_num2=(vvv[j][l])/100000;
							if(act_num==82 && line_num2>line_num1 && v_num2==v_num1)
							{
								//recoverable
								if((vvv[j][vvv[j].size()-1])/100000==0)
								{
									if((vvv[i][vvv[i].size()-1])/100000 != 0)
									{
										recoverable=false;
									}
									else
									{
										if(vvv[i][vvv[i].size()-1]>vvv[j][vvv[j].size()-1])
										{
											recoverable=false;
										}
									}
								}
								//cascadeless
								if((vvv[i][vvv[i].size()-1])/100000 != 0)
									cascadeless=false;
								if(((vvv[i][vvv[i].size()-1])/100000 == 0) && (vvv[i][vvv[i].size()-1]>line_num2))
									cascadeless=false;
							}
						}
					}
				}
			}
		}
	}


	if(g.isCyclic())
		cout << "NO\n";
	else
		cout << "YES\n";

	if(recoverable)
		cout<<"YES\n";
	else
		cout<<"NO\n";

	if(cascadeless)
		cout<<"YES\n";
	else
		cout<<"NO\n";
	cin>>n;
	return 0;

}

