#include<bits/stdc++.h>
#include "classes.h"

using namespace std;

extern Visitor *Vis;
int errors;


map<string,Var_data> Global_Map,Local_Map;
map<string,int> Functions;


int convert(char* type)
{
  if(strcmp(type,"int")==0)
    return 1;
  else if(strcmp(type,"boolean")==0)
    return 0;
  else
    return 2;
}

                            //Constructors

Method_decl::Method_decl(char* type,char* id,class Block* bl)
{
   if(Functions.find(id)!=Functions.end())
   {
     cout<<"function: "<<id<<" already declared\n";
     exit(0);
   }
   Functions[id] = convert(type);
   this->return_type = type;
   this->method_name = id;
   this->method_args = NULL;
   this->block = bl;
}
Method_decl::Method_decl(char* type,char* id,class Method_args* ma,class Block* bl)
{
   if(Functions.find(id)!=Functions.end())
   {
      cout<<"function: "<<id<<" already declared\n";
      exit(0);
   }
   Functions[id] = convert(type);
   this->return_type = type;
   this->method_name = id;
   this->method_args = ma;
   this->block = bl;

}
void Method_args::push(char* type,char* id)
{
  param p;
  p.type = type;
  p.id = id;
  this->method_arg_list.push_back(p);
}

Forstatement::Forstatement(char* var_name,class Expression* start,class Expression* end,class Block* forblock)
{
  this->var_name = var_name;
  this->start = start;
  this->end = end;
  this->forblock = forblock;
  this->return_type = 0;
}
Ifelsestatement::Ifelsestatement(class Expression* expr,class Block* ifblock,class Block* elseblock)
{
  this->expr = expr;
  this->ifblock = ifblock;
  this->elseblock = elseblock;
  this->return_type = 0;
}
Assignment::Assignment(class Location* loc,class Assign_op* assign_op,class Expression* expr)
{
  this->location = loc;
  this->assign_op = assign_op;
  this->expression = expr;
  this->return_type = 0;
}
Location::Location(char* var_name)
{
  this->var_name = var_name;
  this->type = 0;
  this->expr_type = 2;
}
Location::Location(char* var_name,class Expression* index)
{
  this->var_name = var_name;
  this->type = 1;
  this->index = index;
  this->expr_type = 2;
}
BinaryExpression::BinaryExpression(class Expression* lhs,char* op,class Expression* rhs)
{
  this->lhs = lhs;
  this->op = op;
  this->rhs = rhs;
  this->expr_type = 0;
  if(strcmp(op,"+")==0 || strcmp(op,"-")==0 || strcmp(op,"*")==0 || strcmp(op,"/")==0 || strcmp(op,"%")==0)
    this->type = 0;
  else if(strcmp(op,"<")==0 || strcmp(op,">")==0 || strcmp(op,"<=")==0 || strcmp(op,">=")==0)
    this->type = 1;
  else if(strcmp(op,"==")==0 || strcmp(op,"!=")==0)
    this->type = 2;
  else
    this->type = 3;
}
UnaryExpression::UnaryExpression(char* op,class Expression* rhs)
{
  this->op = op;
  this->rhs = rhs;
  this->expr_type = 1;
}
Literal::Literal(int type,int int_value)
{
  this->type = type;
  this->int_value = int_value;
  this->expr_type = 3;
  this->r_type = 1;
}
Literal::Literal(int type,char* bool_value)
{
  this->type = type;
  this->bool_value = bool_value;
  this->expr_type = 3;
  this->r_type = 0;
}
Literal::Literal(int type,char char_value)
{
  this->type = type;
  this->char_value = char_value;
  this->expr_type = 3;
  this->r_type = 2;
}
                                        //Traverse Visit
void Traverse::visit(class Program* pr)
{
  (pr->field_decls)->accept(this);
  (pr->method_decls)->accept(this);
}
void Traverse::visit(class Field_decls* fds)
{
  for(int i=0;i<(fds->field_decl_list).size();i++)
  {
    (fds->field_decl_list[i])->accept(this);
  }
}
void Traverse::visit(class Field_decl* fd)
{
  (fd->out_decls)->accept(this);
  out_declaration out;
  char* t;
  t = fd->type;
  for(int i=0;i<((fd->out_decls)->out_decl_list).size();i++)
  {
    Var_data var_data;
    var_data.int_values.clear();
    var_data.bool_values.clear();
    out = (fd->out_decls)->out_decl_list[i];

    if(Global_Map.find(out.var_name)!=Global_Map.end())
    {
      cout<<"Variable name: "<<out.var_name<<" Already used\n";
      exit(0);
    }
    var_data.data_type = t;
    if(strcmp(t,"int")==0)
    {
      if(out.size==0)
      {
        var_data.int_value = 0;
      }
      else
      {
        var_data.int_values.resize(out.size);
      }
    }
    else
    {
      if(out.size==0)
      {
        var_data.bool_value = 0;
      }
      else
      {
        var_data.bool_values.resize(out.size);
      }
    }
    Global_Map[out.var_name] = var_data;
  }
}
void Traverse::visit(class Method_decls* mds)
{
  for(int i=0;i<(mds->method_decl_list).size();i++)
  {
    (mds->method_decl_list[i])->accept(this);
  }
}
void Traverse::visit(class Method_decl* md)
{
  Local_Map.clear();
  if(md->method_args)
  {
    md->method_args->accept(this);
  }
  (md->block)->accept(this);
}
void Traverse::visit(class Method_args* margs)
{
  param p;
  for(int i=0;i<(margs->method_arg_list).size();i++)
  {
    p = margs->method_arg_list[i];
    if(Local_Map.find(p.id)!=Local_Map.end())
    {
      cout<<"Variable name: "<<p.id<<" Already used\n";
      exit(0);
    }
    Var_data vardata;
    vardata.data_type = p.type;
    Local_Map[p.id] = vardata;
  }
}
void Traverse::visit(class Block* bl)
{
  (bl->var_decls)->accept(this);
  (bl->statements)->accept(this);
}
void Traverse::visit(class Var_declarations* vds)
{
  for(int i=0;i<(vds->var_decl_list).size();i++)
  {
    (vds->var_decl_list[i])->accept(this);
  }
}
void Traverse::visit(class Var_declaration* vd)
{
  char* type = vd->var_type;
  Var_data vardata;
  vardata.data_type = type;
  for(int i=0;i<(vd->id_list).size();i++)
  {
    char* id = vd->id_list[i];
    if(Local_Map.find(id)!=Local_Map.end())
    {
      cout<<"Variable name: "<<id<<" Already used\n";
      exit(0);
    }
    Local_Map[id] = vardata;
  }
}
void Traverse::visit(class Statements* sts)
{
  for(int i=0;i<(sts->statement_list).size();i++)
  {
    (sts->statement_list[i])->accept(this);
  }
}
void Traverse::visit(class Assignment* as)
{
  (as->location)->accept(this);
  (as->assign_op)->accept(this);
  (as->expression)->accept(this);
  if((as->location)->r_type != (as->expression)->r_type)
  {
    cout<<"location and expression doesnt have same type\n";
    exit(0);
  }
}
void Traverse::visit(class Ifelsestatement* ifelse)
{
  (ifelse->expr)->accept(this);
  (ifelse->ifblock)->accept(this);
  if(ifelse->elseblock)
    (ifelse->elseblock)->accept(this);
  if((ifelse->expr)->r_type==1)
  {
    cout<<"Boolean value expected inside if statement\n";
    exit(0);
  }
}
void Traverse::visit(class Forstatement* forst)
{
  (forst->start)->accept(this);
  (forst->end)->accept(this);
  (forst->forblock)->accept(this);
}
void Traverse::visit(class Returnstatement* ret)
{
  if(ret->return_expr)
      (ret->return_expr)->accept(this);
}
void Traverse::visit(class Calloutarg* car)
{
  if((car->expr)!=NULL)
    (car->expr)->accept(this);
}
void Traverse::visit(class Calloutcall* ccall)
{
  (ccall->calloutargs)->accept(this);
}
void Traverse::visit(class Calloutargs* cargs)
{
  for(int i=0;i<(cargs->calloutarg_list).size();i++)
  {
    (cargs->calloutarg_list[i])->accept(this);
  }
}
void Traverse::visit(class Expressionscall* expr_call)
{
  if(expr_call->expressions)
      (expr_call->expressions)->accept(this);
  expr_call->r_type = Functions[expr_call->method_name];
}
void Traverse::visit(class Expressions* exprs)
{
  for(int i=0;i<(exprs->expressions_list).size();i++)
  {
    (exprs->expressions_list[i])->accept(this);
  }
}
void Traverse::visit(class Location* loc)
{
  if(Local_Map.find(loc->var_name)!=Local_Map.end())
  {
    if(strcmp(Local_Map[loc->var_name].data_type,"int")==0)
      loc->r_type = 1;
    else
      loc->r_type = 0;
  }
  else if(Global_Map.find(loc->var_name)!=Global_Map.end())
  {
    if(strcmp(Global_Map[loc->var_name].data_type,"int")==0)
      loc->r_type = 1;
    else
      loc->r_type = 0;
  }
  else
  {
    cout<<"Variable: "<<loc->var_name<<" not declared\n";
    exit(0);
  }
  if(loc->type==1)
    (loc->index)->accept(this);
}
void Traverse::visit(class BinaryExpression* bexp)
{
  (bexp->lhs)->accept(this);
  (bexp->rhs)->accept(this);
  if(bexp->type==0 || bexp->type==1)
  {
    if((bexp->lhs)->r_type!=1 || (bexp->rhs)->r_type!=1)
    {
      cout<<"Invalid use of operator: "<<bexp->op<<" both operands must have type int "<<endl;
      exit(0);
    }
    bexp->r_type = 1-bexp->type;
  }
  else if(bexp->type==2)
  {
    if((bexp->lhs)->r_type==2 || (bexp->rhs)->r_type==2 || (bexp->lhs)->r_type!=(bexp->rhs)->r_type)
    {
      cout<<"Invalid use of operator: "<<bexp->op<<"both operands have same type, either int or boolean"<<endl;
      exit(0);
    }
    bexp->r_type = 0;
  }
  else if(bexp->type==3)
  {
    if((bexp->lhs)->r_type!=0 || (bexp->rhs)->r_type!=0)
    {
      cout<<"Invalid use of operator: "<<bexp->op<<" both operands must be of type boolean"<<endl;
      exit(0);
    }
    bexp->r_type = 0;
  }
}
void Traverse::visit(class UnaryExpression* unexp)
{
  (unexp->rhs)->accept(this);
  if(strcmp(unexp->op,"!")==0)
  {
    if((unexp->rhs)->r_type!=0)
    {
      cout<<"Invalid use of operator: "<<unexp->op<<" must have boolean expression on right side"<<endl;
      exit(0);
    }
    unexp->r_type = 0;
  }
}
