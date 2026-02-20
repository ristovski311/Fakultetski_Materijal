

// Ristovski Nikola 19347 - Zadatak 2

/* Prepoznate kljucne reci:
 * 
 * main
 * int
 * real
 * boolean
 * if
 * elif
 * else
 * true
 * false
 * 
 * Prepoznati separatori:
 * 
 * (
 * )
 * {
 * }
 * ;
 * :
 * 
 * Prepoznati operatori:
 * 
 * :=
 * <
 * <=
 * ==
 * <>
 * >
 * >=
 * 
 * Identifikatori: ID
 * 
 * Niz slova i cifara, prvi znak ne moze da bude cifra
 * [a-zA-Z][a-zA-Z0-9]*
 * 
 * Konstante: CONST
 * 
 * 1. format - tipa int
 * posebna stanja
 * 
 * 2. format - tipa real
 * [0-9]+\.[0-9]*(E[+-]?[0-9]+)?
 * 
 * 3. format - tipa boolean
 * true|false
 * 
 * Komentari:
 * \/\*\* ... \*\/
 * 
 * */


public class sym {

	public final static int EOF = 0;
	public final static int MAIN = 1;
	public final static int INT = 2;
	public final static int REAL = 3;
	public final static int BOOLEAN = 4;
	public final static int IF = 5;
	public final static int ELIF = 6;
	public final static int ELSE = 7;
	//public final static int TRUE = 8;
	//public final static int FALSE = 9;
	public final static int ID = 10;
	public final static int CONST = 11;
	public final static int ASSIGN = 12;
	public final static int LESS = 13;
	public final static int LESSOREQUAL = 14;
	public final static int EQUAL = 15;
	public final static int NOTEQUAL = 16;
	public final static int MORE = 17;
	public final static int MOREOREQUAL = 18;
	public final static int LEFTPAR = 19;
	public final static int RIGHTPAR = 20;
	public final static int LEFTCURLYBR = 21;
	public final static int RIGHTCURLYBR= 22;
	public final static int COLON = 23;
	public final static int SEMICOLON = 24;
}
