#include<iostream>
#include<climits>
using namespace std;

int Length =100;
struct Items{
    string name;
    int Id;
    
} item[100];

struct allRoutes{
     string name;
     int Id;
     int distance;
} route[100];
int Path[100];

int miniDist(int distance[], bool Tset[]) // finding minimum distance
{
    int minimum=INT_MAX,ind;
              
    for(int k=0;k<6;k++) 
    {
        if(Tset[k]==false && distance[k]<=minimum)      
        {
            minimum=distance[k];
            ind=k;
        }
    }
    return ind;
}

void DijkstraAlgo(int graph[6][6],int src) // adjacency matrix 
{
    int distance[6]; // // array to calculate the minimum distance for each node                             
    bool Tset[6];// boolean array to mark visited and unvisited for each node
    
     
    for(int k = 0; k<6; k++)
    {
        distance[k] = INT_MAX;
        Tset[k] = false;    
    }
    
    distance[src] = 0;   // Source vertex distance is set 0               
    
    for(int k = 0; k<6; k++)                           
    {
        int m=miniDist(distance,Tset); 
        Tset[m]=true;
        for(int k = 0; k<6; k++)                  
        {
            // updating the distance of neighbouring vertex
            if(!Tset[k] && graph[m][k] && distance[m]!=INT_MAX && distance[m]+graph[m][k]<distance[k])
                distance[k]=distance[m]+graph[m][k];
        }
    }
    cout<<"origin\t\tVertex\t\tDistance from source vertex"<<endl;
    for(int k = 0; k<6; k++)                      
    { 
        
        char str=65+k; 
        route[k].name = str;
        route[k].Id=k;
        route[k].distance=distance[k];
        cout<<k<<"\t\t\t"<<str<<"\t\t\t"<<distance[k]<<endl;
    }
}

bool FindItem(string Name){
    bool found = false;
   for (int i = 0; i < Length; i++) {
        if(item[i].name == Name){
            Path[i]=item[i].Id;
             found = true;
            break;
        }
   } 
   
   return found;
}

int DefinedPath[100];

int sorted[100];

int remove_duplicate(int arr[], int n)
{

  if (n == 0 || n == 1)
    return n;

  int temp[n];

  int j = 0;
  int i;
  for (i = 0; i < n - 1; i++)
    if (arr[i] != arr[i + 1])
      temp[j++] = arr[i];
  temp[j++] = arr[n - 1];

  for (i = 0; i < j; i++)
    arr[i] = temp[i];

  return j;
}

void SortDefinedPath(int n){
    int i,j;
	int temp;
    for(i=0;i<n;i++)
	{		
		for(j=i+1;j<n;j++)
		{
			if(DefinedPath[i]>DefinedPath[j])
			{
				temp  =DefinedPath[i];
				DefinedPath[i]=DefinedPath[j];
				DefinedPath[j]=temp;
			}
		}
	}
}

void PrintPath(){
       int count =0;
    	for (int i = 0; i < sizeof(Path)/sizeof(Path[0]); i++) {
	    if(Path[i] !=0){
	    //cout<<Path[i];
	     for (int j = 0; j < (sizeof route / sizeof *route); j++) {
	         if(route[j].Id == Path[i]){
	             DefinedPath[i]=route[j].distance;
	             count = count +1;
	         }
	      }
	     
	    }
	}
	
	SortDefinedPath(count);
	remove_duplicate(DefinedPath,sizeof(DefinedPath)/sizeof(DefinedPath[0]));
	//removeDuplicates(DefinedPath);
	 cout<<"The path you have to follow is\n";
	 bool Printed =false;
	for (int i = 0; i < sizeof(DefinedPath)/sizeof(DefinedPath[0]); i++) {
	      for (int j = 0; j < (sizeof route / sizeof *route); j++) {
	         if(route[j].distance == DefinedPath[i] && DefinedPath[i] !=0){
	            
	            if(!Printed){
	             cout<<route[i].name<<","<<route[j].name<<",";
	             Printed=true;
	            }else{
	              cout<<route[j].name<<",";  
	            }
	             //cout<<route[j].distance<<" "<<DefinedPath[i];
	         }
	      }
	}
	
	//read path with realtion to short distance 
	
	
}

int main()
{
    
    item[0].name="chips";
    item[0].Id=3;
    item[1].name="Automotive";
    item[1].Id=2;
    item[2].name="Applesauce";
    item[2].Id=1;
    
 
  
    int graph[6][6]={
        {0, 1, 2, 0, 0, 0},
        {1, 0, 0, 5, 1, 0},
        {2, 0, 0, 2, 3, 0},
        {0, 5, 2, 0, 2, 2},
        {0, 1, 3, 2, 0, 1},
        {0, 0, 0, 2, 1, 0}};
    DijkstraAlgo(graph,0);
    cout<<"\n"<<"enter shoping list to get the path\n";
    while (true) {
		string command;    // Now it's a string!
		cin >> command;
		

		if (command == "g") {
			break;
		}else{
		 bool result= FindItem(command);
		 if(!result){
		       cout<< command<<" Is not Available";
		 }
		 
		    
		}
		
		
	}
	PrintPath();

	cout <<"Program stoped";
    
    return 0;                           
}