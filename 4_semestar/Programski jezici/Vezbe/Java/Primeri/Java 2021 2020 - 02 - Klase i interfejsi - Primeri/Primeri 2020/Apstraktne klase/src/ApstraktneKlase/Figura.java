package ApstraktneKlase;

abstract public class Figura {

    protected String boja;
    protected String ime;

    Figura(String b, String i) {
        ime = i;
        boja = b;
    }

    abstract public double povrsina();
}
