
class AstNode {
  protected:
    AstNode*      right_;
    AstNode*      left_;
    bool          bool_;
    int           type_;
    double        num_;
    std::string   text_;
    std::string   op_;
    AstNode*      arg1_;
    AstNode*      arg2_;

  public: // enumerations

      enum {
          TUndef  = 0,
          TNum    = 1,
          TText   = 2,
          TExpr   = 3,
          TOps    = 4,
          TStrOps = 5,
          TIf     = 6,
          TBool   = 7,
          TVar    = 8,
          TParam  = 9,
          TField  = 10
      };

  public:
    //setters
    virtual   void        setRight(AstNode* t_right);
    virtual   void        setLeft(AstNode* t_left);
    virtual   void        setOp(std::string t_op);
    virtual   void        setVal(double t_val);
    virtual   void        setText(std::string t_text);
    virtual   void        setArg1(AstNode* t_arg1);
    virtual   void        setArg2(AstNode* t_arg2);

    //getters
    virtual   AstNode*    getRight();
    virtual   AstNode*    getLeft();
    virtual   std::string getOp();
    virtual   double      getVal();
    virtual   std::string getText();
    virtual   AstNode*    getArg1();
    virtual   AstNode*    getArg2();

    virtual bool  getBool  ()             { return bool_; };
    virtual void  setBool  (bool t_bool)  { bool_=t_bool; };
    virtual int   getType  ()             { return type_; };
    virtual void  setType  (int t_tipo)   { type_=t_tipo; };

               AstNode ();                    // constructor
               AstNode (const AstNode &obj);  // copy constructor
    virtual   ~AstNode ();                    // destructor

    void          operator          =(const char* a_string);
    void          operator          =(std::string a_string);
    void          operator          =(double a_value);
    void          operator          =(bool t_bool);
};

inline void AstNode::operator =(const char* a_string) {
    text_ = a_string;
    type_ = TText;
}

inline void AstNode::operator =(std::string a_string) {
    text_ = a_string;
    type_ = TText;
}

inline void AstNode::operator =(bool t_bool) {
    if(t_bool) num_=1;
    else num_=0;
    bool_ = t_bool;
    type_ = TBool;
}

inline void AstNode::operator =(double a_value) {
    left_   = nullptr;
    right_  = nullptr;
    num_    = a_value;
    type_   = TNum;
}

AstNode ast_expression(std::string t_op, AstNode t_left, AstNode t_right);

AstNode ast_operation(std::string t_op, AstNode t_left);

AstNode ast_strOp(std::string t_op, AstNode t_left);
AstNode ast_strOp(std::string t_op, AstNode t_left, AstNode t_right);
AstNode ast_strOp(std::string t_op, AstNode t_left, AstNode t_r1, AstNode t_r2);

AstNode ast_if(AstNode t_left, AstNode t_r1, AstNode t_r2);

AstNode ast_bool(bool t_bool);
AstNode ast_null();

AstNode mkVar(AstNode t_ast);
AstNode mkField(AstNode t_ast);
AstNode mkParam(AstNode t_ast);
