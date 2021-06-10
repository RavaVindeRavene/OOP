 #include <iostream>   //#include <iostream.h>, C stils
#include <conio>      //#include <conio.h>, C stils
#include <string>

/*    Strings: C++ stils    */
//#include <string>
using namespace std;

class OverflowException { // var jau sseit pabeigt ar, jeb visu zemam ieks sim iekavam var izdzest };
   public:
      OverflowException() {
         cout << endl << "Exception created!" << endl;
      }
      OverflowException(const OverflowException&) {
         cout << "Exception copied!" << endl;
      }
      ~OverflowException() {
         cout << "Exception finished!" << endl;
      }
};

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

class ComputerNetwork {
	private:
   	typedef NetComputer* NCPointer;
      NCPointer *Nodes;
      static const unsigned int DEFAULT_MAX_LENGTH;
      unsigned int MaxLength;
      unsigned int Length;
   public:
   	ComputerNetwork(): MaxLength(DEFAULT_MAX_LENGTH), Length(0) {
      	Nodes= new NCPointer[MaxLength];
      }
      ComputerNetwork(unsigned int MaxLength):MaxLength(MaxLength),Length(0){
      	Nodes = new NCPointer[MaxLength];
      }
      ~ComputerNetwork();
      static unsigned int GetDefaultMaxLength(){
      	return DEFAULT_MAX_LENGTH;
      }
      int GetMaxLength() const{
      	return MaxLength;
      }
      int GetLength() {
      	return Length;
      }
      void AddNode(const NetComputer&);
      void Print() const;

};
const unsigned int ComputerNetwork::DEFAULT_MAX_LENGTH= 5;


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

ComputerNetwork::~ComputerNetwork(){
	for (unsigned int i=0; i<Length;i++)
   	delete Nodes[i];
   delete [] Nodes;
}

void ComputerNetwork::Print() const{
	cout<<" Network's computers: "<< endl;
   for (unsigned int i=0;i<Length; i++){
   	cout<<(i+1)<<". ";
      Nodes[i]->Print();
      cout<<"."<<endl;
   }
}

void ComputerNetwork::AddNode(const NetComputer& Node){
	if (Length==MaxLength)
   	throw OverflowException();
   else
   	Nodes[Length++]=new NetComputer(
      Node.GetProcesors(), Node.GetFrekvence(), Node.GetApjoms(), Node.GetIP()
      );
}


void main(void) {
	ComputerNetwork *Network = new ComputerNetwork(2 ) ;//ko te tu neierakstiji??, laikam tagad ok
   NetComputer *NPC1= new NetComputer ("intel i3",3.60,4, "10.20.6.30");
   NetComputer NPC2("Ryzen 7", 4.2, 8, "20.30.5.20");

   try {
      Network->AddNode(*NPC1);
      cout << "\nNew node as in computer has been added successfully!" << endl;
   }
      catch (const OverflowException&) {
         cout << "*** Error: maximal length exceeded ! ***" << endl;
      }
      catch (...) {
         cout << "Unknown Error !" << endl;
      }
      delete NPC1;

  
   cout << "\n\nDefault maximal length (from CLASS): " <<
     ComputerNetwork::GetDefaultMaxLength() << "." << endl;
   cout << "Default maximal length (from OBJECT): " <<
     Network->GetDefaultMaxLength() << "." << endl;
   cout << "Maximal length: " << Network->GetMaxLength() << "." << endl;
   cout << "Current length: " << Network->GetLength() << "." << endl;


	try {
      Network->AddNode(NPC2);
      cout << "\nNew node as in computer has been added successfully!" << endl;
   }
      catch (const OverflowException&) {
         cout << "*** Error: maximal length exceeded! ***" << endl;
      }
      catch (...) {
         cout << "Unknown error !" << endl;
      }
   Network->Print();
   delete Network;

	cin.get();
}

