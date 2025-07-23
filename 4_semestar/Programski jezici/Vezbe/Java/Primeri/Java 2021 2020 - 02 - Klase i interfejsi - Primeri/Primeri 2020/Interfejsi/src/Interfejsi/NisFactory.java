package Interfejsi;

public class NisFactory implements IFactory {
    private String name;

    NisFactory(String n) {
        name = n;
    }

    @Override
    public String getFactoryName() {
        return name;
    }

    @Override
    public void startWork() {
        System.out.println(name + " start!");
        this.pauseWork();
    }

    @Override
    public void endWork() {
        System.out.println(name + " end!");
    }

    public void pauseWork() {
        System.out.println(name + " pause!");
        System.out.println("Cigarette break");
    }
}
