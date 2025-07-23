package ApstraktneKlase;

public class Kvadrat extends Figura {

    private double a;

    Kvadrat(String ime, String boja, double a) {
        super(boja, ime);
        this.a = a;
    }

    public double povrsina() {
        return a*a;
    }
}
