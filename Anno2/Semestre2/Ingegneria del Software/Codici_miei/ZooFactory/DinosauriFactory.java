public class DinosauriFactory implements ZooFactory {
    @Override
    public Animal createAnimal(String type) {
        if(type.equals("tiresso")) return new TiResso();
        else if(type.equals("brachio")) return new Brachiosauro();
        else return null;
    }
}
