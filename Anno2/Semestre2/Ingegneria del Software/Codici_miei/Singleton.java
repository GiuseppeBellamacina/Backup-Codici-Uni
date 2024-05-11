public class Singleton{
    private static Singleton instance = null;
    private int value;

    private Singleton(){
        System.out.println("Singleton instance created");
    }

    public static Singleton getInstance(){
        if(instance == null){
            instance = new Singleton();
        }
        return instance;
    }

    public void setValue(int value){
        this.value = value;
    }

    public static void main(String[] args) {
        Singleton s1 = Singleton.getInstance();
        s1.setValue(115);
        System.out.println("s1 value: " + s1.value);
        Singleton s2 = Singleton.getInstance();
        System.out.println("s2 value: " + s2.value);
        s2.setValue(1111514545);
        System.out.println("s1 value: " + s1.value);
        System.out.println(s1.equals(s2));
    }
}