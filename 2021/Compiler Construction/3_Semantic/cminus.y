/***************************************************/
/* File: tiny.y                                     */
/* The TINY Yacc/Bison specification file           */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/
%{
#define YYPARSER /* distinguishes Yacc output from other code files */

#include "globals.h"
#include "util.h"
#include "scan.h"
#include "parse.h"

#define YYSTYPE TreeNode *
//static char * savedName; /* for use in assignments */
//static int savedLineNo;  /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */
static int yylex(void);
static int yyerror(char*);

%}

%token IF ELSE WHILE RETURN
%token INT VOID
%token ID NUM
%token PLUS MINUS TIMES OVER SEMI COMMA LPAREN RPAREN LBRACE RBRACE LCURLY RCURLY
%token ASSIGN EQ NE LT LE GT GE
%token ERROR

%nonassoc RPAREN
%nonassoc ELSE

%% /* Grammar for TINY */

program     : decl_list
                 { savedTree = $1; } 
            ;
decl_list   : decl_list decl
                 { YYSTYPE t = $1;
                   if (t != NULL)
                   { while (t->sibling != NULL)
                        t = t->sibling;
                     t->sibling = $2;
                     $$ = $1; 
                   }
                   else $$ = $2;
                 }
            | decl  { $$ = $1; }
            ;
decl        : var_decl { $$ = $1; }
            | func_decl { $$ = $1; }
            ;
var_decl    : type_spec id SEMI
                { $$ = $1;
                  $$->kind.stmt = VarDeclK;
                  $$->attr.name = $2->attr.name;
                  $$->lineno = $2->lineno;
                }
            | type_spec id LBRACE num RBRACE SEMI
                { $$ = $1;
                  $$->kind.stmt = VarDeclK;
                  $$->attr.name = $2->attr.name;
                  $$->type += 2;
                  $$->lineno = $2->lineno;
                  $$->child[0] = newExpNode(ConstK);
                  $$->child[0]->attr.val = $4->attr.val;
                }
            ;
id          : ID
                { $$ = newExpNode(IdK);
                  $$->attr.name = copyString(tokenString);
                  $$->lineno = lineno;
                }
            ;
num         : NUM 
                { $$ = newExpNode(NumK); 
                  $$->attr.val = atoi(tokenString);
                }
            ;
type_spec   : INT
                { $$ = newStmtNode(ParamK);
                  $$->type = Integer;
                }
            | VOID
                { $$ = newStmtNode(ParamK);
                  $$->type = Void; 
                }
            ;
func_decl   : type_spec id LPAREN params RPAREN comp_stmt
                { $$ = $1;
                  $$->kind.stmt = FuncDeclK;
                  $$->attr.name = $2->attr.name;
                  $$->child[0] = $4;
                  $$->child[1] = $6;
                  $$->lineno = $2->lineno;
                }
            ;
params      : param_list { $$ = $1; }
            | VOID
                { $$ = newStmtNode(VoidParamK);
                  $$->lineno = lineno;
                }
            ;
param_list  : param_list COMMA param
                { YYSTYPE t = $1;
                  if (t != NULL)
                  { while (t->sibling != NULL)
                      t = t->sibling;
                    t->sibling = $3;
                    $$ = $1;
                  }
                  else $$ = $3;
                }
            | param { $$ = $1; }
            ;
param       : type_spec id
                { $$ = $1;
                  $$->attr.name = $2->attr.name;
                  $$->lineno = $2->lineno;
                }
            | type_spec id LBRACE RBRACE
                { $$ = $1;
                  $$->type = $1->type + 2;
                  $$->attr.name = $2->attr.name;
                  $$->lineno = $2->lineno;
                }
            ;
comp_stmt   : LCURLY local_decl stmt_list RCURLY
                { $$ = newStmtNode(CompK);
                  $$->child[0] = $2;
                  $$->child[1] = $3;
                }
            ;
local_decl  : local_decl var_decl
                { YYSTYPE t = $1;
                  if (t != NULL)
                  { while (t->sibling != NULL)
                      t = t->sibling;
                    t->sibling = $2;
                    $$ = $1;
                  }
                  else $$ = $2;
                }
            | { $$ = NULL; }
            ;
stmt_list   : stmt_list stmt
                { YYSTYPE t = $1;
                  if (t != NULL)
                  { while (t->sibling != NULL)
                      t = t->sibling;
                    t->sibling = $2;
                    $$ = $1;
                  }
                  else $$ = $2;
                }
            | { $$ = NULL; }
            ;
stmt        : exp_stmt { $$ = $1; }
            | comp_stmt { $$ = $1; }
            | selec_stmt { $$ = $1; }
            | iter_stmt { $$ = $1; }
            | return_stmt { $$ = $1; }
            ;
exp_stmt    : expression SEMI { $$ = $1; }
            | SEMI { $$ = NULL; }
            ;
selec_stmt  : IF LPAREN expression RPAREN stmt
                { $$ = newStmtNode(IfK);
                  $$->child[0] = $3;
                  $$->child[1] = $5;
                }
            | IF LPAREN expression RPAREN stmt ELSE stmt
                { $$ = newStmtNode(IfElseK);
                  $$->child[0] = $3;
                  $$->child[1] = $5;
                  $$->child[2] = $7;
                }
            ;
iter_stmt   : WHILE LPAREN expression RPAREN stmt
                { $$ = newStmtNode(WhileK);
                  $$->child[0] = $3;
                  $$->child[1] = $5;
                }
            ;
return_stmt : RETURN SEMI
                { $$ = newStmtNode(ReturnK); }
            | RETURN expression SEMI
                { $$ = newStmtNode(ReturnK);
                  $$->child[0] = $2;
                }
            ;
expression  : var ASSIGN expression
                { $$ = newExpNode(AssignK);
                  $$->child[0] = $1;
                  $$->child[1] = $3;
                }
            | simpl_exp { $$ = $1; }
            ;
var         : id
                { $$ = newExpNode(VarK);
                  $$->attr.name = $1->attr.name;
                }
            | id LBRACE expression RBRACE
                { $$ = newExpNode(VarK);
                  $$->attr.name = $1->attr.name;
                  $$->child[0] = $3; 
                }
            ;
simpl_exp   : addi_exp relop addi_exp
                { $$ = $2;
                  $$->child[0] = $1;
                  $$->child[1] = $3;
                }
            | addi_exp { $$ = $1; }
            ;
relop       : LE
                { $$ = newExpNode(OpK);
                  $$->attr.op = LE;
                }
            | LT
                { $$ = newExpNode(OpK);
                  $$->attr.op = LT;
                }
            | GT
                { $$ = newExpNode(OpK);
                  $$->attr.op = GT;
                }
            | GE
                { $$ = newExpNode(OpK);
                  $$->attr.op = GE;
                }
            | EQ
                { $$ = newExpNode(OpK);
                  $$->attr.op = EQ;
                }
            | NE
                { $$ = newExpNode(OpK);
                  $$->attr.op = NE;
                }
            ;
addi_exp    : addi_exp addop term
                { $$ = $2;
                  $$->child[0] = $1;
                  $$->child[1] = $3;
                }
            | term { $$ = $1; }
            ;
addop       : PLUS
                { $$ = newExpNode(OpK);
                  $$->attr.op = PLUS;
                }
            | MINUS
                { $$ = newExpNode(OpK);
                  $$->attr.op = MINUS;
                }
            ;
term        : term mulop factor
                { $$ = $2;
                  $$->child[0] = $1;
                  $$->child[1] = $3;
                }
            | factor { $$ = $1; }
            ;
mulop       : TIMES
                { $$ = newExpNode(OpK);
                  $$->attr.op = TIMES;
                }
            | OVER
                { $$ = newExpNode(OpK);
                  $$->attr.op = OVER;
                }
            ;
factor      : LPAREN expression RPAREN
                { $$ = $2; }
            | var { $$ = $1; }
            | call { $$ = $1; }
            | NUM 
                { $$ = newExpNode(ConstK);
                  $$->attr.val = atoi(tokenString);
                }
            ;
call        : id LPAREN args RPAREN
                { $$ = newExpNode(CallK);
                  $$->attr.name = $1->attr.name;
                  $$->child[0] = $3; 
                }
            ;
args        : arg_list { $$ = $1; }
            | { $$ = NULL; }
            ;
arg_list    : arg_list COMMA expression
                { YYSTYPE t = $1;
                  if (t != NULL)
                  { while (t->sibling != NULL)
                      t = t->sibling;
                    t->sibling = $3;
                    $$ = $1;
                  }
                  else $$ = $3;
                }
            | expression { $$ = $1; }
            ;

%%

int yyerror(char * message)
{ fprintf(listing,"Syntax error at line %d: %s\n",lineno,message);
  fprintf(listing,"Current token: ");
  printToken(yychar,tokenString);
  Error = TRUE;
  return 0;
}

/* yylex calls getToken to make Yacc/Bison output
 * compatible with ealier versions of the TINY scanner
 */
static int yylex(void)
{ return getToken(); }

TreeNode * parse(void)
{ yyparse();
  return savedTree;
}

