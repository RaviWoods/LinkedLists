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

void ReadFile(int& filenumber, NodePtr& hdlist);
void WriteFile(vector<int>& vectoutfile, NodePtr hdlist);
Item GetFromList(NodePtr& hdlist);
void AddToList(Item number, NodePtr& hdlist);

int main() {
	int filenumber = 1;
	vector<int> vectoutfile;
	NodePtr hdlist = new Node;
	hdlist = NULL;
	ReadFile(filenumber, hdlist);
	WriteFile(vectoutfile, hdlist);
	for(int i = 0; i < vectoutfile.size(); i++) {
		cout << vectoutfile[i] << endl;
	}
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

void WriteFile(vector<int>& vectoutfile, NodePtr hdlist) {
	while (hdlist != NULL) {
		vectoutfile.push_back(GetFromList(hdlist));
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
	//cout << hdlist->data << endl;
}
