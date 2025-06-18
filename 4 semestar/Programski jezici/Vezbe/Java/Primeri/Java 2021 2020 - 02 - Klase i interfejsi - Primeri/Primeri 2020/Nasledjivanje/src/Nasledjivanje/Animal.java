package Nasledjivanje;

public class Animal {
    public String name;

    public Animal(String name) {
        this.name = name;
    }

    public void eat() {
        System.out.println(name + " is eating...");
    }

    public void survive() {
        System.out.println(name + " is surviving...");
    }
}
