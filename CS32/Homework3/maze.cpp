int countPaths(const int dist[][10], int ur, int uc)
	{
		//find the initial starting coordinate
		int sr=0;
		int sc=0;
		for(int i=0;i<10;i++){
			bool found=false;
			for(int j=0;j<10;j++){
				if(dist[i][j]==0){
					sr=i;
					sc=j;
					found=true;
					break;
				}
			}
			if(found){
				break;
			}
		}
	    //If (ur,uc) is the starting coordinate, then return 1.
		if(ur==sr&&uc==sc){
			return 1;
		}


	    //Start a running total at 0.
		int total=0;
        //For each of the four directions,
	        //If the location one step in that direction is on a shortest
		    //path from (ur,uc) to the starting coordinate,
		
		int minDist=dist[ur-1][uc];

		if(minDist>dist[ur+1][uc]){
			minDist=dist[ur+1][uc];
		}
		if(minDist>dist[ur][uc-1]){
			minDist=dist[ur][uc-1];
		}
		if(minDist>dist[ur][uc+1]){
			minDist=dist[ur][uc+1];
		}
		        //then call countPaths with that location as the upstream
				//coordinate, and add the value returned to the
				//running total.
		if(minDist==dist[ur-1][uc]){
			total+=countPaths(dist,ur-1,uc);
		}
		if(minDist==dist[ur+1][uc]){
			total+=countPaths(dist,ur+1,uc);
		}
		if(minDist==dist[ur][uc-1]){
			total+=countPaths(dist,ur,uc-1);
		}
		if(minDist==dist[ur][uc+1]){
			total+=countPaths(dist,ur,uc+1);
		}

	    //Return the running total.
		return total;
	}

