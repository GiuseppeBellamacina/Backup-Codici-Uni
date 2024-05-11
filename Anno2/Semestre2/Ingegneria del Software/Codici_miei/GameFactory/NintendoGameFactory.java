public class NintendoGameFactory implements GameFactory {
    @Override
    public Game getCus() {
        return new NintendoGameCus();
    }
    @Override
    public Game getDysc() {
        return new NintendoGameDysc();
    }
}
