
class Computer {
    private final static String DEFAULT_procesors="Ryzen 7";
    private final static float DEFAULT_frekvence= 4.2f;
    private final static short DEFAULT_atmApjoms= (short)4;
    private String procesors;
    private float frekvence;
    private short atmApjoms;
    private static int objectsCounter=0;


    //copy konstruktors
    public Computer (Computer cmptr){
        this(cmptr.procesors, cmptr.frekvence, cmptr.atmApjoms);
    }
    // konstruktors bez parametriem
    public Computer() {this( DEFAULT_procesors, DEFAULT_frekvence, DEFAULT_atmApjoms);}
    //konstruktors ar parametriem
    public Computer(String procesors, float frekvence, short atmApjoms) {
        this.procesors=procesors;
        this.frekvence=frekvence;
        this.atmApjoms=atmApjoms;
        objectsCounter++;
    }
    public static int getObjectsCount() {
        return objectsCounter;
    }


    public String getProcesors(){ return procesors;}
    public float getFrekvence(){ return frekvence;}
    public short getAtmApjoms(){ return atmApjoms;}

    public void setProcesors(String procesors){this.procesors=procesors;}
    public void setFrekvence(float frekvence){this.frekvence=frekvence;}
    public void setAtmApjoms(short atmApjoms){this.atmApjoms=atmApjoms;}


    @Override
    public String toString() {
        return "Procesors:" + procesors + ", frekvence:" + frekvence + ", atmiņas apjoms " + atmApjoms; }


}
public class ld_6 {
    public static void main(String[] args){
        Computer PC = new Computer("ryzen", 4.1f,(short)2);
        Computer PC2=new Computer();
        Computer PCCopy = new Computer(PC);

        System.out.println(PC.toString());
        System.out.println(PC2.toString());
        System.out.println(PCCopy.toString());
        System.out.println();
        System.out.println("Objektu skaits ir "+Computer.getObjectsCount());
        System.out.println();
        System.out.println("PC2 atminas apjoms ir "+ PC2.getAtmApjoms());
        PC2.setFrekvence(3.8f);
        System.out.println("PC2 jauna frekvence ir " + PC2.getFrekvence());

        System.out.println("\nPress \"Enter\" to finish program... ");

        try {
            System.in.read();
        }
        catch(java.io.IOException e) {
            System.out.println("Input/output exception.");
        }

    }
}
