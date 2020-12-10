//============================================================================
// Name        : VectorSorting.cpp
// Author      : Katie Stapleton
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Vector Sorting Algorithms
//============================================================================

//MAJOR ISSUE: problem with loading CSV file. attempted, but no solution found
// menu will run, but bids are not able to load to fully test the algorithms
 /* menu choice 1:
 * Loading CSV file eBid_Monthly_Sales_Dec_2016.csv
 * terminate called after throwing an instance of 'csv::Error'
 * what():  CSVparser : Failed to open eBid_Monthly_Sales_Dec_2016.csv
 * this may be the issues with Choice 3 also.
 */


#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information using console (std::in)
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            bids.push_back(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

// FIXME (2a): Implement the quick sort logic over bid.title

/**
 * Partition the vector of bids into two parts, low and high
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */

// quick sort partitioning. source: Zybooks.com
// split input into 2 unsorted parts, low and high
int partition(vector<Bid>& bids, int begin, int end) {
	 //define variables.
 	 //variable type issue: use Bid for pivot/temp instead of int
  	int i = begin;
  	int k = end;
    bool done = false;
    cout << "partition has started" << endl;

    /* define midpoint and pivot for quick sort
	  * midpoint = lowIndex + ((highIndex - lowIndex)/2)
	  */
    int midpoint = i + (i + k)/2;
    Bid pivot = bids.at(midpoint);

    // loop perform quick sort on bid.title until finished
    while(!done) {
    	cout << "while done has started" << endl;
    	  // increment while bid i index is less than pivot. compare titles
       while (bids.at(i).title < pivot.title) {
    	   ++i;
    	   cout << "while at i" << i << endl;

       }
       // decrement while bid k index is greater than pivot. compare titles
       while (bids.at(k).title > pivot.title) {
    	   --k;
    	   cout << "while at k" << k << endl;
       }
       // if 0-1 elements remaining, done = true
       if (i>=k) {
    	   done = true;
    	   return k;
    	   cout << "if at i" << i << endl;
       }
       //exchange bid position and update index
       //formatting issue resolved: temp must be Bid type
       else {
    	   Bid temp = bids.at(i);
    	   bids.at(i) = bids.at(k);
    	   bids.at(k) = temp;
    	   ++i;
    	   --k;
    	   cout << "else k and i swap: " << k << " and " << i << endl;
       }
    }

    //return k when all numbers are partitioned
    return k;
    cout << "return k" << endl;
}

/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */

// perform quick sort. source: Zybooks.com
// split input into 2 unsorted parts, low and high
void quickSort(vector<Bid>& bids, int begin, int end) {
	//define variable for location of last element in low partition
     int split = 0;
     cout << "starting quicksort" << endl;

	// checks if partition is already sorted (0 to 1 elements)
    if (begin >= end) {
	    return;
  	}
	// partitions data within the vector.
    split = partition(bids, begin, end);
    cout << "first partition done" << endl << endl;
	// sorts the low partition and high partitions recursively
    quickSort(bids, begin, split);
    cout << "QS 1 COMPLETED" << endl << endl;
    //ISSUE: BELOW CAUSES INDEFINITE LOOP. fine prior. unable to pinpoint error.
   quickSort(bids, split + 1, end);
   cout << "QS 2 COMPLETED" << endl << endl;
	return;
}

// FIXME (1a): Implement the selection sort logic over bid.title

/**
 * Perform a selection sort on bid title
 * Average performance: O(n^2))
 * Worst case performance O(n^2))
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
// Selection sorting. no separate partitioning needed. Source: ZYBooks
void selectionSort(vector<Bid>& bids) {
   //define variables
	 // issue: temp is Bid, not int
	  int i = 0;
	  int k = 0;
	  int indexSml = i;
      Bid temp;

   // loop through all bids
	  for (i=0; i < bids.size()-1; i++) {
       // find index # of the smallest remaining element
 		   indexSml = i;
 		   for (k = i + 1; k < bids.size(); k++) {
 			    //compare bid titles
 			     if (bids.at(k).title < bids.at(indexSml).title) {
 			    	    indexSml = k;
 			     }
 		   }

  		  // swaps bid and bid with smallest element
  	    temp = bids.at(i);
  	    bids.at(i) = bids.at(indexSml);
  	    bids.at(indexSml) = temp;
  	 }

}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Selection Sort All Bids" << endl;
        cout << "  4. Quick Sort All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            // used in case 3 and 4. if changes occur, make sure to review case 3 and 4 also
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            // Loop and display the bids read
            for (int i = 0; i < bids.size(); ++i) {
                displayBid(bids[i]);
            }
            cout << endl;

            break;

        // FIXME (1b): DONE Invoke the selection sort and report timing results
        case 3:
           	// Initialize a timer variable before loading bids
           	ticks = clock();

           	//method needed to execute the selection sort
           	// quicksort (vector, start , end=vector length-1)
           	selectionSort(bids);

            // display total of bids stored
           	cout << bids.size() << " bids stored" << endl;

        	   //calculate and display timing results. pulled from case 1
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

           	//end case with break
           	break;


        // FIXME (2b): DONE Invoke the quick sort and report timing results
        case 4:
        	    // Initialize a timer variable before loading bids
        	    ticks = clock();

           	//method used to execute the quick sort
           	quickSort(bids, 0, bids.size()-1);

           	//display total bids sorted
           	cout << bids.size() << " bids sorted" << endl;

           	//calculate and display timing results. pulled from case 1
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

           	//end case with break
           	break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
