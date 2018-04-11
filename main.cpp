#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#define size8 size*8
#define sizeb size*8+crcbit


using namespace std;

int licznik =0;
unsigned procent;

void crc (char* mem, long size)
{
    long long k=0;
    int crcbit,temp;
    int* poly = new int [crcbit];
    int* newmem = new int [sizeb];

    cout << "Podaj ilu bitowy ma byc CRC: " << endl;
    cin >> crcbit;

     for (long long t = size8; t < sizeb+1; t++)
		{
			newmem[t] = 0;
		}

    for (int i = 0 ; i < crcbit+1;  i++ )
    cin >> poly[i];

    for (int i =0; i < size ; i++)
    {
        for (int j = 128; j ; j>>=1)
        {
            if (mem[i]&j)
            {
                newmem[k] = 1;
                k++;
            }
            else
            {
            newmem[k] = 0;
            k++;
            }
        }
    }

temp=0;
	while(temp<size8)
	{

		if (newmem[temp]=1)
		{

			for (int j=0; j<crcbit; j++)
			{
				if ((newmem[temp] == 1 && poly[j] == 1) || (newmem[temp] == 0 && poly[j] == 0))
				{
					newmem[temp] = 0;
                }
				else
                {
                newmem[temp]=1;
                }
				temp++;
			}
			temp = temp-crcbit;
		}
		else{temp++;}
	}


cout << "CRC:" << endl;
	for (long long z = size8; z<sizeb; z++)
	{
		cout << newmem[z];
	}



delete[] poly;
delete[] newmem;
}




void blad_powtorzenia (char* buffer, long size)
{
    double b;
    int bajt,bit;

    cout << "Podaj ilu procentowy ma byc blad: ";
    cin >> b;
    cout << "Jest " << licznik << " bitow" << endl;
    procent = (b * licznik)/100;
    cout << "Ilosc bledow " << procent  <<  endl;
    srand(time(NULL));

     for(int i=0;i<procent;i++)
   {
       bajt = rand()% size +0;
    bit = rand()% 8 + 0;
    if (buffer[bajt]&1<<bit !=0)
{
buffer[bajt] = buffer[bajt]&(~(1<<bit));
}
else {
        buffer[bajt] = buffer[bajt]|1<<bit;
}
   }
}
void blad_bez (char* buffer, long size)
{
    double b;
    int bajt,bit;

    cout << "Podaj ilu procentowy ma byc blad: ";
    cin >> b;
    cout << "Jest " << licznik << " bitow" << endl;
    procent = (b * licznik)/100;
    cout << "Ilosc bledow " << procent  <<  endl;
    int *sprawdz = new int[procent];
    srand(time(NULL));
     for(int i=0;i<procent;i++)
   {
       bajt = rand()% size +0;
    bit = rand()% 8 + 0;
    for (int j=0;j<procent;j++)
    {if (buffer[bajt] != sprawdz[j])
    {
        sprawdz[j] = buffer[bajt];
    if (buffer[bajt]&1<<bit !=0)
{
buffer[bajt] = buffer[bajt]&(~(1<<bit));
}
else {
        buffer[bajt] = buffer[bajt]|1<<bit;
}
    }
else
    i--;
   }
   }
}
bool parz(char* c,long size)
{
bool p = true;
for(int i=0;i<size;i++)
{
    unsigned v = c[i];
for(unsigned k = 128; k; k >>= 1)
{
 if ((v&k)){
        licznik++;
    if (p)
        p = false;
else p = true;
}
else {
    licznik ++;
}
}
}
return p;

}


int main()
{

    long mod = 0;
    int a,b;
  ifstream infile ("test.jpg",ifstream::binary);
  ofstream outfile ("new.jpg",ofstream::binary);
  // get size of file
  infile.seekg (0,infile.end);
  long size = infile.tellg();
  infile.seekg (0);
  // allocate memory for file content
  char* buffer = new char[size+1];

  // read content of infile
  infile.read (buffer,size);
  parz(buffer,size);
  cout << "Co chcesz zrobiæ z plikiem?: " << endl;
  cout << "1. Zmienic z powtorzeniami \n2. Zmienic bez powtorzen \n3. Nic nie psuc \n";
  cin >> a;
  switch(a)
  {
  case 1:
    {
   blad_powtorzenia(buffer,size);
   cout << "Plik zostal zmieniony" << endl;
    }
    break;
   case 2:
       {
   blad_bez(buffer,size);
    cout << "Plik zostal zmieniony" << endl;
    break;
       }
  }
  int podaj;
  cout << "Podaj modulo: ";
  cin >> podaj;
  for (int i=0;i<size;i++)
  {
    a = (int)(unsigned char)buffer[i];
   mod = (mod + a)%podaj;

  }
cout << "Modulo calego bloku danych = " << mod%podaj << endl;
  bool dodaj = parz(buffer,size);
  cout << endl << "Bit parzystosci calego bloku danych= ";
  cout << dodaj ;
  buffer[size] = dodaj ? '1':'0';
  cout << endl << "Bit parzystosci zostal dodany do pliku" << endl;

//CRC
crc(buffer, size);

  // write to outfile;
  outfile.write (buffer,size+1);
  infile.close();
  outfile.close();
  return 0;

}

