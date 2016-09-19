FROM absalomedia/mini
MAINTAINER Lawrence Meckan <media@absalom.biz>

# Set correct environment variables.
ENV DOCKER_NAME rev_tensile
ENV DEBIAN_FRONTEND noninteractive
ENV HOME /root
ENV DEFAULT_TIMEZONE Australia/Brisbane

# Enable ssh access
RUN rm -f /etc/service/sshd/down

# Regenerate SSH host keys. baseimage-docker does not contain any, so you
# have to do that yourself. You may also comment out this instruction; the
# init system will auto-generate one during boot.
# RUN /etc/my_init.d/00_regen_ssh_host_keys.sh

# !!! Enabling the insecure key permanently !!! REMOVE ME AT PRODUCTION
# RUN /usr/sbin/enable_insecure_key

# Use baseimage-docker's init system.
CMD ["/sbin/my_init"]

RUN apt-get update \
  && apt-get -y install wget curl python-software-properties curl unzip git build-essential clang-3.6 pkg-config zip zlib1g-dev default-jdk \
  && apt-get -y upgrade \
  && apt-get -y clean \
  && rm -rf /tmp/* /var/tmp/*

RUN echo "deb http://storage.googleapis.com/bazel-apt stable jdk1.8" > /etc/apt/sources.list
RUN curl https://storage.googleapis.com/bazel-apt/doc/apt-key.pub.gpg | sudo apt-key add -

RUN add-apt-repository ppa:webupd8team/java \
  && apt-get update \
  && apt-get -y install oracle-java8-installer 

RUN apt-get update && sudo apt-get install bazel \
  && apt-get upgrade bazel \
  && apt-get install python-numpy swig python-dev python-wheel

WORKDIR /usr/src

RUN git clone https://github.com/absalomedia/tensile.git && \
  cd tensile && \
  git submodule update --init --recursive && \
  cd lib/tensorflow/tensorflow && \
  bazel build --genrule_strategy=standalone --spawn_strategy=standalone //tensorflow:libtensorflow.so
