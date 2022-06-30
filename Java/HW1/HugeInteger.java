import java.text.ParseException;
import java.util.ArrayList;

public class HugeInteger {
    private ArrayList<Short> num;
    private ArrayList<Short> carry;
    private boolean sign;

    // Check if the input string is a valid integer.
    private boolean checkValid(String s) {
        boolean sign = false;
        for (int i = 0; i < s.length(); ++i) {
            if ((s.charAt(i) == '+' || s.charAt(i) == '-') && !sign) {
                sign = true;
            } else if (s.charAt(i) < '0' || s.charAt(i) > '9') {
                return false;
            } else { // 2-1 is invalid.
                sign = true;
            }
        }
        return true;
    }

    // Remove the redundant 0 of string
    private String trim(String s) {
        String out = "";
        int start_pos = 0;
        boolean redundant_zero = true;

        if (s.charAt(start_pos) == '-') {
            out += '-';
            ++start_pos;
        } else if (s.charAt(start_pos) == '+') {
            out += '+';
            ++start_pos;
        } else {
            out += '+';
        }

        for (int i = start_pos; i < s.length(); ++i) {
            if (s.charAt(i) == '0' && redundant_zero) {
                continue;
            }
            redundant_zero = false;
            out += s.charAt(i);
        }
        return out;
    }

    // Expand the string to MAXLEN with extra 0 and set it in members.
    private void setNum(String s) {
        int i, j;

        if (MAXLEN - s.length() + 1 < 0) {
            System.err.println("Error, the input " + s + " is too long, the max size is " + MAXLEN + ".");
            return;
        }
        switch (s.charAt(0)) {
            case '+':
                this.sign = POSITIVE;
                break;
            case '-':
                this.sign = NEGATIVE;
                break;
            default:
                break;
        }
        for (i = 0; i < MAXLEN - s.length() + 1; ++i) {
            this.num.set(i, (short) 0);
        }
        for (j = 1; j < s.length(); ++j) {
            this.num.set(i++, (short) (s.charAt(j) - '0'));
        }
    }

    private void setCarryZero() {
        for (int i = 0; i < MAXLEN; ++i) {
            this.carry.set(i, (short) 0);
        }
    }

    private boolean isNumGreaterThan(HugeInteger h) {
        for (int i = 0; i < MAXLEN; i++) {
            if (this.num.get(i) != h.num.get(i)) {
                return this.num.get(i) > h.num.get(i);
            }
        }
        return false;
    }

    private void numAdd(HugeInteger h) {
        short c, s;
        s = (short) (this.num.get(MAXLEN - 1) + h.num.get(MAXLEN - 1));
        c = (short) (s / 10);
        s = (short) (s % 10);
        this.num.set(MAXLEN - 1, s);
        this.carry.set(MAXLEN - 1, c);
        
        for (int i = MAXLEN - 2; i >= 0; --i) {
            s = (short) (this.num.get(i) + h.num.get(i) + this.carry.get(i + 1));
            c = (short) (s / 10);
            s = (short) (s % 10);
            this.num.set(i, s);
            this.carry.set(i, c);
        }
        if (this.carry.get(0) != 0) {
            throw new ArithmeticException("Overflow occured");
        }
    }

    private void numSub(HugeInteger h) {
        short b, d;

        if (isNumGreaterThan(h)) {
            d = (short) (this.num.get(MAXLEN - 1) - h.num.get(MAXLEN - 1));
            if (d < 0) {
                d += 10;
                b = 1;
            } else {
                b = 0;
            }
            this.num.set(MAXLEN - 1, d);
            this.carry.set(MAXLEN - 1, b);
            for (int i = MAXLEN - 2; i >= 0; --i) {
                d = (short) (this.num.get(i) - h.num.get(i) - this.carry.get(i + 1));
                if (d < 0) {
                    d += 10;
                    b = 1;
                } else {
                    b = 0;
                }
                this.num.set(i, d);
                this.carry.set(i, b);
            }
        } else {
            this.sign = !this.sign;
            d = (short) (h.num.get(MAXLEN - 1) - this.num.get(MAXLEN - 1));
            if (d < 0) {
                d += 10;
                b = 1;
            } else {
                b = 0;
            }
            this.num.set(MAXLEN - 1, d);
            this.carry.set(MAXLEN - 1, b);
            for (int i = MAXLEN - 2; i >= 0; --i) {
                d = (short) (h.num.get(i) - this.num.get(i) - this.carry.get(i + 1));
                if (d < 0) {
                    d += 10;
                    b = 1;
                } else {
                    b = 0;
                }
                this.num.set(i, d);
                this.carry.set(i, b);
            }
        }
    }

    public static boolean POSITIVE = false;
    public static boolean NEGATIVE = true;
    public static int MAXLEN = 40;

    public HugeInteger() {
        this.num = new ArrayList<Short>();
        this.carry = new ArrayList<Short>();
        for (int i = 0; i < MAXLEN; ++i) {
            this.num.add((short) 0);
            this.carry.add((short) 0);
        }
        this.sign = POSITIVE;
    }

    public HugeInteger(String s) throws ParseException {
        this.num = new ArrayList<Short>();
        this.carry = new ArrayList<Short>();
        for (int i = 0; i < MAXLEN; ++i) {
            this.num.add((short) 0);
            this.carry.add((short) 0);
        }
        parse(s);
    }

    public void setNumZero() {
        for (int i = 0; i < MAXLEN; ++i) {
            this.num.set(i, (short) 0);
        }
    }

    // Parse a string into a char array.
    public void parse(String s) throws ParseException {
        if (checkValid(s)) {
            s = trim(s);
            setNum(s);
        } else {
            throw new ParseException("Error, " + s + " is invalid", 0);
            // System.err.println("Error, " + s + " is invalid, ignoring.");
        }
    }

    // Print number, removing redundant 0, and only print sign when negative
    public void printNum() {
        boolean redundant_zero = true;

        if (this.sign == NEGATIVE) {
            System.out.print('-');
        }
        for (int i = 0; i < this.num.size(); ++i) {
            if (this.num.get(i) == 0 && redundant_zero) {
                continue;
            }
            redundant_zero = false;
            System.out.print(this.num.get(i));
        }
        if (redundant_zero) { // If the number is exactly zero
            System.out.print(0);
        }
        System.out.print('\n');
    }

    // Print all message include sign and redundant 0
    public void printNumAll() {
        if (this.sign == NEGATIVE) {
            System.out.print('-');
        } else {
            System.out.print('+');
        }
        for (int i = 0; i < this.num.size(); ++i) {
            System.out.print(this.num.get(i));
        }
        System.out.print('\n');
    }

    public boolean isEqualTo(HugeInteger h) {
        return this.sign == h.sign && this.num.equals(h.num);
    }

    public boolean isGreaterThan(HugeInteger h) {
        if (this.sign != h.sign) {
            return this.sign == POSITIVE;
        }
        for (int i = 0; i < MAXLEN; i++) {
            if (this.num.get(i) != h.num.get(i)) {
                return this.num.get(i) > h.num.get(i) != h.sign;
            }
        }
        return false;
    }

    public boolean isGreaterThanOrEqualTo(HugeInteger h) {
        return this.isEqualTo(h) || this.isGreaterThan(h);
    }

    public boolean isLessThan(HugeInteger h) {
        return !this.isGreaterThanOrEqualTo(h);
    }

    public boolean isLessThanOrEqualTo(HugeInteger h) {
        return !this.isGreaterThan(h);
    }

    // Perform add and set the result to the caller class instance
    public void add(HugeInteger h) {
        setCarryZero();
        if (this.sign == h.sign) {
            numAdd(h);
        } else {
            numSub(h);
        }
    }

    public void subtract(HugeInteger h) {
        setCarryZero();
        if (this.sign == h.sign) {
            numSub(h);
        } else {
            numAdd(h);
        }
    }

    public static void main(String[] args) throws ParseException {
        HugeInteger h1 = new HugeInteger("1999999999999999999999999999999999999999");
        HugeInteger h2 = new HugeInteger("9111111111111111111111111111111111111111");
        try {
            h1.subtract(h2);
        } catch (ArithmeticException e) {
            System.err.println(e);
        }
        
        h1.printNum();
    }
}
