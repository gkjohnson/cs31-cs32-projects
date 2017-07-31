	// Return true if any of the array elements is negative, false
	  // otherwise.
	bool anyNegative(const double a[], int n)
	{
		if(n<=0){
			return false;
		}
		if(a[n-1]<0){
			return true;
		}
	    return anyNegative(a,n-1);  // This is not always correct.
	}

	  // Return the number of negative elements in the array.
	int countNegatives(const double a[], int n)
	{
		if(n<=0){
			return 0;
		}
		if(a[n-1]<0){
			return countNegatives(a,n-1)+1;
		}
	    return countNegatives(a,n-1);
	}

	  // Return the subscript of the first negative element in the array.
	  // If no element is negative, return -1.
	int firstNegative(const double a[], int n)
	{
		if(n<=0){
			return -1;
		}
		if(a[0]<0){
			return 0;
		}
		int next=firstNegative(a+1,n-1);

		if(next==-1){
			return -1;
		}else{
			return next+1;
		}
	}

	  // Return the subscript of the largest element in the array.  If
	  // more than one element has the same largest value, return the
	  // smallest index of such an element.  If the array is empty,
	  // return -1.
	int indexOfMax(const double a[], int n)
	{
		if(n<=0){
			return -1;
		}
		int max_index=indexOfMax(a,n-1);

		if(max_index<0||a[max_index]<a[n-1]){
			max_index=n-1;
		}
		
	    return max_index;
	}

	  // If all n2 elements of a2 appear in the n1 element array a1, in
	  // the same order (though not necessarily consecutively), then
	  // return true; otherwise (i.e., if the array a1 does not include
	  // a2 as a not-necessarily-contiguous subsequence), return false.
	  // (Of course, if a2 is empty (i.e., n2 is 0), return true.)
	  // For example, if a1 is the 7 element array
	  //    10 50 40 20 50 40 30
	  // then the function should return true if a2 is
	  //    50 20 30
	  // or
	  //    50 40 40
	  // and it should return false if a2 is
	  //    50 30 20
	  // or
	  //    10 20 20
	bool includes(const double a1[], int n1, const double a2[], int n2)
	{
		if(n2==0){
			return true;
		}else if(n1==0){
			return false;
		}
		
		if(a1[0]!=a2[0]){		
			return includes(a1+1,n1-1,a2,n2);
		}else if(a1[0]==a2[0]){
			return includes(a1+1,n1-1,a2+1,n2-1);
		}
	}

