#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace boost::interprocess;
using namespace std;

int main(int argc, char* argv[])
{
    using namespace boost::interprocess;

    if (argc == 1) {  //Parent process
        //Create a native windows shared memory object.
        windows_shared_memory shmem(create_only, "shm", read_write, sizeof(unsigned int[2]));

        //Map the whole shared memory in this process
        mapped_region region(shmem, read_write);

        //Write all the memory to 1
        std::memset(region.get_address(), 1, region.get_size());

        unsigned int* tab = static_cast<unsigned int*>(region.get_address());
        *tab = 1736435;
        tab[1] = 24;

        cout << region.get_address() << endl << sizeof(unsigned int[2]) << endl;
  
        std::system("pause");

        cout << tab[0] << endl << tab[1];
    }
    else {
        //Open already created shared memory object.
        windows_shared_memory shmem(open_only, "shm", read_only);

        //Map the whole shared memory in this process
        mapped_region region(shmem, read_only);

        //Check that memory was initialized to 1
        char* mem = static_cast<char*>(region.get_address());
        for (std::size_t i = 0; i < region.get_size(); ++i)
            if (*mem++ != 1)
                return 1;   //Error checking memory
    }
    
    return 0;
}