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

string RunComFileOps(const vector<string>& vectcomfile, vector<string>& vectoutfile);

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
	string x = "d";
	NodePtr hdlist = new Node;
	hdlist = NULL;
    if(x == "r" or  "w" or "i" or "d") {
      cout << "YES";
	}
    return filenumber;
}





