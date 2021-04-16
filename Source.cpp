/*მოცემულ გრაფში, G=(V,E) სადაცV={a,b,c,d,e},
E={(a,b),(b,c),(d,e),(e,a),(c,e),(c,a),(c,d)}
სიღრმეში ძებნის ალგორითმის კოდის გამოყენებით, შეადგინეთ კოდი,
რომელიც მოცემული ორიენტირებულ გრაფისთვის დაადგენს ძლიერად
ბმული კომპონენტების რაოდენობას.*/

#include<iostream>
#include<list>
#include <stack>
using namespace std;
class Graph {
	int V;
	int scc_count = 0;// ძლიერად ბმული კომპონენტების რაოდენობა
	list<int>* adj;
	list<int>* adjT; //ტრანსპონირებული მოსაზღვრე სია,რომელიც მოგვცემს ტრანსპონირებულ გრაფს
	stack<int> Stack;//სტეკი, დამუშავებული წვეროების მიმდევრობით დამატებისთვის
public:
	Graph(int V);
	void addEdge(int x, int y);
	void dfsviz(int v, bool* visited);
	void Tdfsviz(int v, bool* visited);// ფუნქცია ტრანსპონირებული გრაფის წვეროების დამუშავებისთვის 
	void DFS(int v);
	void SCC(); // ფუნქცია, რომელიც DFS-ს ჩაატარებს ტრანსპონირებულ გრაფზე და დაადგენს ძლიერად ბმულობის კომპონენტებს
};
Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
	adjT = new list<int>[V];
}
void Graph::addEdge(int x, int y)
{
	adj[x].push_back(y);
	adjT[y].push_back(x);//ვამატებთ მოსაზღვრე სიაში შებრუნებული კომბინაციით წიბოებს
}
void Graph::dfsviz(int v, bool* visited)
{
	visited[v] = true;
	cout << v << " ";
	for (auto i = adj[v].begin(); i != adj[v].end(); i++)
		if (!visited[*i]) {
			dfsviz(*i, visited);
		}
	Stack.push(v); // სტეკში ემატება დამუშავებული ელემენტი, პირველად ჩაემატება ყველაზე ადრე დამუშავებული ელემენტი, 
	//ბოლოს - ყველაზე გვიან და გამოვა დამუშავების დროის კლების მიხედვით დალაგებული
}
void Graph::Tdfsviz(int v, bool* visited)
{
	visited[v] = true;
	cout << v << " "; 
	for (auto i = adjT[v].begin(); i != adjT[v].end(); i++)
		if (!visited[*i]) {
			Tdfsviz(*i, visited);
		}
}
void Graph::DFS(int v) {
	bool* visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	dfsviz(v, visited); cout << endl;
	for (int i = 0; i < V; i++) {
		if (!visited[i]) {
			dfsviz(i, visited);
			cout << endl;
		}
	}
}
void Graph::SCC() {
	bool* visited = new bool[V]; 
	for (int i = 0; i < V; i++)
		visited[i] = false;
	while (!Stack.empty()) 
	{
		int k = Stack.top(); //ამოვიღოთ პირველი ელემენტი
		Stack.pop();//წავშალოთ ამოღებული ელემენტი
		if (visited[k] == false) // თუ წვეროში არ ვყოფილვართ ჯერ
		{
			Tdfsviz(k, visited);
			++scc_count;
			cout << endl;
		}
	}
	cout << "Number of strongly connected components: " << scc_count << endl;
}
int main() 
{
	//E = { (a,b),(b,c),(d,e),(e,a),(c,e),(c,a),(c,d) }
	Graph g(5); //V = { a,b,c,d,e }={0,1,2,3,4}
	g.addEdge(0, 1); //(a,b)
	g.addEdge(1, 2);//(b,c)
	g.addEdge(3, 4);//(d,e)
	g.addEdge(4, 0); //(e,a)
	g.addEdge(2, 4);//(c,e)
	g.addEdge(2, 0);//(c,a)
	g.addEdge(2, 3);//(c, d)
	
	g.DFS(1);
	cout << endl << "Strongly connected components: " << endl;
	g.SCC();
	

}