#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class UEdge{
	public:
		int Ni;
		int Nj;
		int cost;
		UEdge *next;

		UEdge(int Ni_, int Nj_, int cost_, UEdge *next_) : Ni(Ni_), Nj(Nj_), cost(cost_), next(next_){
		}

		void printEdge(ofstream& debugFile){
			if(next){
				debugFile<<"<Ni: "<< Ni << " Nj: " << Nj << " Cost: " << cost << " Next Node: " << next->Ni << ">-->"; 			
			}
			else{
				debugFile<<"<Ni: "<< Ni << " Nj: " << Nj << " Cost: " << cost << " Next Node: NULL>";
			}			
		}
};

class PrimMST{
	public:
		int numNodes;
		int nodeInSetA;
		int*  whichSet;
		UEdge* edgeListHead;
		UEdge* MSTlistHead;
		int totalMSTCost = 0;
		
		PrimMST(int numNodes_, int nodeInSetA_) : numNodes(numNodes_), nodeInSetA(nodeInSetA_){
			whichSet = new int[numNodes + 1];
		 	whichSet[nodeInSetA] = 1;	
			edgeListHead = new UEdge(0, 0, 0, NULL);
			MSTlistHead = new UEdge(0, 0, 0, NULL);
		}

		void listInsert(UEdge* newEdge){
			UEdge* scanner = edgeListHead;
			while(scanner->next && scanner->next->cost < newEdge->cost){
				scanner = scanner->next;
			}

			newEdge->next = scanner->next;
			scanner->next = newEdge;
		}

		UEdge* removeEdge(){
			UEdge* scanner = edgeListHead;
			UEdge* retval = scanner;
			while(scanner->next){
				if((whichSet[scanner->next->Ni] != whichSet[scanner->next->Nj]) && (whichSet[scanner->next->Ni] == 1 || whichSet[scanner->next->Nj] == 1)){
					retval = scanner->next;
					scanner->next = scanner->next->next;
					return retval;
				}
				scanner = scanner->next;
			}

			return retval;
		}

		void addEdge(UEdge* newEdge){
			newEdge->next = MSTlistHead->next;
			MSTlistHead->next = newEdge;
		}

		void printSet(ofstream& debugFile){
			debugFile<<"*** PRINTING WHICHSET ***"<<endl;
			for(int i = 0; i < numNodes + 1; i++){
				debugFile<<" "<<whichSet[i];
			}

			debugFile<<endl<<"*** DONE PRINTING WHICHSET ***"<<endl;
		}

		void printEdgeList(ofstream& debugFile){
			UEdge* scanner = edgeListHead;
			debugFile<<"*** PRINTING EDGE LIST ***"<<endl;
			while(scanner){
				scanner->printEdge(debugFile);
				scanner = scanner->next;
			}	
			debugFile<<endl<<"*** DONE PRINTING EDGE LIST ***"<<endl;
		}

		void printMSTList(ofstream& debugFile){
			UEdge* scanner = MSTlistHead;
			debugFile<<"*** PRINTING MST LIST ***"<<endl;
			while(scanner){
				scanner->printEdge(debugFile);
				scanner = scanner->next;
			}	
			debugFile<<endl<<"*** DONE PRINTING MST LIST ***"<<endl;
		}

		void updateMST(UEdge* newEdge){
			addEdge(newEdge);
			totalMSTCost += newEdge->cost;
			if(whichSet[newEdge->Ni] == 1){
				whichSet[newEdge->Nj] = 1;
			}
			else{
				whichSet[newEdge->Ni] = 1;
			}
		}

		bool setBisEmpty(){
			for(int i = 0; i < numNodes+1; i++){
				if(whichSet[i] != 1){
					return false;
				}
			}

			return true;
		}
};

int main(int argc, char* argv[]){
	ifstream inFile(argv[1]);
	int nodeInSetA(stoi(argv[2]));
	ofstream MSTFile(argv[3]);
	ofstream debugFile(argv[4]);

	string line;
	int numNodes;
	int index = 0;
	PrimMST* prim;
	while(getline(inFile, line)){
		if(index == 0){
			string num = "";
			for(auto c : line){
				if(c!=' '){
					num+=c;
				}
			}
				
			numNodes = stoi(num);
			index++;	
			prim = new PrimMST(numNodes, nodeInSetA);
			prim->printSet(debugFile);
			continue;
		}
		

		vector<int> param = {};
		string curr = "";
		for(auto c : line){
			if(c!=' '){
				curr += c;
			}
			else{
				param.push_back(stoi(curr));
				curr = "";
			}
		}
				
		param.push_back(stoi(curr));

		int Ni = param[0];
		int Nj = param[1];
		int edgeCost = param[2];
		UEdge* newEdge = new UEdge(Ni, Nj, edgeCost, NULL);
		prim->listInsert(newEdge);
		prim->printEdgeList(debugFile);
	}
	
	while(!prim->setBisEmpty()){
		UEdge* nextEdge = prim->removeEdge();

		debugFile<<endl;
		nextEdge->printEdge(debugFile);
		debugFile<<endl;

		if(nextEdge->Ni == 0 && nextEdge->Nj ==0){
			break;
		}

		prim->updateMST(nextEdge);
		prim->printSet(debugFile);
		prim->printEdgeList(debugFile);
		prim->printMSTList(debugFile);
	}	

	MSTFile << "*** Prim's MST of he input graph G is: ***" << endl;
    MSTFile << "numNodes: " << numNodes << endl;
	prim->printMSTList(MSTFile);
	MSTFile << "*** MST total cost = " << prim->totalMSTCost<<" ***";	

	inFile.close();
	MSTFile.close();
	debugFile.close();

	return 0;
}
