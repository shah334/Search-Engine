
struct URLRecord {
  char * _url;          // URL of the document.
  char * _description;  // First 200 chars of the document without tags
};

struct URLRecordList {
  URLRecord * _urlRecord;  // Pointer to the URL Record
  URLRecordList * _next;   // Pointer to the next URL Record in the list
};

/**

	k++;
	  string ind = "";
	  string url = "";
	  string desc;
	  int index;
	  if(k%3==1){
		  
		  for(int i=0;i<st.length();i++){
			  if(st[i]!=' '){
				  ind = ind + st[i];
		  		}else{
			  for(int j=i+1;j<st.length();j++){
				  url = url + st[j];
			  }
		  }
	  	}
	  	UR = url.c_str();
	  	index = atoi(ind.c_str());

	  } 
	  if(k%3==2){
		  desc = st;
		  d=strdup(st.c_str());
	  } 
	  if(k%3==0)
	  {//store if blank
		  if(k!=0){
			  if(index==213){
				  printf("%s\n",UR);
			  }
		 	 _urlArray[in]._url = strdup(UR);
		 	 	if(index==213){
				  printf("%s\n",UR);
			  }
		 	// printf("%s\n",_urlArray[in]._url);
		 	 UR = "";
		 	 _urlArray[in]._description = strdup(d);
		 	 d = "";
		 	// printf("%s\n",_urlArray[in]._description);
		 	 in++;
		  }
	  }

*/