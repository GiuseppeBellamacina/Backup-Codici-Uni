// javac *.java
// java Main ps - nintendo - xbox

public class Main {
    public static void main(String[] args) {
        GameFactory factory;
        if (args.length == 0) {
            System.out.println("No console specified");
            return;
        } else if (args[0].equals("ps")) {
            factory = new PSGameFactory();
        } else if (args[0].equals("nintendo")) {
            factory = new NintendoGameFactory();
        } else if (args[0].equals("xbox")) {
            factory = new XBoxGameFactory();
        } else {
            System.out.println("Invalid console");
            return;
        }

        Description desc = new Description(factory);
        desc.printDesc();
    }   
}