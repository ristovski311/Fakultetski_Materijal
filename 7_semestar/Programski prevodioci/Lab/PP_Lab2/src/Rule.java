
public class Rule {

	int number;
	String left;
	String right;
	
	public Rule(int num, String l, String r) {
		left = l;
		right = r;
		number = num;
	}
	
	String[] tokenizeRight() {
		String[] tokens = right.split("\\s+");
		return tokens;
	}
	
	public int ruleSize() {
		return tokenizeRight().length;
	}
 }
