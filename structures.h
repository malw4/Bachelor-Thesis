// fileS.txt
//#define FILENR 1
//#define WYMIAR 6 
//#define NONZ 13

// bc30.txt
#define FILENR 2
#define WYMIAR 28924 
#define NONZ 1036208

// file.txt - nie dziaÅ‚a
//#define FILENR 3
//#define WYMIAR 16614 
//#define NONZ 1091362

// fileM37.txt - nie dziaÅ‚a
//#define FILENR 4
//#define WYMIAR 9152 
//#define NONZ 765944

#define ROZMIAR (WYMIAR*WYMIAR)
#define C 4

struct Sell{
  int nr_slice; 		//wysokoœæ plastra
  double* val; 			//g³ówna tablica wartoœci dla slice_C
  int* slice_col;  //tablica kolumn
  int* sliceStart; //tablica slice_start
  int* cl; 				//pomocnicza tablica d³ugoœci plastrów
};

struct CSR{
  double* a_csr;	//g³ówna tablica wartoœci
  int* row_ptr;		//tablica row_ptr
  int* col_ind;	 //tablica kolumn
  int* row_ind; //tablica potrzebna do ustawienia Sell-C
};

struct CSC{
  double* a_csc;	//g³ówna tablica wartoœci
  int* col_ptr;		//tablica col_ptr
  int* col_ind;		//tablica koumn
  int* row_ind;		//tablica wierszy
};


struct Wpis{
  int col;
  int row;
  double value;
};
