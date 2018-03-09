#include "casper/java/interpreter.h"

void printJS(AstNode* node){

  //Numbers
  if(node->getType()==AstNode::TNum){
    std::cout << node->getVal();
  }

  //Text
  else if(node->getType()==AstNode::TText){
    std::cout  << "(\"";
    std::cout  << node->getText();
    std::cout  << "\")";
  }

  //Expressions
  else if(node->getType()==AstNode::TExpr){
    if(!node->getOp().compare("!")){
      std::cout  << "!(";
      printJS(node->getLeft());
      std::cout  << ")";
    }
    else if(!node->getOp().compare("UM")){
      std::cout  << "-(";
      printJS(node->getLeft());
      std::cout  << ")";
    }
    else{
      std::cout  << "(";
      printJS(node->getLeft());
      std::cout  << node->getOp();
      printJS(node->getRight());
      std::cout  << ")";
    }
  }

  //Operations
  else if(node->getType()==AstNode::TOps){
    if(!node->getOp().compare("toString")){
      std::cout  << "(";
      printJS(node->getLeft());
      std::cout  << ").toString()";
    }
    else if(!node->getOp().compare("valueOf")){
      std::cout  << "(";
      printJS(node->getLeft());
      std::cout  << ").valueOf()";
    }
    else if(!node->getOp().compare("parseBool")){
      printJS(node->getLeft());
      std::cout  << " == \"true\" ? true : false";
    }
    else{
      std::cout  << node->getOp() << "(";
      printJS(node->getLeft());
      std::cout   << ")";
    }
  }

  //String Ops
  else if(node->getType()==AstNode::TStrOps){

    if(!node->getOp().compare("IsEmpty")){
      printJS(node->getLeft());
      std::cout  << ".length===0";
    }
    else if(!node->getOp().compare("length")){
      printJS(node->getLeft());
      std::cout  << ".length";
    }
    else if(node->getOp().compare("toUpperCase") == 0 ||
            node->getOp().compare("toLowerCase") == 0 ){
      printJS(node->getLeft());
      std::cout  << "." << node->getOp() << "()";
    }
    else if(!node->getOp().compare("substring")){
      if(node->getArg2()==nullptr){
        printJS(node->getLeft());
        std::cout  << "." << node->getOp() << "(";
        printJS(node->getArg1());
        std::cout << ")";
      }
      else{
        printJS(node->getLeft());
        std::cout  << "." << node->getOp() << "(";
        printJS(node->getArg1());
        std::cout  << ",";
        printJS(node->getArg2());
        std::cout  << ")";
      }
    }
    else if(!node->getOp().compare("indexOf")){
      printJS(node->getLeft());
      std::cout  << "." << node->getOp() << "(";
      printJS(node->getArg1());
      std::cout << ")";
    }
    else if(!node->getOp().compare("replace")){
      printJS(node->getLeft());
      std::cout  << "." << node->getOp() << "(";
      printJS(node->getArg1());
      std::cout << ",";
      printJS(node->getArg2());
      std::cout << ")";
    }
    else std::cout << "error";
  }

  //Ifs
  else if(node->getType()==AstNode::TIf){
    std::cout << "(";
    printJS(node->getLeft());
    std::cout << " ? ";
    printJS(node->getArg1());
    std::cout << " : ";
    printJS(node->getArg2());
    std::cout << ")";
  }

  //Vars Params & Fields
  else if(node->getType()==AstNode::TVar || node->getType()==AstNode::TParam){
    std::cout << "$." << node->getText();
  }
  else if(node->getType()==AstNode::TField){
    std::cout << "$.lines[$._dri]." << node->getText();
  }
}
