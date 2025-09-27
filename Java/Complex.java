import java.util.Scanner;

class Complex {
    private double real;
    private double imag;

    // Default constructor
    public Complex() {
        this.real = 0.0;
        this.imag = 0.0;
    }

    // Parameterized constructor
    public Complex(double real, double imag) {
        this.real = real;
        this.imag = imag;
    }

    // Addition
    public Complex add(Complex c) {
        return new Complex(this.real + c.real, this.imag + c.imag);
    }

    // Subtraction
    public Complex subtract(Complex c) {
        return new Complex(this.real - c.real, this.imag - c.imag);
    }

    // Multiplication
    public Complex multiply(Complex c) {
        double r = this.real * c.real - this.imag * c.imag;
        double i = this.real * c.imag + this.imag * c.real;
        return new Complex(r, i);
    }

    // Division
    public Complex divide(Complex c) {
        double denominator = c.real * c.real + c.imag * c.imag;
        if (denominator == 0) {
            System.out.println("Error: Division by zero is not possible!");
            return new Complex(0, 0);
        }
        double r = (this.real * c.real + this.imag * c.imag) / denominator;
        double i = (this.imag * c.real - this.real * c.imag) / denominator;
        return new Complex(r, i);
    }

    // Display
    public void display() {
        if (imag >= 0) {
            System.out.println(real + " + " + imag + "i");
        } else {
            System.out.println(real + " - " + (-imag) + "i");
        }
    }

    // Main method
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Take input for first complex number
        System.out.print("Enter real part of first complex number: ");
        double r1 = sc.nextDouble();
        System.out.print("Enter imaginary part of first complex number: ");
        double i1 = sc.nextDouble();
        Complex c1 = new Complex(r1, i1);

        // Take input for second complex number
        System.out.print("Enter real part of second complex number: ");
        double r2 = sc.nextDouble();
        System.out.print("Enter imaginary part of second complex number: ");
        double i2 = sc.nextDouble();
        Complex c2 = new Complex(r2, i2);

        int choice;
        do {
            System.out.println("\n----- MENU -----");
            System.out.println("1. Add");
            System.out.println("2. Subtract");
            System.out.println("3. Multiply");
            System.out.println("4. Divide");
            System.out.println("5. Exit");
            System.out.print("Enter your choice: ");
            choice = sc.nextInt();

            switch (choice) {
                case 1:
                    System.out.print("Sum: ");
                    c1.add(c2).display();
                    break;
                case 2:
                    System.out.print("Difference: ");
                    c1.subtract(c2).display();
                    break;
                case 3:
                    System.out.print("Product: ");
                    c1.multiply(c2).display();
                    break;
                case 4:
                    System.out.print("Quotient: ");
                    c1.divide(c2).display();
                    break;
                case 5:
                    System.out.println("Exiting... Thank you!");
                    break;
                default:
                    System.out.println("Invalid choice! Please try again.");
            }
        } while (choice != 5);

        sc.close();
    }
}
