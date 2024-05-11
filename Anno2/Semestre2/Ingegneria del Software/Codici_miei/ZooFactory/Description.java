public class Description {
    ZooFactory factory;
    
    public Description(ZooFactory factory) {
        this.factory = factory;
    }

    public void printDesc(String type) {
        Animal an = factory.createAnimal(type);
        an.eat();
        an.sleep();
    }
}
