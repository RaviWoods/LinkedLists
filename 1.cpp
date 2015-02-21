#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <sstream>

using namespace std;

typedef int Item;

struct Node {
	Item data;
	Node* next;
};

typedef Node* NodePtr;

int RunComFileOps(vector<string> vectcomfile, vector<string>& vectoutfile);
void ReadFile(int& filenumber, NodePtr& hdlist);
void WriteFile(vector<string>& vectoutfile, NodePtr hdlist);
Item GetFromList(NodePtr& hdlist);
void AddToList(Item number, NodePtr& hdlist);

int main() {
	//HELLO
	//Read command file name and open file
	string commandfilename;
	ifstream commandfile;
	cout << "Enter Command File Name" << endl;
	cin >> commandfilename;
	commandfile.open(commandfilename.c_str());

	//If execution error, exit the program
	if(!commandfile.is_open()){
		cout << "Couldn't open" << endl;
		exit(EXIT_FAILURE);
	}

	//If not, real file names into a structure and close the file
	string cftemp;
	vector<string> vectcomfile;

	while(commandfile >> cftemp) {
		vectcomfile.push_back(cftemp);
	}

	commandfile.close();

	//Write the output of the command file to an output file
    vector<string> vectoutfile;
	int outfilenumber = RunComFileOps(vectcomfile, vectoutfile);

	//Read outpur file name into a string
	stringstream outfiless;
	outfiless << "output_" << outfilenumber << ".txt";
	string outfilename = outfiless.str();

	//Open data file
	ofstream outfile;
	outfile.open(outfilename.c_str());

	//If execution error, exit the program
	if(!outfile.is_open()){
		cout << "Couldn't open" << endl;
		exit(EXIT_FAILURE);
	}

	//Input items of data file into new list and close data file

	for (int index = 0; index < vectoutfile.size(); index++) {
		outfile << vectoutfile[index] << endl ;
	}

}

int RunComFileOps(vector<string> vectcomfile, vector<string>& vectoutfile) {
	do {
		int filenumber;
		bool ordered;
		int comfileindex = 0;
		NodePtr hdlist = new Node;
		hdlist = NULL;

		if((vectcomfile[comfileindex] == 'r') || (vectcomfile[comfileindex] == 'w') || (vectcomfile[comfileindex] == 'i') || (vectcomfile[comfileindex] = 'd')) {
			if(vectcomfile[comfileindex] == 'r') {
				int filenumber = vectcomfile[comfileindex++];
				ReadFile(filenumber, hdlist);
			}
			else if(vectcomfile[comfileindex] == 'i') {
				//InsertElement();
				;
			}
			else {

				//DeleteElement();
				;
			}
			comfileindex += 2;
		}
		else {
			if(vectcomfile[comfileindex] == 's') {
				//SortFile();
				;
			}
			else if(vectcomfile[comfileindex] == 'w') {
				WriteFile(vectoutfile, hdlist);
			}
			else if(vectcomfile[comfileindex] == 'e') {
				//FindNoOfEntries();
				;
		    }
			else if(vectcomfile[comfileindex] == 'm')
				//FindMinEntry();
				;
		    }
			else {
				//SmoothList();
				;
			}
			comfileindex++;
		}
	} while(comfileindex < vectcomfile.size());
	return filenumber;
}

void ReadFile(int& filenumber, NodePtr& hdlist) {
	//Read data file name into a string
	stringstream datafiless;
	datafiless << "data_" << filenumber << ".txt";
	string datafilename = datafiless.str();

	//Open data file
	ifstream datafile;
	datafile.open(datafilename.c_str());

	//If execution error, exit the program
	if(!datafile.is_open()){
		cout << "Couldn't open" << endl;
		exit(EXIT_FAILURE);
	}

	//Input items of data file into new list and close data file
	Item temp;

	while(datafile >> temp) {
		AddToList(temp,hdlist);
	}

	datafile.close();
}

void WriteFile(vector<string>& vectoutfile, NodePtr hdlist) {
	while (hdlist != NULL) {
		stringstream tempss;
        outss << GetFromList(hdlist) << endl;
        string out = outss.str();
		vectoutfile.push_back(out);
	}
}

Item GetFromList(NodePtr& hdlist) {
	Item outdata;
	NodePtr tempPtr;
	tempPtr = hdlist;
	outdata = tempPtr->data;
	hdlist = tempPtr->next;
	delete tempPtr;
	return outdata;
}
void AddToList(Item number, NodePtr& hdlist) {
	NodePtr newnode = new Node;
	newnode->data = number;
	newnode->next = hdlist;
	hdlist = newnode;
	"cout << hdlist->data << endl;"
}




