import java.util.Scanner;

// Base class
abstract class Shape {
    double dim1, dim2;

    Shape(double dim1, double dim2) {
        this.dim1 = dim1;
        this.dim2 = dim2;
    }

    // Abstract method
    abstract void compute_area();
}

// Derived class for Triangle
class Triangle extends Shape {
    Triangle(double base, double height) {
        super(base, height);
    }

    @Override
    void compute_area() {
        double area = 0.5 * dim1 * dim2;
        System.out.println("Area of Triangle = " + area);
    }
}

// Derived class for Rectangle
class Rectangle extends Shape {
    Rectangle(double length, double breadth) {
        super(length, breadth);
    }

    @Override
    void compute_area() {
        double area = dim1 * dim2;
        System.out.println("Area of Rectangle = " + area);
    }
}

// Main class (must match file name)
public class DynamicBinding {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int choice;

        do {
            System.out.println("\n----- MENU -----");
            System.out.println("1. Area of Triangle");
            System.out.println("2. Area of Rectangle");
            System.out.println("3. Exit");
            System.out.print("Enter your choice: ");
            choice = sc.nextInt();

            Shape shape = null;

            switch (choice) {
                case 1:
                    System.out.print("Enter base of triangle: ");
                    double base = sc.nextDouble();
                    System.out.print("Enter height of triangle: ");
                    double height = sc.nextDouble();
                    shape = new Triangle(base, height); // dynamic binding
                    shape.compute_area();
                    break;

                case 2:
                    System.out.print("Enter length of rectangle: ");
                    double length = sc.nextDouble();
                    System.out.print("Enter breadth of rectangle: ");
                    double breadth = sc.nextDouble();
                    shape = new Rectangle(length, breadth); // dynamic binding
                    shape.compute_area();
                    break;

                case 3:
                    System.out.println("Exiting... Thank you!");
                    break;

                default:
                    System.out.println("Invalid choice! Please try again.");
            }
        } while (choice != 3);

        sc.close();
    }
}
