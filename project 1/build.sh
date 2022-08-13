g++ -shared -fPIC framework/*.cpp framework/*.h -o Network.o
cp Network.o framework/Network.o
rm -f Network.o

g++ client.cpp framework/Network.o -o client.lm
g++ server.cpp framework/Network.o -o server.lm