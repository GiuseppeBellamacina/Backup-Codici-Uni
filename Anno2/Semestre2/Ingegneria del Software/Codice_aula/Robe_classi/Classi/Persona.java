package Classi;

public class Persona{
    private String nome, co;
    
    public void setNome(String n, String c){
        this.nome = n;
        this.co = c;
    }

    public void printAll(){
        System.out.println(nome + " " + co);
    }
}