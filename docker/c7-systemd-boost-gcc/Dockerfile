FROM local/c7-systemd
RUN yum -y groupinstall "Development Tools"
RUN yum -y install vim
RUN yum -y install wget
RUN yum -y install boost-program-options.x86_64
RUN yum -y install boost-devel-1.53.0-23.el7.x86_64
RUN wget http://sourceforge.net/projects/log4cplus/files/log4cplus-stable/1.1.3/log4cplus-1.1.3-rc5.tar.gz
RUN tar zxfv log4cplus-1.1.3-rc5.tar.gz
RUN rm log4cplus-1.1.3-rc5.tar.gz
RUN cd log4cplus-1.1.3-rc5/
RUN ./log4cplus-1.1.3-rc5/configure &&  make && make  install

CMD /bin/bash

