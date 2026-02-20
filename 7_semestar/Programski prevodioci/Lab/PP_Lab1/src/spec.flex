// KORISNICKI KOD

%% 

// OPCIJE I DEKLARACIJE

%class MPLexer
%function next_token
%type java_cup.runtime.Symbol
%implements java_cup.runtime.Scanner

%line
%column
%debug

%{

%}

%eofval{
	return new Symbol(sym.EOF);
%eofval}

//STANJA
%xstate KOMENTAR
%xstate INT_OSNOVA_2
%xstate INT_OSNOVA_3
%xstate INT_OSNOVA_4
%xstate INT_OSNOVA_5
%xstate INT_OSNOVA_6
%xstate INT_OSNOVA_7
%xstate INT_OSNOVA_8
%xstate INT_OSNOVA_9
%xstate INT_OSNOVA_10
%xstate INT_OSNOVA_11
%xstate INT_OSNOVA_12
%xstate INT_OSNOVA_13
%xstate INT_OSNOVA_14
%xstate INT_OSNOVA_15
%xstate INT_OSNOVA_16

//MAKROI
slovo = [a-zA-Z]
cifra = [0-9]

%%

//LEKSICKA PRAVILA

"/**" {yybegin(KOMENTAR);}
<KOMENTAR>~"*/" {yybegin(YYINITIAL);}


//INT CONST
"2#" {yybegin(INT_OSNOVA_2);} 
<INT_OSNOVA_2>[0-1]+ { yybegin(YYINITIAL); return new Symbol(sym.CONST);}
<INT_OSNOVA_2>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova2" + yytext() ); yybegin(YYINITIAL);}

"3#" {yybegin(INT_OSNOVA_3);}
<INT_OSNOVA_3>[0-2]+ { yybegin(YYINITIAL); return new Symbol(sym.CONST);}
<INT_OSNOVA_3>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova3" + yytext() ); yybegin(YYINITIAL);}

"4#" {yybegin(INT_OSNOVA_4);}
<INT_OSNOVA_4>[0-3]+ { yybegin(YYINITIAL); return new Symbol(sym.CONST);}
<INT_OSNOVA_4>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova4" + yytext() ); yybegin(YYINITIAL);}

"5#" {yybegin(INT_OSNOVA_5);}
<INT_OSNOVA_5>[0-4]+ { yybegin(YYINITIAL); return new Symbol(sym.CONST);}
<INT_OSNOVA_5>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova5" + yytext() ); yybegin(YYINITIAL);}

"6#" {yybegin(INT_OSNOVA_6);}
<INT_OSNOVA_6>[0-5]+ { yybegin(YYINITIAL); return new Symbol(sym.CONST);}
<INT_OSNOVA_6>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova6" + yytext() ); yybegin(YYINITIAL);}

"7#" {yybegin(INT_OSNOVA_7);}
<INT_OSNOVA_7>[0-6]+ { yybegin(YYINITIAL); return new Symbol(sym.CONST);}
<INT_OSNOVA_7>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova7" + yytext() ); yybegin(YYINITIAL);}

"8#" {yybegin(INT_OSNOVA_8);}
<INT_OSNOVA_8>[0-7]+ { yybegin(YYINITIAL); return new Symbol(sym.CONST);}
<INT_OSNOVA_8>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova8" + yytext() ); yybegin(YYINITIAL);}

"9#" {yybegin(INT_OSNOVA_9);}
<INT_OSNOVA_9>[0-8]+ { yybegin(YYINITIAL); return new Symbol(sym.CONST);}
<INT_OSNOVA_9>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR:osnova9" + yytext() ); yybegin(YYINITIAL);}

"10#" {yybegin(INT_OSNOVA_10);}
<INT_OSNOVA_10>{cifra}+ { yybegin(YYINITIAL); return new Symbol(sym.CONST);}
<INT_OSNOVA_10>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova10" + yytext() ); yybegin(YYINITIAL);}

"11#" {yybegin(INT_OSNOVA_11);}
<INT_OSNOVA_11>[0-9Aa]+ { yybegin(YYINITIAL); return new Symbol(sym.CONST);}
<INT_OSNOVA_11>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova11" + yytext() ); yybegin(YYINITIAL);}

"12#" {yybegin(INT_OSNOVA_12);}
<INT_OSNOVA_12>[0-9ABab]+ { yybegin(YYINITIAL); return new Symbol(sym.CONST);}
<INT_OSNOVA_12>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova12" + yytext() ); yybegin(YYINITIAL);}

"13#" {yybegin(INT_OSNOVA_13);}
<INT_OSNOVA_13>[0-9A-Ca-c]+ { yybegin(YYINITIAL); return new Symbol(sym.CONST);}
<INT_OSNOVA_13>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova13" + yytext() ); yybegin(YYINITIAL);}

"14#" {yybegin(INT_OSNOVA_14);}
<INT_OSNOVA_14>[0-9A-Da-d]+ { yybegin(YYINITIAL); return new Symbol(sym.CONST);}
<INT_OSNOVA_14>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova14" + yytext() ); yybegin(YYINITIAL);}

"15#" {yybegin(INT_OSNOVA_15);}
<INT_OSNOVA_15>[0-9A-Ea-e]+ { yybegin(YYINITIAL); return new Symbol(sym.CONST);}
<INT_OSNOVA_15>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova15" + yytext() ); yybegin(YYINITIAL);}

"16#"|# {yybegin(INT_OSNOVA_16);}
<INT_OSNOVA_16>[0-9A-Fa-f]+ { yybegin(YYINITIAL); return new Symbol(sym.CONST);}
<INT_OSNOVA_16>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR osnova16: " + yytext() ); yybegin(YYINITIAL);}

{cifra}+ {return new Symbol(sym.CONST);}

//OPERATORI, SEPARATORI, BLANKO

[\t\n\r ] {;}
\( {return new Symbol(sym.LEFTPAR);}
\) {return new Symbol(sym.RIGHTPAR);}
\{ {return new Symbol(sym.LEFTCURLYBR);}
\} {return new Symbol(sym.RIGHTCURLYBR);}
; {return new Symbol(sym.SEMICOLON);}
: {return new Symbol(sym.COLON);}
":=" {return new Symbol(sym.ASSIGN);}
">=" {return new Symbol(sym.MOREOREQUAL);}
> {return new Symbol(sym.MORE);}
"<>" {return new Symbol(sym.NOTEUQAL);}
"<=" {return new Symbol(sym.LESSOREUQAL);}
"<" {return new Symbol(sym.LESS);}
"==" {return new Symbol(sym.EUQAL);}

//KLJUCNE RECI
"main" {return new Symbol(sym.MAIN);}
"int" {return new Symbol(sym.INT);}
"real" {return new Symbol(sym.REAL);}
"boolean" {return new Symbol(sym.BOOLEAN);}
"if" {return new Symbol(sym.IF);}
"else" {return new Symbol(sym.ELSE);}
"elif" {return new Symbol(sym.ELIF);}

//BOOLEAN CONST 
//true|false mozemo tretirati i kao kljucne reci
//ako ih ne tretiramo kao kljucne reci, moramo navesti pravilo
//pre keyword pravila da ne bi bilo obuhvaceno u keyword i vracen ID
true {return new Symbol(sym.CONST);}
false {return new Symbol(sym.CONST);}

//ID
[a-zA-Z][a-zA-Z0-9]* {return new Symbol(sym.ID);}

//REAL CONST
[0-9]+\.[0-9]*(E[+-]?[0-9]+)? {return new Symbol(sym.CONST);}

//GRESKE
. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: " + yytext() );}



