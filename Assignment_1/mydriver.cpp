#include <iostream>
#include <string>

#include "tlist.h"

using namespace std;

template <typename T> 
void PrintList(const TList<T>& L, string label)
{
   cout << label << " size is: " << L.GetSize() << "\n"
        << label << " = "; 
   L.Print(cout);
   cout << "\n\n";
}

int main()
{
   TList<int> L1;		// integer list test ----------------------------------------

   // Check if IsEmpty function works
   if ( L1.IsEmpty()==true ){
      cout << "List is empty";
   }
   cout << "\n\n";

   // check if InsertBack, InsertFront, RemoveBack, and RemoveFront functions work 
   L1.InsertBack( 1 );

   if ( L1.IsEmpty()==false ){
      cout << "List is not empty";
   }
   cout << "\n\n";

   for (int i = 0; i < 10; i++){
      L1.InsertBack( 2 );
   }

   PrintList(L1, "L1");

   for (int i = 0; i < 10; i++){
      L1.RemoveBack();
   }

   PrintList(L1, "L1");

   for (int i = 0; i < 10; i++){
      L1.InsertFront( 10 );
   }

   PrintList(L1, "L1");

   for (int i = 0; i < 10; i++){
      L1.RemoveFront();
   }

   PrintList(L1, "L1");

   //Get first and last item in list
   int data_first = L1.GetFirst();
   int data_last = L1.GetLast();
   cout << "First element: " << data_first << "\nLast element: " << data_last;

   // try an iterator, and some middle inserts/deletes
   cout << "\n\nTesting some inserts with an iterator\n\n";

   TListIterator<int> itr = L1.GetIterator();

   for (int i = 0; i < 10; i++){
      L1.Insert(itr, 999);
   }

   for (int i = 0; i < 5; i++){
      itr.Previous();
   }

   L1.Insert(itr, 555);

   PrintList(L1, "L1");

   if (itr.HasNext()){
      itr.Next();
   }

   L1.Insert(itr, 555);

   PrintList(L1, "L1");

   cout << "Testing some removes (with iterator)\n\n";

   for (int i = 0; i < 5; i++){
      if (itr.HasPrevious()){
         itr.Previous();
      }
   }   		

   for (int i = 0; i < 5; i++){
      cout << itr.GetData() << " ";
      itr = L1.Remove(itr);
   }

   cout << "\n\n";

   PrintList(L1, "L1");

   itr = L1.GetIterator();
   while (itr.HasNext()) {
    // Print the data
    cout << itr.GetData() << " ";

    itr.Next();
   }

   cout << "\n\n";

   itr = L1.GetIteratorEnd();
   while (itr.HasPrevious()) {
    // Print the data
    cout << itr.GetData() << " ";

    itr.Previous();
   }

   cout << "\n\n";
   
   // building another list
   TList<int> L2;
   for (int i = 0; i < 10; i++)
      L2.InsertBack(i * 3 + 1);

   PrintList(L2, "L2");

   // Testing + overload:
   TList<int> L3 = L1 + TList<int>(100, 7);

   TList<int> L4;
   L4 = L2 + L1;

   PrintList(L3, "L3");
   PrintList(L4, "L4");

   // Check if GetSize and Clear functions work
   cout << "\nSize of all lists:\n" <<
   L1.GetSize() << " " <<
   L2.GetSize() << " " <<
   L3.GetSize() << " " <<
   L4.GetSize() << "\n\n";

   L1.Clear();
   L2.Clear();
   L3.Clear();
   L4.Clear();
   

// End of integer list test ----------------------------------------

   cout << "-------------------------------------- TEST # 2 ---------------------------------------------\n\n";

   TList<string> S1;		// String list test ----------------------------------------

   // Check if IsEmpty function works
   if ( S1.IsEmpty()==true ){
      cout << "List is empty";
   }
   cout << "\n\n";

   // check if InsertBack, InsertFront, RemoveBack, and RemoveFront functions work 
   S1.InsertBack( "Hello" );

   if ( S1.IsEmpty()==false ){
      cout << "List is not empty";
   }
   cout << "\n\n";

   for (int i = 0; i < 10; i++){
      S1.InsertBack( "Hello world" );
   }

   PrintList(S1, "S1");

   for (int i = 0; i < 10; i++){
      S1.RemoveBack();
   }

   PrintList(S1, "S1");

   for (int i = 0; i < 10; i++){
      S1.InsertFront( "World" );
   }

   PrintList(S1, "S1");

   for (int i = 0; i < 10; i++){
      S1.RemoveFront();
   }

   PrintList(S1, "S1");

   //Get first and last item in list
   string Sdata_first = S1.GetFirst();
   string Sdata_last = S1.GetLast();
   cout << "First element: " << Sdata_first << "\nLast element: " << Sdata_last;

   // try an iterator, and some middle inserts/deletes
   cout << "\n\nTesting some inserts with an iterator\n\n";

   TListIterator<string> Sitr = S1.GetIterator();

   for (int i = 0; i < 10; i++){
      S1.Insert(Sitr, "Hey");
   }

   for (int i = 0; i < 5; i++){
      Sitr.Previous();
   }

   S1.Insert(Sitr, "Hello there");

   PrintList(S1, "S1");

   if (Sitr.HasNext()){
      Sitr.Next();
   }

   S1.Insert(Sitr, "Hello there");

   PrintList(S1, "S1");

   cout << "Testing some removes (with iterator)\n\n";

   for (int i = 0; i < 5; i++){
      if (Sitr.HasPrevious()){
         Sitr.Previous();
      }
   }   		

   for (int i = 0; i < 5; i++){
      cout << Sitr.GetData() << " ";
      Sitr = S1.Remove(Sitr);
   }

   cout << "\n\n";

   PrintList(S1, "S1");

   Sitr = S1.GetIterator();
   while (Sitr.HasNext()) {
    // Print the data
    cout << Sitr.GetData() << " ";

    Sitr.Next();
   }

   cout << "\n\n";

   Sitr = S1.GetIteratorEnd();
   while (Sitr.HasPrevious()) {
    // Print the data
    cout << Sitr.GetData() << " ";

    Sitr.Previous();
   }

   cout << "\n\n";
   
   // building another list
   TList<string> S2;
   for (int i = 0; i < 10; i++)
      S2.InsertBack( "Yello" );

   PrintList(S2, "S2");

   // Testing + overload:
   TList<string> S3 = S1 + TList<string>("Hello 7 times", 7);

   TList<string> S4;
   S4 = S2 + S1;

   PrintList(S3, "S3");
   PrintList(S4, "S4");

   // Check if GetSize and Clear functions work
   cout << "\nSize of all lists:\n" <<
   S1.GetSize() << " " <<
   S2.GetSize() << " " <<
   S3.GetSize() << " " <<
   S4.GetSize()<< "\n\n";

   S1.Clear();
   S2.Clear();
   S3.Clear();
   S4.Clear();
   

// End of String list test ----------------------------------------

}
