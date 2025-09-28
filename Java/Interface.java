import java.util.Scanner;

// Interface
interface Vehicle {
    void gearChange(int gear);

    void speedUp(int increment);

    void applyBrakes(int decrement);

    void displayStatus();
}

// Bicycle class
class Bicycle implements Vehicle {
    int speed = 0;
    int gear = 1;

    @Override
    public void gearChange(int gear) {
        this.gear = gear;
        System.out.println("Bicycle gear changed to: " + this.gear);
    }

    @Override
    public void speedUp(int increment) {
        speed += increment;
        System.out.println("Bicycle speed increased to: " + speed + " km/h");
    }

    @Override
    public void applyBrakes(int decrement) {
        speed -= decrement;
        if (speed < 0)
            speed = 0;
        System.out.println("Bicycle speed decreased to: " + speed + " km/h");
    }

    @Override
    public void displayStatus() {
        System.out.println("Bicycle -> Gear: " + gear + ", Speed: " + speed + " km/h");
    }
}

// Car class
class Car implements Vehicle {
    int speed = 0;
    int gear = 1;

    @Override
    public void gearChange(int gear) {
        this.gear = gear;
        System.out.println("Car gear changed to: " + this.gear);
    }

    @Override
    public void speedUp(int increment) {
        speed += increment;
        System.out.println("Car speed increased to: " + speed + " km/h");
    }

    @Override
    public void applyBrakes(int decrement) {
        speed -= decrement;
        if (speed < 0)
            speed = 0;
        System.out.println("Car speed decreased to: " + speed + " km/h");
    }

    @Override
    public void displayStatus() {
        System.out.println("Car -> Gear: " + gear + ", Speed: " + speed + " km/h");
    }
}

// Bike class
class Bike implements Vehicle {
    int speed = 0;
    int gear = 1;

    @Override
    public void gearChange(int gear) {
        this.gear = gear;
        System.out.println("Bike gear changed to: " + this.gear);
    }

    @Override
    public void speedUp(int increment) {
        speed += increment;
        System.out.println("Bike speed increased to: " + speed + " km/h");
    }

    @Override
    public void applyBrakes(int decrement) {
        speed -= decrement;
        if (speed < 0)
            speed = 0;
        System.out.println("Bike speed decreased to: " + speed + " km/h");
    }

    @Override
    public void displayStatus() {
        System.out.println("Bike -> Gear: " + gear + ", Speed: " + speed + " km/h");
    }
}

// Main class (must match file name)
public class Interface {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Vehicle vehicle = null;
        int choice;

        do {
            System.out.println("\n----- VEHICLE MENU -----");
            System.out.println("1. Bicycle");
            System.out.println("2. Car");
            System.out.println("3. Bike");
            System.out.println("4. Exit");
            System.out.print("Choose your vehicle: ");
            choice = sc.nextInt();

            switch (choice) {
                case 1:
                    vehicle = new Bicycle();
                    break;
                case 2:
                    vehicle = new Car();
                    break;
                case 3:
                    vehicle = new Bike();
                    break;
                case 4:
                    System.out.println("Exiting... Thank you!");
                    break;
                default:
                    System.out.println("Invalid choice! Please try again.");
                    continue;
            }

            if (choice >= 1 && choice <= 3) {
                int action;
                do {
                    System.out.println("\n-- Actions for " + vehicle.getClass().getSimpleName() + " --");
                    System.out.println("1. Change Gear");
                    System.out.println("2. Speed Up");
                    System.out.println("3. Apply Brakes");
                    System.out.println("4. Show Status");
                    System.out.println("5. Back to Vehicle Menu");
                    System.out.print("Enter your action: ");
                    action = sc.nextInt();

                    switch (action) {
                        case 1:
                            System.out.print("Enter gear: ");
                            int g = sc.nextInt();
                            vehicle.gearChange(g);
                            break;
                        case 2:
                            System.out.print("Increase speed by: ");
                            int inc = sc.nextInt();
                            vehicle.speedUp(inc);
                            break;
                        case 3:
                            System.out.print("Decrease speed by: ");
                            int dec = sc.nextInt();
                            vehicle.applyBrakes(dec);
                            break;
                        case 4:
                            vehicle.displayStatus();
                            break;
                        case 5:
                            System.out.println("Returning to Vehicle Menu...");
                            break;
                        default:
                            System.out.println("Invalid action!");
                    }
                } while (action != 5);
            }

        } while (choice != 4);

        sc.close();
    }
}
