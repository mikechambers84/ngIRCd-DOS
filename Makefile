Compiler_C = wcc
Compiler_CPP = wpp
Compiler_ASM = wasm

Compiler_Options_C = -i$(%watcom)\h -i="src\portab" -i="src\ngircd" -i="src\ipaddr" -i="src\tool" -i="mTCP\TCPINC" -w0 -e25 -d__16BIT -zt0 -zq -os -of -fpi -zdf -zu -zc -bt=dos -fo=.obj -ml
Compiler_Options_CPP = -i$(%watcom)\h -i="mTCP\TCPINC" -i="src\portab" -w0 -e25 -dCFG_H="GLOBAL.CFG" -dNOTRACE -dCOMPILE_ARP -dCOMPILE_UDP -dCOMPILE_TCP -dCOMPILE_ICMP -dCOMPILE_DNS -zq -os -of -fpi -zu -zc -bt=dos -fo=.obj -ml -xs -xr
Compiler_Options_ASM = -ml -d1 -w4 -e25 -zq

Linker_options   = op st=8192 op m op v op maxe=25 op q op symf op el

System       = dos

Exe_file     = ngircd.exe
Map_file     = ngircd.map

Object_files =	IPASM.obj &
		ng_ipaddr.obj &
		array.obj &
		channel.obj &
		class.obj &
		client-cap.obj &
		client.obj &
		conf.obj &
		conn-encoding.obj &
		conn-func.obj &
		conn-ssl.obj &
		conn-zip.obj &
		conn.obj &
		hash.obj &
		io.obj &
		irc-cap.obj &
		irc-channel.obj &
		irc-encoding.obj &
		irc-info.obj &
		irc-login.obj &
		irc-metadata.obj &
		irc-mode.obj &
		irc-op.obj &
		irc-oper.obj &
		irc-server.obj &
		irc-write.obj &
		irc.obj &
		lists.obj &
		log.obj &
		login.obj &
		match.obj &
		ngircd.obj &
		numeric.obj &
		op.obj &
		pam.obj &
		parse.obj &
		proc.obj &
		resolve.obj &
		sighandlers.obj &
		strdup.obj &
		strlcpy.obj &
		strndup.obj &
		strtok_r.obj &
		vsnprintf.obj &
		waitpid.obj &
		tool.obj &
		ARP.obj &
		DNS.obj &
		ETH.obj &
		ETHTYPE.obj &
		IP.obj &
		IPTYPE.obj &
		PACKET.obj &
		TCP.obj &
		TCPSOCKM.obj &
		TIMER.obj &
		UDP.obj &
		UTILS.obj &
		mtcpwrap.obj

all: ngircd.exe

ng_ipaddr.obj:
	*$(Compiler_C) $(Compiler_Options_C) src\ipaddr\ng_ipaddr.c

array.obj: src\ngircd\array.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\array.c 

channel.obj: src\ngircd\channel.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\channel.c 

class.obj: src\ngircd\class.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\class.c 

client-cap.obj: src\ngircd\client-cap.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\client-cap.c 

client.obj: src\ngircd\client.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\client.c 

conf.obj: src\ngircd\conf.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\conf.c 

conn-encoding.obj: src\ngircd\conn-encoding.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\conn-encoding.c 

conn-func.obj: src\ngircd\conn-func.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\conn-func.c 

conn-ssl.obj: src\ngircd\conn-ssl.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\conn-ssl.c 

conn-zip.obj: src\ngircd\conn-zip.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\conn-zip.c 

conn.obj: src\ngircd\conn.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\conn.c 

hash.obj: src\ngircd\hash.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\hash.c 

io.obj: src\ngircd\io.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\io.c 

irc-cap.obj: src\ngircd\irc-cap.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\irc-cap.c 

irc-channel.obj: src\ngircd\irc-channel.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\irc-channel.c 

irc-encoding.obj: src\ngircd\irc-encoding.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\irc-encoding.c 

irc-info.obj: src\ngircd\irc-info.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\irc-info.c 

irc-login.obj: src\ngircd\irc-login.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\irc-login.c 

irc-metadata.obj: src\ngircd\irc-metadata.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\irc-metadata.c 

irc-mode.obj: src\ngircd\irc-mode.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\irc-mode.c 

irc-op.obj: src\ngircd\irc-op.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\irc-op.c 

irc-oper.obj: src\ngircd\irc-oper.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\irc-oper.c 

irc-server.obj: src\ngircd\irc-server.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\irc-server.c 

irc-write.obj: src\ngircd\irc-write.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\irc-write.c 

irc.obj: src\ngircd\irc.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\irc.c 

lists.obj: src\ngircd\lists.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\lists.c 

log.obj: src\ngircd\log.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\log.c 

login.obj: src\ngircd\login.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\login.c 

match.obj: src\ngircd\match.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\match.c 

ngircd.obj: src\ngircd\ngircd.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\ngircd.c 

numeric.obj: src\ngircd\numeric.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\numeric.c 

op.obj: src\ngircd\op.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\op.c 

pam.obj: src\ngircd\pam.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\pam.c 

parse.obj: src\ngircd\parse.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\parse.c 

proc.obj: src\ngircd\proc.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\proc.c 

resolve.obj: src\ngircd\resolve.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\resolve.c 

sighandlers.obj: src\ngircd\sighandlers.c
	$(Compiler_C) $(Compiler_Options_C) src\ngircd\sighandlers.c 

mtcpwrap.obj: src\ngircd\mtcpwrap.cpp
	$(Compiler_CPP) $(Compiler_Options_CPP) src\ngircd\mtcpwrap.cpp

strdup.obj: src\portab\strdup.c
	$(Compiler_C) $(Compiler_Options_C) src\portab\strdup.c 

strlcpy.obj: src\portab\strlcpy.c
	$(Compiler_C) $(Compiler_Options_C) src\portab\strlcpy.c 

strndup.obj: src\portab\strndup.c
	$(Compiler_C) $(Compiler_Options_C) src\portab\strndup.c 

strtok_r.obj: src\portab\strtok_r.c
	$(Compiler_C) $(Compiler_Options_C) src\portab\strtok_r.c 

vsnprintf.obj: src\portab\vsnprintf.c
	$(Compiler_C) $(Compiler_Options_C) src\portab\vsnprintf.c 

waitpid.obj: src\portab\waitpid.c
	$(Compiler_C) $(Compiler_Options_C) src\portab\waitpid.c 

tool.obj: src\tool\tool.c
	$(Compiler_C) $(Compiler_Options_C) src\tool\tool.c

ARP.obj: mTCP\ARP.cpp
	$(Compiler_CPP) $(Compiler_Options_CPP) mTCP\ARP.cpp

DNS.obj: mTCP\DNS.cpp
	$(Compiler_CPP) $(Compiler_Options_CPP) mTCP\DNS.cpp

ETH.obj: mTCP\ETH.cpp
	$(Compiler_CPP) $(Compiler_Options_CPP) mTCP\ETH.cpp

ETHTYPE.obj: mTCP\ETHTYPE.cpp
	$(Compiler_CPP) $(Compiler_Options_CPP) mTCP\ETHTYPE.cpp

IP.obj: mTCP\IP.cpp
	$(Compiler_CPP) $(Compiler_Options_CPP) mTCP\IP.cpp

IPTYPE.obj: mTCP\IPTYPE.cpp
	$(Compiler_CPP) $(Compiler_Options_CPP) mTCP\IPTYPE.cpp

PACKET.obj: mTCP\PACKET.cpp
	$(Compiler_CPP) $(Compiler_Options_CPP) mTCP\PACKET.cpp

TCP.obj: mTCP\TCP.cpp
	$(Compiler_CPP) $(Compiler_Options_CPP) mTCP\TCP.cpp

TCPSOCKM.obj: mTCP\TCPSOCKM.cpp
	$(Compiler_CPP) $(Compiler_Options_CPP) mTCP\TCPSOCKM.cpp

TIMER.obj: mTCP\TIMER.cpp
	$(Compiler_CPP) $(Compiler_Options_CPP) mTCP\TIMER.cpp

UDP.obj: mTCP\UDP.cpp
	$(Compiler_CPP) $(Compiler_Options_CPP) mTCP\UDP.cpp

UTILS.obj: mTCP\UTILS.cpp
	$(Compiler_CPP) $(Compiler_Options_CPP) mTCP\UTILS.cpp

IPASM.obj:
	*$(Compiler_ASM) $(Compiler_Options_ASM) mTCP\IPASM.asm

$(Exe_file): $(Object_files)
	*wlink system $(System) $(Linker_Options) name $(Exe_file) file {$(Object_files)}

clean:
	*del $(Exe_file) $(Map_file) $(Object_Files)
