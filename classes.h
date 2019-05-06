#include<bits/stdc++.h>

using namespace std;

#ifndef __HEADER__
#define __HEADER__


typedef struct param
{
  char *type,*id;
}param;

typedef struct args
{
  //0 for int 1 for bool 2 for int array 3 for bool array
  vector<int> args;
}args;

typedef struct out_declaration
{
  char* var_name;
  int size;
}out_declaration;

typedef struct Var_data {
  char* data_type;
  int int_value;
  bool bool_value;
  vector<int> int_values;
  vector<bool> bool_values;
}Var_data;

union Node{
  int value;
  char* identifier;
  class Program* program;
  class Field_decls* field_decls;
  class Field_decl* field_decl;
  class Out_decls* out_decls;
  class Method_decls* method_decls;
  class Method_decl* method_decl;
  class Method_args* method_args;
  class Block* block;
  class Var_declarations* var_decls;
  class Var_declaration* var_decl;
  class Statements* statements;
  class Statement* statement;
  class Assignment* assignment;
  class Location* location;
  class Assign_op* assign_op;
  class Expression* expression;
  class Literal* literal;
  class UnaryExpression* unary_expression;
  class BinaryExpression* binary_expression;
  class Ifelsestatement* ifelsestatement;
  class Forstatement* forstatement;
  class Returnstatement* returnstatement;
  class Breakstatement* breakstatement;
  class Continuestatement* continuestatement;
  class Methodcall* methodcall;
  class Expressions* expressions;
  class Calloutcall* calloutcall;
  class Calloutargs* calloutargs;
  class Calloutarg* calloutarg;
  class Expressionscall* expressionscall;
  Node(){
    value = 0;
    identifier = NULL;
    program = NULL;
    field_decls = NULL;
    field_decl = NULL;
    out_decls = NULL;
    method_decls = NULL;
    method_decl = NULL;
    method_args = NULL;
    block = NULL;
    var_decls = NULL;
    var_decl = NULL;
    statements = NULL;
    statement = NULL;
    assignment = NULL;
    location = NULL;
    assign_op = NULL;
    expression = NULL;
    literal = NULL;
    unary_expression = NULL;
    binary_expression = NULL;
    ifelsestatement = NULL;
    forstatement  = NULL;
    returnstatement = NULL;
    breakstatement = NULL;
    continuestatement = NULL;
    methodcall = NULL;
    expressions = NULL;
    calloutcall = NULL;
    calloutargs = NULL;
    calloutarg = NULL;
    expressionscall = NULL;
  }
  ~Node(){};

};


typedef union Node YYSTYPE;
#define YYSTYPE_IS_DECLARED 1



class AstNode;
class Program;
class Field_decls;
class Field_decl;
class Out_decls;
class Method_decls;
class Method_decl;
class Method_args;
class Block;
class Var_declarations;
class Var_declaration;
class Statements;
class Statement;
class Assignment;
class Location;
class Assign_op;
class Expression;
class Literal;
class UnaryExpression;
class BinaryExpression;
class Ifelsestatement;
class Forstatement;
class Returnstatement;
class Breakstatement;
class Continuestatement;
class Methodcall;
class Expressions;
class Calloutcall;
class Calloutargs;
class Calloutarg;
class Expressionscall;

class Visitor
{
public:
  virtual void visit(class Program*)=0;
  virtual void visit(class Field_decls*)=0;
  virtual void visit(class Field_decl*)=0;
  virtual void visit(class Out_decls*)=0;
  virtual void visit(class Method_decls*)=0;
  virtual void visit(class Method_decl*)=0;
  virtual void visit(class Method_args*)=0;
  virtual void visit(class Block*)=0;
  virtual void visit(class Var_declarations*)=0;
  virtual void visit(class Var_declaration*)=0;
  virtual void visit(class Statements*)=0;
  virtual void visit(class Statement*)=0;
  virtual void visit(class Assignment*)=0;
  virtual void visit(class Location*)=0;
  virtual void visit(class Assign_op*)=0;
  virtual void visit(class Expression*)=0;
  virtual void visit(class Literal*)=0;
  virtual void visit(class UnaryExpression*)=0;
  virtual void visit(class BinaryExpression*)=0;
  virtual void visit(class Ifelsestatement*)=0;
  virtual void visit(class Forstatement*)=0;
  virtual void visit(class Returnstatement*)=0;
  virtual void visit(class Breakstatement*)=0;
  virtual void visit(class Continuestatement*)=0;
  virtual void visit(class Methodcall*)=0;
  virtual void visit(class Expressions*)=0;
  virtual void visit(class Calloutcall*)=0;
  virtual void visit(class Calloutargs*)=0;
  virtual void visit(class Calloutarg*)=0;
  virtual void visit(class Expressionscall*)=0;
};
class Traverse:public Visitor
{
public:
  void visit(class Program*);
  void visit(class Field_decls*);
  void visit(class Field_decl*);
  void visit(class Out_decls*){}
  void visit(class Method_decls*);
  void visit(class Method_decl*);
  void visit(class Method_args*);
  void visit(class Block*);
  void visit(class Var_declarations*);
  void visit(class Var_declaration*);
  void visit(class Statements*);
  void visit(class Statement*){}
  void visit(class Assignment*);
  void visit(class Location*);
  void visit(class Assign_op*){}
  void visit(class Expression*){}
  void visit(class Literal*){}
  void visit(class UnaryExpression*);
  void visit(class BinaryExpression*);
  void visit(class Ifelsestatement*);
  void visit(class Forstatement*);
  void visit(class Returnstatement*);
  void visit(class Breakstatement*){}
  void visit(class Continuestatement*){}
  void visit(class Methodcall*){}
  void visit(class Expressions*);
  void visit(class Calloutcall*);
  void visit(class Calloutargs*);
  void visit(class Calloutarg*);
  void visit(class Expressionscall*);
};

class AstNode
{

};

class Assign_op:public AstNode
{
  public:
    char* assign_op;
  public:
    Assign_op(char* assign_op)
    {
      this->assign_op  = assign_op;
    }
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Expression:public AstNode
{
  public:
    int expr_type;// 0 -binary ,1-unary , 2- location, 3-literal
    int r_type; //0 for bool ,1 for int,else char
  public:
    virtual void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Literal:public Expression
{
  public:
    int type;//0 for int,1 for char,2 for bool
    int int_value;
    char* bool_value;
    char char_value;
  public:
    Literal(int,int);
    Literal(int,char*);
    Literal(int,char);
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class UnaryExpression:public Expression
{
  public:
    char* op;
    class Expression* rhs;
  public:
    UnaryExpression(char*,class Expression*);
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class BinaryExpression:public Expression
{
  public:
    class Expression* lhs;
    char* op;
    class Expression* rhs;
    int type;//0 for arith_op,1 for rel_op,2 for eq_op,3 for cond_op
  public:
    BinaryExpression(class Expression*,char*,class Expression*);
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Location:public Expression
{
  public:
    char* var_name;
    int type; //0 for variable 1 for array
    class Expression* index;
  public:
    Location(char*);
    Location(char*,class Expression*);
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Statement:public AstNode
{
  public:
    int return_type;//0 for not return , 1 for return
  public:
    virtual void accept(Visitor *v)
    {
      v->visit(this);
    }
};

class Expressions:public AstNode
{
  public:
    vector<class Expression*> expressions_list;
  public:
    Expressions()
    {
      this->expressions_list.clear();
    }
    void push(class Expression* expr)
    {
      this->expressions_list.push_back(expr);
    }
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Methodcall:public Statement,public Expression
{
  public:
    char* method_name;
  public:
    virtual void accept(Visitor* v)
    {
      v->visit(this);
    }
};
class Expressionscall:public Methodcall
{
  public:
    class Expressions* expressions;
  public:
    Expressionscall(char* method_name,class Expressions* exprs)
    {
      this->method_name  = method_name;
      this->expressions = exprs;
    }
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Calloutargs:public AstNode
{
  public:
    vector<class Calloutarg*> calloutarg_list;
  public:
    Calloutargs()
    {
      this->calloutarg_list.clear();
    }
    void push(class Calloutarg* carg)
    {
      this->calloutarg_list.push_back(carg);
    }
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Calloutcall:public Methodcall
{
  public:
    char* method_name;
    class Calloutargs* calloutargs;
  public:
    Calloutcall(char* method_name,class Calloutargs* calloutargs)
    {
      this->method_name = method_name;
      this->calloutargs = calloutargs;
    }
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Calloutarg:public AstNode
{
  public:
    class Expression* expr;
    char* str;
  public:
    Calloutarg(class Expression* expr)
    {
      this->expr = expr;
      str = NULL;
    }
    Calloutarg(char* str)
    {
      this->str = NULL;
      this->expr = expr;
    }

    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Breakstatement:public Statement
{
  public:
    Breakstatement()
    {
      this->return_type = 0;
    }
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Continuestatement:public Statement
{
  public:
    Continuestatement()
    {
      this->return_type = 0;
    }
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Returnstatement:public Statement
{
  public:
    class Expression* return_expr;
  public:
    Returnstatement(class Expression* expr)
    {
      this->return_expr = expr;
      this->return_type = 1;
    }
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Forstatement:public Statement
{
  public:
    char* var_name;
    class Expression* start;
    class Expression* end;
    class Block* forblock;
  public:
    Forstatement(char*,class Expression*,class Expression*,class Block*);
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Ifelsestatement:public Statement
{
  public:
    class Expression* expr;
    class Block* ifblock;
    class Block* elseblock;
  public:
    Ifelsestatement(class Expression*,class Block*,class Block*);
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Assignment:public Statement
{
  public:
    class Location* location;
    class Assign_op* assign_op;
    class Expression* expression;
  public:
    Assignment(class Location*,class Assign_op*,class Expression*);
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};

class Statements:public AstNode
{
  public:
    vector<class Statement*> statement_list;
  public:
    Statements()
    {
      this->statement_list.clear();
    }
    void push(class Statement* st)
    {
      this->statement_list.push_back(st);
    }
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Var_declaration:public AstNode
{
  public:
    char* var_type;
    vector<char*> id_list;
  public:
    Var_declaration(char* type)
    {
      this->var_type = type;
      this->id_list.clear();
    }
    void push(char* id)
    {
      this->id_list.push_back(id);
    }
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Var_declarations:public AstNode
{
  public:
    vector<class Var_declaration*> var_decl_list;
  public:
    Var_declarations()
    {
      this->var_decl_list.clear();
    }
    void push(class Var_declaration* vd)
    {
      this->var_decl_list.push_back(vd);
    }
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};

class Block:public Statement
{
  public:
    class Var_declarations* var_decls;
    class Statements* statements;
  public:
    Block(class Var_declarations* var_decls,class Statements* statements)
    {
      this->var_decls = var_decls;
      this->statements = statements;
    }
    void accept(Visitor *v)
    {
      v->visit(this);
    }
};
class Method_args:public AstNode
{
public:
  vector<param> method_arg_list;
public:
  Method_args()
  {
    this->method_arg_list.clear();
  }
  void push(char* type,char* id);
  void accept(Visitor *v)
  {
    v->visit(this);
  }
};
class Method_decl:public AstNode
{
public:
  char* return_type;
  char* method_name;
  class Method_args* method_args;
  class Block* block;
public:
  Method_decl(char*, char*, class Block*);
  Method_decl(char*, char*, class Method_args*,class Block*);
  void accept(Visitor *v)
  {
    v->visit(this);
  }
};
class Method_decls:public AstNode
{
public:
  vector<class Method_decl*> method_decl_list;
public:
  Method_decls()
  {
      this->method_decl_list.clear();
  }
  void push(class Method_decl* md)
  {
      this->method_decl_list.push_back(md);
      reverse(this->method_decl_list.begin(),this->method_decl_list.end());
  }
  void accept(Visitor *v)
  {
    v->visit(this);
  }
};

class Out_decls:public AstNode
{
public:
  vector<out_declaration> out_decl_list;
public:
  Out_decls()
  {
    this->out_decl_list.clear();
  }

  void push(char* id)
  {
    out_declaration out;
    out.var_name = id;
    out.size = 0;
    this->out_decl_list.push_back(out);
  }
  void push(char* id,int sz)
  {
    if(sz<=0)
    {
      cout<<"Parsing Over\n";
      cout<<"Error: Array "<<id<<" must have size greater than 0\n";
      exit(0);
    }
    out_declaration out;
    out.var_name = id;
    out.size = sz;
    this->out_decl_list.push_back(out);
  }
  void accept(Visitor *v)
  {
    v->visit(this);
  }
};
class Field_decl:public AstNode
{
public:
  char* type;
  class Out_decls* out_decls;
public:
  Field_decl(char* t,class Out_decls* ods)
  {
    this->type =t;
    this->out_decls = ods;
  }
  void accept(Visitor *v)
  {
    v->visit(this);
  }
};
class Field_decls:public AstNode
{
public:
  vector<class Field_decl*> field_decl_list;
public:
  Field_decls()
  {
      this->field_decl_list.clear();
  }
  void push(class Field_decl* fd)
  {
    this->field_decl_list.push_back(fd);
  }
  void accept(Visitor *v)
  {
    v->visit(this);
  }
};

class Program:public AstNode
{
public:
  class Field_decls* field_decls;
  class Method_decls* method_decls;
public:
  Program(class Field_decls* fd,class Method_decls* md)
  {
      this->field_decls = fd;
      this->method_decls = md;
  }

  void accept(Visitor *v)
  {
    v->visit(this);
  }
};
#endif
