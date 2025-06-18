package Interfejsi;

public class MainClass {
    public static void main(String[] args) {
        IFactory factory1 = new BelgradeFactory("Beogradska fabrika");
        IFactory factory2 = new NisFactory("Niska fabrika");
        NisFactory fact1 = new NisFactory("Niska fabrika 2");
        fact1.pauseWork();
        IFactory[] fabrike = new IFactory[3];
        fabrike[0] = new NisFactory("a");
        fabrike[1] = new BelgradeFactory("b");
        fabrike[2] = new NisFactory("c");
        for(IFactory f: fabrike) {
            f.startWork();
            f.endWork();
        }
    }
}
