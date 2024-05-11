package Classi;

public class Esame{
    private String mat;
    private int voto;
    
    public Esame(String m, int v){
        this.mat = m;
        this.voto = v;
    }
    
    public String getMat(){return mat;}
    public int getVoto(){return voto;}
}