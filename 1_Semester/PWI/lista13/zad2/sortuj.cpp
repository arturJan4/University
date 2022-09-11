#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>

using namespace std;

// bubble sort based on:
// https://pl.wikibooks.org/wiki/Kody_%C5%BAr%C3%B3d%C5%82owe/Sortowanie_b%C4%85belkowe
int bubble(const vector<int>&v1) {
	vector <int> v= v1;

        bool swapped; // Czy zamieniono w ostatnim obrocie?

	int n = v.size();	
        do {
            swapped = false;
            for (int i = 0; i < n - 1; ++i) {
                if (v[i] > v[i + 1]) {  
                    swap(v[i], v[i + 1]);
                    swapped = true;
                }
            }
        } while (swapped);

	return v[0];

}

int main(int argc, char *argv[]) {

    if (argc<=1) {
		cout << "Program nalezy wywołać w następujący sposób:\n";
		cout << "sortuj n, gdzie n jest rozmiarem listy do posortowania. \n";
 		cout << "np. wywołanie sortuj 100 wypisze czas sortowania dla listy rozmiaru 100.\n"; 	
    		return 1;
    }

    int size = atol(argv[1]);

    cout << size << " ";

    vector<int> v(size);
    generate(v.begin(), v.end(), std::rand);
    
    auto t1 = chrono::high_resolution_clock::now();
    bubble(v);
    auto t2 = chrono::high_resolution_clock::now();
    chrono::duration<double,milli> b_elapsed = t2 - t1; 
   
    t1 = chrono::high_resolution_clock::now();
    sort(v.begin(), v.end());
    t2 = chrono::high_resolution_clock::now();
    chrono::duration<double,milli> q_elapsed = t2 - t1;

    cout << b_elapsed.count() << " " << q_elapsed.count() << endl;

    return 0;
}
