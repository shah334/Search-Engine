
#include <string.h>
#include "search-engine.h"
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <fstream>
using namespace std;
SearchEngine::SearchEngine( int port, DictionaryType dictionaryType):
  MiniHTTPD(port)
{
  // Create dictionary of the indicated type
  // Populate dictionary and sort it if necessary  _wordToURLList This member variable will point to the dictionary that will map words to URLRecordList's.  Initially this dictionary will be an ArrayDicitonary but you will later use other dictionary implementations depending on the dictionaryType. Once you create the dictionary, you will populate it with the files url.txt and word.txt. 
//Note: The key in the dictionary is a word (const char *) and the data is the URLRecordList *. You will need to cast the data to from (void*) to (URLRecordList *) before adding to the dictionary. The structure URLRecordList is defined in webcrawl.h but you may use your own header file if you desire.
	
  switch(dictionaryType){
	  case ArrayDictionaryType:
	  	_wordToURLList = new ArrayDictionary();
	  break;

	  case HashDictionaryType:
	  	_wordToURLList = new HashDictionary();
	  break;

	  case AVLDictionaryType:
	    //_wordToURLList = new AVLDictionary();
	  break;

	  case BinarySearchDictionaryType:
	  	_wordToURLList = new BinarySearchDictionary();
	  break;

	  default:
	  return;
  }
  int maxSize = 1000;
  _urlArray = new URLRecord[maxSize];
  ifstream f1("url.txt");
  string st;
  int k=0;
  const char * UR;
  const char * d;
  int in = 0;
  while(getline(f1,st)){
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
	  	if(index == 213)
	  		printf("%s\n",UR);
	  } 
	  if(k%3==2){
		  desc = st;
		  d=strdup(st.c_str());
		  if(index == 213)
		  	printf("%s\n",d);
	  } 
	  if(k%3==0)
	  {//store if blank
		  if(k!=0){
		 	 _urlArray[in]._url = strdup(UR);
		 	 
		 	 if(index==213){
		 	 printf("%s\n",UR);
		 	 printf("%s\n",_urlArray[in]._url);
		 	 }
		 	 _urlArray[in]._description = strdup(d);
		 	 if(index==213)
		 	 printf("%s\n",_urlArray[in]._description);
		 	 free((void *)UR);
		 	 in++;/*
		 		 if(in == maxSize){
		 		 	maxSize = maxSize * 2;
		 		 	URLRecord * n = new URLRecord[maxSize];
		 		 		for(int i =0; i < maxSize ; i ++){
		 		 			n = NULL;
			  			}
			  			for(int i=0;i< maxSize/2; i++){
			  				n[i] = _urlArray[i];
			  			}
			  			delete [] _urlArray;
			  			_urlArray = n;
			  }*/
		  }
	  }
  }

  ifstream f("word.txt");
  string s;
  while(getline(f,s)){
	  s = s+ " ";
	  string w = "";
	  int sp = 0;//store the index of first space
	  for(int i=0;i<s.length();i++){
		  if(s[i]!=' '){
			  w = w + s[i];//store the words
		  }
		  else{
			 // printf("Word %s\n\n", w.c_str());
			  sp = i;
			  break;
		  }

	  }
	  const char * word = w.c_str();
	  //printf("WORD: %s\n",word);
	  int _index;
	  string _ind="";
	  for(int i=sp+1;i<s.length();i++){
		  if(s[i]!=' '){
			  _ind = _ind + s[i];//store the number
		  }
		  else{
			  _index = atoi(_ind.c_str());//get the numerical value
			 // printf("%d\n",_index);
			  _ind = "";//for next numbers
			  
			  URLRecord n = _urlArray[_index];
		  }

	  }
	  
  }


}
void
SearchEngine::dispatch( FILE * fout, const char * documentRequested)
{
  if (strcmp(documentRequested, "/")==0) {
    // Send initial form
    fprintf(fout, "<TITLE>CS251 Search</TITLE>\r\n");
    fprintf(fout, "<CENTER><H1><em>Parshwa's Search Engine</em></H1>\n");
    fprintf(fout, "<H2>\n");
    fprintf(fout, "<FORM ACTION=\"search\">\n");
    fprintf(fout, "Search:\n");
    fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
    fprintf(fout, "</H2>\n");
    fprintf(fout, "</FORM></CENTER>\n");
    return;
  }

  string w = "";

  for(int i=13;i<strlen(documentRequested);i++){
    if(documentRequested[i]=='+'){
        w = w + " ";
    }else{
        w = w + documentRequested[i];
    }

  }

  vector<string> strs;//vector of words
  boost::split(strs,w,boost::is_any_of(" "));

  // TODO: The words to search in "documentRequested" are in the form
  // /search?word=a+b+c


  // You need to separate the words before search
  // Search the words in the dictionary and find the URLs that
  // are common for al the words. Then print the URLs and descriptions
  // in HTML. Make the output look nicer.

  // Here the URLs printed are hardwired

  const int nurls=2;

  const char * words = w.c_str();



  const char * urls[] = {
    "http://www.cs.purdue.edu",
    "http://www.cs.purdue.edu/homes/cs251"
  };
  
  const char * description[] = {
    "Computer Science Department. Purdue University.",
    "CS251 Data Structures"
  };

  fprintf( stderr, "Search for words: \"%s\"\n", words );

  fprintf( fout, "<TITLE>Search Results</TITLE>\r\n");
  fprintf( fout, "<H1> <Center><em>Boiler Search</em></H1>\n");
  fprintf( fout, "<H2> Search Results for \"%s\"</center></H2>\n", words );

  for ( int i = 0; i < nurls; i++ ) {
    fprintf( fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", i+1, urls[i], urls[i] );
    fprintf( fout, "<blockquote>%s<p></blockquote>\n", description[i] );
  }

  // Add search form at the end
  fprintf(fout, "<HR><H2>\n");
  fprintf(fout, "<FORM ACTION=\"search\">\n");
  fprintf(fout, "Search:\n");
  fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
  fprintf(fout, "</H2>\n");
  fprintf(fout, "</FORM>\n");
}

void
printUsage()
{
  const char * usage =
    "Usage: search-engine port (array | hash | avl | bsearch)\n"
    "  It starts a search engine at this port using the\n"
    "  data structure indicated. Port has to be larger than 1024.\n";

  fprintf(stderr, "%s", usage);
}

int main(int argc, char ** argv)
{
  if (argc < 3) {
    printUsage();
    return 1;
  }

  // Get port
  int port;
  sscanf( argv[1], "%d", &port);

  // Get DictionaryType
  const char * dictType = argv[2];
  DictionaryType dictionaryType;
  if (!strcmp(dictType, "array")) {
    dictionaryType = ArrayDictionaryType;
  }
  else if (!strcmp(dictType, "hash")) {
    dictionaryType = HashDictionaryType;
  }
  else if (!strcmp(dictType, "avl")) {
    dictionaryType = AVLDictionaryType;
  }
  else if (!strcmp(dictType, "bsearch")) {
    dictionaryType = BinarySearchDictionaryType;
  }
  else {
    printUsage();
    return 0;
  }

  SearchEngine httpd(port, dictionaryType);

  httpd.run();

  return 0;
}
