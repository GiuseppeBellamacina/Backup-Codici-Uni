public class ErbivoriFactory implements ZooFactory {
    @Override
    public Animal createAnimal(String type) {
        if(type.equals("capibara")) return new Capibara();
        else if(type.equals("tano")) return new Tano();
        else return null;
    }
}
