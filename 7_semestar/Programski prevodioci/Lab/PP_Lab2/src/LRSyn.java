import java.io.*;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Deque;
import java.util.List;

enum rules_sym {
	IS,
	EP,
	RE,
	EX,
	T
}

public class LRSyn {

	String inputPath;
    Lab2NR19347 lexer;
    Deque<Integer> stack = new ArrayDeque<Integer>();
    ArrayList<Rule> rules;
    
    // Tabela simbola sastavljena iz akcija i prelaza
    action[][] actions;
    int[][] goTo = new int[20][5];

    public LRSyn(String inputPath) {
        try {
        	this.inputPath = inputPath;
            Reader reader = new FileReader(inputPath);
            lexer = new Lab2NR19347(reader);
            rules = new ArrayList<Rule>();
            initializeRules();
            initializeActions();
            initializeGoTo();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    int top() {
    	return stack.peek();
    }
    
    void push(int x) {
    	stack.push(x);
    }
    
    int pop() {
    	return stack.pop();
    }
    
    void initializeRules() {
    	rules.add(new Rule(1, "IS", "if ( RE ) : EX EP"));
    	rules.add(new Rule(2, "EP", "else : EX"));
    	rules.add(new Rule(3, "RE", "T > T"));
    	rules.add(new Rule(4, "RE", "T"));
    	rules.add(new Rule(5, "EX", "EX * T"));
    	rules.add(new Rule(6, "EX", "T"));
    	rules.add(new Rule(7, "T", "ID"));
    	rules.add(new Rule(8, "T", "CONST"));
    }
    
    void initializeActions() {
    	actions = new action[20][sym.HASH+1];
    	
    	for(int i = 0; i < 20; i++) {
    		for(int j = 0; j < sym.HASH+1; j++)
    		{
    			actions[i][j] = new action(action_type.ERR);
    		}
    	}
    	
    	actions[0][sym.IF] = new action(action_type.SK, 2);
    	
    	actions[1][sym.HASH] = new action(action_type.ACC);
    	
    	actions[2][sym.LEFTPAR] = new action(action_type.SK, 3);
    	
    	actions[3][sym.ID] = new action(action_type.SK, 6);
    	actions[3][sym.CONST] = new action(action_type.SK, 7);
    	
    	actions[4][sym.RIGHTPAR] = new action(action_type.SK, 8);
    	
    	actions[5][sym.RIGHTPAR] = new action(action_type.RK, 4);
    	actions[5][sym.MORE] = new action(action_type.SK, 9);
    	
    	actions[6][sym.RIGHTPAR] = new action(action_type.RK, 7);
    	actions[6][sym.ELSE] = new action(action_type.RK, 7);
    	actions[6][sym.MORE] = new action(action_type.RK, 7);
    	actions[6][sym.MULTIPLY] = new action(action_type.RK, 7);
    	actions[6][sym.HASH] = new action(action_type.RK, 7);
    	
    	actions[7][sym.RIGHTPAR] = new action(action_type.RK, 8);
    	actions[7][sym.ELSE] = new action(action_type.RK, 8);
    	actions[7][sym.MORE] = new action(action_type.RK, 8);
    	actions[7][sym.MULTIPLY] = new action(action_type.RK, 8);
    	actions[7][sym.HASH] = new action(action_type.RK, 8);
    	
    	actions[8][sym.COLON] = new action(action_type.SK, 10);
    	
    	actions[9][sym.ID] = new action(action_type.SK, 6);
    	actions[9][sym.CONST] = new action(action_type.SK, 7);
    	
    	actions[10][sym.ID] = new action(action_type.SK, 6);
    	actions[10][sym.CONST] = new action(action_type.SK, 7);
    	
    	actions[11][sym.RIGHTPAR] = new action(action_type.RK, 3);
    	
    	actions[12][sym.ELSE] = new action(action_type.SK, 16);
    	actions[12][sym.MULTIPLY] = new action(action_type.SK, 15);
    	
    	actions[13][sym.ELSE] = new action(action_type.RK, 6);
    	actions[13][sym.MULTIPLY] = new action(action_type.RK, 6);
    	actions[13][sym.HASH] = new action(action_type.RK, 6);
    	
    	actions[14][sym.HASH] = new action(action_type.RK, 1);
    	
    	actions[15][sym.ID] = new action(action_type.SK, 6);
    	actions[15][sym.CONST] = new action(action_type.SK, 7);
    	
    	actions[16][sym.COLON] = new action(action_type.SK, 18);
    	
    	actions[17][sym.ELSE] = new action(action_type.RK, 5);
    	actions[17][sym.MULTIPLY] = new action(action_type.RK, 5);
    	actions[17][sym.HASH] = new action(action_type.RK, 5);
    	
    	actions[18][sym.ID] = new action(action_type.SK, 6);
    	actions[18][sym.CONST] = new action(action_type.SK, 7);
    	
    	actions[19][sym.MULTIPLY] = new action(action_type.SK, 15);
    	actions[19][sym.HASH] = new action(action_type.RK, 2);
    }
    
    void initializeGoTo() {
    	goTo[0][rules_sym.IS.ordinal()] = 1;
    	goTo[3][rules_sym.RE.ordinal()] = 4;
    	goTo[3][rules_sym.T.ordinal()] = 5;
    	goTo[9][rules_sym.T.ordinal()] = 11;
    	goTo[10][rules_sym.EX.ordinal()] = 12;
    	goTo[10][rules_sym.T.ordinal()] = 13;
    	goTo[12][rules_sym.EP.ordinal()] = 14;
    	goTo[15][rules_sym.T.ordinal()] = 17;
    	goTo[18][rules_sym.EX.ordinal()] = 19;
    	goTo[18][rules_sym.T.ordinal()] = 13;
    }

    public boolean SA_LR() throws IOException {
    	
    	Yytoken current_token;

    	push(0);
    	boolean found = false;
    	boolean error = false;
    	current_token = lexer.generate_token();
    	
    	do {
    		action current_action = actions[top()][current_token.m_index];
    		System.out.println("\n\nTop: " + top() + "\nToken : " + current_token.m_text + " [" + current_token.m_index + "]\n" + "Akcija: " + current_action.type.toString() + " " + current_action.state + "\n\n");
    		
    		switch (current_action.type) {
	    		case action_type.SK:
	    			push(current_token.m_index);
	    			push(current_action.state);
	    			current_token = lexer.generate_token();
	    			break;
	    		case action_type.RK:
	    			int k = current_action.state; //State ovde zapravo ukazuje na redni broj pravila na osnovu kog redukujemo
	    			for(int i = 0; i < rules.get(k-1).ruleSize(); i++) { // get(k-1) zato sto lista krece od indeksa 0, pa ako mi je potrebno pravilo 1, pristupam mu na 1-1=0 poziciji liste
	    				pop(); //Za stanje
	    				pop(); // Za simbol
	    			}
	    			int top_state = top();
	    			System.out.println("\nPravilo: " + k + " je: " + rules.get(k-1).left + " -> " + rules.get(k-1).right + " | Top stack-a: " + top() + " | Obrisano je " + rules.get(k-1).ruleSize() * 2 + " simbola\n");
	    			
	    			Rule r = rules.get(k-1); //Ponovo, ako je akcija r7, pravilo 7 mi treba, a ono je na mesto 7-1=6 u listi
	    			String rule_left = r.left; //Uzimam levu stranu pravila, recimo IS ili slicno
	    			int rule_left_index = rules_sym.valueOf(rule_left).ordinal(); //Trazim indeks tog neterminala u matrici goTo, koja je to kolona
	    			push(rule_left_index);
	    			
	    			int new_state = goTo[top_state][rule_left_index];
	    			push(new_state);
	    			
	    			break;
	    		case action_type.ACC:
	    			found = true;
	    			break;
	    		case action_type.ERR:
	    			error = true;
	    			System.out.println("trenutna akcija:" + current_action.ToString());
	    			break;
    		}
    		
    	} while(!found && !error);
    	    	  	
    	return found;
    }
}