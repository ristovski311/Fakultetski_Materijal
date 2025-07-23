package Nasledjivanje;

public class Cat extends Animal {

    Cat(String name) {
        super(name);
    }

    public void meow() {
        System.out.println(name + " is meowing...");
    }

    public void survive() {
        System.out.println("CAT!");
    }
}
