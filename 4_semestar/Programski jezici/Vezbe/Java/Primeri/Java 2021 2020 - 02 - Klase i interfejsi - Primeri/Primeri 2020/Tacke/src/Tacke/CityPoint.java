package Tacke;

public class CityPoint extends Point {
	
    private String name;
    private long population;
    
    CityPoint(float x, float y, String n, long p) {
        super(x, y);
        name = n;
        population = p;
    }

    CityPoint() { super(2.1f, 3.5f); }

    public void printData() {
    	super.printData();
        System.out.println(name);
        System.out.println(population);
    }

    public static void main(String[] args) {
        CityPoint p1 = new CityPoint(1.2f, 3.5f, "ime", 10000);
        CityPoint p2 = new CityPoint(1.5f, 3.8f, "ime2", 20000);
        float d = p1.distance(p2);
        System.out.println(d);
        p1.printData();
        p2.printData();
    }
}
