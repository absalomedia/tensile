FROM absalomedia/mini
MAINTAINER Lawrence Meckan <media@absalom.biz>

# Set correct environment variables.
ENV DOCKER_NAME rev_tensile
ENV DEBIAN_FRONTEND noninteractive
ENV HOME /root
ENV DEFAULT_TIMEZONE Australia/Brisbane

# Tensorflow shared object
ENV TF_TYPE=cpu # Set to gpu for GPU support
ENV TF_OS=linux

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
  && apt-get -y install wget curl python-software-properties curl unzip git build-essential clang-3.6 pkg-config zip zlib1g-dev default-jdk python-numpy swig python-dev python-wheel \
  && apt-get -y upgrade \
  && apt-get -y clean \
  && rm -rf /tmp/* /var/tmp/* \
  && apt-get -y install software-properties-common

RUN curl https://get.docker.com/builds/Linux/x86_64/docker-1.9.1 > /usr/bin/docker && chmod +x /usr/bin/docker

WORKDIR /usr/src

RUN curl -L \ "https://storage.googleapis.com/tensorflow/libtensorflow/libtensorflow-${TF_TYPE}-${TF_OS}-x86_64-1.0.0.tar.gz" |sudo tar -C /usr/local -xz

RUN git clone https://github.com/absalomedia/tensile.git && \
  cd tensile && \
  
