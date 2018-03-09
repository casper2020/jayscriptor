#include <stdio.h>
#include <iostream>
#include <fstream>
#include "casper/term.h"
#include "casper/dm_data_source.h"
#include "casper/java/fake_java_expression.h"

int main(int argc, char* argv[]){

  casper::java::FakeJavaExpression exp;
  casper::MyDataSource* data_source = new casper::MyDataSource;

  exp.SetDataSource(data_source);

  std::ifstream in(argv[1]);

  if(!in){
    std::cout<< "Cannot open input file!\n";
    return 1;
  }

  std::string line;
  int n=0;

  std::cout << "var t0 = performance.now();\n";

  while(getline(in, line)){
    try{
      std::cout << "console.log(";
      exp.Convert(line);
      std::cout << ")";
    }catch (osal::Exception& a_exception){
      std::cout << a_exception.Message() << '\n';
    }
    std::cout  << '\n';
    n++;
  }
  in.close();
  std::cout << "var t1 = performance.now();\n";
  std::cout << "console.log(\"nr of operations: "<< n <<"\")\n";
  std::cout << "console.log(\"elapsed time: \" + (t1 - t0)/1000 + \"s\\n\")\n";


  return 0;
}
