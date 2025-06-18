package Interfejsi;

public class BelgradeFactory implements IFactory {
    private String name;

    BelgradeFactory(String n) {
        name = n;
    }

    @Override
    public String getFactoryName() {
        return name;
    }

    @Override
    public void startWork() {
        System.out.println(name + " start!");
        System.out.println("work started!");
    }

    @Override
    public void endWork() {
        System.out.println(name + " end!");
    }
}
