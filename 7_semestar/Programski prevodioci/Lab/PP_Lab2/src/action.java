
enum action_type {
	SK,
	RK,
	ERR,
	ACC
}

public class action {
	action_type type;
	int state;

	public action(action_type type, int state) {
		this.type = type;
		this.state = state;
	}
	public action(action_type type) {
		this.type = type;
		this.state = -1;
	}
	public String ToString() {
		return type.toString() + " " + state;
 	}
}
