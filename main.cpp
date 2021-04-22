#include <iostream>
#include <vector>


class UEdge{
	public:
		int Ni;
		int Nj;
		int cost;
		UEdge *next;

		UEdge(int Ni_, int Nj_, int cost_) : Ni(Ni_) , Nj(Nj_), cost(cost_){
			UEdge head = new UEdge(Ni, Nj, cost, NULL);
		}

		void printEdge(UEdge edge, ofstream debugFile){
			
		}
};

class PrimMST{
	public:
		int numNodes;
		int nodeInSetA;
		int whichSet[];
		UEdge* edgeListHead;
		UEdge* MSTlistHead;
		int totalMSTCost = 0;
		
		PrimMSt(int numNodes_, int nodeInSetA_) : numNodes(numNodes_), nodeInSetA(nodeInSetA_){
			whichSet = new int[numNodes + 1];
		 	whichSet[nodeInSetA] = 1;	
		}

		void listInsert(UEdge* newEdge){
		}

		UEdge* removeEdge(){
		}

		void addEdge(UEdge* newEdge){
		}

		void printSet(){
		}

		void printEdgeList(){
		}

		void printMSTList(ofstream& outFile){
		}

		bool setBisEmpty(){

			return true;
		}
};

int main(int argc, char*[]argv){
	ifstream inFile(argv[1]);
	int nodeInSetA(argv[2]);
	string line;
	string num;
	int numNodes;
	PrimMST prim;
	index = 0;
	while(nextLine(inFile, line)){
		num = "";
		if(index = 0){
			for(auto c : line){
				if(c!=' '){
					num+=c;
				}
				else{
					numNodes = stoi(num);
				}
			}
			
		prim = new PrimMST(numNodes, nodeInSetA);
		prim.printSet();
	}
}	
			
			
					
				



	return 0;
}

	
	







	return 0;
}
