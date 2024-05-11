import Classi.*;

public class Main {
    public static void main(String[] args){
        Studente s = new Studente(); // Creo un oggetto di tipo Studente
        s.setMatr("1234");
        s.setNome("Neo", "Mammuru");
        s.nuovoEsame("Kung-Fu", 30);
        s.nuovoEsame("Filosofia", 18);
        s.nuovoEsame("Porcologia", 124);
        s.printAll();
        System.out.println();
        Persona p = s; // Creo un oggetto di tipo Persona da un oggetto di tipo Studente
        p.printAll(); //equivale a s.printAll();
        System.out.println();
        Persona p2 = new Persona();
        p2.setNome("Pino", "Filip");
        p2.printAll();
    }
}
