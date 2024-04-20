#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <iostream>
#include <vector>
#include <tuple> 
#include <sstream>
#include <fstream> 
#include <string>


using namespace std;
namespace py = pybind11;

template<typename T>
T test( T x, T y ){
  return x + y ; 
}

class CSV{
public : 
   string file_name = "" ; 
   vector<tuple<int,bool,string,string,int,string,string>> data;
   vector<tuple<int,bool,string,string,int,string,string>> sorted ;
   vector<tuple<int,bool,string,string,int,string,string>> filtered_data ;

   int data_size ;
   bool res[12] ;
   bool filtered = false ;
   vector<int> order ;
 
   CSV(string file_name, int n ){
      this->file_name = file_name ;
      data.reserve(n) ;  
      this->data_size = n ;
      order = vector<int> { 1, 2, 3, 4, 0, 5 } ;
   }
   inline void store(string& line ){
      stringstream ss ( line ) ; 
      string temp ; 
      int price ; 
      bool is_new ;
      string brand ; 
      string model ; 
      int year ; 
      string type ; 
      string color ;       

      std::getline(ss, temp, ',') ;
      std::getline(ss, temp, ',') ;
      price = stoi( temp ) ; 

      std::getline(ss, temp, ',') ;
      std::getline(ss, temp, ',') ;
      is_new = ( temp == "New" ) ; 
      
      std::getline(ss, brand, ',') ;
      std::getline(ss, model, ',') ;

      std::getline(ss, temp, ',') ;
      year = stoi( temp ) ; 
       
      std::getline(ss, type, ',') ;
      std::getline(ss, color, ',') ;     
       
      data.push_back(make_tuple( price, is_new, brand, model, year, type, color ))  ;  
   }
   bool set_filter( int used, int year ){
        filtered_data.clear() ;
        filtered = true ;

        if( used == 0 ) 
        {
            filtered = false ; 
        }
        else if( used == 1 ){
            for( int i = 0 ; i < data.size() ; i ++ ){
                 if( get<1>(data[i]) && get<4>(data[i]) >= year ){
                     filtered_data.push_back(data[i]) ;
                 }
            }
        }
        else if( used == 2 ){
            for( int i = 0 ; i < data.size() ; i ++ ){
                 if( ! get<1>(data[i]) && get<4>(data[i]) >= year ){
                     filtered_data.push_back(data[i]) ;
                 }
            }
        }
        return true ;
   }
   bool get_file(){
      fstream fin ; 
      fin.open( file_name, ios::in); 
      string line, temp ;
      getline( fin, line ) ;  
      for( int i = 0 ; i < this->data_size ; i ++ ) {
           getline( fin, line ) ;
           store( line ) ;  
      }
      return true ;
   }

   
   bool comp(tuple<int,bool,string,string,int,string,string> &t1, tuple<int,bool,string,string,int,string,string> &t2 ){
       res[0] = ( get<0>(t1) < get<0>(t2) ) ;
       res[1] = ( get<2>(t1).compare(get<2>(t2)) < 0 ); 
       res[2] = ( get<3>(t1).compare(get<3>(t2)) < 0) ;
       res[3] = ( get<4>(t1) < get<4>(t2) ) ;
       res[4] = ( get<5>(t1).compare(get<5>(t2)) < 0 ) ;
       res[5] = ( get<6>(t1).compare(get<6>(t2)) < 0 ) ;
       res[6] = ( get<0>(t1) == get<0>(t2)) ;
       res[7] = ( get<2>(t1).compare(get<2>(t2)) == 0 ) ;
       res[8] = ( get<3>(t1).compare(get<3>(t2)) == 0 ) ;
       res[9] = ( get<4>(t1) == get<4>(t2) ) ;
       res[10] = ( get<5>(t1).compare(get<5>(t2)) == 0 ) ;
       res[11] = ( get<6>(t1).compare(get<6>(t2)) == 0 ) ;
       
   
       for( int i = 0 ; i < 6 ; i ++ ) {
           if( res[order[i]] ) return true ; 
           if( ! res[order[i]+6] ) return false ; 
       }
      
       return true ; 
   }
   
   void set_order(py::list my_list){
        order = my_list.cast<vector<int>>() ;
      //  for(auto temp : order ) 
      //     cout <<  temp  << endl ;  
   }



   int partition(int start, int end, bool is_random )
   {
        if( is_random )
        {
          int rand_idx = rand()%(end-start+1) + start ;  
          swap( sorted[start], sorted[rand_idx] ) ; 
        }
	auto pivot = sorted[start] ;

	int count = 0;
	for (int i = start + 1; i <= end; i++) {
		if ( comp( sorted[i], pivot) )
			count++;
	}

	int pivotIndex = start + count;
	swap(sorted[pivotIndex], sorted[start]);

	int i = start, j = end;

	while (i < pivotIndex && j > pivotIndex) {

		while (comp(sorted[i],pivot)) {
			i++;
		}

		while (!comp(sorted[j],pivot)) {
			j--;
		}

		if (i < pivotIndex && j > pivotIndex) {
			swap(sorted[i++], sorted[j--]);
		}
	}

	return pivotIndex;
   } 

   void quickSort( int start, int end, bool is_random)
   {

	// base case
	if (start >= end)
		return;

	int p = partition( start, end, is_random);

	quickSort( start, p - 1, is_random );
	quickSort( p + 1, end, is_random );
   } 

  void heapify( int N, int i)
  {

    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < N &&  ! comp( sorted[l],sorted[largest]) )
        largest = l;

    if (r < N &&  ! comp( sorted[r], sorted[largest]) )
        largest = r;

    if (largest != i) {
        swap(sorted[i], sorted[largest]);

        heapify(N, largest);
    }
  }

  void heapSort(int N)
  {

    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(  N, i);

    for (int i = N - 1; i > 0; i--) {
        swap(sorted[0], sorted[i]);
        heapify( i, 0);
    }
  }


   void sort_by(int method) {

     if( filtered )
         sorted = filtered_data ;
     else
         sorted = data ;
     if( method == 1 ) 
        quickSort( 0, sorted.size() -1, false ) ;
     else if( method == 2 ) 
        quickSort( 0, sorted.size() -1, true ) ; 
     else 
        heapSort( sorted.size() ) ; 
      
   }
   py::list print_file() {
        vector<string> vs ; 
 
        for( int i = 0 ; i < sorted.size() ; i ++ ) {
            string temp = "" ; 
            temp +=  to_string( get<0>(sorted[i])) + ", "; 
            temp +=  get<1>(sorted[i]) ? "New, " : "Used, ";  
            temp +=  get<2>(sorted[i]) + ", " ;
            temp +=  get<3>(sorted[i]) + ", " ;
            temp +=  to_string( get<4>(sorted[i])) + ", " ;
            temp += get<5>(sorted[i]) + ", " ;
            temp += get<6>(sorted[i])  ;

            vs.push_back( temp ) ; 
        }
        return py::cast(vs) ; 
   } 
} ; 


PYBIND11_MODULE(csvpy, m) {
  m.doc() = "pybind11 csvpy plugin";      // module doc string
  m.def("test", &test<double>, "A function for test" ) ;
  py::class_<CSV>(m, "CSV")
       .def(py::init<string,int>() )  
       .def("get_file", &CSV::get_file)
       .def("set_order", &CSV::set_order)
       .def("sort_by", &CSV::sort_by )
       .def("set_filter", &CSV::set_filter)
       .def("print_file",&CSV::print_file)  
       ; 
}
