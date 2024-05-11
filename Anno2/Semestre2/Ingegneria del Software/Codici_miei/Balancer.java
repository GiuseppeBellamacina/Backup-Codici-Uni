public class Balancer {
    private String[] hosts = new String[]{"host1", "host2", "host3"};
    private int x;
    private static Balancer b = new Balancer();

    private Balancer(){
        x=0;
    }

    public String getHost(){
        if(x == hosts.length){
            x = 0;
        }
        return hosts[x++];
    }

    public static Balancer getInstance(){
        return b;
    }

    public static void main(String[] args) {
        Balancer b = Balancer.getInstance();
        for(int i=0; i<6; i++){
            System.out.println("Call: " + b.getHost());
        }
    }
}
