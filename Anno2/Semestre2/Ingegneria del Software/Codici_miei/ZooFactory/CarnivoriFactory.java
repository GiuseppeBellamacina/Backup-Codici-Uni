public class CarnivoriFactory implements ZooFactory {
    @Override
    public Animal createAnimal(String type) {
        if(type.equals("cicciogamer")) return new CiccioGamer();
        else if(type.equals("tigre")) return new Tigre();
        else return null;
    }
}
