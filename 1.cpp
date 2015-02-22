#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <math.h>
#include <sstream>

using namespace std;

typedef int Item;

struct Node {
	Item data;
	Node* next;
};

typedef Node* NodePtr;

string RunComFileOps(const vector<string>& vectcomfile, vector<string>& vectoutfile);
void SmoothList(NodePtr hdlist);
void DeleteElement(Item number, NodePtr& hdlist) ;
void FindMinEntry(vector<string>& vectoutfile, NodePtr hdlist);
void FindNoOfEntries(vector<string>& vectoutfile, NodePtr hdlist);
void ReadFile(string& filenumber, NodePtr& hdlist);
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
	string outfilenumber = RunComFileOps(vectcomfile, vectoutfile);

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

string RunComFileOps(const vector<string>& vectcomfile, vector<string>& vectoutfile) {
        string filenumber;
		bool ordered;
		int comfileindex = 0;
		NodePtr hdlist = new Node;
		hdlist = NULL;
        do {
            cout << vectcomfile[comfileindex] << "\t" << comfileindex << endl;
			if(vectcomfile[comfileindex] == "r" or vectcomfile[comfileindex] == "i" or vectcomfile[comfileindex] == "d") {
				if(vectcomfile[comfileindex] == "r") {
					filenumber = vectcomfile[comfileindex + 1];
					ReadFile(filenumber, hdlist);
				}
				else if(vectcomfile[comfileindex] == "i") {
                    Item numtoinsert = atoi(vectcomfile[comfileindex + 1].c_str());
					//InsertElement();
					;
				}
				else {
					Item numtodelete = atoi(vectcomfile[comfileindex + 1].c_str());
					DeleteElement(numtodelete, hdlist);
				}
				comfileindex += 2;
			}
			else {
				if(vectcomfile[comfileindex] == "s") {
					//SortFile();
					;
				}
				else if(vectcomfile[comfileindex] == "w") {
					WriteFile(vectoutfile, hdlist);
				}
				else if(vectcomfile[comfileindex] == "e") {
					FindNoOfEntries(vectoutfile, hdlist);
				}
				else if(vectcomfile[comfileindex] == "m") {
					FindMinEntry(vectoutfile, hdlist);
				}
				else {
					SmoothList(hdlist);
				}
				comfileindex++;
			}
		} while(comfileindex < vectcomfile.size());
	return filenumber;
}

void SmoothList(NodePtr hdlist) {
	while(!insertion) {
		bool insertion = false;
		NodePtr newPtr, frontPtr, backPtr;
		backPtr = hdlist;
		frontPtr = hdlist->next;
		Item tempmean;
		while(frontPtr != NULL) {
			if(abs(backPtr->data - frontPtr->data) > 5) {
				tempmean = (backPtr->data + frontPtr->data / 2);
				newPtr->data = round(tempmean);
				newPtr->next = frontPtr;
				backPtr->next = newPtr;
				insertion = true;
			}
			backPtr = frontPtr;
			frontPtr = frontPtr->next;
		}
	}
}

void DeleteElement(Item number, NodePtr& hdlist) {
	bool found = false;
	NodePtr oldPtr;
	if(hdlist == NULL) {
		return;
	}
	else if(hdlist->data == number) {
		oldPtr = hdlist;
		hdlist = hdlist->next;
		delete oldPtr;
	}
	else {
        NodePtr searchPtr = hdlist;
		NodePtr lastPtr = hdlist;
		while((searchPtr != NULL) && (!found)) {
			if(searchPtr->data == number) {
				found = true;
				lastPtr->next = searchPtr->next;
				delete searchPtr;
				return;
			}
			else {
				lastPtr = searchPtr;
				searchPtr = searchPtr->next;
			}
		}
	}
}

void FindMinEntry(vector<string>& vectoutfile, NodePtr hdlist) {
    Item minentry;
	if(hdlist == NULL) {
        minentry = NULL;
	}
	else {
        minentry = hdlist->data;
	}
	while (hdlist != NULL) {
		if(hdlist->data < minentry) {
            minentry = hdlist->data;
		}
		hdlist = hdlist->next;
	}
	stringstream outss;
	if(minentry == NULL) {
        outss << "No entries, Therefore no minimum element" << endl;
	}
    else {
        outss << "Minimum value: " << minentry << endl;
    }
    string out = outss.str();
	vectoutfile.push_back(out);
}

void FindNoOfEntries(vector<string>& vectoutfile, NodePtr hdlist) {
	int noofentries = 0;
	while (hdlist != NULL) {
		noofentries++;
		hdlist = hdlist->next;
	}
	stringstream outss;
    outss << "Number of elements in the list: " << noofentries << endl;
    string out = outss.str();
	vectoutfile.push_back(out);
}


void ReadFile(string& filenumber, NodePtr& hdlist) {
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

    Item temp;

	//Input items of data file into new list and close data file
	while(datafile >> temp) {
		AddToList(temp,hdlist);
	}

	datafile.close();
}

void WriteFile(vector<string>& vectoutfile, NodePtr hdlist) {
	while (hdlist != NULL) {
		stringstream outss;
        outss << GetFromList(hdlist) << endl;
        string out = outss.str();
		vectoutfile.push_back(out);
	}
}

Item GetFromList(NodePtr& hdlist) {
	int outdata;
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
}







