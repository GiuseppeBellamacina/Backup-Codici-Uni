public class Description {
    GameFactory factory;
    
    public Description(GameFactory factory) {
        this.factory = factory;
    }

    public void printDesc() {
        Game cus = factory.getCus();
        Game dysc = factory.getDysc();
        cus.show();
        dysc.show();
    }
}
