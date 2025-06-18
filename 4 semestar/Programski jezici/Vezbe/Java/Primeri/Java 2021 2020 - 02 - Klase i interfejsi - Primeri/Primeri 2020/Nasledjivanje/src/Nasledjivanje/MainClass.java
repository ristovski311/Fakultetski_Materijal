package Nasledjivanje;

public class MainClass {
    public static void main(String[] args) {
        Animal cat = new Cat("macka1");
        Animal dog = new Dog("pas");
        Cat cat2 = new Cat("maca");
        Dog dog2 = new Dog("lesi");
        cat.eat();
        cat.survive();
        dog.eat();
        dog.survive();
        cat2.eat();
        cat2.meow();
        cat2.survive();
        dog2.eat();
        dog2.bark();
        dog2.survive();
    }
}
