#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include "casper/term.h"
#include "casper/dm_data_source.h"
#include "casper/java/fake_java_expression.h"
#include "v8_shell.h"

using namespace std;


int main(int argc, char* argv[]){

  //Data Source declaration
  casper::Term t1=1.0;
  casper::Term t2;
  casper::Term t3;
  casper::Term t4;
  casper::Term tstr;

  casper::java::FakeJavaExpression exp;
  casper::MyDataSource* data_source = new casper::MyDataSource;

  casper::SymbolTable tmp_st;

  casper::Term tTrue;
  tTrue.BooleanTrue();
  tmp_st.insert(std::pair <std::string, casper::Term> ("field1",t1));
  tmp_st.insert(std::pair <std::string, casper::Term> ("field2",t1));
  tmp_st.insert(std::pair <std::string, casper::Term> ("gajo",tTrue));

  data_source->AppendDataRow(tmp_st);

  t3="178985112";
  data_source->SetParameter("tax_registration_number", t3);

  t4=53.0;
  try{
    data_source->SetField("field1",t4);
  }catch (osal::Exception& a_exception){
    std::cout << a_exception.Message() << '\n';
  }

  t4="eurico";
  try{
    data_source->SetField("field2",t4);
  }catch (osal::Exception& a_exception){
    std::cout << a_exception.Message() << '\n';
  }

  try{
    data_source->SetField("gajo",tTrue);
  }catch (osal::Exception& a_exception){
    std::cout << a_exception.Message() << '\n';
  }



  //Program starts here
  exp.SetDataSource(data_source);

  std::ifstream in(argv[1]);

  if(!in){
    std::cout<< "Cannot open input file!\n";
    return 1;
  }

  std::string line;

  int cnt = 1000;

  while(getline(in, line)){
    try{

      auto start = std::chrono::system_clock::now();

      for(int i=0; i<cnt; i++){
        t1 = exp.Calculate(line);
      }

      auto end = std::chrono::system_clock::now();
      std::chrono::duration<double> elapsed_seconds = end-start;

      std::cout << "C++ ---> nr of operations: " << cnt
                << "\nelapsed time: " << elapsed_seconds.count()*1000 << "ms\n";

    /*
      t1 = exp.Calculate(line);
      if(t1.GetType()==0x01)
        std::cout << t1.GetNumber() << '\n';
      else if(t1.GetType()==0x02)
        std::cout << t1.GetText() << '\n';
      else if(t1.GetType()==0x08){
        if(t1.GetBoolean()==1)
          std::cout << "true" << '\n';
        else
          std::cout << "false" << '\n';
      }*/
    }catch (osal::Exception& a_exception){
      std::cout << a_exception.Message() << "\n";
    }

  }
  in.close();

  return 0;
}
