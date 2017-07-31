#include <iostream>
#include <algorithm>
#include <numeric>  // for std::accumulate
#include <vector>
#include <string>
#include <cstdlib>  // for std::rand
#include <cassert>

using namespace std;

//========================================================================
//  Set this to false to skip the insertion sort tests; you'd do this if
//  you're sorting so many items that insertion_sort would take more time
//  than you're willing to wait.

const bool TEST_INSERTION_SORT = true;
//========================================================================

//========================================================================
// TimerType            - a type to hold a timer reading
// TimerType getTimer() - get the current timer reading
// double interval(TimerType start, TimerType end) - milliseconds between
//                                                   two readings
//========================================================================

#ifdef _MSC_VER  // If we're compiling for Windows

#include <windows.h>

typedef LARGE_INTEGER TimerType;
inline TimerType getTimer()
{
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return t;
}

inline double interval(TimerType start, TimerType end)
{
    LARGE_INTEGER ticksPerSecond;
    QueryPerformanceFrequency(&ticksPerSecond);
    return (1000.0 * (end.QuadPart - start.QuadPart)) / ticksPerSecond.QuadPart;
}

#else // If we're not compiling for Windows, use Standard C

#include <ctime>

typedef clock_t TimerType;
inline TimerType getTimer() { return clock(); }
inline double interval(TimerType start, TimerType end)
{
    return (1000.0 * (end - start)) / CLOCKS_PER_SEC;
}

#endif  // ifdef _MSC_VER

//========================================================================

// Here's a class that is not cheap to copy -- the vector holds a pointer
// to dynamic memory, so vector's assignment operator and copy constructor
// have to allocate storage.

// We'll simplify writing our timing tests by declaring everything public
// in this class.  (We wouldn't make data public in a class intended for
// wider use.)

typedef int IdType;

struct Store
{
    IdType id;
    double total;
    vector<double> monthlySales;
    Store(IdType i) : id(i)
    {
          // create twelve random sales figures (from 20000 to 60000)
        for (size_t k = 0; k < 12; k++)
            monthlySales.push_back(20000 + rand() % 40000);
          // (accumulate computes 0.0 + monthlySales[0] + monthlySales[1] + ...)
        total = accumulate(monthlySales.begin(), monthlySales.end(), 0.0);
    }
};

inline
bool compareStore(const Store& lhs, const Store& rhs)
{
      // The Store with the higher total should come first.  If they have
      // the same total, then the Store with the smaller id number should
      // come first.  Return true iff lhs should come first.  Notice that
      // this means that a false return means EITHER that rhs should come
      // first, or there's a tie, so we don't care which comes first,

    if (lhs.total > rhs.total)
        return true;
    if (lhs.total < rhs.total)
        return false;
    return lhs.id < rhs.id;
}

inline
bool compareStorePtr(const Store* lhs, const Store* rhs)
{
    // DONE: You implement this.  Using the same criteria as compareStore,
    //       compare two Stores POINTED TO by lhs and rhs.  Think about
    //       how you can do it in one line by calling compareStore.

	return compareStore(*lhs,*rhs);
}

bool isSorted(const vector<Store>& s)
{
      // Return true iff the vector is sorted according to the ordering
      // relationship compareStore

    for (size_t k = 1; k < s.size(); k++)
    {
        if (compareStore(s[k],s[k-1]))
            return false;
    }
    return true;
}

void insertion_sort(vector<Store>& s, bool comp(const Store&, const Store&))
{
    // DONE: Using the insertion sort algorithm (pp. 463-465), sort s
    //       according to the ordering relationship passed in as the
    //       parameter comp.

    // Just to show you how to use the second parameter, we'll write code
    // that sorts only a vector of 2 elements.  (This is *not* the
    // insertion sort algorithm.)

    // Note that if comp(x,y) is true, it means x must end up before y in the
    // final ordering.
    if (s.size() == 2  &&  comp(s[1], s[0]))
        swap(s[0], s[1]);


	//MY CODE
	for (int unsorted = 1; unsorted < s.size(); ++ unsorted)
	{
		Store nextItem = s[unsorted];
		int loc = unsorted;
		for (; (loc>0) && !comp(s[loc-1], nextItem); --loc)
		{
			s[loc]=s[loc-1];
		}
		s[loc] = nextItem;
	}
}

  // Report the results of a timing test

void report(string caption, double t, const vector<Store>& s)
{
    cout << t << " milliseconds; " << caption
             << "; first few stores are\n  ";
    size_t n = s.size();
    if (n > 5)
        n = 5;
    for (size_t k = 0; k < n; k++)
        cout << " (" << s[k].id << ", " << s[k].total << ")";
    cout << endl;
}

int main()
{
    size_t nstores;
    cout << "Enter number of stores to sort: ";
    cin >> nstores;
    if ( !cin  ||  nstores <= 0)
    {
        cout << "You must enter a positive number.  Goodbye." << endl;
        return 1;
    }

      // Create a random ordering of id numbers 0 through nstores-1
    vector<IdType> ids;
    for (size_t j = 0; j < nstores; j++)
        ids.push_back(IdType(j));
    random_shuffle(ids.begin(), ids.end());  // from <algorithm>
    
      // Create a bunch of Stores
    vector<Store> unorderedStores;
    for (size_t k = 0; k < ids.size(); k++)
        unorderedStores.push_back(Store(ids[k]));

    TimerType startSort;
    TimerType endSort;

      // Sort the Stores using the STL sort algorithm.  It uses a variant
      // of quicksort called introsort.

    vector<Store> stores(unorderedStores);
    startSort = getTimer();
    sort(stores.begin(), stores.end(), compareStore);
    endSort = getTimer();
    report("STL sort", interval(startSort, endSort), stores);
    assert(isSorted(stores));

      // Sort the already sorted array using the STL sort.  This should be
      // fast.

    startSort = getTimer();
    sort(stores.begin(), stores.end(), compareStore);
    endSort = getTimer();
    report("STL sort if already sorted", interval(startSort, endSort), stores);
    assert(isSorted(stores));

    if (TEST_INSERTION_SORT)
    {
          // Sort the original unsorted array using insertion sort.  This
          // should be really slow.  If you have to wait more than a minute,
          // try rerunning the program with a smaller number of Stores.
    
        stores = unorderedStores;
        startSort = getTimer();
        insertion_sort(stores, compareStore);
        endSort = getTimer();
        report("insertion sort if not already sorted",
                                         interval(startSort, endSort), stores);
        assert(isSorted(stores));
    
          // Sort the already sorted array using insertion sort.  This should
          // be fast.
    
        startSort = getTimer();
        insertion_sort(stores, compareStore);
        endSort = getTimer();
        report("insertion sort if already sorted",
                                         interval(startSort, endSort), stores);
        assert(isSorted(stores));
    }

      // Since Stores are expensive to copy, and since the STL's sort copies
      // Stores O(N log N) times, let's sort POINTERS to the Stores, then
      // make one final pass to rearrange the Stores according to the
      // reordered pointers.  We'll write some code; you write the rest.

      // Set stores to the original unsorted sequence
    stores = unorderedStores;

      // Start the timing
    startSort = getTimer();

      // Create a auxiliary copy of stores, to faciliate the later reordering.
      // We create it in a local scope so that we also account for the
      // destruction time.
    {
		vector<Store> auxStores(stores);

      // DONE:  Create a vector of Store pointers, and set each pointer
      //        to point to the corresponding Store in auxStores.
		vector<Store*> storesPtr;
		storesPtr.reserve(auxStores.size());
		for(int i=0;i<auxStores.size();i++)
		{
			storesPtr.push_back(&auxStores[i]);
			assert(storesPtr[i]==&auxStores[i]);
		}


      // DONE:  Sort the vector of pointers using the STL sort algorithm
      //        with compareStorePtr as the ordering relationship.

		sort(storesPtr.begin(), storesPtr.end(), compareStorePtr);
		
      // DONE:  Using the now-sorted vector of pointers, replace each Store
      //        in stores with the Stores from auxStores in the correct order.

		for(int i=0; i<stores.size();i++){
			stores[i]=*storesPtr[i];
		}
    } // auxStores will be destroyed here

      // End the timing, report, and verify the sort worked
    endSort = getTimer();
    report("STL sort of pointers", interval(startSort, endSort), stores);
    assert(isSorted(stores));
}