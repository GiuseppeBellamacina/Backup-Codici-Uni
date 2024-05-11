// javac *.java
// java Main <erbivori/carnivori/dinosauri> <type>

public class Main {
    public static void main(String[] args) {
        ZooFactory factory;
        if (args.length == 0) {
            System.out.println("No animal");
            return;
        } else if (args[0].equals("erbivori")) {
            factory = new ErbivoriFactory();
        } else if (args[0].equals("carnivori")) {
            factory = new CarnivoriFactory();
        } else if (args[0].equals("dinosauri")) {
            factory = new DinosauriFactory();
        } else {
            System.out.println("Invalid console");
            return;
        }

        String type = args[1];

        Description desc = new Description(factory);
        desc.printDesc(type);
    }   
}