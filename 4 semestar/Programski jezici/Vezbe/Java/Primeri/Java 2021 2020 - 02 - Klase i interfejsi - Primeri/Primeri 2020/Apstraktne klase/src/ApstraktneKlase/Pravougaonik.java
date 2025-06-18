package ApstraktneKlase;

public class Pravougaonik extends Figura {
    private double a;
    private double b;

    Pravougaonik(String name, String color, double a, double b) {
        super(color, name);
        this.a = a;
        this.b = b;
    }
    public double povrsina() {
        return a*b;
    }
}
