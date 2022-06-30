// import java.io.*;
import java.util.Scanner;

public class Add {
    public static void main(String args[]) {
        String amtStr;
        double num1 = 0.0, num2 = 0.0, tot = 0.0;
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the first number: ");
        amtStr = sc.next();
        // try to convert amt String to double for calculation
        try {
            // num1 = new Double(amtStr).doubleValue();  // The constructor Double(string) is deprecated since version 9.
            num1 = Double.valueOf(amtStr);
        } catch (NumberFormatException e) {
            System.out.println("Bad numeric input; 1st num set to 100");
            num1 = 100;
        }
        System.out.println("Enter the second number: ");
        amtStr = sc.next();
        try {
            // num2 = new Double(amtStr).doubleValue();
            num2 = Double.valueOf(amtStr);
        } catch (NumberFormatException e) {
            System.out.println("Bad numeric input; 2nd num set to 50");
            num1 = 50;
        }
        
        tot = num1 + num2;
        System.out.println("Sum is: " + tot);
        
        sc.close();
    }  // end main
}  // end of class Add
