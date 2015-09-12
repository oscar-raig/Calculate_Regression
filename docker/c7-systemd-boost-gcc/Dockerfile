FROM local/c7-systemd
RUN yum -y groupinstall "Development Tools"
RUN yum -y install vim
RUN yum -y install wget
RUN wget http://sourceforge.net/projects/boost/files/boost/1.59.0/boost_1_59_0.tar.gz
RUN tar xzvf boost_1_59_0.tar.gz
RUN cd boost_1_59_0
#RUN chmod 777 bootstrap.sh
#RUN ./bootstrap.sh
#RUN ./b2 cxxflags="-stdlib=libstdc++" linkflags="-stdlib=libstdc++" 
#RUN ./b2 install
RUN yum -y install boost-program-options.x86_64
RUN yum -y install boost-devel-1.53.0-23.el7.x86_64
RUN echo "gsl library and boost library installed succesfully"
CMD /bin/bash

