// KORISNICKI KOD
import java_cup.runtime.*;

%% 

// OPCIJE I DEKLARACIJE

%class MPLexer
%function next_token
%type java_cup.runtime.Symbol
%implements java_cup.runtime.Scanner

%line
%column

%{
	public int getLine()
	{
		return yyline;
	}
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
<INT_OSNOVA_2>[0-1]+ { yybegin(YYINITIAL); int val = Integer.parseInt(yytext(), 2); return new Symbol(sym.INTCONST, yyline, yycolumn, val);}
<INT_OSNOVA_2>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova2" + yytext() ); yybegin(YYINITIAL);}

"3#" {yybegin(INT_OSNOVA_3);}
<INT_OSNOVA_3>[0-2]+ { yybegin(YYINITIAL); int val = Integer.parseInt(yytext(), 3); return new Symbol(sym.INTCONST, yyline, yycolumn, val);}
<INT_OSNOVA_3>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova3" + yytext() ); yybegin(YYINITIAL);}

"4#" {yybegin(INT_OSNOVA_4);}
<INT_OSNOVA_4>[0-3]+ { yybegin(YYINITIAL); int val = Integer.parseInt(yytext(), 4); return new Symbol(sym.INTCONST, yyline, yycolumn, val);}
<INT_OSNOVA_4>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova4" + yytext() ); yybegin(YYINITIAL);}

"5#" {yybegin(INT_OSNOVA_5);}
<INT_OSNOVA_5>[0-4]+ { yybegin(YYINITIAL); int val = Integer.parseInt(yytext(), 5); return new Symbol(sym.INTCONST, yyline, yycolumn, val);}
<INT_OSNOVA_5>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova5" + yytext() ); yybegin(YYINITIAL);}

"6#" {yybegin(INT_OSNOVA_6);}
<INT_OSNOVA_6>[0-5]+ { yybegin(YYINITIAL); int val = Integer.parseInt(yytext(), 6); return new Symbol(sym.INTCONST, yyline, yycolumn, val);}
<INT_OSNOVA_6>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova6" + yytext() ); yybegin(YYINITIAL);}

"7#" {yybegin(INT_OSNOVA_7);}
<INT_OSNOVA_7>[0-6]+ { yybegin(YYINITIAL); int val = Integer.parseInt(yytext(), 7); return new Symbol(sym.INTCONST, yyline, yycolumn, val);}
<INT_OSNOVA_7>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova7" + yytext() ); yybegin(YYINITIAL);}

"8#" {yybegin(INT_OSNOVA_8);}
<INT_OSNOVA_8>[0-7]+ { yybegin(YYINITIAL); int val = Integer.parseInt(yytext(), 8); return new Symbol(sym.INTCONST, yyline, yycolumn, val);}
<INT_OSNOVA_8>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova8" + yytext() ); yybegin(YYINITIAL);}

"9#" {yybegin(INT_OSNOVA_9);}
<INT_OSNOVA_9>[0-8]+ { yybegin(YYINITIAL); int val = Integer.parseInt(yytext(), 9); return new Symbol(sym.INTCONST, yyline, yycolumn, val);}
<INT_OSNOVA_9>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR:osnova9" + yytext() ); yybegin(YYINITIAL);}

"10#" {yybegin(INT_OSNOVA_10);}
<INT_OSNOVA_10>{cifra}+ { yybegin(YYINITIAL); int val = Integer.parseInt(yytext(), 10); return new Symbol(sym.INTCONST, yyline, yycolumn, val);}
<INT_OSNOVA_10>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova10" + yytext() ); yybegin(YYINITIAL);}

"11#" {yybegin(INT_OSNOVA_11);}
<INT_OSNOVA_11>[0-9Aa]+ { yybegin(YYINITIAL); int val = Integer.parseInt(yytext(), 11); return new Symbol(sym.INTCONST, yyline, yycolumn, val);}
<INT_OSNOVA_11>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova11" + yytext() ); yybegin(YYINITIAL);}

"12#" {yybegin(INT_OSNOVA_12);}
<INT_OSNOVA_12>[0-9ABab]+ { yybegin(YYINITIAL); int val = Integer.parseInt(yytext(), 12); return new Symbol(sym.INTCONST, yyline, yycolumn, val);}
<INT_OSNOVA_12>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova12" + yytext() ); yybegin(YYINITIAL);}

"13#" {yybegin(INT_OSNOVA_13);}
<INT_OSNOVA_13>[0-9A-Ca-c]+ { yybegin(YYINITIAL); int val = Integer.parseInt(yytext(), 13); return new Symbol(sym.INTCONST, yyline, yycolumn, val);}
<INT_OSNOVA_13>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova13" + yytext() ); yybegin(YYINITIAL);}

"14#" {yybegin(INT_OSNOVA_14);}
<INT_OSNOVA_14>[0-9A-Da-d]+ { yybegin(YYINITIAL); int val = Integer.parseInt(yytext(), 14); return new Symbol(sym.INTCONST, yyline, yycolumn, val);}
<INT_OSNOVA_14>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova14" + yytext() ); yybegin(YYINITIAL);}

"15#" {yybegin(INT_OSNOVA_15);}
<INT_OSNOVA_15>[0-9A-Ea-e]+ { yybegin(YYINITIAL); int val = Integer.parseInt(yytext(), 15); return new Symbol(sym.INTCONST, yyline, yycolumn, val);}
<INT_OSNOVA_15>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: osnova15" + yytext() ); yybegin(YYINITIAL);}

"16#"|# {yybegin(INT_OSNOVA_16);}
<INT_OSNOVA_16>[0-9A-Fa-f]+ { yybegin(YYINITIAL); int val = Integer.parseInt(yytext(), 16); return new Symbol(sym.INTCONST, yyline, yycolumn, val);}
<INT_OSNOVA_16>. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR osnova16: " + yytext() ); yybegin(YYINITIAL);}

{cifra}+ {return new Symbol(sym.INTCONST, yyline, yycolumn, new Integer(yytext()));}

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
"<>" {return new Symbol(sym.NOTEQUAL);}
"<=" {return new Symbol(sym.LESSOREQUAL);}
"<" {return new Symbol(sym.LESS);}
"==" {return new Symbol(sym.EQUAL);}

//KLJUCNE RECI
"main" {return new Symbol(sym.MAIN);}
"int" {return new Symbol(sym.INT);}
"real" {return new Symbol(sym.REAL);}
"boolean" {return new Symbol(sym.BOOLEAN);}
"if" {return new Symbol(sym.IF);}
"else" {return new Symbol(sym.ELSE);}
"elif" {return new Symbol(sym.ELIF);}

//BOOLEAN CONST 
true {return new Symbol(sym.BOOLCONST, yyline, yycolumn, Boolean.TRUE);}
false {return new Symbol(sym.BOOLCONST,yyline, yycolumn, Boolean.FALSE);}

//ID
[a-zA-Z][a-zA-Z0-9]* {return new Symbol(sym.ID, yyline, yycolumn, yytext());}

//REAL CONST
[0-9]+\.[0-9]*(E[+-]?[0-9]+)? {return new Symbol(sym.REALCONST, yyline, yycolumn, new Double(yytext()));}

//GRESKE
. {if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: " + yytext() );}



