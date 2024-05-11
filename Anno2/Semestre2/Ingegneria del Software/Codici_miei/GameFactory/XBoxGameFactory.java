public class XBoxGameFactory implements GameFactory {
    @Override
    public Game getCus() {
        return new XBoxGameCus();
    }
    @Override
    public Game getDysc() {
        return new XBoxGameDysc();
    }
}
