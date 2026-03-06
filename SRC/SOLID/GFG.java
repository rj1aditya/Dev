
interface geo_object {
    double getVolume();
};

class Cuboid implements geo_object {
    public double length;
    public double breadth;
    public double height;

    public Cuboid(double l, double b, double h) {
        length = l;
        breadth = b;
        height = h;
    }

    public double getVolume() {
        return length * breadth * height;
    }
};

class Sphere implements geo_object {
    public double radius;

    public Sphere(double r) {
        radius = r;
    }

    public double getVolume() {
        return (4.0 / 3.0) * Math.PI * Math.pow(radius, 3);
    }
};

class Application {
    public static double totalVolume(geo_object[] objects) {
        double total = 0.0;
        for (geo_object obj : objects) {
            total += obj.getVolume();
        }
        return total;
    }
}

public class GFG {
    public static void main(String[] args) {
        Cuboid c = new Cuboid(3, 4, 5);
        Sphere s = new Sphere(3);
        geo_object[] objects = { c, s };
        System.out.println(Application.totalVolume(objects));
    }
}