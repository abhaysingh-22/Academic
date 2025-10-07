import java.util.Scanner;

// Base class
class Publication {
    protected String title;
    protected double price;
    protected int copies;

    public Publication(String title, double price) {
        this.title = title;
        this.price = price;
        this.copies = 0;
    }

    public double saleCopy(int number) {
        copies += number;
        return number * price;
    }
}

// Book class
class Book extends Publication {
    private String author;

    public Book(String title, double price, String author) {
        super(title, price);
        this.author = author;
    }

    public double orderCopies(int number) {
        return saleCopy(number);
    }

    public void displayInfo() {
        System.out.println("Book: " + title + " by " + author + " | Price: Rs." + price + " | Total copies sold: " + copies);
    }
}

// Magazine class
class Magazine extends Publication {
    private int orderQty;
    private String currentIssue;

    public Magazine(String title, double price, String currentIssue) {
        super(title, price);
        this.currentIssue = currentIssue;
    }

    public double receiveIssue(int qty) {
        this.orderQty = qty;
        return saleCopy(qty);
    }

    public void displayInfo() {
        System.out.println("Magazine: " + title + " | Issue: " + currentIssue + " | Price: Rs." + price + " | Total copies sold: " + copies + " | Last order quantity: " + orderQty);
    }
}

// Main class (must match filename)
public class Polymorphism {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Create one book and one magazine
        Book book = new Book("Java Programming", 500, "Herbert Schildt");
        Magazine magazine = new Magazine("Tech World", 100, "September 2025");

        double totalSales = 0;
        int choice;

        do {
            System.out.println("\n----- MENU -----");
            System.out.println("1. Order Book Copies");
            System.out.println("2. Order Magazine Copies");
            System.out.println("3. Display Total Publication Sales");
            System.out.println("4. Display Book Info");
            System.out.println("5. Display Magazine Info");
            System.out.println("6. Exit");
            System.out.print("Enter your choice: ");
            choice = sc.nextInt();

            switch (choice) {
                case 1:
                    System.out.print("Enter number of book copies to order: ");
                    int bookCopies = sc.nextInt();
                    double bookSales = book.orderCopies(bookCopies);
                    totalSales += bookSales;
                    System.out.println(bookCopies + " copies of Book ordered. Sales = Rs." + bookSales);
                    break;

                case 2:
                    System.out.print("Enter number of magazine copies to order: ");
                    int magCopies = sc.nextInt();
                    double magSales = magazine.receiveIssue(magCopies);
                    totalSales += magSales;
                    System.out.println(magCopies + " copies of Magazine ordered. Sales = Rs." + magSales);
                    break;

                case 3:
                    System.out.println("Total Publication Sales = Rs." + totalSales);
                    break;

                case 4:
                    book.displayInfo();
                    break;

                case 5:
                    magazine.displayInfo();
                    break;

                case 6:
                    System.out.println("Exiting... Thank you!");
                    break;

                default:
                    System.out.println("Invalid choice! Please try again.");
            }
        } while (choice != 6);

        sc.close();
    }
}
