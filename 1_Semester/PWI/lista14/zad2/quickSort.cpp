#include <vector>
#include <algorithm>
#include <chrono>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    if (argc<=1) {
		cout << "Program nalezy wywołać w następujący sposób:\n";
		cout << "sortuj n, gdzie n jest rozmiarem listy do posortowania. \n";
 		cout << "np. wywołanie sortuj 100 wypisze czas sortowania dla listy rozmiaru 100.\n"; 	
    		return 1;
    }

    int size = atol(argv[1]);

    vector<int> v(size);
    generate(v.begin(), v.end(), std::rand);
   
    sort(v.begin(), v.end());


    return 0;
}

