#include <iostream>   //#include <iostream.h>, C stils
//#include <conio>      //#include <conio.h>, C stils
#include <string>


using namespace std;

class OverflowException { // var jau seit pabeigt ar, jeb visu zemam ieks sim iekavam var izdzest };
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

template <class T>
class Computer {
protected:
	string procesors;
	float frekvence;
	T atmApjoms;
public:
	Computer();
	Computer(string, float, T);
	virtual ~Computer() {
		cout << "Message from the \"Computer\" - destroyed!" << endl;
	}
	string GetProcesors() const;
	float GetFrekvence() const;
	T GetApjoms() const;

	void SetProcesors(string processorN);

	void SetFrekvence(float freq);
	void SetApjoms(T apjoms);
	virtual void Print() const;

};
template <class T>
class NetComputer : public Computer<T> {
private:
	string IP_adrese;
public:
	NetComputer() :Computer<T>(), IP_adrese("20.20.20.20") {}
	NetComputer(string, float, T, string);
	virtual ~NetComputer() {
		cout << endl << "Message from the \"NetComputer\"  - destroyed" << endl;
	}

	string GetIP() const {
		return IP_adrese;
	}
	void SetIP(string newIP) {
		IP_adrese = newIP;
	}
	virtual void Print() const;

};
template <class T>
class ComputerNetwork {
private:
	typedef NetComputer<T>* NCPointer;
	NCPointer* Nodes;
	static const unsigned int DEFAULT_MAX_LENGTH;
	unsigned int MaxLength;
	unsigned int Length;
public:
	ComputerNetwork() : MaxLength(DEFAULT_MAX_LENGTH), Length(0) {
		Nodes = new NCPointer[MaxLength];
	}
	ComputerNetwork(unsigned int MaxLength) :MaxLength(MaxLength), Length(0) {
		Nodes = new NCPointer[MaxLength];
	}
	~ComputerNetwork();
	static unsigned int GetDefaultMaxLength() {
		return DEFAULT_MAX_LENGTH;
	}
	int GetMaxLength() const {
		return MaxLength;
	}
	int GetLength() {
		return Length;
	}
	void AddNode(const NetComputer<T>&);
	void Print() const;

};
template <class T>
const unsigned int ComputerNetwork<T>::DEFAULT_MAX_LENGTH = 5;

template <class T>
Computer<T>::Computer() : procesors("Celeron g3900 "), frekvence(2.8), atmApjoms(8) {
}
template <class T>
Computer<T>::Computer(string proc, float freq, T ram) {
	procesors = proc;
	frekvence = freq;
	atmApjoms = ram;
}
template <class T>
inline void Computer<T>::Print() const {
	cout << "Procesors ir " << procesors << ", frekvence ir " << frekvence << ", operativas atminas apjoms ir " << atmApjoms << endl;
}

template <class T>
inline string Computer<T>::GetProcesors() const {
	return procesors;
}

template <class T>
inline float Computer<T>::GetFrekvence() const {
	return frekvence;
}
template <class T>
inline T Computer<T>::GetApjoms() const {
	return atmApjoms;
}
template <class T>
inline void Computer<T>::SetProcesors(string processorN) {
	procesors = processorN;
}
template <class T>
inline void Computer<T>::SetFrekvence(float freq) {
	frekvence = freq;
}
template <class T>
inline void Computer<T>::SetApjoms(T apjoms) {
	atmApjoms = apjoms;
}
template <class T>
NetComputer<T>::NetComputer(string proc, float freq, T ram, string IP) :Computer<T>(proc, freq, ram) {
	IP_adrese = IP;
}

template <class T>
inline void NetComputer<T>::Print() const {
	Computer<T>::Print();
	cout << "IP adrese = " << IP_adrese;
}
template <class T>
ComputerNetwork<T>::~ComputerNetwork() {
	for (unsigned int i = 0; i < Length; i++)
		delete Nodes[i];
	delete[] Nodes;
}
template <class T>
void ComputerNetwork<T>::Print() const {
	cout << " Network's computers: " << endl;
	for (unsigned int i = 0; i < Length; i++) {
		cout << (i + 1) << ". ";
		Nodes[i]->Print();
		cout << "." << endl;
	}
}
template <class T>
void ComputerNetwork<T>::AddNode(const NetComputer<T>& Node) {
	if (Length == MaxLength)
		throw OverflowException();
	else
		Nodes[Length++] = new NetComputer<T>(
			Node.GetProcesors(), Node.GetFrekvence(), Node.GetApjoms(), Node.GetIP()
			);
}


int main() {
	ComputerNetwork<unsigned short>* NetworkUShort = new ComputerNetwork<unsigned short>(2);
	ComputerNetwork<unsigned int>* NetworkUInt = new ComputerNetwork<unsigned int>(2);

	NetComputer<unsigned short>* NPC1 = new NetComputer<unsigned short>("intel i3", 3.60, 4, "10.20.6.30");
	NetComputer<unsigned int>* NPC2 = new NetComputer<unsigned int>("intel i5", 4.2, 8, "20.20.20.20");

	NetComputer<unsigned short> NPC11("Ryzen 5", 4.2, 8, "10.10.10.10");
	NetComputer<unsigned int> NPC22("Ryzen 7", 4.2, 8, "20.30.5.20");

	try {
		NetworkUShort->AddNode(*NPC1);
		cout << "\nNew  UNSIGNED SHORT node as in computer has been added successfully!" << endl;
	}
	catch (const OverflowException&) {
		cout << "*** Error: maximal length exceeded ! ***" << endl;
	}
	catch (...) {
		cout << "Unknown Error !" << endl;
	}


	try {
		NetworkUShort->AddNode(NPC11);
		cout << "\nNew UNSIGNED SHORT node as in computer has been added successfully!" << endl;
	}
	catch (const OverflowException&) {
		cout << "*** Error: maximal length exceeded ! ***" << endl;
	}
	catch (...) {
		cout << "Unknown Error !" << endl;
	}


	try {
		NetworkUInt->AddNode(*NPC2);
		cout << "\nNew  UNSIGNED INT node as in computer has been added successfully!" << endl;
	}
	catch (const OverflowException&) {
		cout << "*** Error: maximal length exceeded ! ***" << endl;
	}
	catch (...) {
		cout << "Unknown Error !" << endl;
	}


	try {
		NetworkUInt->AddNode(NPC22);
		cout << "\nNew UNSIGNED INT node as in computer has been added successfully!" << endl;
	}
	catch (const OverflowException&) {
		cout << "*** Error: maximal length exceeded! ***" << endl;
	}
	catch (...) {
		cout << "Unknown error !" << endl;
	}

	delete NPC1;
	delete NPC2;
	cout << "Unsigned short computer network" << endl;
	NetworkUShort->Print();
	cout << endl;
	cout << "Unsigned int computer network" << endl;
	NetworkUInt->Print();

	delete NetworkUShort;
	delete NetworkUInt;
	cin.get();
}

