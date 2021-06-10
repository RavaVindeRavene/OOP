 #include <iostream>   //#include <iostream.h>, C stils
#include <conio>      //#include <conio.h>, C stils
#include <string>

/*    Strings: C++ stils    */
//#include <string>
using namespace std;

class Computer {
   private:
       string procesors;
      float frekvence;
      short atmApjoms;
   public:
      Computer();
      Computer(string, float, short);
      ~Computer() {
         cout << "Message from the \"Computer\" - destroyed!" <<endl;
      }
      string GetProcesors() const;
      float GetFrekvence() const;
      short GetApjoms() const;

      void SetProcesors(string processorN);

      void SetFrekvence(float freq);
      void SetApjoms(short apjoms);
      void Print() const;



};
Computer::Computer(): procesors("Celeron g3900"), frekvence(2.8), atmApjoms(8){}
Computer::Computer (string proc, float freq, short ram){
    procesors=proc;
   frekvence=freq;
   atmApjoms=ram;
   }

inline void Computer::Print() const {
    cout << "Procesors ir "  <<procesors<< ", frekvence ir "<< frekvence<<", operativas atminas apjoms ir "<<atmApjoms<<endl;
}
    inline string Computer::GetProcesors() const {
         return procesors;
      }
   inline float Computer::GetFrekvence() const{
          return frekvence;
      }
   inline short Computer::GetApjoms() const{
          return atmApjoms;
      }

   inline void Computer::SetProcesors(string processorN) {
         procesors = processorN;
      }

   inline void Computer::SetFrekvence(float freq){
          frekvence=freq;
      }
   inline void Computer::SetApjoms(short apjoms){
          atmApjoms=apjoms;
      }




void main(void) {
   Computer PC1, PC2("intel i3",3.60,4),
   *PC4 = new Computer("intel i5",1.6,4), *PC5;
   PC5 = new Computer("Ryzen 5",3.2,8);

   clrscr();

    PC1.Computer::Print();cout<<endl;
   PC1.SetFrekvence(1.6);
   PC1.Computer::Print();cout<<endl;

   cout << endl << "**************" << endl << endl;

   (*PC4).Computer::Print();cout<<endl;
   PC4->SetApjoms(8);
   PC4->Computer::Print();cout<<endl;
   (*PC4).GetFrekvence();cout<<endl;
   PC5->Computer::Print();cout<<endl;

   delete PC4;
   delete PC5;

/* Aizture: C stils */
   while (kbhit()) // C stils
      getch();     // C stils
   getch();        // C stils

/* Aizture: C++ stils */
// cin.get();
}

