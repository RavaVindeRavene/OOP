
//#include "stdafx.h" // for Visual C++
//#include <conio>      
#include <iostream>   
#include <string>

using namespace std;

class OverflowException {
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
		//cout << "Message from the \"Computer\" - destroyed!" << endl;
	}
	string GetProcesors() const;
	float GetFrekvence() const;
	short GetApjoms() const;

	void SetProcesors(string processorN);
	void SetFrekvence(float freq);
	void SetApjoms(short apjoms);

	friend ostream& operator << (ostream& O, const Computer& PC);

};

class NetComputer : public Computer {
private:
	string IP_adrese;
public:
	NetComputer() :Computer(), IP_adrese("20.20.20.20") {}
	NetComputer(string, float, short, string);
	virtual ~NetComputer() {
		//cout << endl << "Message from the \"NetComputer\"  - destroyed" << endl;
	}

	string GetIP() const {
		return IP_adrese;
	}
	void SetIP(string newIP) {
		IP_adrese = newIP;
	}

	friend ostream& operator << (ostream& O, const NetComputer& NC);

};

class ComputerNetwork {
private:
	typedef NetComputer* NCPointer;
	NCPointer* Datori;
	static const unsigned int DEFAULT_MAX_LENGTH;
	unsigned int MaxLength;
	unsigned int Length;
public:
	ComputerNetwork() : MaxLength(DEFAULT_MAX_LENGTH), Length(0) {
		Datori = new NCPointer[MaxLength];
	}
	ComputerNetwork(unsigned int MaxLength) :MaxLength(MaxLength), Length(0) {
		Datori = new NCPointer[MaxLength];
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
	void operator += (const NetComputer&);

	friend ostream& operator << (ostream& O, const ComputerNetwork& CNet);


};
const unsigned int ComputerNetwork::DEFAULT_MAX_LENGTH = 5;


Computer::Computer() : procesors("Celeron g3900 "), frekvence(2.8f), atmApjoms(8) {
}

Computer::Computer(string proc, float freq, short ram) {
	procesors = proc;
	frekvence = freq;
	atmApjoms = ram;
}
ostream& operator << (ostream& O, const Computer& PC) {
	O << "Pricesors ir " << PC.procesors << ", frekvence ir " << PC.frekvence << ", operativas atminas apjoms ir " << PC.atmApjoms;
	return O;

}

inline string Computer::GetProcesors() const {
	return procesors;
}
inline float Computer::GetFrekvence() const {
	return frekvence;
}
inline short Computer::GetApjoms() const {
	return atmApjoms;
}
inline void Computer::SetProcesors(string processorN) {
	procesors = processorN;
}
inline void Computer::SetFrekvence(float freq) {
	frekvence = freq;
}
inline void Computer::SetApjoms(short apjoms) {
	atmApjoms = apjoms;
}

NetComputer::NetComputer(string proc, float freq, short ram, string IP) :Computer(proc, freq, ram) {
	IP_adrese = IP;
}
ostream& operator << (ostream& O, const NetComputer& NC) {
	O << (Computer&)NC << ", IP adrese : " << NC.IP_adrese;
	return O;
}

ComputerNetwork::~ComputerNetwork() {
	for (unsigned int i = 0; i < Length; i++)
		delete Datori[i];
	delete[] Datori;
}
ostream& operator << (ostream& O, const ComputerNetwork& CNet) {
	O << "Network's computers: " << endl;
	for (unsigned i = 0; i < CNet.Length; i++) {
		O << (i + 1) << ". " << *(CNet.Datori[i]) << endl;
	}
	return O;
}

void ComputerNetwork:: operator+=(const NetComputer& NC) {
	if (Length == MaxLength) throw OverflowException();
	else Datori[Length++] = new NetComputer(
		NC.GetProcesors(), NC.GetFrekvence(), NC.GetApjoms(), NC.GetIP()
	);
}





int main() {
	ComputerNetwork* Network = new ComputerNetwork(2);
	NetComputer* NPC1 = new NetComputer("intel i3", 3.6f, 4, "10.20.6.30");
	NetComputer NPC2("Ryzen 7", 4.2f, 8, "20.30.5.20");
	NetComputer NPC3("Ryzen 5", 4.2f, 8, "20.30.5.20");
	try {
		
		*Network += *NPC1;
		cout << "\nNew  computer has been added to the network successfully!" << endl;
	}
	catch (const OverflowException&) {
		cout << "*** Error: maximal length exceeded ! ***" << endl;
	}
	catch (...) {
		cout << "Unknown Error !" << endl;
	}

	try {
		*Network+=NPC2;
		cout << "\nNew computer has been added to the network successfully!" << endl;
	}
	catch (const OverflowException&) {
		cout << "*** Error: maximal length exceeded! ***" << endl;
	}
	catch (...) {

		cout << "Unknown error !" << endl;
	}

	try {
		*Network += NPC3;
		cout << "\nNew computer has been added to the network successfully!" << endl;
	}
	catch (const OverflowException&) {
		cout << "*** Error: maximal length exceeded! ***" << endl;
	}
	catch (...) {

		cout << "Unknown error !" << endl;
	}

	cout << "\n\nDefault maximal length (from CLASS): " <<
		ComputerNetwork::GetDefaultMaxLength() << "." << endl;
	cout << "Default maximal length (from OBJECT): " <<
		Network->GetDefaultMaxLength() << "." << endl;
	cout << "Maximal length: " << Network->GetMaxLength() << "." << endl;
	cout << "Current length: " << Network->GetLength() << "." << endl;

	cout << *Network;
	
	delete NPC1;
	delete Network;

	cin.get();
	return 0;
}

