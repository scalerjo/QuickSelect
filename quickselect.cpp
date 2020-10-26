/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        :
 * Pledge        :
 * Date          :
 * Description   : Implements the quickselect algorithm found on page 160 in
 *                 Algorithms, 3e by Anany Levitin.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;



size_t lomuto_partition(int array[], size_t left, size_t right) {
    // TODO
    // DO NOT change the function header in any way.

    int pivot = array[left];
    int SwapIndex = left;
    for (unsigned int i = left + 1; i <= right; i++){
        if (array[i] < pivot){
            SwapIndex++;
            swap(array[i], array[SwapIndex]);
        }
    }
    swap(array[left], array[SwapIndex]);
    return SwapIndex;
}

int quick_select(int array[], size_t left, size_t right, size_t k) {
    // TODO
    // DO NOT change the function header in any way.

    //Pivot Index
    unsigned int p = lomuto_partition(array, left, right);
    
    if (p-left == k-1){
        return array[p];
    }
    else if (p-left > k-1){
        return quick_select(array, left, p-1, k);
    }
    else {
        return quick_select(array, p+1, right, k-p+left-1);
    }
}

int quick_select(int array[], const size_t length, size_t k) {
    return quick_select(array, 0, length - 1, k);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <k>" << endl;
        return 1;
    }

    int k;
    istringstream iss;
    iss.str(argv[1]);
    if ( !(iss >> k) || k <= 0 ) {
        cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    iss.clear();
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    int num_values = values.size();
    if (num_values == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    // TODO - error checking k against the size of the input
    int size = values.size();
    if (k > size){
        if (size == 1){
            cerr << "Error: Cannot find smallest element " << k << " with only " << size << " value." << endl;
            return 1;
        }
        else {
            cerr << "Error: Cannot find smallest element " << k << " with only " << size << " values." << endl;
            return 1;
        }
    }
    int kth_smallest = quick_select(&values[0], size, k);
    cout << "Smallest element " << k << ": " << kth_smallest << endl;
    // TODO - call the quick_select function and display the result

    return 0;
}
