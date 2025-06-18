package Tacke;

public class Point {
    protected float x;
    protected float y;

    Point(float a, float b) {
        x = a;
        y = b;
    }

    float distance(Point p) {
        return (float) (Math.sqrt(Math.pow(x-p.x, 2) + Math.pow(y-p.y, 2)));
    }

    void printData() {
        System.out.println("X je " + x + " y je " + y) ;
    }
}
