/*
 * Meg Jaffy & Khue Le
 * Date: 4/5/2018
 * File: test_list.cpp
 * ---------------------
 * This file performs some test case for the Complex class
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include <cassert>
#include <string>
#include<sstream>


int main()
{
  //Constructor
  List<char> list1;

  //append method
  list1.append('b');
  assert(list1[0]=='b');
  list1.append('c');
  assert(list1[1]=='c');
  list1.append('d');
  assert(list1[2]=='d');

  //insert method
  list1.insert(0,'a');//first element
  assert(list1[0]=='a');
  list1.insert(4,'e');//last element
  assert(list1[4]=='e');
  list1.insert(2,'*');//random middle element
  assert(list1[2]=='*');

  //cout
  cout<<list1<<endl;

  assert(list1.pop(2)=='*');
  assert(list1.pop(0)=='a');//first element
  assert(list1.pop(0)=='b');
  assert(list1.pop(-1)=='e');//last element-negative indexing

  List<int> list2;
  list2.append(1);//list contains only one element
  assert(list2.pop(0)==1);

  //assignment operator
  List<char> list3;
  list3=list1;
  for (int i=0;i<list1.length();++i)
  {
    assert(list1[i]==list3[i]);
  }


  // //error test
  //
  // //cout list with no elements
  // List a;
  // cout << a[1] << endl;
  //
  // //insert with index out of range:
  // list.insert(7, 'm');
  //
  // //pop list with no elements
  // List a1;
  // a1.pop(1);
  //
  // //pop list with index out of range
  // list.pop(6);
  //
  // //index out of range
  // List a2;
  // a2.append('x');
  // a2.append('y');
  // a2.append('z');
  //
  // cout<<a2[3]<<endl;
  // cout<<a2[-4]<<endl;
  //

  cout<<"Passed all test!"<<endl;
  return 0;

}
