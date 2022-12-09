import mmap
import struct

        # create
if __name__ == '__main__':
        shmem = mmap.mmap(-1, 8 ,"shm", access=mmap.ACCESS_WRITE)
        ints = [125,37489]
        i=0
        for data in ints:
                shmem.seek(i)
                shmem.write((data).to_bytes(4,"little"))
                i+=4
        shmem.close()
        
        #i = struct.unpack("<I", shmem.read(4))
         #fmt = "<%di" % len(ints)
        #data =struct.pack(fmt, *ints)
        