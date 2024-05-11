public class PSGameFactory implements GameFactory {
    @Override
    public Game getCus() {
        return new PSGameCus();
    }
    @Override
    public Game getDysc() {
        return new PSGameDysc();
    }
}
