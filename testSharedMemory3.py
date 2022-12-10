import mmap
import struct

        # create
if __name__ == '__main__':
        shmem = mmap.mmap(-1, 64 ,"shm", access=mmap.ACCESS_WRITE)
        ints = [[1]*8,[1]*8]
        i=0
        for i in range (2):
                for y in range (8):
                        ints[i][y]=i+y
        i=0
        for tab in ints:
                for data in tab:
                        shmem.seek(i)
                        shmem.write((data).to_bytes(4,"little"))
                        i+=4
        shmem.close()
        
        #i = struct.unpack("<I", shmem.read(4))
         #fmt = "<%di" % len(ints)
        #data =struct.pack(fmt, *ints)
        