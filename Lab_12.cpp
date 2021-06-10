 #include <iostream>   //#include <iostream.h>, C stils
#include <conio>      //#include <conio.h>, C stils
#include <string>

/*    Strings: C++ stils    */
//#include <string>
using namespace std;

class Computer {
   protected:
       string procesors;
      float frekvence;
      short atmApjoms;
   public:
      Computer();
      Computer(string, float, short);
      virtual ~Computer() {
         cout << "Message from the \"Computer\" - destroyed!" <<endl;
      }
      string GetProcesors() const;
      float GetFrekvence() const;
      short GetApjoms() const;

      void SetProcesors(string processorN);

      void SetFrekvence(float freq);
      void SetApjoms(short apjoms);
      virtual void Print() const;

};

class NetComputer: public Computer{
	private :
   	string IP_adrese;
   public:
   	NetComputer():Computer(),IP_adrese("20.20.20.20"){}
      NetComputer(string, float, short, string);
      virtual ~NetComputer() {
      	cout<<endl<<"Message from the \"NetComputer\"  - destroyed"<< endl;
      }

      string GetIP() const {
      	return IP_adrese;
      }
      void SetIP(string newIP){
      	IP_adrese=newIP;
      }
      virtual void Print() const;

};


Computer::Computer(): procesors("Celeron g3900 "), frekvence(2.8), atmApjoms(8){
}

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

NetComputer::NetComputer (string proc, float freq, short ram, string IP):Computer (proc,freq,ram) {
	 IP_adrese=IP;
}

inline void NetComputer::Print() const {
	Computer::Print();
   cout<<"IP adrese = "<< IP_adrese;
}


void main(void) {
	const int N=3;
   NetComputer *NPC1= new NetComputer ("intel i3",3.60,4, "10.20.6.30");
   Computer *PC2 =new NetComputer();


   Computer *pcs[N]= {
    new Computer("Ryzen 5",3.2,8),
    new NetComputer(),
    new NetComputer("Ryzen 7", 4.2, 8, "20.30.5.20")
   } ;
  
   cout<< "Array of computers: " <<endl;
   for (int i =0; i<N; i++){
   	cout<<(i+1)<<". ";
      pcs[i]->Print();
      cout<<endl;
   }

	cout<< endl<< "Net Computer:" << endl;

   NPC1->Print();
   cout<< endl<< "Procesors ir "<< NPC1->GetProcesors()<< ", frekvence ir "<< NPC1->GetFrekvence()<< ", RAM ir " <<NPC1->GetApjoms()<<".";
   cout<< endl<< "IP adrese ir "<< NPC1->GetIP()<<"." <<endl<<endl;

   for(int k=0; k<N; k++) {
      delete pcs[k];
   }
   delete NPC1;
   delete PC2;


	cin.get();
}

