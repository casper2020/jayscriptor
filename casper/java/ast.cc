#include <iostream>
#include "ast.h"

AstNode::AstNode (){
  left_  = nullptr;
  right_ = nullptr;
  arg1_  = nullptr;
  arg2_  = nullptr;
}

AstNode::~AstNode (){
  if ( nullptr != left_ ) {
    //delete left_;
    //left_ = nullptr;
  }
  if ( nullptr != right_ ) {
    //delete right_;
    //right_ = nullptr;
  }
}

AstNode::AstNode(const AstNode &obj) {
   left_  = obj.left_;
   right_ = obj.right_;
   arg1_ = obj.arg1_;
   arg2_ = obj.arg2_;
   num_  = obj.num_;
   op_   = obj.op_;
   text_ = obj.text_;
   type_ = obj.type_;
}

void AstNode::setRight(AstNode* t_right){
  right_=t_right;
}
void AstNode::setLeft(AstNode* t_left){
  left_=t_left;
}
void AstNode::setOp(std::string t_op){
  op_=t_op;
}
void AstNode::setVal(double t_val){
  num_=t_val;
}
void AstNode::setText(std::string t_text){
  text_=t_text;
}
void AstNode::setArg1(AstNode* t_arg1){ arg1_=t_arg1; }
void AstNode::setArg2(AstNode* t_arg2){ arg2_=t_arg2; }

AstNode* AstNode::getRight    (){ return right_; }
AstNode* AstNode::getLeft     (){ return left_; }
std::string AstNode::getOp    (){ return op_; }
double AstNode::getVal        (){ return num_; }
std::string AstNode::getText  (){ return text_; }
AstNode* AstNode::getArg1     (){ return arg1_; }
AstNode* AstNode::getArg2     (){ return arg2_; }

AstNode ast_expression(std::string t_op, AstNode t_left, AstNode t_right){
    AstNode node;
    AstNode* tr = new AstNode();
    AstNode* tl = new AstNode();
    *tr = t_right;
    *tl = t_left;
    node.setRight(tr);
    node.setLeft(tl);
    node.setOp(t_op);
    node.setType(AstNode::TExpr);
    node.setVal(0);
    node.setArg1(nullptr);
    node.setArg2(nullptr);

    return node;
}

AstNode ast_operation(std::string t_op, AstNode t_left){
    AstNode node;
    AstNode* tl = new AstNode();
    *tl = t_left;
    node.setRight(nullptr);
    node.setLeft(tl);
    node.setOp(t_op);
    node.setType(AstNode::TOps);
    node.setVal(0);
    node.setArg1(nullptr);
    node.setArg2(nullptr);

    return node;
}

AstNode ast_strOp(std::string t_op, AstNode t_left){
    AstNode node;
    AstNode* tl = new AstNode();
    *tl = t_left;
    node.setRight(nullptr);
    node.setLeft(tl);
    node.setOp(t_op);
    node.setType(AstNode::TStrOps);
    node.setVal(0);
    node.setArg1(nullptr);
    node.setArg2(nullptr);

    return node;
}

AstNode ast_strOp(std::string t_op, AstNode t_left, AstNode t_right){
    AstNode node;
    AstNode* tr = new AstNode();
    AstNode* tl = new AstNode();
    *tr = t_right;
    *tl = t_left;
    node.setRight(nullptr);
    node.setLeft(tl);
    node.setOp(t_op);
    node.setType(AstNode::TStrOps);
    node.setVal(0);
    node.setArg1(tr);
    node.setArg2(nullptr);

    return node;
}

AstNode ast_strOp(std::string t_op, AstNode t_left, AstNode t_r1, AstNode t_r2){
    AstNode node;
    AstNode* tl = new AstNode();
    *tl = t_left;
    node.setRight(nullptr);
    node.setLeft(tl);
    node.setOp(t_op);
    node.setType(AstNode::TStrOps);
    node.setVal(0);
    AstNode* tr1 = new AstNode();
    *tr1 = t_r1;
    AstNode* tr2 = new AstNode();
    *tr2 = t_r2;
    node.setArg1(tr1);
    node.setArg2(tr2);

    return node;
}

AstNode ast_if(AstNode t_left, AstNode t_r1, AstNode t_r2){
    AstNode node;
    AstNode* tl = new AstNode();
    *tl = t_left;
    node.setRight(nullptr);
    node.setLeft(tl);
    node.setOp("if");
    node.setType(AstNode::TIf);
    node.setVal(0);
    AstNode* tr1 = new AstNode();
    *tr1 = t_r1;
    AstNode* tr2 = new AstNode();
    *tr2 = t_r2;
    node.setArg1(tr1);
    node.setArg2(tr2);

    return node;
}

AstNode ast_bool(bool t_bool){
    AstNode node;
    node.setLeft(nullptr);
    node.setRight(nullptr);
    node.setArg1(nullptr);
    node.setArg2(nullptr);
    node.setType(AstNode::TBool);
    node.setBool(t_bool);
    if(t_bool) node.setVal(1);
    else node.setVal(0);

    return node;
}

AstNode ast_null(){
    AstNode node;
    node.setLeft(nullptr);
    node.setRight(nullptr);
    node.setArg1(nullptr);
    node.setArg2(nullptr);
    node.setType(AstNode::TUndef);

    return node;
}

AstNode mkVar(AstNode t_ast){
  AstNode node;
  node.setLeft(nullptr);
  node.setRight(nullptr);
  node.setArg1(nullptr);
  node.setArg2(nullptr);
  node.setType(AstNode::TVar);
  node.setText(t_ast.getText());

  return node;
}
AstNode mkField(AstNode t_ast){
  AstNode node;
  node.setLeft(nullptr);
  node.setRight(nullptr);
  node.setArg1(nullptr);
  node.setArg2(nullptr);
  node.setType(AstNode::TField);
  node.setText(t_ast.getText());

  return node;
}
AstNode mkParam(AstNode t_ast){
  AstNode node;
  node.setLeft(nullptr);
  node.setRight(nullptr);
  node.setArg1(nullptr);
  node.setArg2(nullptr);
  node.setType(AstNode::TParam);
  node.setText(t_ast.getText());

  return node;
}
