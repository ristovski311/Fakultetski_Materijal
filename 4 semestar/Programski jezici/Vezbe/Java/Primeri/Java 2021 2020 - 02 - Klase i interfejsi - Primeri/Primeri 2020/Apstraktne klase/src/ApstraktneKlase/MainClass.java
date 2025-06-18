package ApstraktneKlase;

public class MainClass {
    public static void main(String[] args) {
        Figura f = new Kvadrat("kvadrat", "crvena", 1.3);
        System.out.println(f.povrsina());
        Figura p = new Pravougaonik("pravougaonik", "zelena", 2.4, 3.5);
        p.povrsina();
    }
}
