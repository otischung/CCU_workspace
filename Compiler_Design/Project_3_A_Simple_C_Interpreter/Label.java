public class Label {
    private static int labelIdx = 0;

    public static String next() {
        return "L" + (labelIdx++);
    }

}
