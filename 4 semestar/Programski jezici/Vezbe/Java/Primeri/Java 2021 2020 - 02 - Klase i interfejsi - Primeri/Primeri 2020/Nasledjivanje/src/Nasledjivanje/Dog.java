package Nasledjivanje;

public class Dog extends Animal {

    Dog(String name) {
        super(name);
    }

    public void bark() {
        System.out.println(name + " is barking...");
    }

    public void survive() {
        System.out.println("DOG!");
    }
}
