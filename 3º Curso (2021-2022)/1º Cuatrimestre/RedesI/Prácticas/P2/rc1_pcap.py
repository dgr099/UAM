'''
    Librería rc1-pcap. Wrapper sobre librería C PCAP para 
    poder usar las funciones desde Python
    Javier Ramos <javier.ramos@uam.es>
    2020
    V0.2
'''
import ctypes,sys
from ctypes.util import find_library
from typing import Callable






user_callback = None

DLT_EN10MB = 1

def mycallback(us,h,data):
    header = pcap_pkthdr ()
    header.len = h[0].len
    header.caplen = h[0].caplen
    header.ts = timeval(h[0].tv_sec,h[0].tv_usec)
    if user_callback is not None:
        user_callback (us,header,bytes(data[:header.caplen]))



pcap = ctypes.cdll.LoadLibrary("libpcap.so")







class timeval():
    def __init__(self,tv_sec,tv_usec):
        self.tv_sec = tv_sec
        self.tv_usec = tv_usec

class pcap_pkthdr():
    def __init__(self):
        self.len=0
        self.caplen=0
        self.ts=timeval(0,0)

class pcappkthdr(ctypes.Structure):
    _fields_ = [("tv_sec", ctypes.c_long), ("tv_usec", ctypes.c_long), ("caplen", ctypes.c_uint32), ("len", ctypes.c_uint32)]


def pcap_open_offline(fname:str,errbuf:bytearray) -> ctypes.c_void_p:
    #pcap_t *pcap_open_offline(const char *fname, char *errbuf);
    if fname is None:
        raise ValueError("El objeto fname no puede ser None")
    if errbuf is None:
        raise ValueError("El objeto errbuf no puede ser None")
    poo = pcap.pcap_open_offline
    fn =  bytes(str(fname), 'ascii')
    poo.restype = ctypes.POINTER(ctypes.c_void_p)
    eb = ctypes.create_string_buffer(256)
    handle = poo(fn,eb)
    errbuf.extend(bytes(format(eb.value).encode('ascii')))
    return handle


def pcap_open_dead(linktype:int,snaplen:int) -> ctypes.c_void_p:
    #pcap_t *pcap_open_dead(int linktype, int snaplen)
    pod = pcap.pcap_open_dead
    pod.restype = ctypes.POINTER(ctypes.c_void_p)
    lt = ctypes.c_int(linktype)
    sn = ctypes.c_int(snaplen)
    handle = pod(lt,sn)
    return handle

def pcap_dump_open(descr:ctypes.c_void_p, fname:str)-> ctypes.c_void_p:
    #pcap_dumper_t *pcap_dump_open(pcap_t *p, const char *fname);
    if fname is None:
        raise ValueError("El objeto fname no puede ser None")
    if descr is None:
        raise ValueError("El objeto descr no puede ser None")
    pdo = pcap.pcap_dump_open
    pdo.restype = ctypes.POINTER(ctypes.c_void_p)
    ds = descr

    fn =  bytes(str(fname), 'ascii')
    handle = pdo(ds,fn)
    return handle

def pcap_dump(dumper:ctypes.c_void_p,header,data:bytes):
    # void pcap_dump(u_char *user, struct pcap_pkthdr *h,u_char *sp);
    if dumper is None:
        raise ValueError("El objeto dumper no puede ser None")
    if header is None:
        raise ValueError("El objeto header no puede ser None")
    if data is None:
        raise ValueError("El objeto data no puede ser None")
    pd = pcap.pcap_dump
    dp = dumper
    haux = pcappkthdr()
    haux.len = header.len
    haux.caplen = header.caplen
    haux.tv_sec = header.ts.tv_sec
    haux.tv_usec = header.ts.tv_usec
    h = ctypes.byref(haux)
    d = ctypes.c_char_p(bytes(data))
    pd(dp,h,d)



def pcap_open_live(device:str,snaplen:int,promisc:int,to_ms:int,errbuf:bytearray) -> ctypes.c_void_p:
    
    #pcap_t *pcap_open_live(const char *device, int snaplen,int promisc, int to_ms, char *errbuf)
    if device is None:
        raise ValueError("El objeto device no puede ser None")
    pol = pcap.pcap_open_live
    pol.restype = ctypes.c_void_p
    dv =  bytes(str(device), 'ascii')
    sn = ctypes.c_int(snaplen)
    tms = ctypes.c_int(to_ms)
    pr = ctypes.c_int(promisc)
    eb = ctypes.create_string_buffer(256)
    handle = pol(dv,sn,pr,tms,eb)
    errbuf.extend(bytes(format(eb.value).encode('ascii')))

    return handle

def pcap_close(handle:ctypes.c_void_p):
    #void pcap_close(pcap_t *p);

    if handle is None:
        raise ValueError("El objeto handle no puede ser None")
    pc = pcap.pcap_close
    pc(handle)

def pcap_dump_close(handle:ctypes.c_void_p):
    #void pcap_close(pcap_dumper_t *p);
    if handle is None:
        raise ValueError("El objeto handle no puede ser None")
    pdc = pcap.pcap_dump_close
    pdc(handle)

def pcap_next(handle:ctypes.c_void_p,header)-> bytes:
    #const u_char *pcap_next(pcap_t *p, struct pcap_pkthdr *h)
    if handle is None:
        raise ValueError("El objeto handle no puede ser None")
    pn = pcap.pcap_next
    pn.restype = ctypes.c_char_p
    h = pcappkthdr()
    aux = pn(handle,ctypes.byref(h))
    header.len = h.len
    header.caplen = h.caplen
    header.ts = timeval(h.tv_sec,h.tv_usec)
    return bytes(aux)


def pcap_loop(handle:ctypes.c_void_p,cnt:int,callback_fun: Callable[[ctypes.c_void_p,pcap_pkthdr,bytes],None],user:ctypes.c_void_p) -> int:
    global user_callback
    if handle is None:
        raise ValueError("El objeto handle no puede ser None")
   
    user_callback = callback_fun
    #  typedef void (*pcap_handler)(u_char *user, const struct pcap_pkthdr *h,const u_char *bytes);
    PCAP_HANDLER = ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_char_p,ctypes.POINTER(pcappkthdr),ctypes.POINTER(ctypes.c_uint8))
    cf = PCAP_HANDLER(mycallback)
    #int pcap_loop(pcap_t *p, int cnt,pcap_handler callback, u_char *user);
    pl = pcap.pcap_loop
    pl.restype = ctypes.c_int
    us = ctypes.c_void_p(user)
    c = ctypes.c_int(cnt)
    ret = pl(handle,c,cf,us)
    user_callback = None
    return ret

def pcap_dispatch(handle:ctypes.c_void_p,cnt:int,callback_fun:Callable[[ctypes.c_void_p,pcap_pkthdr,bytes],None],user:ctypes.c_void_p) -> int:
    global user_callback
    if handle is None:
        raise ValueError("El objeto handle no puede ser None")
    user_callback = callback_fun
    #  typedef void (*pcap_handler)(u_char *user, const struct pcap_pkthdr *h,const u_char *bytes);
    PCAP_HANDLER = ctypes.CFUNCTYPE(ctypes.c_void_p, ctypes.c_char_p,ctypes.POINTER(pcappkthdr),ctypes.POINTER(ctypes.c_uint8))
    cf = PCAP_HANDLER(mycallback)
    #int pcap_loop(pcap_t *p, int cnt,pcap_handler callback, u_char *user);
    pd = pcap.pcap_dispatch
    pd.restype = ctypes.c_int
    us = ctypes.c_void_p(user)
    c = ctypes.c_int(cnt)
    ret = pd(handle,c,cf,us)
    user_callback = None
    return ret
def pcap_breakloop(handle:ctypes.c_void_p):
    #void pcap_breakloop(pcap_t *);
    if handle is None:
        raise ValueError("El objeto handle no puede ser None")
    pbl = pcap.pcap_breakloop
    pbl(handle)

def pcap_inject(handle:ctypes.c_void_p,buf:bytes,size:int) -> int:
    #int pcap_inject(pcap_t *p, const void *buf, size_t size);
    if handle is None:
        raise ValueError("El objeto handle no puede ser None")
    if buf is None:
        raise ValueError("El objeto buf no puede ser None")
    if not isinstance(buf, bytes):
        raise ValueError("El objeto buf debe ser de tipo bytes()")
    pi = pcap.pcap_inject
    pi.restype = ctypes.c_int
    ret = pi(handle,ctypes.c_char_p(buf),ctypes.c_longlong(size))
    return ret





