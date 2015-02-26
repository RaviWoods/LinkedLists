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

int RunComFileOps(const vector<string>& vectcomfile, vector<string>& vectoutfile, bool& filenumgiven);
void ReadFile(int& filenumber, NodePtr& hdlist, bool& filenumgiven);
void InsertElement(Item number, NodePtr& hdlist, bool ordered);
void DeleteElement(Item number, NodePtr& hdlist) ;
void SortList(NodePtr& hdlist, bool& ordered);
void WriteFile(vector<string>& vectoutfile, NodePtr hdlist);
void FindNoOfEntries(vector<string>& vectoutfile, NodePtr hdlist);
void FindMinEntry(vector<string>& vectoutfile, NodePtr hdlist);
void SmoothList(NodePtr hdlist);
Item GetFromList(NodePtr& hdlist);
void AddToHeadofList(Item number, NodePtr& hdlist);


int main(int argc, char *argv[]) {
	//Read command file name and open file
	string commandfilename = argv[1];
	ifstream commandfile;
	commandfile.open(commandfilename.c_str());

	//If execution error, exit the program
	if(!commandfile.is_open()){
		cout << "Couldn't open" << endl;
		exit(EXIT_FAILURE);
	}

	//If not, read command file lines into a structure and close the file
	string cftemp;
	vector<string> vectcomfile;

	while(commandfile >> cftemp) {
		vectcomfile.push_back(cftemp);
	}

	commandfile.close();

	//Write the output of the command file to an output file
    	vector<string> vectoutfile;
	bool filenumgiven;
	int outfilenumber = RunComFileOps(vectcomfile, vectoutfile, filenumgiven);

	//If no output file number given, end the program at this point.
	if(filenumgiven = false) {
		return 0;
	}

	//Read output file name into a string
	stringstream outfiless;
	outfiless << "output_" << outfilenumber << ".txt";
	string outfilename = outfiless.str();

	//Open output file
	ofstream outfile;
	outfile.open(outfilename.c_str());

	//If execution error, exit the program
	if(!outfile.is_open()){
		cout << "Couldn't open" << endl;
		exit(EXIT_FAILURE);
	}

	//Input items of output vector into output file and close output file

	for (int index = 0; index < vectoutfile.size(); index++) {
		outfile << vectoutfile[index] << endl ;
	}
	
	outfile.close();
	return 0;
}

int RunComFileOps(const vector<string>& vectcomfile, vector<string>& vectoutfile, bool& filenumgiven) {
        int filenumber = 0;
	filenumgiven = false;
	bool ordered = false;
	int comfileindex = 0;
	NodePtr hdlist = new Node;
	hdlist = NULL;
        while(comfileindex < vectcomfile.size()) {
			//If operation takes a number in input, input number as a parameter, and increase index by 2.
			if(vectcomfile[comfileindex] == "r" or vectcomfile[comfileindex] == "i" or vectcomfile[comfileindex] == "d") {
				if(vectcomfile[comfileindex] == "r") {
					filenumber = atoi(vectcomfile[comfileindex + 1].c_str());
					ReadFile(filenumber, hdlist, filenumgiven);
					filenumgiven = true;
				}
				else if(vectcomfile[comfileindex] == "i") {
                    			Item numtoinsert = atoi(vectcomfile[comfileindex + 1].c_str());
					InsertElement(numtoinsert, hdlist, ordered);
				}
				else {
					Item numtodelete = atoi(vectcomfile[comfileindex + 1].c_str());
					DeleteElement(numtodelete, hdlist);
				}
				comfileindex += 2;
			}
			//If operation doesn't take a number in input, execute function and increase index by 1.
			else {
				if(vectcomfile[comfileindex] == "s") {
					SortList(hdlist, ordered);
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
		}
	return filenumber;
}

void ReadFile(int& filenumber, NodePtr& hdlist, bool& filenumgiven) {
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

	//Input items of data file into list and close data file
    	Item temp;

	
	while(datafile >> temp) {
		AddToHeadofList(temp,hdlist);
	}

	datafile.close();
	filenumgiven = false;
}

void InsertElement(Item number, NodePtr& hdlist, bool ordered) {
	//If list isn't ordered, add element to head of list
	if(!ordered) {
		AddToHeadofList(number, hdlist);
	}  
	else {
		bool found = false;
		NodePtr searchPtr, lastPtr, newPtr;

		newPtr = new Node;
		newPtr->data = number;
		newPtr->next = NULL;

		//If list is empty, insert element at end of list.
		if(hdlist == NULL) {
			hdlist = newPtr;
			return;
		}

		//If number to insert is less than the head of the list, insert element at head of list.
		else if(hdlist->data >= number) {
			AddToHeadofList(number, hdlist);
			delete newPtr;
			return;
		}
	
		//Else, go through list and insert number when list data greater than number.
		else {
			searchPtr = hdlist;
			lastPtr = hdlist;
			while((searchPtr != NULL) && (!found)) {
				if(searchPtr->data >= number) {
					found = true;
				}
				else {
					lastPtr = searchPtr;
					searchPtr = searchPtr->next;
				}
			}
			newPtr->next = searchPtr;
			lastPtr->next = newPtr;
		}

	}
}

void DeleteElement(Item number, NodePtr& hdlist) {
	bool found = false;
	NodePtr oldPtr;
	
	//If list is empty, do nothing
	if(hdlist == NULL) {
		return;
	}
	
	//If number to delete is the head of the list, exception case is needed.
	else if(hdlist->data == number) {
		oldPtr = hdlist;
		hdlist = hdlist->next;
		delete oldPtr;
	}

	//If neither case, search list and delete one element containing number to delete.
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

void SortList(NodePtr& hdlist, bool& ordered) {
	//If list is empty or has one element, do nothing
	if(hdlist == NULL || hdlist->next == NULL) {
		return;
	}
    	bool swapping = false;
	NodePtr trailPtr, testPtr1, testPtr2;
	trailPtr = hdlist;
	testPtr1 = hdlist;
	testPtr2 = hdlist->next;
	while(testPtr2 != NULL) {
		//If second element less than first element, swap elements.
		if(testPtr2->data < testPtr1->data) {
            	swapping = true;
			if(testPtr1 == hdlist) {
				hdlist->next = testPtr2->next;
				testPtr2->next = hdlist;
				hdlist = testPtr2;
			}
			else {
				trailPtr->next = testPtr2;
				testPtr1->next = testPtr2->next;
				testPtr2->next = testPtr1;
			}
		}
		//Move pointers along list sequentially. 
		trailPtr = testPtr1;
		testPtr1 = testPtr2;
		testPtr2 = testPtr2->next;
	}

	//If element swapping occurred, sort list again.
	if(swapping) {
        	SortList(hdlist, ordered);
		ordered = true;
        	return;
	}
	//If not, list is sorted, so exit function.
	else {
		ordered = true;
		return;
	}
}

void WriteFile(vector<string>& vectoutfile, NodePtr hdlist) {
	//Go through list, outputting data at each node
	while (hdlist != NULL) {
		stringstream outss;
        	outss << GetFromList(hdlist);
        	string out = outss.str();
		vectoutfile.push_back(out);
	}
}

void FindNoOfEntries(vector<string>& vectoutfile, NodePtr hdlist) {
	//Find entry number by travelling through list
	int noofentries = 0;
	while (hdlist != NULL) {
		noofentries++;
		hdlist = hdlist->next;
	}

	//Output entry number into output vector
	stringstream outss;
    	outss << "Number of elements in the list: " << noofentries;
    	string out = outss.str();
	vectoutfile.push_back(out);
}

void FindMinEntry(vector<string>& vectoutfile, NodePtr hdlist) {
    	Item minentry;
	bool emptylist = false;

	//If list is empty, note this
	if(hdlist == NULL) {
        	emptylist = true;
	}
	//If list is not empty, set first minimum value
	else {
        	minentry = hdlist->data;
	}

	//Go through list, updating minimum if needed 
	while (hdlist != NULL) {
		if(hdlist->data < minentry) {
            		minentry = hdlist->data;
		}
		hdlist = hdlist->next;
	}
	
	stringstream outss;
	// If list empty, output error
	if(emptylist == true) {
        	outss << "No entries, Therefore no minimum element";
	}
	// If list not empty, output minimum value.
    	else {
    	    outss << "Minimum value: " << minentry;
    	}
    	string out = outss.str();
	vectoutfile.push_back(out);
}

void SmoothList(NodePtr hdlist) {
	//If list is empty or has one element, return
	if(hdlist == NULL || hdlist->next == NULL) {
		return;
	}
    	bool insertion;
	insertion = false;
	NodePtr frontPtr, backPtr;
	backPtr = hdlist;
	frontPtr = hdlist->next;
	int tempsum;
	while(frontPtr != NULL) {
		//If absolute difference greater than 5, input new node between them (containing rounded mean)
		if(abs(backPtr->data - frontPtr->data) > 5) {	
			NodePtr newPtr = new Node;
			tempsum = (backPtr->data + frontPtr->data);
			if(tempsum%2 == 1) {
                		newPtr->data = (tempsum+1)/2;
			}
			else {
                		newPtr->data = tempsum/2;
			}
			newPtr->next = frontPtr;
			backPtr->next = newPtr;
			insertion = true;
		}
		
		//Move pointers along list sequentially. 
		backPtr = frontPtr;
		frontPtr = frontPtr->next;
		
	}

	//If element insertion occurred, smooth list again.
	if(insertion) {
		SmoothList(hdlist);
		return;
	}
	//If not, list is smoothed, so exit function.
	else {
		return;
	}
}


Item GetFromList(NodePtr& hdlist) {
	int outdata;
	NodePtr tempPtr = new Node;
	tempPtr = hdlist;
	outdata = tempPtr->data;
	hdlist = tempPtr->next;
	return outdata;
}

void AddToHeadofList(Item number, NodePtr& hdlist) {
	NodePtr newnode = new Node;
	newnode->data = number;
	newnode->next = hdlist;
	hdlist = newnode;
}






