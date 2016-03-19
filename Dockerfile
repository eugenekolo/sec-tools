from ubuntu:trusty
maintainer eugene@eugenekolo.com

RUN adduser grill
COPY .git /home/grill/sec-tools/.git
RUN chown -R grill:grill /home/grill/sec-tools

RUN echo "grill ALL=NOPASSWD: ALL" > /etc/sudoers.d/grill
RUN apt-get update
RUN apt-get -y install git virtualenvwrapper

USER grill

WORKDIR /home/grill/sec-tools
RUN git checkout .
RUN ./sec-tools -s setup

WORKDIR /home/grill/
RUN bash -c "source /etc/bash_completion.d/virtualenvwrapper && mkvirtualenv grill"
RUN echo "workon grill" >> /home/grill/.bashrc

ENTRYPOINT bash -i
