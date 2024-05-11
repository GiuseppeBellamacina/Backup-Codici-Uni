import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.LineNumberReader;
import java.util.ArrayList;
import java.util.List;

public class CalcolaImporti{
    private final List<String> importi = new ArrayList<>(); // posso anche non parametrizzare da un lato
    private float totale, massimo;

    public float calcola(String c, String n) throws IOException{
        LineNumberReader f = new LineNumberReader(new FileReader(new File(c, n)));
        totale = 0;
        while(true){
            final String riga = f.readLine(); // legge una riga
            if(riga == null) break; // fine file
            importi.add(riga); // aggiunge alla lista
            totale += Float.parseFloat(riga); // se non è un numero, lancia NumberFormatException, converte string a float
        }
        f.close();
        return totale;
    }
}

public class CalcolaImporti2{
    private final List<String> importi = new ArrayList<>();
    private float totale, massimo;

    public float calcola(String c, String n) throws IOException{
        LineNumberReader f = new LineNumberReader(new FileReader(new File(c, n)));
        totale = massimo = 0;
        while(true){
            final String riga = f.readLine();
            if(riga == null) break;
            if(!importi.contains(riga)){
                importi.add(riga);
                float x = Float.parseFloat(riga);
                totale += x;
                if (massimo < x) massimo = x;
            }
        }
        f.close();
        return totale;
    }
}

public class CalcolaImporti3{
    private final List<String> importi = new ArrayList<>();
    private float totale, massimo;

    public float calcola(String c, String n) throws IOException{
        LineNumberReader f = new LineNumberReader(new FileReader(new File(c, n)));
        String riga;
        while(true){
            riga = f.readLine();
            if(riga == null) break;
            if(!importi.contains(riga)) importi.add(riga);
        }
        f.close();
        totale = 0;
        for(int i=0; i<importi.size(); i++)
            totale += Float.parseFloat(importi.get(i));
        massimo = Float.parseFloat(importi.get(0));
        for(int i=1; i<importi.size(); i++){
            if(massimo < Float.parseFloat(importi.get(i)))
                massimo = Float.parseFloat(importi.get(i));
        }
        return totale;
    }
}