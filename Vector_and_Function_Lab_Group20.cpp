
/** This is the Vector and Function lab  */


#include <iostream>
#include <vector>

using namespace std;

bool binarySearch(vector<int> vect, int value);					/* implement binary search fucntion*/
bool binarySearchRecursive(vector<int> vect, int start, int end, int value);  /*  implement binary search recusive function*/
void sort(vector<int> &vect);									/* sort the vector elements with descending order*/

bool binarySearch(vector<int> vect, int value) {
	
	return binarySearchRecursive(vect, 0, vect.size(), value);   /* call implement binary search recusive function */
}


bool binarySearchRecursive(vector<int> vect, int start, int end, int value) {
	int mid = (start + end) / 2;		/*  find the halfway element at the vector*/

	if (vect[mid] == value) {			/*  if find the search value , return true */
		cout << "The value is found, which is "<<vect[mid] <<"  The position is "<<mid<< endl;
		return true;
	}

	if (mid == start) {					/* if cannot find the value at last, return false */
		cout << "Cannot find the value, search failed" << endl;
		return false;
	}

	/* if value larger than vect[mid], 
	   the value should be the larger part before the vect[mid], 
	   else shoule be the smaller part after vect[mid] */
	if (value > vect[mid])				
		return binarySearchRecursive(vect, start, mid-1, value);
	else
		return binarySearchRecursive(vect, mid+1, end, value);


	return false;
}

void sort(vector<int> &vect) {   /* bubble sort to make sure vector is in descending order*/
	for (int i = 0; i < vect.size(); i++)
		for (int j = 0; j < vect.size(); j++) {
			if (vect[i] > vect[j])
				swap(vect[i], vect[j]);
		}
}

int main() {
	vector<int> vect;
	int value;

	

	while (true) {
		cout << "Please input the number you want , input -1 to exit this program" << endl;
		cin >> value;
		if (value == -1)
			break;
		vect.push_back(value);
	}

	sort(vect);

	for (int i = 0; i < vect.size(); i++)
		cout << vect[i] << " ";

	cout << endl;

	while (true) {
		cout << "input the number you want to search: ";
		cin >> value;
		bool returnvalue = binarySearch(vect, value);
		cout << "The function return value is : " << returnvalue << "  0 means false, 1 means true "<< endl;
	}

	return 0;
}
