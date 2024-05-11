import java.io.IOException;

public class TestPagamenti {
    private Pagamenti pgm = new Pagamenti();
    private void initlista(){
        pgm.svuota();
        pgm.inserisci(321.01f);
        pgm.inserisci(531.7f);
        pgm.inserisci(1234.5f);
    }

    public void testSommaValori(){
        initlista();
        if(pgm.calcolaSomma() == 2087.21f)
            System.out.println("Test somma valori: OK");
        else
            System.out.println("Test somma valori: FAIL");
    }

    public void testListaVuota(){
        pgm.svuota();
        if(pgm.calcolaSomma() == 0)
            System.out.println("Test somma vuota: OK");
        else
            System.out.println("Test somma vuota: FAIL");
        if(pgm.calcolaMassimo() == 0)
            System.out.println("Test max vuota: OK");
        else
            System.out.println("Test max vuota: FAIL");
    }

    public void testLeggiFile(){
        try{
            pgm.leggiFile("csvfiles", "Importi.csv");
            System.out.println("Test lettura file: OK");
        } catch(IOException e){
            System.out.println("Test lettura file: FAIL");
        }
    }

    public static void main(String[] args){
        TestPagamenti tl = new TestPagamenti();
        tl.testSommaValori();
        tl.testListaVuota();
        tl.testLeggiFile();
    }
}