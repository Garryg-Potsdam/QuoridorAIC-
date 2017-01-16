
#Boost
In order to install boost dependency from the repositories (Used this for my version):
[StackOverflow Question](http://stackoverflow.com/questions/12578499/how-to-install-boost-on-ubuntu)
```bash
sudo apt-get install libboost-all-dev
```
To install the boost dependency with a specific version:
```bash
wget -O boost_1_55_0.tar.gz http://sourceforge.net/projects/boost/files/boost/1.55.0/boost_1_55_0.tar.gz/download
tar xzvf boost_1_55_0.tar.gz
cd boost_1_55_0/
sudo apt-get update
sudo apt-get install build-essential g++ python-dev autotools-dev libicu-dev build-essential libbz2-dev libboost-all-dev
./bootstrap.sh --prefix=/usr/local
./b2
sudo ./b2 install
```

#MySQL/C++ Connector
To install the connector
[AskUbuntu Question](http://askubuntu.com/questions/165868/installing-mysql-connector-c)
[StackOverflow Question](http://stackoverflow.com/questions/15995319/c-mysql-connector-undefined-reference-to-get-driver-instance-already-tri)
```bash
apt-get install libmysqlcppconn-dev
```

#Compiling the software for the SQL driver
You must compile with the following command:
```bash
g++ -Wall -I/usr/include/cppconn dbconnect.cpp -L/usr/lib -lmysqlcppconn
```
