import java.util.Scanner;
import java.util.regex.*;
import java.text.DecimalFormat;

public class hw1 {
    private static final DecimalFormat df = new DecimalFormat("0.00");

    public static void main(String args[]) {
        int number; // The number of scores read.
        int sum; // The summation of all the scores read.
        int grade; // Holds each individual score as it is read from the keyboard.
        double average; // Holds the computed average.
        String input;
        String pattern = "[^\\d\\+\\-]";
        Pattern p = Pattern.compile(pattern);
        Matcher m;

        Scanner sc = new Scanner(System.in);
        number = 0;
        sum = 0;
        while (true) {
            System.out.println("Please input your score:");
            input = sc.nextLine();
            m = p.matcher(input);
            if (m.find()) {
                System.out.println("illegal input, ending the program...");
                System.exit(1);
            }
            try {
                grade = Integer.valueOf(input);
            } catch(NumberFormatException ex) {
                System.out.println("illegal input, ending the program...");
                grade = 0;
                System.exit(1);
            }
            if (grade == -1) {
                break;
            } else if (grade < 0 || grade > 100) {
                System.out.println("illegal input, ending the program...");
                System.exit(1);
            } else {
                sum += grade;
                ++number;
            }
        }
        average = (double) sum / number;
        System.out.println("The average is " + df.format(average) + ".");
        sc.close();
    }
}
