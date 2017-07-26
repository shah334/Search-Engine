//TODO:AVL.
#include <string.h>
#include "search-engine.h"
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <string>
#include <fstream>
using namespace std;
#define BILLION 1000000000L;
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
    printf("HII");
	    _wordToURLList = new AVLDictionary();
	  break;

	  case BinarySearchDictionaryType:
	  	_wordToURLList = new BinarySearchDictionary();
	  break;

	  default:
      _wordToURLList = new AVLDictionary();
	  //return;
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
	 int sp;
	 for(int i=0;i<st.length();i++){
		 if(st[i]==' '){
			 sp = i;
		 }
	 }
	 string w = "";
	 for(int i=sp+1;i<st.length();i++){
		 w = w+st[i];
	 }
	 UR = w.c_str();
	 getline(f1,st);
	 d = st.c_str();
	 _urlArray[k]._description = strdup(d);
	 getline(f1,st);
	 _urlArray[k]._url = strdup(UR);
	 //printf("%s\n",_urlArray[k]._url);
	 //printf("%s\n",_urlArray[k]._description);
	 k++;
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
			// printf("%s ", w.c_str());
			  sp = i;
			  break;
		  }

	  }
	  const char * word = w.c_str();
	  //printf("WORD: %s\n",word);
	  int _index;
	  string _ind="";
	  URLRecordList *head;
	  head = NULL;
	  URLRecordList *previous;
	  previous = NULL;
	   for(int i=sp+1;i<s.length();i++){
		  if(s[i]!=' '){
			  _ind = _ind + s[i];//store the number
		  }
		  else{
			  _index = atoi(_ind.c_str());//get the numerical value
			 _ind = "";
			 //printf("%d\n",_index);
			 URLRecordList * e = new URLRecordList();
			  if(head==NULL){
				  head = e;
			  }
			  e->_urlRecord = &_urlArray[_index];
			  e->_next = NULL;
			  if(previous!=NULL){
				  previous->_next = e;
			  }
			  previous = e;
		  }

	   }
	   URLRecordList * l = head;
	 bool flag = _wordToURLList->addRecord(word,(URLRecordList*)head);//ADDED!
	}


}
void
SearchEngine::dispatch( FILE * fout, const char * documentRequested)
{
  struct timespec start, stop;
  long accum;
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
  URLRecordList * head;
  int arr[10000] ;
  for(int i=0;i<10000;i++){
    arr[i] = 0;
  }
  int counter = 0;
  URLRecord * _u = new URLRecord[10000];
  clock_gettime( CLOCK_REALTIME, &start);
  for(int i=0;i<strs.size();i++){
	  head = (URLRecordList*)_wordToURLList->findRecord(strs[i].c_str());
    if(i==0){//if the first word is searched, store all urls else cross them off if theyre not intersections
      URLRecordList * temp = head;
      while(temp!=NULL){
        _u[counter] = *temp->_urlRecord;
        arr[counter]++;
        temp = temp->_next;
        counter ++;
      }
    }else{
      URLRecordList * temp = head;
      while(temp!=NULL){
        for(int j=0;j<counter;j++){
          if(!(strcmp(temp->_urlRecord->_url,_u[j]._url))){
              arr[j]++;
            }
          }
          temp = temp ->_next;
        }
      }
  }
  clock_gettime( CLOCK_REALTIME, &stop);
  accum = (( stop.tv_nsec - start.tv_nsec ));
  printf( "%ld\n", accum );
  double timeTaken = (accum * 1.0)/BILLION;
  //printf( "%d\n", stop.tv_sec - start.tv_sec);
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
  fprintf( fout, "<H1> <Center><em>Parshwa's Search Engine</em></H1>\n");
  fprintf( fout, "<H2> Search Results for \"%s\", time elapsed is \"%ld\" nanoseconds, (%f seconds)</center></H2>\n", words, accum, timeTaken );

  /*
  for ( int i = 0; i < nurls; i++ ) {
    fprintf( fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", i+1, urls[i], urls[i] );
    fprintf( fout, "<blockquote>%s<p></blockquote>\n", description[i] );
  }
  
  URLRecordList * t = head;
  int countURLs = 1;
  while(t!=NULL){
	fprintf( fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", countURLs, t->_urlRecord->_url, t->_urlRecord->_url );
    fprintf( fout, "<blockquote>%s<p></blockquote>\n", t->_urlRecord->_description );
  	countURLs ++;
  	t=t->_next;
    }
  */

  for(int i=0;i<counter;i++){
    if(arr[i]==strs.size()){
      fprintf( fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", i+1, _u[i]._url, _u[i]._url );
      fprintf( fout, "<blockquote>%s<p></blockquote>\n", _u[i]._description );
    }
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

  if (!strcmp(dictType, "avl")) {
    printf("Yo\n");
    return 0;
    dictionaryType = AVLDictionaryType;
  }
  else if (!strcmp(dictType, "hash")) {
    dictionaryType = HashDictionaryType;
  }
  else if (!strcmp(dictType, "bsearch")) {
    dictionaryType = BinarySearchDictionaryType;
  }
  else if (!strcmp(dictType, "array")) {
    dictionaryType = ArrayDictionaryType;
  }
  else {
    printUsage();
    return 0;
  }
  dictionaryType = AVLDictionaryType;
  SearchEngine httpd(port, dictionaryType);

  httpd.run();

  return 0;
}
