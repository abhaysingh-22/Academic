import java.util.Scanner;

// Base class
class Employee {
    String empName, empId, address, mailId;
    long mobileNo;
    double basicPay;

    public Employee(String empName, String empId, String address, String mailId, long mobileNo, double basicPay) {
        this.empName = empName;
        this.empId = empId;
        this.address = address;
        this.mailId = mailId;
        this.mobileNo = mobileNo;
        this.basicPay = basicPay;
    }

    public void generatePaySlip() {
        double da = 0.97 * basicPay;
        double hra = 0.10 * basicPay;
        double pf = 0.12 * basicPay;
        double staffClubFund = 0.001 * basicPay;

        double grossSalary = basicPay + da + hra;
        double netSalary = grossSalary - (pf + staffClubFund);

        System.out.println("\n----- SALARY SLIP -----");
        System.out.println("Employee Name: " + empName);
        System.out.println("Employee ID: " + empId);
        System.out.println("Address: " + address);
        System.out.println("Mail ID: " + mailId);
        System.out.println("Mobile No: " + mobileNo);
        System.out.println("Basic Pay: Rs." + basicPay);
        System.out.println("DA (97%): Rs." + da);
        System.out.println("HRA (10%): Rs." + hra);
        System.out.println("PF (12%): Rs." + pf);
        System.out.println("Staff Club Fund (0.1%): Rs." + staffClubFund);
        System.out.println("Gross Salary: Rs." + grossSalary);
        System.out.println("Net Salary: Rs." + netSalary);
        System.out.println("------------------------\n");
    }
}

// Derived classes
class Programmer extends Employee {
    public Programmer(String empName, String empId, String address, String mailId, long mobileNo, double basicPay) {
        super(empName, empId, address, mailId, mobileNo, basicPay);
    }
}

class TeamLead extends Employee {
    public TeamLead(String empName, String empId, String address, String mailId, long mobileNo, double basicPay) {
        super(empName, empId, address, mailId, mobileNo, basicPay);
    }
}

class AssistantProjectManager extends Employee {
    public AssistantProjectManager(String empName, String empId, String address, String mailId, long mobileNo,
            double basicPay) {
        super(empName, empId, address, mailId, mobileNo, basicPay);
    }
}

class ProjectManager extends Employee {
    public ProjectManager(String empName, String empId, String address, String mailId, long mobileNo, double basicPay) {
        super(empName, empId, address, mailId, mobileNo, basicPay);
    }
}

// Main class (must match filename)
public class Inheritance {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int choice;

        do {
            System.out.println("\n----- EMPLOYEE PAYROLL MENU -----");
            System.out.println("1. Programmer");
            System.out.println("2. Team Lead");
            System.out.println("3. Assistant Project Manager");
            System.out.println("4. Project Manager");
            System.out.println("5. Exit");
            System.out.print("Enter your choice: ");
            choice = sc.nextInt();
            sc.nextLine(); // clear buffer

            if (choice >= 1 && choice <= 4) {
                // Collect employee details
                System.out.print("Enter Employee Name: ");
                String name = sc.nextLine();
                System.out.print("Enter Employee ID: ");
                String id = sc.nextLine();
                System.out.print("Enter Address: ");
                String addr = sc.nextLine();
                System.out.print("Enter Mail ID: ");
                String mail = sc.nextLine();
                System.out.print("Enter Mobile No: ");
                long mobile = sc.nextLong();
                System.out.print("Enter Basic Pay: ");
                double basicPay = sc.nextDouble();

                Employee emp = null;
                switch (choice) {
                    case 1:
                        emp = new Programmer(name, id, addr, mail, mobile, basicPay);
                        break;
                    case 2:
                        emp = new TeamLead(name, id, addr, mail, mobile, basicPay);
                        break;
                    case 3:
                        emp = new AssistantProjectManager(name, id, addr, mail, mobile, basicPay);
                        break;
                    case 4:
                        emp = new ProjectManager(name, id, addr, mail, mobile, basicPay);
                        break;
                }

                if (emp != null) {
                    emp.generatePaySlip();
                }
            } else if (choice == 5) {
                System.out.println("Exiting... Thank you!");
            } else {
                System.out.println("Invalid choice! Please try again.");
            }
        } while (choice != 5);

        sc.close();
    }
}
